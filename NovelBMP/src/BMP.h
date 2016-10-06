/**********************************************************************************
 * BITMAPHEADER REIMPLEMENTATIONS                                                 *
 * The following code exists because Linux does not have a standard library       *
 * for dealing with BITMAPS. To make this code portable across Operating Systems, *
 * The headers are reduplicated                                                   *
 * It is important to note that this could should NEVER be called if we're	  *
 * Compiling for Windows. This should only be used on Linux and MacOSX 		  *
 * (And FreeBSD/OpenBSD, I suppose)						  *
 **********************************************************************************/


/* defines */
#define BYTE  unsigned char
#define DWORD unsigned int
#define LONG  int
#define UINT  unsigned int
#define WORD  unsigned short int

#define LPSTR char*


#pragma pack(1) /* Magic - it appears to enforce byte aligment 
                 See also: https://gcc.gnu.org/onlinedocs/gcc-4.8.4/gcc/Structure-Packing-Pragmas.html */
typedef struct tagBITMAPFILEHEADER
{
	        WORD    bfType;
	        DWORD   bfSize;
	        WORD    bfReserved1;
	        WORD    bfReserved2;
	        DWORD   bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

#pragma pack()

#pragma pack(1)
typedef struct tagBITMAPINFOHEADER
{
	        DWORD biSize;
	        LONG  biWidth;
	        LONG  biHeight;
	        WORD  biPlanes;
	        WORD  biBitCount;
	        DWORD biCompression;
	        DWORD biSizeImage;
	        LONG  biXPelsPerMeter;
	        LONG  biYPelsPerMeter;
	        DWORD biClrUsed;
	        DWORD biClrImportant;

} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

#pragma pack()
 
