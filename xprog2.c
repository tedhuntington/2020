#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

main ()
{
        Display *xdisplay;
        Window xwindow;
        int xscreen;
        unsigned long xforeground, xbackground;
        XEvent xevent;
        GC xgc;
        Colormap cmap;
        XColor color, colorrgb;

        /* connect to the X server */
        xdisplay = XOpenDisplay ("");

        if (xdisplay == NULL) {
                fprintf (stderr, "cannot connect to server\n");
                exit (EXIT_FAILURE);
        }

        /* get default screen */
        xscreen = DefaultScreen (xdisplay);

        /* get black and white representation on current screen */        
        xbackground = BlackPixel (xdisplay, xscreen);
        xforeground = WhitePixel (xdisplay, xscreen);

        /* Create window at (100,50), width 350, height 250, border width
           2, in default root  */
        xwindow = XCreateSimpleWindow (xdisplay,
                DefaultRootWindow(xdisplay), 100, 50, 350, 250, 2,
                xforeground, xbackground);

        if (xwindow == NULL) {
                fprintf (stderr, "cannot open window\n");
                exit (EXIT_FAILURE);
        }

        /* ask for exposure event */
        XSelectInput(xdisplay, xwindow, ExposureMask);

        /* pop this window up on the screen */
        XMapRaised (xdisplay, xwindow);

        /* wait for the window showing up before continuing */
        XNextEvent (xdisplay, &xevent);

        /* set graphics context of rectangle to red */
        xgc= XCreateGC (xdisplay, xwindow, 0, 0);
        if (DisplayPlanes (xdisplay, xscreen) != 1) {
                cmap = DefaultColormap (xdisplay, xscreen);
                if (XAllocNamedColor (xdisplay, cmap, "red", &color, &colorrgb))
                        XSetForeground (xdisplay, xgc, color.pixel);
        }

        /* Draw rectangle at (25,25), width 300, height, 200 */
        XFillRectangle (xdisplay, xwindow, xgc, 25, 25,
                300, 200);

        /* flush X request queue to server */
        XFlush (xdisplay);

        sleep (10);
        XDestroyWindow(xdisplay, xwindow);
        XCloseDisplay (xdisplay);

        return 0;
}
