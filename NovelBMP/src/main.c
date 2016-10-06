 /********************************************************
 * Code Inspired By: Dr. Richard Leinecker		*
 * Authors: Derrick Greenspan, Wendelyn Sanabria	*
 * Program Name: NovelBMPDataHiding			*
 * Date: Fall 2016					*
 ********************************************************/

#include <limits.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char * argv[])
{

	if(argc != 4 && argc != 1) // improper number of arguments arguments
	{  	       // prevents segmentation fault 
		if(argc > 4)
			printf("Excessive number of arguments.\n");
		else 
			printf("Insufficent number of arguments");

		printf("This program accepts either no arguments\n");
		printf("or exactly 4 arguments\n");
	        exitProgram();
		return -1; 
	}   

	char ch; // for flushing fgets
	char *input;
	char *messageToStore;
	char *writeInput; 

	if(argc == 4)
	{
		input = calloc(sizeof(char), strlen(argv[1]));
		messageToStore = calloc(sizeof(char),strlen(argv[2]));
		writeInput = calloc(sizeof(char), strlen(argv[3]));
	}


	if(argc == 1) // Prompt for input 
	{
		if(argc == 1) // no arguments specified
		{
			input = calloc(sizeof(char), 255);
			printf("Please enter the file you wish to modify:\n");
			scanf("%s", input);
		}
		while ((ch = getchar()) != '\n' && ch != EOF); // flush old input for fgets
		messageToStore = calloc(sizeof(char), 100000);	// Realistically, the message to store should be much smaller
		printf("Please enter the text you wish to hide:\n");
		fgets(messageToStore, 100000, stdin);
		printf("Please enter the name of the file you wish to write to:\n");
		writeInput = calloc(sizeof(char), 255);
		scanf("%s", writeInput);
	}
	else
	{
		strcpy(input, argv[1]);
		strcpy(writeInput, argv[3]);
		strcpy(messageToStore, argv[2]); // otherwise it overruns the buffer
	}

	padString(messageToStore, 2);


	/* Verify File Exists */
	FILE *ifp;
	ifp = fopen(input, "rb");
	if(!ifp) // cannot open file
	{
		printf("Cannot open file %s for reading.\n", input);
		printf("No Such file or directory\n");
		exitProgram();
		return -1;
	}


	fileData inputFile = readInFile(ifp); 
	if(!verifyFileBMP(inputFile)) // verify that this is actually a BMP file
	{
		printf("The specified file %s does not appear to be a valid BMP file\n", input);
		printf("Please verify that this file is a valid BMP file\n");
		exitProgram();
		return -1;
	}
		
	printf("Storing message %s\n", messageToStore);

	hideData(inputFile, messageToStore); // now hide the data

	writeNewFile(inputFile, writeInput);

	

	/* Just to test, fopen the file again */
	ifp = fopen(writeInput, "rb");
	inputFile = readInFile(ifp);

	printf("FOUND DATA: %s\n", findData(inputFile)); // check to see if we found a string
	
	


	//printf("%s", findData(inputFile));



	// prompt user to exit (done so that it does not close immediately after entering all data)

	exitProgram();

}

void exitProgram(void)
{
/*	if(!prompt) // the user entered arguments
	       return;	
	       */

	#ifdef _WIN32
		system("pause");
		printf("\n");
        #elif linux
		system("read -n 1 -s -p \"Press any key to continue . . .\n\"");
        #elif __APPLE__
                system("read -n 1 -s -p \"Press any key to continue . . .\n\"");
	#endif

	exit(0);
}
