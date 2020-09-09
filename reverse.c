// Programmer:			Zachary William Preston
// Date:			2020 September 3
// Course:			Intro to Operating Systems
// Description:			a program that will enter in the lines of a
//				backwards, then either write to another file, or to the screen

// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMD_ERROR "--> ERROR: Too few arguments ./reverse <inputFile> <outputFile>"
#define SAME_ERROR "--> ERROR: Input file must be different from Output file"
#define MAX_ERROR "--> ERROR: Too many arguments ./reverse <inputFile> <outputFile>"
#define FILE_ERROR "--> ERROR: File couldn't be opened"
#define TEST_INPUT "test.txt"
#define TEST_OUTPUT "output.txt"

// Function Prototypes
void oneArgument(char *);
void twoArguments(char *, char *);
int getNumLines(char *);
int getMaxLineSize(char *);

// Main function, function invocation happens here
// If there is only one argument, CMD error then exit
// If there are two arguments, then one file was entered, so result will print to screen
// If there are three arguments, then one of two things is true
// 	either both files are the same file, and then an error
// 	else the files are different, and the first will be read from
// 		and the second will be written to
// else if there are more than 3 arguments, then MAX error and exit
int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf( "%s\n", CMD_ERROR );
		exit(1);
	} else if (argc == 2) {
		oneArgument(argv[1]);
	} else if (argc == 3) {
		if (strcmp(argv[1], argv[2]) == 0) {
			printf( "%s\n", SAME_ERROR );
			exit(1);
		} else {
			twoArguments(argv[1], argv[2]);
		}
	} else {
		printf( "%s\n", MAX_ERROR );
		exit(1);
	}
	return EXIT_SUCCESS;
}

// If there is one argument, then the input file will be read from
// then printed to the screen backwards
void oneArgument(char *inputFile) {
	int numLines = getNumLines(inputFile);
	int maxLine = getMaxLineSize(inputFile);
	char lineArray[numLines][maxLine + 1];
	FILE *file = fopen(inputFile, "r");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		char *line = NULL;
		size_t lineSize = 0;
		ssize_t length;
		int current = 0;
		length = getline(&line, &lineSize, file);
		strcpy(lineArray[current], line);
		current++;
		while (length >= 0) {
			length = getline(&line, &lineSize, file);
			strcpy(lineArray[current], line);
			current++;
		} fclose(file);
	}
	for (int i = numLines - 1; i >= 0; i--)
		printf( "%s\n", lineArray[i] );
}

// If there are two arguments, then the input file will be read from,
// then the output file will be written to
void twoArguments(char *inputFile, char *outputFile) {
        int numLines = getNumLines(inputFile);
        int maxLine = getMaxLineSize(inputFile);
        char lineArray[numLines][maxLine + 1];
        FILE *file = fopen(inputFile, "r");
        if (file == NULL) {
                printf( "%s\n", FILE_ERROR );
                exit(1);
        } else {
                char *line = NULL;
                size_t lineSize = 0;
                ssize_t length;
                int current = 0;
                length = getline(&line, &lineSize, file);
                strcpy(lineArray[current], line);
                current++;
                while (length >= 0) {
                        length = getline(&line, &lineSize, file);
                        strcpy(lineArray[current], line);
                        current++;
                } fclose(file);
        }
	file = fopen(outputFile, "w");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		for (int i = numLines - 1; i >= 0; i--)
			fprintf(file, "%s", lineArray[i]);
		fclose(file);
	}
}

// Returns an integer that is the number of lines in the file
int getNumLines(char *fileName) {
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		char *line = NULL;
		size_t lineSize = 0;
		ssize_t length;
		int count = 0;
		length = getline(&line, &lineSize, file);
		while (length >= 0) {
			length = getline(&line, &lineSize, file);
			count++;
		} fclose(file);
		return count;
	}
}

// Returns the maximum size of the longest line, to allow for allocation of a long line first
int getMaxLineSize(char *fileName) {
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
                printf( "%s\n", FILE_ERROR );
                exit(1);
        } else {
                char *line = NULL;
                size_t lineSize = 0;
                ssize_t length;
                int max = 0;
                int i = 0;
                length = getline(&line, &lineSize, file);
                while (line[i] != '\0')
                        i++;
                max = i;
                while (length >= 0) {
                        length = getline(&line, &lineSize, file);
                        i = 0;
                        while (line[i] != '\0')
                                i++;
                        if (i > max)
                                max = i;
                } fclose(file);
                return max;
        }
}
