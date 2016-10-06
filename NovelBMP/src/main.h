
/* defines */
#define GROUPSIZE 12
#define MODNUMBER 127
#define HALFWAY 128

typedef struct fileData // file data struct
{
	unsigned char *data; // the raw, unsigned, file data in 8 bit octets
	long long fileSize; // the size of the file, represented as long long so as to support huge files
} fileData;

fileData readInFile(FILE *myFile); // reads the file in, returning a filedata struct

char verifyFileBMP(fileData fileToVerify); // verify that the file is an (actual) BMP file 

void exitProgram(void); // program exit handling. Forces the program to remain on screen
			// even if the user has not launched it from a shell

int countTotal(unsigned char * data);

void hideData(fileData file, char *message);	// hides a message into the BMP file 
						// (Note, it should be possible to hide an actual file as well)

char *findData(fileData file);			// retrieves the message (if there even is one) from the file
						// Note that the argument it accepts is fileData, not a stdlib.h file

void writeNewFile(fileData file, char *fileName); // writes filename to disk

void padString(char *myInput, int amount); // pads the string by the specified amount (generally 2 for this program), modifying it in place
