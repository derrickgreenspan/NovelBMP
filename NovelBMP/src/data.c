#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

/* implement header based on system */
#ifdef linux 
	#include "BMP.h"
#elif __APPLE__   
        #include "BMP.h"
#elif _WIN32
	#include <windows.h> // includes the BMP header library 
#endif



/* The following function hides data following the NovelBMP implementation that Dr. Leinecker 
 * came up with. */

void hideData(fileData file, char *message)
{
	message[0] = (strlen(message) / 10) + '0';
	message[1] = (strlen(message) % 10) + '0';

	int i;

	unsigned char *dataPointer = &file.data[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];
	for(i = 0; i < strlen(message); i++)
	{       
		int total = countTotal(dataPointer);
	        char deltadirection = 1;

                if(total < GROUPSIZE * HALFWAY)
			deltadirection = -1;

		int j = 0;
		while((char)(total % MODNUMBER != message[i]))
		{
			if(deltadirection > 0)
			{
				if(dataPointer[j%GROUPSIZE] != 255)
				{
					dataPointer[j%GROUPSIZE]++;
					total++;
				}
			}
			else 
			{
				if (dataPointer[j%GROUPSIZE] != 0)
				{
					dataPointer[j%GROUPSIZE]--;
					total--;
				}
			}
			j++;
		}
		dataPointer += GROUPSIZE;
	}
}


/* The following function takes in a fileData input and returns a 
 * signed string of chars representing the hidden message.
 * In theory it should also be possible to use unsigned chars and 
 * hide any type of data
 * Note that the function passes in a fileData struct, and not a 
 * FILE as defined in stdlib. In order to use this function, we 
 * MUST first read in the file 
 */

char * findData(fileData file) 
{
	char size[3]; // we could use a struct for this
	char *dataPointer = &file.data[sizeof(BITMAPFILEHEADER) + 
		sizeof(BITMAPINFOHEADER)];

	int total = countTotal(dataPointer);	

	size[0] = (char)(total % MODNUMBER);
	dataPointer += GROUPSIZE;
	total = countTotal(dataPointer);

	size[1] = (char) (total % MODNUMBER);

	dataPointer += GROUPSIZE;
	size[2] = 0;

	char *retrievedMessage = calloc(sizeof(char), file.fileSize);
	

	int i;

	for(i = 0; i < atoi(size) - 2; i++)	
	{
		total = countTotal(dataPointer);
		dataPointer += GROUPSIZE;
		retrievedMessage[i] = (char)(total % MODNUMBER);
		retrievedMessage[i+1] = 0;
	}

	return retrievedMessage;
}


int countTotal(unsigned char *data)
{
	        int total = 0, i;
		for(i = 0; i < GROUPSIZE; i++)
	                total += (int)data[i];

 		return total;
}

void padString(char *myString, int amount)
{
	memmove(myString + amount, myString, strlen(myString) + 1);
	memset(myString, ' ', amount);
}
