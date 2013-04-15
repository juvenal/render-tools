#ifndef _SHADER_H_
#define _SHADER_H_

/* Define GUI function prototypes */
void CreateInterface ( Widget);
void SetUpShell ( Widget);

/* Define callback function prototypes */
void fileCallback ( Widget, XtPointer, XtPointer);
void editCallback ( Widget, XtPointer, XtPointer);
void optionsCallback ( Widget, XtPointer, XtPointer);
void windowsCallback ( Widget, XtPointer, XtPointer);
void helpCallback ( Widget, XtPointer, XtPointer);

/* Application's icon file */
#include "shader.xpm"

#endif
