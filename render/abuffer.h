/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#ifndef ABUFFER_H  /* abuffer.h */
#define ABUFFER_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Pixel Mask */
typedef char PixelMsk [4];

/* Fragment definition */
typedef struct tagFragment
{
    char                r, g, b;
    char                Opacity;
    char                Area;
    int                 ObjectTag;
    PixelMsk            Mask;
    float               zMax, zMin;
    struct tagFragment *Next;
} FRAGMENT;

/* Pixelstruct definition */
typedef struct tagPCOMPLEXZ
{
    float         z;        /* Negative Z for complex pixels */
    FRAGMENT     *Flist;
} PCOMPLEXZ;

typedef struct tagPSIMPLEZ
{
    float         z;        /* Positive Z for simple pixels */
    char          r, g, b, a;
} PSIMPLEZ;

typedef union tagPIXELSTRUCT
{
    PCOMPLEXZ    ComplexPixel;
    PSIMPLEZ     SimplePixel;
} PIXELSTRUCT;

/* Virtual A-Buffer */
typedef struct tagA_BUFFER
{
    int                  XPos;
    int                  YPos;
    PIXELSTRUCT         *PixelColor;
    struct tagA_BUFFER  *Next;
} A_BUFFER;

/* Function Prototypes */
void InitABuffer ( int, int);
void FreeABuffer ( void);
void ErrDisplay ( char *);

/* Global variables for A-Buffer */
A_BUFFER    *aBuffer;
int          ABufferX, ABufferY;

#ifdef __cplusplus
}
#endif
#endif  /* abuffer.h */
