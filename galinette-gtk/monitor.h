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

/*
 * Constants
 */
#define B1_VENDOR_ID	"0403"
#define B1_MODEL_ID	"6001"

/*
 * Includes
 */
#include <gudev/gudev.h>

/*
 * Functions
 */
gboolean deviceDetect(GUdevClient *client);
gboolean isB1Device(GUdevDevice *device);
int monitormain();
void updateStatus();
