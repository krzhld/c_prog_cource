#include "functions.h"

void NeedTypeHelp(int argc, char const* argv) {
    if (argc == 1) 
        Help();
    if ((argc == 2) && (!strcmp(argv, "/?") || !strcmp(argv, "-?"))) 
        Help();
}

void SearchFiles(char* dir, FILEINFO** info) {

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char buffer[MAX_PATH];
    char fullPath[MAX_PATH];
    int maskC, maskCpp, maskH;

    hFind = FindFirstFile(dir, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Invalid file handle. Error is %u\n", GetLastError());
    }
    else {
        if (findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && strcmp(findFileData.cFileName, ".") && strcmp(findFileData.cFileName, "..")) {
            strcpy(buffer, dir);
            size_t i = strlen(buffer) - 1;
            buffer[i] = '\0';
            strcat(buffer, findFileData.cFileName);
            strcat(buffer, "\\*");
            SearchFiles(buffer, info);
        }

        maskC = !strcmp(strrchr(findFileData.cFileName, '\0') - 2, ".c");
        maskCpp = !strcmp(strrchr(findFileData.cFileName, '\0') - 4, ".cpp");
        maskH = !strcmp(strrchr(findFileData.cFileName, '\0') - 2, ".h");

        if (maskC || maskCpp || maskH) {
            strcpy(fullPath, dir);
            fullPath[strlen(fullPath) - 1] = '\0';
            strcat(fullPath, findFileData.cFileName);
            ScanFile(fullPath, info[INTERM]);
            info[INTERM]->bytes = COUNTSIZE;
            if (maskC) {
                ++info[CFILES]->files;
                if (info[INTERM]->lines > info[CFILES]->maxNumberOfLines)
                    info[CFILES]->maxNumberOfLines = info[INTERM]->lines;
            }
            if (maskCpp) {
                ++info[CPPFILES]->files;
                if (info[INTERM]->lines > info[CPPFILES]->maxNumberOfLines)
                    info[CPPFILES]->maxNumberOfLines = info[INTERM]->lines;
            }
            if (maskH) {
                ++info[HFILES]->files;
                if (info[INTERM]->lines > info[HFILES]->maxNumberOfLines)
                    info[HFILES]->maxNumberOfLines = info[INTERM]->lines;
            }
            printf("%s, size: %d, lines: %d, size of comments: %d, in percents: %d, average length of line: %d\n",
                findFileData.cFileName,
                info[INTERM]->bytes,
                info[INTERM]->lines,
                (int)(info[INTERM]->bytes * ((float)info[INTERM]->cChars / (float)info[INTERM]->aChars)),
                (int)(100 * ((float)info[INTERM]->cChars / (float)info[INTERM]->aChars)),
                info[INTERM]->aChars / info[INTERM]->lines);

            info[ALLFILES]->bytes += info[INTERM]->bytes;
            info[ALLFILES]->aChars += info[INTERM]->aChars;
            info[ALLFILES]->cChars += info[INTERM]->cChars;
            info[ALLFILES]->lines += info[INTERM]->lines;
            ClearStruct(info[INTERM]);
        }

        while (FindNextFile(hFind, &findFileData) != 0) {
            if (findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                strcpy(buffer, dir);
                size_t i = strlen(buffer) - 1;
                buffer[i] = '\0';
                strcat(buffer, findFileData.cFileName);
                strcat(buffer, "\\*");
                SearchFiles(buffer, info);
            }

            maskC = !strcmp(strrchr(findFileData.cFileName, '\0') - 2, ".c");
            maskCpp = !strcmp(strrchr(findFileData.cFileName, '\0') - 4, ".cpp");
            maskH = !strcmp(strrchr(findFileData.cFileName, '\0') - 2, ".h");

            if (maskC || maskCpp || maskH) {
                strcpy(fullPath, dir);
                fullPath[strlen(fullPath) - 1] = '\0';
                strcat(fullPath, findFileData.cFileName);
                ScanFile(fullPath, info[INTERM]);
                info[INTERM]->bytes = COUNTSIZE;
                if (maskC) {
                    ++info[CFILES]->files;
                    info[CFILES]->lines += info[INTERM]->lines;
                    if (info[INTERM]->lines > info[CFILES]->maxNumberOfLines)
                        info[CFILES]->maxNumberOfLines = info[INTERM]->lines;
                }
                if (maskCpp) {
                    ++info[CPPFILES]->files;
                    info[CPPFILES]->lines += info[INTERM]->lines;
                    if (info[INTERM]->lines > info[CPPFILES]->maxNumberOfLines)
                        info[CPPFILES]->maxNumberOfLines = info[INTERM]->lines;
                }
                if (maskH) {
                    ++info[HFILES]->files;
                    info[HFILES]->lines += info[INTERM]->lines;
                    if (info[INTERM]->lines > info[HFILES]->maxNumberOfLines)
                        info[HFILES]->maxNumberOfLines = info[INTERM]->lines;
                }
                printf("%s, size: %d, lines: %d, size of comments: %d, in percents: %d, average length of line: %d\n",
                    findFileData.cFileName,
                    info[INTERM]->bytes,
                    info[INTERM]->lines,
                    (int)(info[INTERM]->bytes * ((float)info[INTERM]->cChars / (float)info[INTERM]->aChars)),
                    (int)(100 * ((float)info[INTERM]->cChars / (float)info[INTERM]->aChars)),
                    info[INTERM]->aChars / info[INTERM]->lines);

                info[ALLFILES]->bytes += info[INTERM]->bytes;
                info[ALLFILES]->aChars += info[INTERM]->aChars;
                info[ALLFILES]->cChars += info[INTERM]->cChars;
                info[ALLFILES]->lines += info[INTERM]->lines;
                ClearStruct(info[INTERM]);
            }
        }
        FindClose(hFind);
    }
} 

void ScanFile(char* pathname, FILEINFO* info) {
    size_t lines = 0;
    size_t all = 0;
    size_t comm = 0;

    char temp;

    short int flagStar = 0;
    short int flagComm = 0;

    FILE* fp = fopen(pathname, "r");
    if (fp == NULL)
        system("exit");

    while ((temp = fgetc(fp)) != EOF) {
        if (temp == '\n') 
            ++lines;
        if (temp == '\n' && flagComm == 1) {
            flagComm = 0;
        }
        if (flagComm == 2 || flagComm == 3) {
            ++comm;
        }
        if (temp == '/') {
            switch (flagComm) {
            case 0: {
                flagComm = 1;
                break;
            }
            case 1:
                flagComm = 2;
            }
            if (flagStar == 1)
                flagComm = 0;
        }
        if (temp == '*') {
            flagStar = 1;
            if (flagComm == 1)
                flagComm = 3;
        }
        else
            flagStar = 0;
        ++all;
    }
    ++lines;
    info->aChars = all;
    info->cChars = comm;
    info->lines = lines;
    fclose(fp);
}

void ClearStruct(FILEINFO* info) {
    info->aChars = 0;
    info->cChars = 0;
    info->bytes = 0;
    info->files = 0;
    info->lines = 0;
    info->maxNumberOfLines = 0;
}

void Help() {
    printf("In arguments of programm add path of directory, which you'd like research (don't forget to add \\*)");
    exit(NULL);
}