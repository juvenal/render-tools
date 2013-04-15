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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "abuffer.h"
#define TRUE 1

/* Main function to create an A-Buffer */
void
InitABuffer ( int SizeX, int SizeY)
{
  /* Local variables */
  A_BUFFER  *aBufferAtu = NULL, *aBufferLast = NULL;
  int        x, y;

  ABufferX = SizeX;
  ABufferY = SizeY;

  for ( y = 1; y <= SizeY; y++) {
    for ( x = 1; x <= SizeX; x++) {
      if ( aBuffer == NULL) {
        if ( ( aBuffer = ( A_BUFFER *) malloc ( sizeof ( A_BUFFER))) == NULL) {
          ErrDisplay ( "Memoria insuficiente!");
          FreeABuffer ();
        }
        aBuffer->XPos = x;
        aBuffer->YPos = y;
        if ( ( aBuffer->PixelColor = ( PIXELSTRUCT *) malloc ( sizeof ( PIXELSTRUCT))) == NULL) {
          ErrDisplay ( "Memoria insuficiente!");
          FreeABuffer ();
        }
        aBuffer->PixelColor->SimplePixel.z = 1.0;
        aBuffer->PixelColor->SimplePixel.r = 0;
        aBuffer->PixelColor->SimplePixel.g = 0;
        aBuffer->PixelColor->SimplePixel.b = 0;
        aBuffer->PixelColor->SimplePixel.a = 0;
        aBuffer->Next = NULL;
        aBufferLast = aBuffer;
      }
      else {
        if ( ( aBufferAtu = ( A_BUFFER *) malloc ( sizeof ( A_BUFFER))) == NULL) {
          ErrDisplay ( "Memoria insuficiente!");
          FreeABuffer ();
        }
        aBufferAtu->XPos = x;
        aBufferAtu->YPos = y;
        if ( ( aBufferAtu->PixelColor = ( PIXELSTRUCT *) malloc ( sizeof ( PIXELSTRUCT))) == NULL) {
          ErrDisplay ( "Memoria insuficiente!");
          FreeABuffer ();
        }
        aBufferAtu->PixelColor->SimplePixel.z = 1.0;
        aBufferAtu->PixelColor->SimplePixel.r = 0;
        aBufferAtu->PixelColor->SimplePixel.g = 0;
        aBufferAtu->PixelColor->SimplePixel.b = 0;
	aBufferAtu->PixelColor->SimplePixel.a = 0;
        aBufferAtu->Next = NULL;
	aBufferLast->Next = aBufferAtu;
	aBufferLast = aBufferAtu;
      }
    }
  }
}

/* Main function to destroy an A-Buffer */
void
FreeABuffer ( void)
{
  /* Local variables */
  A_BUFFER      *aBufferPointer = NULL, *aBufferHold = NULL;
  FRAGMENT      *FragmentPointer = NULL, *FragmentHold = NULL;

  aBufferPointer = aBuffer;
  while ( TRUE) {
    if ( aBufferPointer->PixelColor->ComplexPixel.z < 0) {
      FragmentPointer = aBufferPointer->PixelColor->ComplexPixel.Flist;
      while ( TRUE) {
        FragmentHold = aBufferPointer->PixelColor->ComplexPixel.Flist->Next;
        free ( FragmentPointer);
        if ( FragmentHold == NULL)
          break;
        FragmentPointer = FragmentHold;
      }
    }
    aBufferHold = aBufferPointer->Next;
    free ( aBufferPointer->PixelColor);
    free ( aBufferPointer);
    if ( aBufferHold == NULL)
      break;
    aBufferPointer = aBufferHold;
  }
}

/* Function to display error messages */
void
ErrDisplay ( char *Message)
{
  printf ( "Erro: %s.\n", Message);
}
