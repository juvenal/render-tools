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
   int                 n, s, len;
   char                command[10];
   char                hostname[64];
   struct hostent      *hp;
   struct sockaddr_in  name;

   /* Clear the variables */
   strcpy ( command, " ");
   memset ( &name, 0, sizeof ( struct sockaddr_in));

   /* Assign the proper values to the variables */
   if ( gethostname ( hostname, sizeof ( hostname)) < 0)
   {
      perror ( "gethostname");
      exit ( 1);
   }
   if ( ( hp = gethostbyname ( hostname)) == NULL)
   {
      fprintf ( stderr, "unknown host: %s.\n", hostname);
      exit ( 1);
   }
   name.sin_family = AF_INET;
   name.sin_port   = htons ( LPORTNUMBER);
   memcpy ( &name.sin_addr, hp->h_addr_list[0], hp->h_length);
   len = sizeof ( struct sockaddr_in);

   /* Loop asking for commands while command not empty */
   while ( strcmp ( command, "") != 0)
   {
      printf ( "Enter a command: ");
      gets ( command);
      if ( strcmp ( command, "") != 0)
      {
         /* Prepare for the connection */
         /* Create a socket for the connection */
         if ( ( s = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
         {
            perror ( "ask socket failed");
            exit ( 1);
         }

         /* Open the connection to the renderd */
         if ( connect ( s, ( struct sockaddr *) &name, len) < 0)
         {
            perror ( "ask connect failed");
            exit ( 1);
         }

         /* Send the command to the renderd */
         if ( send ( s, command, strlen ( command), 0) < 0)
         {
            perror ( "ask send failed");
            exit ( 1);
         }

         /* Close connection */
         close ( s);
      }
   }
   exit ( 0);
}
