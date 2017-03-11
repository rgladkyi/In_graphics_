/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimageundo_pdb.h
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl */

#if !defined (__GIMP_H_INSIDE__) && !defined (GIMP_COMPILATION)
#error "Only <libgimp/gimp.h> can be included directly."
#endif

#ifndef __GIMP_IMAGE_UNDO_PDB_H__
#define __GIMP_IMAGE_UNDO_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gboolean gimp_image_undo_group_start (gint32 image_ID);
gboolean gimp_image_undo_group_end   (gint32 image_ID);
gboolean gimp_image_undo_is_enabled  (gint32 image_ID);
gboolean gimp_image_undo_disable     (gint32 image_ID);
gboolean gimp_image_undo_enable      (gint32 image_ID);
gboolean gimp_image_undo_freeze      (gint32 image_ID);
gboolean gimp_image_undo_thaw        (gint32 image_ID);


G_END_DECLS

#endif /* __GIMP_IMAGE_UNDO_PDB_H__ */
