/*
 *
 *
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include "abuffer.h"

int
main ( int argc, char *argv[])
{
  printf ( "Alocando memoria para o A-Buffer...\n");
  InitABuffer ( 200, 200);
  printf ( "Liberando memoria do A-Buffer...\n");
  FreeABuffer ();
  printf ( "Processo completo!\n");
  exit ( 0);
}
