/*
 * Copyright (C) 2013 Alexander Mezin <mezin.alexander@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

//Debug tool
//Must NOT be translated/localized

#include <iostream>

#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>

int main(void)
{
    Display *display = XOpenDisplay(0);
    int nDevices = 0;
    XDeviceInfo *devices = XListInputDevices(display, &nDevices);
    for (int i = 0; i < nDevices; i++) {
        const char *name = devices[i].name;
        char *type = 0;
        if (devices[i].type) {
            type = XGetAtomName(display, devices[i].type);
        }
        const char *use;
        switch (devices[i].use) {
        case IsXPointer: use = "Pointer"; break;
        case IsXKeyboard: use = "Keyboard"; break;
        case IsXExtensionDevice: use = "Extension Device"; break;
        case IsXExtensionPointer: use = "Extension Pointer"; break;
        case IsXExtensionKeyboard: use = "Extension Keyboard"; break;
        default: use = "Unknown";
        }
        std::cout << "Name: " << name << " Type: " << (type ? type : "unknown")
                  << " Use: " << use << std::endl;
        XFree(type);
    }
    XFreeDeviceList(devices);
    XCloseDisplay(display);
}
