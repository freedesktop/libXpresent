/*
 * Copyright © 2013 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef _XPRESENT_H_
#define _XPRESENT_H_

#include <stdint.h>
#include <X11/extensions/presenttokens.h>

#include <X11/Xfuncproto.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>

/*
 * This revision number also appears in configure.ac, they have
 * to be manually synchronized
 */
#define PRESENT_REVISION	0
#define PRESENT_VERSION	((PRESENT_MAJOR * 10000) + (PRESENT_MINOR * 100) + (PRESENT_REVISION))

/**
 * Generic Present event. All Present events have the same header.
 */

typedef struct {
    int type;			/* event base */
    unsigned long serial;
    Bool send_event;
    Display *display;
    int extension;
    int evtype;
} XPresentEvent;

typedef struct {
    int type;			/* event base */
    unsigned long serial;
    Bool send_event;
    Display *display;
    int extension;
    int evtype;

    uint32_t eid;
    Window window;
    int x,y;
    unsigned width, height;
    int off_x, off_y;
    int pixmap_width, pixmap_height;
    long pixmap_flags;
} XPresentConfigureNotifyEvent;

typedef struct {
    int type;			/* event base */
    unsigned long serial;
    Bool send_event;
    Display *display;
    int extension;
    int evtype;

    uint32_t eid;
    Window window;
    uint32_t serial_number;
    uint64_t ust;
    uint64_t msc;
} XPresentCompleteNotifyEvent;

_XFUNCPROTOBEGIN

Bool XPresentQueryExtension (Display *dpy,
                             int *major_opcode_return,
                             int *event_base_return,
                             int *error_base_return);

Status XPresentQueryVersion (Display *dpy,
			    int     *major_version_return,
			    int     *minor_version_return);

int XPresentVersion (void);

void
XPresentRegion(Display *dpy,
               Window window,
               Pixmap pixmap,
               uint32_t serial,
               XserverRegion valid,
               XserverRegion update,
               int x_off,
               int y_off,
               XID idle_fence,
               uint64_t target_msc,
               uint64_t divisor,
               uint64_t remainder);

void
XPresentNotifyMSC(Display *dpy,
                  Window window,
                  uint32_t serial,
                  uint64_t target_msc,
                  uint64_t divisor,
                  uint64_t remainder);

XID
XPresentSelectInput(Display *dpy,
                    Window window,
                    unsigned event_mask);

_XFUNCPROTOEND

#endif /* _XPRESENT_H_ */
