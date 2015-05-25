/*****************************************************************************
 systray.h

 Initialize and clean up the systray area; handle X protocal junk relating to
 systray communication.

 This source code is copyright (C) 2004 Matthew Reppert. Redistribution and
 use may occur under the terms of the GNU General Public License v2.
 ****************************************************************************/

#ifndef WMSYSTRAY_SYSTRAY_H
#define WMSYSTRAY_SYSTRAY_H

#include <xembed.h>
#include "list.h"

struct systray_item {
	Window window_id;
	struct xembed_info info;
	struct list_head systray_list;
};

extern struct list_head systray_list;
extern int systray_item_count;

/*
 * System tray message opcodes. (From the freedesktop.org specification.)
 */
#define SYSTEM_TRAY_REQUEST_DOCK	0  /* Begin icon docking */
#define SYSTEM_TRAY_BEGIN_MESSAGE	1  /* Display balloon mesage */
#define SYSTEM_TRAY_CANCEL_MESSAGE	2  /* Cancel previous balloon message */


int init_systray();
void cleanup_systray();
int event_is_systray_event(XEvent *ev);
int handle_systray_event(XEvent *ev);
void repaint_systray();

#endif
