#include "CacheLineSize.h"

#if defined(__APPLE__)

#include <sys/sysctl.h>
size_t CacheLineSize() {
	size_t lineSize = 0;
	size_t sizeOfLineSize = sizeof(lineSize);
	sysctlbyname("hw.cachelinesize", &lineSize, &sizeOfLineSize, 0, 0);
	return lineSize;
}

#elif defined(_WIN32)

#include <stdlib.h>
#include <windows.h>
size_t CacheLineSize() {
	size_t lineSize = 0;
	DWORD bufferSize = 0;
	DWORD i = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

	GetLogicalProcessorInformation(0, &bufferSize);
	buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *) malloc(bufferSize);
	GetLogicalProcessorInformation(&buffer[0], &bufferSize);

	for (i = 0; i != bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
			lineSize = buffer[i].Cache.LineSize;
			break;
		}
	}

	free(buffer);
	return lineSize;
}

#elif defined(linux)

#include <stdio.h>
size_t CacheLineSize() {
	FILE * p = 0;
	p = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
	unsigned int lineSize = 0;
	if (p) {
		fscanf(p, "%d", &lineSize);
		fclose(p);
	}
	return lineSize;
}

#else
#error Unrecognized platform
#endif