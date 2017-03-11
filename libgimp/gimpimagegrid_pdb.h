/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimagegrid_pdb.h
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

#ifndef __GIMP_IMAGE_GRID_PDB_H__
#define __GIMP_IMAGE_GRID_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gboolean      gimp_image_grid_get_spacing          (gint32         image_ID,
                                                    gdouble       *xspacing,
                                                    gdouble       *yspacing);
gboolean      gimp_image_grid_set_spacing          (gint32         image_ID,
                                                    gdouble        xspacing,
                                                    gdouble        yspacing);
gboolean      gimp_image_grid_get_offset           (gint32         image_ID,
                                                    gdouble       *xoffset,
                                                    gdouble       *yoffset);
gboolean      gimp_image_grid_set_offset           (gint32         image_ID,
                                                    gdouble        xoffset,
                                                    gdouble        yoffset);
gboolean      gimp_image_grid_get_foreground_color (gint32         image_ID,
                                                    GimpRGB       *fgcolor);
gboolean      gimp_image_grid_set_foreground_color (gint32         image_ID,
                                                    const GimpRGB *fgcolor);
gboolean      gimp_image_grid_get_background_color (gint32         image_ID,
                                                    GimpRGB       *bgcolor);
gboolean      gimp_image_grid_set_background_color (gint32         image_ID,
                                                    const GimpRGB *bgcolor);
GimpGridStyle gimp_image_grid_get_style            (gint32         image_ID);
gboolean      gimp_image_grid_set_style            (gint32         image_ID,
                                                    GimpGridStyle  style);


G_END_DECLS

#endif /* __GIMP_IMAGE_GRID_PDB_H__ */
