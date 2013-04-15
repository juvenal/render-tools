/* ------------------------------------------------------
 * Manager of Render-Engine machines on a RenderFarm
 * RenderMan RIB RenderManager-2 (c) Copyright 1997
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

#define TRUE 1
#define LPORTNUMBER 1201         /* Port to send commands.  */
#define SPORTNUMBER 1202         /* Port to receive status. */

int main ( void)
{
   char                 buff[1024];
   int                  n, s, ns, len;
   struct sockaddr_in   name;

   /* Clear structure first */
   memset ( &name, 0, sizeof ( struct sockaddr_in));

   /* Assign the proper values to the variables */
   name.sin_family = AF_INET;
   name.sin_port = htons ( SPORTNUMBER);
   len = sizeof ( struct sockaddr_in);
   n = INADDR_ANY;
   memcpy ( &name.sin_addr, &n, sizeof ( long));

   /* Prepare the connection */
   /* Create the socket for the connection */
   if ( ( s = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror ( "socket");
      exit ( 1);
   }

   /* Bind the socket with the address */
   if ( bind ( s, ( struct sockaddr *) &name, len) < 0)
   {
      perror ( "bind");
      exit ( 1);
   }

   /* Open socket for listening */
   if ( listen ( s, 5) < 0)
   {
      perror ( "listen");
      exit ( 1);
   }

   /* Infinnite loop to accept connections */
   while ( TRUE)
   {
      if ( ( ns = accept ( s, ( struct sockaddr *) &name, &len)) < 0)
      {
         perror ( "accept");
         exit ( 1);
      }

      while ( ( n = recv ( ns, buff, sizeof ( buff), 0)) > 0)
         write ( 1, buff, n);
   
      close ( ns);
   }
   close ( s);
   exit ( 0);
}
