typedef struct tagBITMAPFILEHEADER
{
unsigned short int bfType;
unsigned int bfSize;
unsigned short int bfReserved1;
unsigned short int bfReserved2;
unsigned int bfOffBits;
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
int biSize;
int biWidth;
int biHeight;
short int biPlanes;
short int biBitCount;
int biCompression;
int biSizeImage;
int biXPelsPerMeter;
int biYPelsPerMeter;
int biClrUsed;
int biClrImportant;
}BITMAPINFOHEADER;



