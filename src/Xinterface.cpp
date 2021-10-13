#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

using namespace std;

Window get_active_window(Display * display)
{
    Atom xa_prop_name;
    Atom xa_ret_type;
    int ret_format;
    unsigned long ret_nitems;
    unsigned long ret_bytes_after;
    unsigned long tmp_size;
    unsigned char *ret_prop;
    char *ret;

    xa_prop_name = XInternAtom(display, "_NET_ACTIVE_WINDOW", False);
        
    if(XGetWindowProperty(display, XDefaultRootWindow(display), xa_prop_name,
			   0, 4096 / 4, False, XA_WINDOW, &xa_ret_type,
			   &ret_format, &ret_nitems, &ret_bytes_after, &ret_prop) != Success)
    {
	cout << "Cannot get property: " << xa_prop_name << endl;
        return 0;
    }

	
    if (xa_ret_type != XA_WINDOW) {
        cout << "Invalid type of property: " << xa_prop_name << endl;
        XFree(ret_prop);
        return 0;
    }

    /* null terminate the result to make string handling easier */
    tmp_size = (ret_format / (32 / sizeof(long))) * ret_nitems;
    ret = (char *) malloc(tmp_size + 1);
    memcpy(ret, ret_prop, tmp_size);
    ret[tmp_size] = '\0';
    
    XFree(ret_prop);
    return *((Window *) ret);
}
    

void window_maximize(Display * display, Window window)
{
    XEvent event;
    long mask = SubstructureRedirectMask | SubstructureNotifyMask;
    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.message_type =  XInternAtom(display, "_NET_WM_STATE", False);
    event.xclient.window = window;
    event.xclient.format = 32;
    event.xclient.data.l[0] = 1; // = _NET_WM_STATE_ADD
    event.xclient.data.l[1] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    event.xclient.data.l[2] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    event.xclient.data.l[3] = 0;
    event.xclient.data.l[4] = 0;
    XSendEvent(display, XDefaultRootWindow(display), False, mask, &event);
}

void enum_windows(Display* display, Window window, int depth, Window active) {
    int i;
    
    XTextProperty text;
    XGetWMName(display, window, &text);
    char* name;
    XFetchName(display, window, &name);
    
    if(name != NULL)
    {
	/*
	for (i = 0; i < depth; i++)
	    printf("\t");
	printf("id=0x%lx, XFetchName=\"%s\", XGetWMName=\"%s\"\n", window, name != NULL ? name : "(no name)", text.value);
	*/
	
	if(window==active)
	{
	    window_maximize(display,window);
	}
    }
    
    Window root, parent;
    Window* children;
    unsigned int n;
    XQueryTree(display, window, &root, &parent, &children, &n);
    if (children != NULL) {
	for (i = 0; i < n; i++) {
	    enum_windows(display, children[i], depth + 1, active);
	}
	XFree(children);
    }
}


void maximize_active_window()
{
    Display* display = XOpenDisplay(NULL);
    Window root = XDefaultRootWindow(display);
    enum_windows(display, root, 0, get_active_window(display));
}
