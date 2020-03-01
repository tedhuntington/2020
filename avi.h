
//#if 0 
typedef struct {
    unsigned long dwMicroSecPerFrame;
    unsigned long dwMaxBytesPerSec;
    unsigned long dwPaddingGranularity;//dwReserved1;
    unsigned long dwFlags;
    unsigned long dwTotalFrames;
    unsigned long dwInitialFrames;
		unsigned long noidea;  //tph
    unsigned long dwStreams;
    unsigned long dwSuggestedBufferSize;
    unsigned long dwWidth;
    unsigned long dwHeight;
    unsigned long dwScale;
    unsigned long dwRate;
    unsigned long dwStart;
    unsigned long dwLength;
	//	unsigned long dwReserved2;  //tph
} MainAVIHeader;
//#endif

#define AVIF_HASINDEX		0x00000010
#define AVIF_MUSTUSEINDEX	0x00000020
#define AVIF_ISINTERLEAVED	0x00000100
#define AVIF_WASCAPTUREFILE	0x00010000
#define AVIF_COPYRIGHTED	0x00020000

#define AVIF_KNOWN_FLAGS	0x00030130

#define Defined_MainAVIHeader_Size      (14*4)

//#if 0 
typedef struct {
    unsigned long fccType;
    unsigned long fccHandler;
    unsigned long dwFlags;
    unsigned long dwReserved1;
    unsigned long dwInitialFrames;
    unsigned long dwScale;
    unsigned long dwRate;
    unsigned long dwStart;
    unsigned long dwLength;
    unsigned long dwSuggestedBufferSize;
    unsigned long dwQuality;
    unsigned long dwSampleSize;
    //RECT		rcFrame;
    //unsigned long dwReserved2;
		unsigned short int sx;
	  unsigned short int sy;
		unsigned short int ex;
	  unsigned short int ey;
    //unsigned long dwReserved3;
} AVIStreamHeader;
//#endif

#define AVISF_DISABLED		0x00000001
#define AVISF_VIDEO_PALCHANGES	0x00010000

#define AVISF_KNOWN_FLAGS	0x00010001

#define Defined_AVIStreamHeader_Size_old  (12*4)
#define Defined_AVIStreamHeader_Size      (14*4)

typedef struct {
    unsigned char bFirstEntry;
    unsigned char bNumEntries;
    unsigned short wFlags;
} AVIPALCHANGE;

typedef struct {
    unsigned long ckid;
    unsigned long dwFlags;
    unsigned long dwChunkOffset;
    unsigned long dwChunkLength;
} AVIINDEXENTRY;

#define AVIIF_LIST	0x00000001
#define AVIIF_KEYFRAME	0x00000010
#define AVIIF_FIRSTPART	0x00000020
#define AVIIF_LASTPART	0x00000040
#define AVIIF_MIDPART	(AVIIF_LASTPART | AVIFF_FIRSTPART)
#define AVIIF_NOTIME	0x00000100
#define AVIIF_COMPUSE	0x0fff0000

#define AVIIF_KNOWN_FLAGS 0x0fff0171

#define Defined_AVIINDEXENTRY_Size	(4*4)

