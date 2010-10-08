/*
 *  Copyright (C) Boris Lechner 2009 2010 <boris.lechner.dev@gmail.com>
 *   
 *  This file is part of Galinette.
 *
 *  Galinette is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License.
 *
 *  Galinette is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License along
 *  with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gudev/gudev.h>
#include "callbacks.h"
#include "galinette-gtk.h"
#include "monitor.h"

guint deviceConnected;


/*
 * This function handles device detection.
 */
gboolean deviceDetect (GUdevClient *client)
{
	deviceConnected = 0;
	GList *list, *it;

	list = g_udev_client_query_by_subsystem (client, "usb");
	for (it = list; it != NULL; it = g_list_next (it))
	{
		if ((g_udev_device_has_property (it->data, "ID_VENDOR_ID")) &&
		    (g_udev_device_has_property (it->data, "ID_MODEL_ID")))
		{
			if (isB1Device (it->data))
				deviceConnected++;
		}
		g_object_unref (it->data);
	}
	g_list_free (list);

	updateStatus();
	return TRUE;
}

/*
 * This function assumes that the device passed has
 * the ID_VENDOR_ID attribute.
 */
gboolean isB1Device (GUdevDevice *device)
{
	const gchar *vendor;
	const gchar *model;

	vendor = g_udev_device_get_property (device, "ID_VENDOR_ID");
	model = g_udev_device_get_property (device, "ID_MODEL_ID");

	if (( strcmp (vendor, (const gchar*) B1_VENDOR_ID) == 0) &&
	    ( strcmp (model, (const gchar*) B1_MODEL_ID) == 0))
		return TRUE;
	else
		return FALSE;
}

/*
 * This function updates the status icon.
 */
void updateStatus()
{
	GtkImage *status = GTK_IMAGE( gtk_builder_get_object (builder, "img_devicestatus") );

	if ( deviceConnected > 0 )
	{
		gtk_image_set_from_stock (status, "gtk-connect", GTK_ICON_SIZE_LARGE_TOOLBAR);
		gtk_widget_set_tooltip_text(GTK_WIDGET(status), "B1 connected");
		update_flash_button_state();
	}
	else
	{
		gtk_image_set_from_stock (status, "gtk-disconnect", GTK_ICON_SIZE_LARGE_TOOLBAR);
		gtk_widget_set_tooltip_text(GTK_WIDGET(status), "B1 disconnected");
		update_flash_button_state();
	}
}


/*
 * This is the main loop which creates a gudev client, and listens
 * for "uevent"s only on USB devices.
 */
int monitormain(int argc, char **argv)
{
	GUdevClient *client;
	guint uevent_id;

	const char * const subsystems[] = { "usb", NULL };
	client = g_udev_client_new (subsystems);

	deviceDetect(client);
	
	uevent_id = g_signal_connect_object (client,
					     "uevent",
					     G_CALLBACK (deviceDetect),
					     NULL, 0);
	return EXIT_SUCCESS;
}
