#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/MwmUtil.h>
#include <Xm/RowColumn.h>
#include <X11/xpm.h>
#include "shader.h"
#include "Tab.h"


/* =======================================================================
 * Main program
 */
int
main ( argc, argv)
int argc;
char *argv[];
{
   XtAppContext app;
   Widget       toplevel;
   String fallbacks[] = {
          "Shader.width:                  512",
          "Shader.height:                 384",
          NULL };

   /* Create and set the application main context */
   toplevel = XtVaOpenApplication ( &app, "Shader", NULL, 0, &argc, argv, 
                                    fallbacks, applicationShellWidgetClass,
                                    XmNtitle, "Shader Network Editor",
                                    XmNiconName, "Shader Net",
                                    NULL);

   /* Setup other properties of the main window */
   SetUpShell ( toplevel);

   /* Create the main window interface for the application */
   CreateInterface ( toplevel);

   /* Display the application widgets */
   XtRealizeWidget ( toplevel);

   /* Put the application on event loop */
   XtAppMainLoop ( app);
}



/* ========================================================================
 * Set up the interface for the main Shell Window
 */
void
SetUpShell ( parent)
Widget parent;
{
   Display       *display;
   Pixmap         PixIcon, PixMask;
   XpmAttributes  Attrib;

   /* Get the window icon  */
   Attrib.valuemask = 0;
   display = XtDisplay ( parent);
   XpmCreatePixmapFromData ( display, RootWindow ( display, 0),
                             shader, &PixIcon, &PixMask, &Attrib);

   /* Adjust some of the Main Window Values */
   XtVaSetValues ( parent,
                   XmNiconPixmap, PixIcon,
                   XmNiconMask, PixMask,
                   NULL);
}



/* =======================================================================
 * Create Interface elements for the main window and assign callbacks
 */
void
CreateInterface ( parent)
Widget parent;
{
   Widget       shaderwindow, menubar, toolbar, message, tabpad, initab;
   XmString     file, new, open, database, shader, look, revert, save, saveas,
                close, pagesetup, print, compile, quit,
                edit, undo, redo, cut, copy, paste, clear, delete, find,
                replace,
                options, external, prefs,
                windows, tile, cascade,
                help, about, howto,
                acc01, acc02, acc03, acc04, acc05, acc06, acc07, acc08,
                acc09, acc10, acc11, acc12,
                strtmp;
   int          parm01, parm02;

   /* Define the compounf strings needed */
   file         = XmStringCreateSimple ( "File");
     new        = XmStringCreateSimple ( "New");
     open       = XmStringCreateSimple ( "Open...");
       database = XmStringCreateSimple ( "Database");
       shader   = XmStringCreateSimple ( "Shader");
       look     = XmStringCreateSimple ( "Shader Net");
     compile    = XmStringCreateSimple ( "Compile");
        acc01   = XmStringCreateSimple ( "Ctrl+C");
     revert     = XmStringCreateSimple ( "Revert");
        acc02   = XmStringCreateSimple ( "Ctrl+R");
     save       = XmStringCreateSimple ( "Save");
        acc03   = XmStringCreateSimple ( "Ctrl+S");
     saveas     = XmStringCreateSimple ( "Save As...");
     close      = XmStringCreateSimple ( "Close");
        acc04   = XmStringCreateSimple ( "Ctrl+l");
     pagesetup  = XmStringCreateSimple ( "Page Setup...");
     print      = XmStringCreateSimple ( "Print...");
     quit       = XmStringCreateSimple ( "Quit");
        acc05   = XmStringCreateSimple ( "Ctrl+Q");
   edit         = XmStringCreateSimple ( "Edit");
     undo       = XmStringCreateSimple ( "Undo");
        acc06   = XmStringCreateSimple ( "Ctrl+Z");
     redo       = XmStringCreateSimple ( "Redo");
     cut        = XmStringCreateSimple ( "Cut");
        acc07   = XmStringCreateSimple ( "Ctrl+X");
     copy       = XmStringCreateSimple ( "Copy");
        acc08   = XmStringCreateSimple ( "Ctrl+C");
     paste      = XmStringCreateSimple ( "Paste");
        acc09   = XmStringCreateSimple ( "Ctrl+V");
     clear      = XmStringCreateSimple ( "Clear");
        acc10   = XmStringCreateSimple ( "Backspace");
     delete     = XmStringCreateSimple ( "Delete");
     find       = XmStringCreateSimple ( "Find...");
        acc11   = XmStringCreateSimple ( "Ctrl+F");
     replace    = XmStringCreateSimple ( "Replace...");
        acc12   = XmStringCreateSimple ( "Ctrl+A");
   options      = XmStringCreateSimple ( "Options");
     external   = XmStringCreateSimple ( "External Programs...");
     prefs      = XmStringCreateSimple ( "Preferences...");
   windows      = XmStringCreateSimple ( "Windows");
     tile       = XmStringCreateSimple ( "Tile");
     cascade    = XmStringCreateSimple ( "Cascade");
   help         = XmStringCreateSimple ( "Help");
     about      = XmStringCreateSimple ( "About");
     howto      = XmStringCreateSimple ( "How to...");

   /* Create basic window widget */
   shaderwindow = XtVaCreateManagedWidget ( "shaderMain",
                                          xmMainWindowWidgetClass, parent,
                                          NULL);

   /* Create the window menu bar */
   menubar = XmVaCreateSimpleMenuBar ( shaderwindow, "shaderMenu",
                                       XmVaCASCADEBUTTON, file,    'F',
                                       XmVaCASCADEBUTTON, edit,    'E',
                                       XmVaCASCADEBUTTON, options, 'O',
                                       XmVaCASCADEBUTTON, windows, 'W',
                                       XmVaCASCADEBUTTON, help,    'H',
                                       NULL);

   /* Create the pulldown menu items */
   XmVaCreateSimplePulldownMenu ( menubar, "file", 0, 
                      ( XtCallbackProc) fileCallback,
                      XmVaCASCADEBUTTON, new,       'N',
                      XmVaCASCADEBUTTON, open,      'O',
                      XmVaSEPARATOR,
                      XmVaPUSHBUTTON,    compile,   'C', "Ctrl<Key>c", acc01,
                      XmVaPUSHBUTTON,    revert,    'R', "Ctrl<Key>r", acc02,
                      XmVaPUSHBUTTON,    save,      'S', "Ctrl<Key>s", acc03,
                      XmVaPUSHBUTTON,    saveas,    'A', NULL, NULL,
                      XmVaPUSHBUTTON,    close,     'l', "Ctrl<Key>l", acc04,
                      XmVaSEPARATOR,
                      XmVaPUSHBUTTON,    pagesetup, 'g', NULL, NULL,
                      XmVaPUSHBUTTON,    print,     'P', NULL, NULL,
                      XmVaSEPARATOR,
                      XmVaPUSHBUTTON,    quit,      'Q', "Ctrl<Key>q", acc05,
                      NULL);
   XmVaCreateSimplePulldownMenu ( menubar, "edit", 1,
                      ( XtCallbackProc) editCallback,
                      XmVaPUSHBUTTON,    undo,      'U', "Ctrl<Key>z", acc06,
                      XmVaPUSHBUTTON,    redo,      'R', NULL, NULL,
                      XmVaSEPARATOR,
                      XmVaPUSHBUTTON,    cut,       'C', "Ctrl<Key>x", acc07,
                      XmVaPUSHBUTTON,    copy,      'o', "Ctrl<Key>c", acc08,
                      XmVaPUSHBUTTON,    paste,     'P', "Ctrl<Key>v", acc09,
                      XmVaPUSHBUTTON,    clear,     'r', "Ctrl<Key>h", acc10,
                      XmVaPUSHBUTTON,    delete,    'D', "Ctrl<Key>d", delete,
                      XmVaSEPARATOR,
                      XmVaPUSHBUTTON,    find,      'F', "Ctrl<Key>f", acc11,
                      XmVaPUSHBUTTON,    replace,   'e', "Ctrl<Key>a", acc12,
                      NULL);
   XmVaCreateSimplePulldownMenu ( menubar, "options", 2,
                      ( XtCallbackProc) optionsCallback,
                      XmVaPUSHBUTTON,    external,  'E', NULL, NULL,
                      XmVaPUSHBUTTON,    prefs,     'P', NULL, NULL,
                      NULL);
   XmVaCreateSimplePulldownMenu ( menubar, "windows", 3,
                      ( XtCallbackProc) windowsCallback,
                      XmVaPUSHBUTTON,    tile,      'T', NULL, NULL,
                      XmVaPUSHBUTTON,    cascade,   'C', NULL, NULL,
                      NULL);
   XmVaCreateSimplePulldownMenu ( menubar, "help", 4,
                      ( XtCallbackProc) helpCallback,
                      XmVaPUSHBUTTON,    about,     'A', NULL, NULL,
                      XmVaPUSHBUTTON,    howto,     'H', NULL, NULL,
                      NULL);
   XtManageChild ( menubar);

   strtmp = XmStringCreateSimple ( "Empty Infobox...");
   message = XtVaCreateManagedWidget ( "Info",
                                       xmLabelWidgetClass, shaderwindow,
                                       XmNlabelType,   XmSTRING,
                                       XmNlabelString, strtmp,
                                       XmNalignment, XmALIGNMENT_BEGINNING,
                                       NULL);
   XmStringFree ( strtmp);
   tabpad  = XtVaCreateManagedWidget ( "Tab", 
                                       xmTabWidgetClass, shaderwindow,
                                       NULL);
   strtmp  = XmStringCreateSimple ( "Empty Database...");
   initab  = XtVaCreateManagedWidget ( "None", 
                                       xmLabelWidgetClass, tabpad,
                                       XmNlabelType,   XmSTRING,
                                       XmNlabelString, strtmp,
                                       NULL);
   XmStringFree ( strtmp);
   XmTabSetTabWidget ( tabpad, initab, FALSE);

   XtVaSetValues ( shaderwindow,
                   XmNmenuBar,       menubar,
                   XmNmessageWindow, message,
                   XmNworkWindow,    tabpad,
                   NULL);
}



/* =========================================================================
 * Callback functions related to the GUI interface
 */

/* File Menu Callback *********************** */
void
fileCallback ( menuItem, itemNum, cbs)
Widget     menuItem;
XtPointer  itemNum;
XtPointer  cbs;
{
   printf ( "Selecionada a opcao %d do menu File.\n", ( ( int) itemNum)+1);

   if ( ( int) itemNum == 9)
      exit ( 0);
}

/* Edit Menu Callback *********************** */
void
editCallback ( menuItem, itemNum, cbs)
Widget     menuItem;
XtPointer  itemNum;
XtPointer  cbs;
{
   printf ( "Selecionada a opcao %d do menu Edit.\n", ( ( int) itemNum)+1);
}

/* Options Menu Callback ******************** */
void optionsCallback ( menuItem, itemNum, cbs)
Widget     menuItem;
XtPointer  itemNum;
XtPointer  cbs;
{
   printf ( "Selecionada a opcao %d do menu Options.\n", ( ( int) itemNum)+1);
}

/* Windows Menu Callback ******************** */
void windowsCallback ( menuItem, itemNum, cbs)
Widget     menuItem;
XtPointer  itemNum;
XtPointer  cbs;
{
   printf ( "Selecionada a opcao %d do menu Windows.\n", ( ( int) itemNum)+1);
}

/* Help Menu Callback *********************** */
void helpCallback ( menuItem, itemNum, cbs)
Widget     menuItem;
XtPointer  itemNum;
XtPointer  cbs;
{
   printf ( "Selecionada a opcao %d do menu Help.\n", ( ( int) itemNum)+1);
}
