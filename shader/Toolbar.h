
/************************************************************************* 
 * Version 1.0  on  23-May-1997
 * (c) 1997 Pralay Dakua (pkanti@hotmail.com)
 *     
 * This is a free software and permission to use, modify, distribute,
 * selling and using for commercial purpose is hereby granted provided
 * that THE ABOVE COPYRIGHT NOTICE AND THIS PERMISSION NOTICE SHALL BE
 * INCLUDED IN ALL COPIES AND THEIR SUPPORTING DOCUMENTATIONS.
 *
 * There is no warranty for this software. In no event Pralay Dakua
 * will be liable for merchantability and fitness of the software and 
 * damages due to this software.
 *
 * Author:
 * Pralay Dakua (pkanti@hotmail.com)
 *
 **************************************************************************/

#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include <Xm/Xm.h>

#ifdef __cplusplus
extern "C" {
#endif

extern WidgetClass xmToolbarWidgetClass;

typedef struct _XmToolbarClassRec *XmToolbarWidgetClass;
typedef struct _XmToolbarRec *XmToolbarWidget;

#define XmNtipFontList "tipFontList"
#define XmCTipFontList "TipFontList"

#define XmNtipForeground "tipForeground"
#define XmCTipForeground "TipForeground"

#define XmNtipBackground "tipBackground"
#define XmCTipBackground "TipBackground"

#define XmNtipBorderWidth "tipBorderWidth"
#define XmCTipBorderWidth "TipBorderWidth"

#define XmNtipPosition "tipPosition"
#define XmCTipPosition "TipPosition"
#define XmRTipPosition "TipPosition"

#define XmNtipDistance "tipDistance"
#define XmCTipDistance "TipDistance"

#define XmNtipNotifyDelay "tipNotifyDelay"
#define XmCTipNotifyDelay "TipNotifyDelay"

#define XmNgroupSpacing "groupSpacing"
#define XmCGroupSpacing "GroupSpacing"

#define XmNentryCount "entryCount"
#define XmCEntryCount "EntryCount"

/***** constraint resource name//representations ****/

#define XmNtipLabel "tipLabel"
#define XmCTipLabel "TipLabel"

#define XmNnotifyable "notifyable"
#define XmCNotifyable "Notifyable"

#define XmNnewGroup "newGroup"
#define XmCNewGroup "NewGroup"

#define XmNconfigurable "configurable"
#define XmCConfigurable "Configurable"

enum {
XmTIP_BOTTOM_RIGHT, 
XmTIP_BOTTOM_LEFT, 
XmTIP_TOP_RIGHT, 
XmTIP_TOP_LEFT
};

enum {
XmENTRY_UNSPECIFIED
};

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /**  __TOOLBAR_H__  **/

