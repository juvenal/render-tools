/* ------------------------------------------------------
 * Manager of Render-Engine machines on a RenderFarm
 * RenderMan RIB RenderManager-1 (c) Copyright 1997
 *
 * Program by: Juvenal A. Silva Jr.       Date: 04/21/97
 * Version:    1.0                        Rev.: A
 * ------------------------------------------------------
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

#define LPORTNUMBER 1201         /* Port to send commands.  */
#define SPORTNUMBER 1202         /* Port to receive status. */

int main ( void)
{
   int                 n, n2, s, s2, ns2, len;
   char                command[10];
   char                hostname[64];
   char                buff[1024];
   struct hostent      *hp;
   struct sockaddr_in  name, name2;

   /* Clear the variables */
   strcpy ( command, " ");
   memset ( &name, 0, sizeof ( struct sockaddr_in));
   memset ( &name2, 0, sizeof ( struct sockaddr_in)); 

   /* Assign the proper values to the variables */
   if ( gethostname ( hostname, sizeof ( hostname)) < 0)
   {
      perror ( "Error: 3005 in RenderManager");
      exit ( 1);
   }
   if ( ( hp = gethostbyname ( hostname)) == NULL)
   {
      fprintf ( stderr, "Error: 3006 %s on RenderManager.\n", hostname);
      exit ( 1);
   }
   name.sin_family = AF_INET;
   name.sin_port   = htons ( LPORTNUMBER);
   memcpy ( &name.sin_addr, hp->h_addr_list[0], hp->h_length);
   len = sizeof ( struct sockaddr_in);

   /* Assign values for answer variables */
   name2.sin_family = AF_INET;
   name2.sin_port = htons ( SPORTNUMBER);
   n2 = INADDR_ANY;
   memcpy ( &name2.sin_addr, &n2, sizeof ( long));

   /* Create the socket for the answer connection */
   if ( ( s2 = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror ( "Error: 3001 on answer in RenderManager.");
      exit ( 1);
   }

   /* Bind the socket for answers with the address */
   if ( bind ( s2, ( struct sockaddr *) &name2, len) < 0)
   {
      perror ( "Error: 3002 on answer in RenderManager.");
      exit ( 1);
   }

   /* Open socket for listening answers */
   if ( listen ( s2, 5) < 0)
   {
      perror ( "Error: 3003 on answer in RenderManager.");
      exit ( 1);
   }

   /* Loop asking for commands while command not empty */
   while ( strcmp ( command, "") != 0)
   {
      /* Clear the buff variable */
      memset ( &buff, 0, sizeof ( buff));

      printf ( "Enter a command: ");
      gets ( command);
      if ( strcmp ( command, "") != 0)
      {
         /* Prepare for the connection */
         /* Create a socket for the connection */
         if ( ( s = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
         {
            perror ( "Error: 3001 on RenderManager.");
            exit ( 1);
         }

         /* Open the connection to the renderd */
         if ( connect ( s, ( struct sockaddr *) &name, len) < 0)
         {
            perror ( "Error: 3007 on RenderManager.");
            exit ( 1);
         }

         /* Send the command to the renderd */
         if ( send ( s, command, strlen ( command), 0) < 0)
         {
            perror ( "Error: 3008 on RenderManager.");
            exit ( 1);
         }

         /* Prepare for the answer */
         if ( strcmp ( command, "PING") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (PING) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "STAT") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (STAT) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "JOBN") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (JOBN) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "IMGN") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (IMGN) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "REND") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (REND) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "CPU%") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (CPU%) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "MEM%") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (MEM%) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else if ( strcmp ( command, "RIBF") == 0)
         {
         }
         else if ( strcmp ( command, "RRCF") == 0)
         {
         }
         else if ( strcmp ( command, "WRND") == 0)
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (WRND) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }
         else
         {
            if ( ( ns2 = accept ( s2, ( struct sockaddr *) &name2, &len)) < 0)
            {
               perror ( "Error: 3004 on answer (WRND) on RenderManager.");
               exit ( 1);
            }
            while ( ( n2 = recv ( ns2, buff, sizeof ( buff), 0)) > 0)
               printf ( "renderd returned: %s", buff);
            close ( ns2);
         }

         /* Close connection */
         close ( s);
      }
   }
   close ( s2);
   exit ( 0);
}
