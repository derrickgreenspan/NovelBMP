/***************************************************************
 *				file.c			       * 
 * Contains functions for handling file I/O and identification *
 ***************************************************************/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

fileData readInFile(FILE *ifp)
{
	fileData returnFileData;
	long long fileLength; // fileLength may be extraordinarily long
	fseek(ifp, 0, SEEK_END); // Jump to EOF
	fileLength = ftell(ifp); // Get current byte offset
	rewind(ifp); // return to beginning of file

	unsigned char *buffer= (unsigned char *)malloc((fileLength + 1)
			* sizeof(unsigned char));
	
	fread(buffer, fileLength, 1, ifp);
	returnFileData.data = buffer;	
	returnFileData.fileSize = fileLength;
	fclose(ifp);
	return returnFileData;
}

char verifyFileBMP(fileData fileToVerify) // returns 1 if file is BMP, 0 otherwise
{
	if(fileToVerify.data[0] == 0x42)
		if(fileToVerify.data[1] == 0x4D)
			return 1;
	return 0;
}

void writeNewFile(fileData file, char *fileName) // write file to disk
{
	FILE *ifp = fopen(fileName, "wb");	
	fwrite(file.data, sizeof(unsigned char), file.fileSize, ifp);
	fclose(ifp);
}


