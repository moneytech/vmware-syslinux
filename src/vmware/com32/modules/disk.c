/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 *   Boston MA 02110-1301, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <console.h>
#include <stdlib.h>
#include <string.h>
#include <disk/geom.h>
#include <disk/util.h>

int main(int argc __attribute__ (( unused )),
	 char *argv[] __attribute__ (( unused )))
{
	char* error_buffer;
	int err;
	struct driveinfo drive;
	struct driveinfo *d = &drive;

	openconsole(&dev_null_r, &dev_stdcon_w);

	for (int disk = 0x80; disk < 0xff; disk++) {
		memset(d, 0, sizeof(struct driveinfo));
		d->disk = disk;
		err = get_drive_parameters(d);

		/* Do not print output when drive does not exists */
		if (err == -1)
			continue;

		if (err) {
			get_error(err, &error_buffer);
			printf("Error 0x%Xh while reading disk 0x%X:\n  %s\n",
					err, d->disk, error_buffer);
			free(error_buffer);
			continue;
		}

		printf("DISK 0x%X:\n", d->disk);
		printf("  C/H/S: %d heads, %d cylinders\n",
			d->legacy_max_head + 1, d->legacy_max_cylinder + 1);
		printf("         %d sectors/track, %d drives\n",
			d->legacy_sectors_per_track, d->legacy_max_drive);
		printf("  EDD:   ebios=%d, EDD version: %X\n",
			d->ebios, d->edd_version);
		printf("         %d heads, %d cylinders\n",
			(int) d->edd_params.heads, (int) d->edd_params.cylinders);
		printf("         %d sectors, %d bytes/sector, %d sectors/track\n",
			(int) d->edd_params.sectors, (int) d->edd_params.bytes_per_sector,
			(int) d->edd_params.sectors_per_track);
		printf("         Host bus: %s, Interface type: %s\n\n",
			d->edd_params.host_bus_type, d->edd_params.interface_type);
	}
	return 0;
}
