/* -------------------------------------------------------------
 * Daemon for monitoring of the Machine Load Processing
 * Status feeder process
 *
 * Program by: Juvenal A. Silva Jr.            Date: 05/23/97
 * Version:    1.0                             Rev.: A
 * -------------------------------------------------------------
 */

#include <linux/kernel.h>
#include <linux/sys.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include "renderd.h"

main ( void)
{
   unsigned int    usrtime1=0, nictime1=0, systime1=0, idltime1=0;
   unsigned int    usrtime2=0, nictime2=0, systime2=0, idltime2=0;
   unsigned int    usrtimef=0, nictimef=0, systimef=0, idltimef=0;
   FILE            * fp;
   char            id[4], buffer[65];
   int             size, shmid;
   struct rendstat * Status;
   struct sysinfo  * info;

   /* Create the pointer to the shared memory */
   shmkey = ftok ( ".", 'S');

   /* Connect to the shared memory */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), IPC_CREAT|0666)) == -1)
   {
      perror ( "Error: 2001 - Status");
      exit ( 1);
   }

   /* Assign a pointer to the shared memory */
   if ( ( Status = ( struct rendstat *) shmat ( shmid, 0, 0)) == ( struct rendstat *) -1)
   {
      perror ( "Error: 2002 - Status");
      exit ( 1);
   }

   /* Open the file to gather information */
   if ( ( fp = fopen ( "/proc/stat", "r")) == (FILE *) NULL)
   {
      perror ( "Error: 4001 - stat on Status");
      exit ( 1);
   }

   /* Load the required information into a buffer */
   if ( ( size = fscanf ( fp, "%s %u %u %u %u", &id, &usrtime1, &nictime1, &systime1, &idltime1)) < 5)
   {
      perror ( "Error: 4002 - stat on Status");
      exit ( 1);
   }

   /* Close the opened file */
   if ( fclose ( fp) == EOF)
   {
      perror ( "Error: 4004 - stat on Status");
      exit ( 1);
   }

   while ( TRUE)
   {
      usrtime2 = usrtime1;
      nictime2 = nictime1;
      systime2 = systime1;
      idltime2 = idltime1;

      /* Wait for a second before gather new information */
      sleep ( 1);

      /* Open the file to gather information */
      if ( ( fp = fopen ( "/proc/stat", "r")) == (FILE *) NULL)
      {
         perror ( "Error: 4001 - stat on Status (loop)");
         exit ( 1);
      }

      /* Load the second pass required information into a buffer */
      if ( ( size = fscanf ( fp, "%s %u %u %u %u", &id, &usrtime1, &nictime1, &systime1, &idltime1)) < 5)
      {
         perror ( "Error: 4002 - stat on Status (loop)");
         exit ( 1);
      }

      /* Close the opened file */
      if ( fclose ( fp) == EOF)
      {
         perror ( "Error: 4004 - stat on Status (loop)");
         exit ( 1);
      }

      /* Get the memory information of the machine */
      if ( sysinfo ( info) < 0)
      {
         perror ( "Error: 1003 - Status (loop)");
         exit ( 1);
      }
 
      /* Fill in the shared memory structure */
      Status->usertime      = (usrtime1 + nictime1) - (usrtime2 + nictime2);
      Status->systime       = systime1 - systime2;
      Status->idletime      = idltime1 - idltime2;
      Status->usedmemory    = info->totalram - info->freeram;
      Status->freememory    = info->freeram;
   }
   exit ( 0);
}
