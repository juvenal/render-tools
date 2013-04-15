/* ------------------------------------------------------
 * Server of Render-Engine machines on a RenderFarm
 * RenderMan RIB RenderServer (c) Copyright 1997
 *
 * Program by: Juvenal A. Silva Jr.       Date: 04/20/97
 * Version:    1.0                        Rev.: A
 * ------------------------------------------------------
 */

/* Function prototypes */
void SendPing(void);
void SendStatus(void);
void SendJobName(void);
void SendImageName(void);
void SendRenderPercent(void);
void SendCPULoad(void);
void SendMemLoad(void);
void SendRIBFile(void);
void SendRRCFile(void);
void SendWRenders(void);
void SendErrorMsg(void);
int ConnectSocket(char *);

/* Auxiliary functions prototypes */
int idle ( void);
float usert ( void);
float systemt ( void);
float idlet ( void);
float usedm ( void);
float freem ( void);
int RenderP ( void);
int GetJobName ( char *);
int GetImageName ( char *);
int GetRenders ( char *);

/* Global data types */
struct rendstat
{
   int        stat;
   float      usertime;
   float      systime;
   float      idletime;
   float      usedmemory;
   float      freememory;
} RENDSTAT;

/* Defines for the entire program */
#define TRUE 1                   /* Constant for program.            */
#define RS_COMMANDS 14201        /* RenderServer port (commands/status)  */
#define RM_COMMANDS 14202        /* RenderManager port (commands/status) */

/* Global variables */
key_t    shmkey;


/* Following this line, all is discarded, only still in the code for
   safety reasons.

struct rendstat
{
   int        stat;
   float      usertime;
   float      systime;
   float      idletime;
   float      usedmemory;
   float      freememory;
   int        renderpercent;
   char       FileName[64];
   char       JobName[64];
   char       ImageName[64];
} RENDSTAT;

** End of discarded lines of code */
