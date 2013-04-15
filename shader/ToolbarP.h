
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

#ifndef __TOOLBARP_H__
#define __TOOLBARP_H__

#include <Xm/XmP.h>
#include <Xm/ManagerP.h>
#include "Toolbar.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _XmToolbarClassPart {
XtPointer extension;
} XmToolbarClassPart;

typedef struct _XmToolbarClassRec {
	CoreClassPart core_class;
	CompositeClassPart composite_class;
	ConstraintClassPart constraint_class;
	XmManagerClassPart manager_class;
	XmToolbarClassPart toolbar_class;
} XmToolbarClassRec;

extern XmToolbarClassRec xmToolbarClassRec;

typedef struct _XmToolbarPart {

	unsigned char orientation;
	Dimension spacing;
	Dimension group_spacing;
	Dimension margin_height;
	Dimension margin_width;
	XmFontList tip_font_list;
	int entry_count;

	Pixel tip_foreground;
	Pixel tip_background;
	Dimension tip_border_width;
	unsigned char tip_position;
	Dimension tip_distance;
	int tip_notify_delay;

	XtIntervalId interval_id;
	Widget tooltip;
	Widget label;
	Boolean tooltip_on;
	Boolean interval_id_on;

} XmToolbarPart;

typedef struct _XmToolbarRec {
	CorePart core;
	CompositePart composite;
	ConstraintPart constraint;
	XmManagerPart manager;
	XmToolbarPart toolbar;
} XmToolbarRec;

typedef struct _XmToolbarConstraintPart {
	XmString tip_label;
	Boolean notifyable;
	Boolean new_group;
	Boolean configurable;
} XmToolbarConstraintPart;

typedef struct _XmToolbarConstraintRec {
	XmManagerConstraintPart manager;
	XmToolbarConstraintPart toolbar;
} XmToolbarConstraintRec;

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /**  __TOOLBARP_H__  **/


