#pragma once
#pragma warning(disable: 4996)

#include <stdio.h>
#include <windows.h>

typedef struct {
	size_t bytes;
	size_t lines;
	size_t aChars;
	size_t cChars;
	size_t maxNumberOfLines;
	size_t files;
} FILEINFO;

typedef enum {
	INTERM = 0,
	CFILES,
	CPPFILES,
	HFILES,
	ALLFILES
} numfile_t;

#define LENGTH 2048

#define COUNTSIZE ((findFileData.nFileSizeHigh * (MAXDWORD + 1)) + findFileData.nFileSizeLow)

void NeedTypeHelp(int argc, char const* argv);

void ScanFile(char* dir, FILEINFO* info);

void SearchFiles(char* pathname, FILEINFO** info);

void ClearStruct(FILEINFO* info);

void Help();