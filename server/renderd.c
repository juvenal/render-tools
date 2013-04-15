/* ------------------------------------------------------
 * Server of Render-Engine machines on a RenderFarm
 * RenderMan RIB RenderServer (c) Copyright 1997
 *
 * Program by: Juvenal A. Silva Jr.       Date: 04/20/97
 * Version:    1.0                        Rev.: A
 * ------------------------------------------------------
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "renderd.h"

/* Main Program */
int main ( void)
{
   void                  *handler;
   int                   ls, len, lns, n, pid, shmid;
   char                  buff[1024], command[4];
   char                  hostname[64];
   struct sockaddr_in    lname;
   struct hostent        *hp;
   struct rendstat       *renderStatus;

   /* Change the disposition of the SIGCLD signal */
   if ( ( handler = signal ( SIGCLD, SIG_IGN)) == SIG_ERR)
   {
      fprintf ( stderr, "Error: 1001 - SIGCLD on Renderd.\n");
      exit ( 1);
   }

   /* Create the pointer to the shared memory */
   shmkey = ftok ( ".", 'S');

   /* Create a shared memory segment id */
   if ( ( shmid=shmget ( shmkey, sizeof ( struct rendstat), IPC_CREAT|0666)) == -1)
   {
      perror ( "Error: 2001 - Renderd");
      exit ( 1);
   }

   /* Attach the shared memory segment */
   if ( ( renderStatus = ( struct rendstat *) shmat ( shmid, 0, 0)) == ( struct rendstat *) -1)
   {
      perror ( "Error: 2002 - Renderd");
      exit ( 1);
   }

   /* Fill in the basic fields of shared memory segment */
   renderStatus->stat          = 0;
   renderStatus->usertime      = 0;
   renderStatus->systime       = 0;
   renderStatus->idletime      = 0;
   renderStatus->usedmemory    = 0;
   renderStatus->freememory    = 0;

   /* Clear the structure before assign */
   memset ( &lname, 0, sizeof ( struct sockaddr_in));

   /* Assign the correct values to the structure */
   n = INADDR_ANY;
   lname.sin_family = AF_INET;
   lname.sin_port = htons ( RS_COMMANDS);
   memcpy ( &lname.sin_addr, &n, sizeof ( long));
   len = sizeof ( struct sockaddr_in);

   /* Create a socket for listening */
   if ( ( ls = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror ( "Error: 3001 - listener");
      exit ( 1);
   }

   /* Bind the socket to the address */
   if ( bind ( ls, ( struct sockaddr *) &lname, len) < 0)
   {
      perror ( "Error: 3002 - listener");
      exit ( 1);
   }

   /* Listen for connections */
   if ( listen ( ls, 5) < 0)
   {
      perror ( "Error: 3003 - listener");
      exit ( 1);
   }

   /* Infinite loop accepting connections */
   while ( TRUE)
   {
      /* Accept a connection */
      if ( ( lns = accept ( ls, ( struct sockaddr *) &lname, &len)) < 0)
      {
         perror ( "Error: 3004 - listener");
         exit ( 1);
      }

      /* Fork a new child process for this incomming connection */
      if ( ( pid = fork ()) < 0)
      {
         perror ( "Error: 1002 for listener");
         exit ( 1);
      }

      /* Listener process code */
      if ( pid == 0)
      {
         /* Process for the incomming connection */
         n = recv ( lns, buff, sizeof ( buff), 0);
         if ( n == 4)         /* Incomming command */
         {
            strcpy ( command, buff);
            if ( strcmp ( command, "PING") == 0)       /* Ping request */
               SendPing ();
            else if ( strcmp ( command, "STAT") == 0)  /* Status request */
               SendStatus ();
            else if ( strcmp ( command, "JOBN") == 0)  /* Job name request */
               SendJobName ();
            else if ( strcmp ( command, "IMGN") == 0)  /* Image name request */
               SendImageName ();
            else if ( strcmp ( command, "REND") == 0)  /* Render % request */
               SendRenderPercent ();
            else if ( strcmp ( command, "CPU%") == 0)  /* CPU load request */
               SendCPULoad ();
            else if ( strcmp ( command, "MEM%") == 0)  /* Mem load request */
               SendMemLoad ();
            else if ( strcmp ( command, "RIBF") == 0)  /* RIB job request */
               SendRIBFile ();
            else if ( strcmp ( command, "RRCF") == 0)  /* Render Resource */
               SendRRCFile ();
            else if ( strcmp ( command, "WRND") == 0)  /* Which Renders */
               SendWRenders ();
            else                                       /* Unknown request */
               SendErrorMsg ();
         }
         else                 /* Any other thing generates an error */
            SendErrorMsg ();
         close ( lns);
         close ( ls);
         exit ( 0);
      }
      /* Renderd father process code */
      close ( lns);
   }
   exit ( 0);
}


int ConnectSocket ( char * operation)
{
   int                  ss, len;
   char                 hostname[64];
   struct sockaddr_in   sname;
   struct hostent       *hp;

   if ( gethostname ( hostname, sizeof ( hostname)) < 0)
   {
      fprintf ( stderr, "Error: 3005 on %s.\n", operation);
      exit ( 1);
   }
   if ( ( hp = gethostbyname ( hostname)) == NULL)
   {
      fprintf ( stderr, "Error: 3006 %s on %s.\n", hostname, operation);
      exit ( 1);
   }

   /* Create the socket for communication */
   if ( ( ss = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
   {
      fprintf ( stderr, "Error: 3001 on %s.\n", operation);
      exit ( 1);
   }

   /* Clear the structures before assign */
   memset ( &sname, 0, sizeof ( struct sockaddr_in));

   /* Assign proper values to the elements in the structure */
   sname.sin_family = AF_INET;
   sname.sin_port   = htons ( RS_COMMANDS);
   memcpy ( &sname.sin_addr, hp->h_addr_list[0], hp->h_length);

   /* Connect to the RenderMan RenderManager */
   len = sizeof ( struct sockaddr_in);
   if ( connect ( ss, ( struct sockaddr *) &sname, len) < 0)
   {
      fprintf ( stderr, "Error: 3007 from %s to RenderManager.\n", operation);
      exit ( 1);
   }
   return ss;
}

/* Functions for answering requests */
void SendPing ( void)
{
   int          ss;
   char         hostname[64];
   char         buff[64];

   /* Connect to the client */
   ss = ConnectSocket ( "Ping");

   /* Get host name */
   if ( gethostname ( hostname, sizeof ( hostname)) < 0)
   {
      perror ( "Error: 3005 - Ping");
      exit ( 1);
   }

   /* Send ping status of machine */
   sprintf ( ( char *) &buff, "%s_is_alive\n", hostname);
   if ( send ( ss, buff, ( strlen ( buff)), 0) < 0)
   {
      perror ( "Error: 3008 - Ping");
      exit ( 1);
   }
   close ( ss);
}

void SendStatus ( void)
{
   int          ss;
   char         rstatus[10];

   /* Connect to the client */
   ss = ConnectSocket ( "Status");

   /* Recall status of machine */
   if ( idle() == 0)
      strcpy ( rstatus, "Idle\n");
   else
      strcpy ( rstatus, "Rendering\n");

   if ( send ( ss, rstatus, ( strlen ( rstatus)), 0) < 0)
   {
      perror ( "Error: 3008 - Status");
      exit ( 1);
   }
   close ( ss);
}

void SendJobName ( void)
{
   int      ss;
   int      size;
   char     buff[64];

   /* Connect to the client */
   ss = ConnectSocket ( "JobName");

   /* Get the Job name */
   size = GetJobName ( ( char *) &buff);

   sprintf ( ( char *) &buff, "%s\n", buff);
   if ( send ( ss, buff, size+1, 0) < 0)
   {
      perror ( "Error: 3008 - JobName");
      exit ( 1);
   }
   close ( ss);
}

void SendImageName ( void)
{
   int      ss;
   int      size;
   char     buff[64];

   /* Connect to the client */
   ss = ConnectSocket ( "ImageName");

   /* Get the Job name */
   size = GetImageName ( ( char *) &buff);

   sprintf ( ( char *) &buff, "%s\n", buff);
   if ( send ( ss, buff, size+1, 0) < 0)
   {
      perror ( "Error: 3008 - ImageName");
      exit ( 1);
   }
   close ( ss);
}

void SendRenderPercent ( void)
{
   int      ss;
   int      rend;
   char     buff[4];

   /* Connect to the client */
   ss = ConnectSocket ( "RenderPercent");

   /* Load Render Percent */
   rend = RenderP();

   sprintf ( ( char *) &buff, "%3d%%\n", rend);
   if ( send ( ss, buff, ( strlen ( buff)), 0) < 0)
   {
      perror ( "Error: 3008 - RenderPercent");
      exit ( 1);
   }
   close ( ss);
}

void SendCPULoad ( void)
{
   int      ss;
   float    cpuload;
   char     buff[4];

   /* Connect to the client */
   ss = ConnectSocket ( "CPU Load");

   /* Calculate CPU load */
   cpuload = 100 * ( usert() / ( usert() + systemt() + idlet()));

   sprintf ( ( char *) &buff, "%3.0f%%\n", cpuload);
   if ( send ( ss, buff, ( strlen ( buff)), 0) < 0)
   {
      perror ( "Error: 3008 - CPU Load");
      exit ( 1);
   }
   close ( ss);
}

void SendMemLoad ()
{
   int      ss;
   float    memory;
   char     buff[4];

   /* Connect to the client */
   ss = ConnectSocket ( "Memory Load");

   /* Calculate the memory usage */
   memory = 100 * ( usedm() / ( freem() + usedm()));

   sprintf ( ( char *) &buff, "%3.0f%%\n", memory);
   if ( send ( ss, buff, ( strlen ( buff)), 0) < 0)
   {
      perror ( "Error: 3008 - Memory Load");
      exit ( 1);
   }
   close ( ss);
}

void SendRIBFile ( void)
{
   
}

void SendRRCFile ( void)
{
}

void SendWRenders ( void)
{
   int      ss, renders;
   char     buff[128], final[128];

   /* Connect to the client */
   ss = ConnectSocket ( "Which Renders");

   /* Get the available renders from renders.host */
   renders = GetRenders ( ( char *) &buff);

   sprintf ( ( char *) &final, "%d\n%s\n", renders, buff);
   if ( send ( ss, final, ( strlen ( final)), 0) < 0)
   {
      perror ( "Error: 3008 - Which Renders");
      exit ( 1);
   }
   close ( ss);
}

void SendErrorMsg ( void)
{
   int      ss;
   char     buff[15];

   /* Connect to the client */
   ss = ConnectSocket ( "Error Message");

   /* Send error message to the requester */
   sprintf ( ( char *) &buff, "Unknow_command\n");
   if ( send ( ss, buff, ( strlen ( buff)), 0) < 0)
   {
      perror ( "Error: 3008 - Error Message");
      exit ( 1);
   }
   close ( ss);
}


/* Auxiliary functions */

int idle ( void)
{
   int              shmid, status;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - idle");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   status = renderStatus->stat;

   shmdt ( ( char *) renderStatus);
   return status;
}

float usert ( void)
{
   int              shmid;
   float            utime;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - usert");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   utime = renderStatus->usertime;

   shmdt ( ( char *) renderStatus);
   return utime;
}

float systemt ( void)
{
   int              shmid;
   float            stime;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - systemt");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   stime = renderStatus->systime;

   shmdt ( ( char *) renderStatus);
   return stime;
}

float idlet ( void)
{
   int              shmid;
   float            itime;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - idlet");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   itime = renderStatus->idletime;

   shmdt ( ( char *) renderStatus);
   return itime;
}

float freem ( void)
{
   int              shmid;
   float            fmemory;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - freem");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   fmemory = renderStatus->freememory;

   shmdt ( ( char *) renderStatus);
   return fmemory;
}

float usedm ( void)
{
   int              shmid;
   float            umemory;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - usedm");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   umemory = renderStatus->usedmemory;

   shmdt ( ( char *) renderStatus);
   return umemory;
}

int GetJobName ( char * string)
{
   int              shmid;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - GetJobName");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   strcpy ( string, renderStatus->JobName);

   shmdt ( ( char *) renderStatus);
   return strlen ( string);
}

int GetImageName ( char * string)
{
   int              shmid;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - GetImageName");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   strcpy ( string, renderStatus->ImageName);

   shmdt ( ( char *) renderStatus);
   return strlen ( string);
}

int RenderP ( void)
{
   int              shmid, render;
   struct rendstat  * renderStatus;

   /* Try to get a shared memory identified by shmkey */
   if ( ( shmid = shmget ( shmkey, sizeof ( struct rendstat), 0)) == -1)
   {
      perror ( "Error: 2002 - RenderP");
      exit ( 1);
   }

   renderStatus = ( struct rendstat *) shmat ( shmid, 0, SHM_RDONLY);
   render = renderStatus->renderpercent;

   shmdt ( ( char *) renderStatus);
   return render;
}

int GetRenders ( char * renders)
{
   sprintf ( renders, "BMRT_2.3.5c Blue_Moon_Rendering_Tools_2.3.5_Rev._C\nPRMan_3.6 Pixar_PhotoRealistic_RenderMan_3.6");
   return 2;
}
