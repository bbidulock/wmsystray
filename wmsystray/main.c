/*****************************************************************************
 main.c

 General "top-level" driver code; get wmsystray running and processing events.

 This source code is copyright (C) 2004 Matthew Reppert. Redistribution and
 use may occur under the terms of the GNU General Public License v2.
 ****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "ui.h"
#include "systray.h"
#include "version.h"


void usage();
void parse_cmd_line (int argc, char **argv);



int main(int argc, char **argv) {
	struct sigaction act, oldact;

	parse_cmd_line(argc, argv);
	act.sa_handler = &wmsystray_handle_signal;
	act.sa_flags = 0;
	sigaction (SIGTERM, &act, &oldact);
	sigaction (SIGINT, &act, &oldact);

	if (init_ui ("wmsystray", argc, argv) != 0) {
		printf ("Could not connect to X server!\n");
		return 0;
	}

	if (init_systray()) {
		fprintf (stderr, "Could not get systray!\n");
		cleanup_ui();
		return 0;
	}

	wmsystray_event_loop();

	cleanup_systray();
	cleanup_ui();
	return 0;
}



/*
 * usage
 *
 * Print command usage information.
 */
void usage() {
	printf ("%s\n", PACKAGE_STRING);
	printf ("Usage: %s [OPTION] ... \n\n", PACKAGE_TARNAME);
	printf ("\t-display <display>\t\t\tX display to connect to\n");
	printf ("\t-geometry <geom>\t\t\tinitial window geometry\n");
	printf ("\n\nReport bugs to %s\n", PACKAGE_BUGREPORT);
}



/*
 * parse_cmd_line
 *
 * Parse command line arguments.
 */
void parse_cmd_line (int argc, char **argv) {
	int i;

	display_string = getenv("DISPLAY");

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-geometry") == 0) {
			geometry_string = argv[i + 1];
			i++;
		} else if (strcmp(argv[i], "-display") == 0) {
			display_string = argv[i + 1];
			i++;
		} else if (strcmp(argv[i], "-H") == 0 ||
			   strcmp(argv[i], "--help") == 0)
		{
			usage();
			exit(0);
		} else if (strcmp(argv[i], "--nowm") == 0) {
			wmaker = 0;
		}
	}
}
