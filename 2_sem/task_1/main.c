#include "functions.h"

int main(int argc, char* argv[]) {
    FILEINFO** information = (FILEINFO**)calloc(5, sizeof(FILEINFO*));
    for (int i = 0; i < 5; ++i)
        information[i] = (FILEINFO*)calloc(1, sizeof(FILEINFO));
    NeedTypeHelp(argc, argv[1]);
    int nArg = 1;
    while (argv[nArg] != NULL) {
        SearchFiles(argv[nArg], information);
        printf("\n");
        ++nArg;
    }
    printf("All Files: \n");
    printf("Total size: %d\n", information[ALLFILES]->bytes);
    printf("Total size of comments: %d in bytes, %d in percents",
        (int)(information[ALLFILES]->bytes*((float)information[ALLFILES]->cChars / (float)information[ALLFILES]->aChars)),
        (int)(100*((float)information[ALLFILES]->cChars / (float)information[ALLFILES]->aChars)));
    printf("\nTotal lines: %d", information[ALLFILES]->lines);
    printf("\n\n");

    printf("C Files: \n");
    printf("Max number of lines: %d\n", information[CFILES]->maxNumberOfLines);
    printf("Average number of lines: %d",
        information[CFILES]->lines / information[CFILES]->files);
    printf("\n\n");

    printf("Cpp Files: \n");
    printf("Max number of lines: %d\n", information[CPPFILES]->maxNumberOfLines);
    printf("Average number of lines: %d",
        information[CPPFILES]->lines / information[CPPFILES]->files);

    printf("\n\n");
    printf("H Files: \n");
    printf("Max number of lines: %d\n", information[HFILES]->maxNumberOfLines);
    printf("Average number of lines: %d",
        information[HFILES]->lines / information[HFILES]->files);

    printf("\n");

    for (int i = 0; i < 5; ++i)
        free(information[i]);
    free(information);
    return 0;
}