/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimplayer_pdb.h
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

#ifndef __GIMP_LAYER_PDB_H__
#define __GIMP_LAYER_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


G_GNUC_INTERNAL gint32 _gimp_layer_new                 (gint32                  image_ID,
                                                        gint                    width,
                                                        gint                    height,
                                                        GimpImageType           type,
                                                        const gchar            *name,
                                                        gdouble                 opacity,
                                                        GimpLayerMode           mode);
gint32                 gimp_layer_new_from_visible     (gint32                  image_ID,
                                                        gint32                  dest_image_ID,
                                                        const gchar            *name);
gint32                 gimp_layer_new_from_drawable    (gint32                  drawable_ID,
                                                        gint32                  dest_image_ID);
gint32                 gimp_layer_group_new            (gint32                  image_ID);
G_GNUC_INTERNAL gint32 _gimp_layer_copy                (gint32                  layer_ID,
                                                        gboolean                add_alpha);
gboolean               gimp_layer_add_alpha            (gint32                  layer_ID);
gboolean               gimp_layer_flatten              (gint32                  layer_ID);
gboolean               gimp_layer_scale                (gint32                  layer_ID,
                                                        gint                    new_width,
                                                        gint                    new_height,
                                                        gboolean                local_origin);
GIMP_DEPRECATED_FOR(gimp_layer_scale)
gboolean               gimp_layer_scale_full           (gint32                  layer_ID,
                                                        gint                    new_width,
                                                        gint                    new_height,
                                                        gboolean                local_origin,
                                                        GimpInterpolationType   interpolation);
gboolean               gimp_layer_resize               (gint32                  layer_ID,
                                                        gint                    new_width,
                                                        gint                    new_height,
                                                        gint                    offx,
                                                        gint                    offy);
gboolean               gimp_layer_resize_to_image_size (gint32                  layer_ID);
gboolean               gimp_layer_translate            (gint32                  layer_ID,
                                                        gint                    offx,
                                                        gint                    offy);
gboolean               gimp_layer_set_offsets          (gint32                  layer_ID,
                                                        gint                    offx,
                                                        gint                    offy);
gint32                 gimp_layer_create_mask          (gint32                  layer_ID,
                                                        GimpAddMaskType         mask_type);
gint32                 gimp_layer_get_mask             (gint32                  layer_ID);
gint32                 gimp_layer_from_mask            (gint32                  mask_ID);
gboolean               gimp_layer_add_mask             (gint32                  layer_ID,
                                                        gint32                  mask_ID);
gboolean               gimp_layer_remove_mask          (gint32                  layer_ID,
                                                        GimpMaskApplyMode       mode);
gboolean               gimp_layer_is_floating_sel      (gint32                  layer_ID);
gboolean               gimp_layer_get_lock_alpha       (gint32                  layer_ID);
gboolean               gimp_layer_set_lock_alpha       (gint32                  layer_ID,
                                                        gboolean                lock_alpha);
gboolean               gimp_layer_get_apply_mask       (gint32                  layer_ID);
gboolean               gimp_layer_set_apply_mask       (gint32                  layer_ID,
                                                        gboolean                apply_mask);
gboolean               gimp_layer_get_show_mask        (gint32                  layer_ID);
gboolean               gimp_layer_set_show_mask        (gint32                  layer_ID,
                                                        gboolean                show_mask);
gboolean               gimp_layer_get_edit_mask        (gint32                  layer_ID);
gboolean               gimp_layer_set_edit_mask        (gint32                  layer_ID,
                                                        gboolean                edit_mask);
gdouble                gimp_layer_get_opacity          (gint32                  layer_ID);
gboolean               gimp_layer_set_opacity          (gint32                  layer_ID,
                                                        gdouble                 opacity);
GimpLayerMode          gimp_layer_get_mode             (gint32                  layer_ID);
gboolean               gimp_layer_set_mode             (gint32                  layer_ID,
                                                        GimpLayerMode           mode);
GimpLayerColorSpace    gimp_layer_get_blend_space      (gint32                  layer_ID);
gboolean               gimp_layer_set_blend_space      (gint32                  layer_ID,
                                                        GimpLayerColorSpace     blend_space);
GimpLayerColorSpace    gimp_layer_get_composite_space  (gint32                  layer_ID);
gboolean               gimp_layer_set_composite_space  (gint32                  layer_ID,
                                                        GimpLayerColorSpace     composite_space);
GimpLayerCompositeMode gimp_layer_get_composite_mode   (gint32                  layer_ID);
gboolean               gimp_layer_set_composite_mode   (gint32                  layer_ID,
                                                        GimpLayerCompositeMode  composite_mode);


G_END_DECLS

#endif /* __GIMP_LAYER_PDB_H__ */
