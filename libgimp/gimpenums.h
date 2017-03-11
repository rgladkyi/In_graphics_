/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
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

/* NOTE: This file is autogenerated by enumcode.pl */

#ifndef __GIMP_ENUMS_H__
#define __GIMP_ENUMS_H__

G_BEGIN_DECLS


#define GIMP_TYPE_BRUSH_APPLICATION_MODE (gimp_brush_application_mode_get_type ())

GType gimp_brush_application_mode_get_type (void) G_GNUC_CONST;

typedef enum
{
  GIMP_BRUSH_HARD,
  GIMP_BRUSH_SOFT
} GimpBrushApplicationMode;


#define GIMP_TYPE_CONVERT_DITHER_TYPE (gimp_convert_dither_type_get_type ())

GType gimp_convert_dither_type_get_type (void) G_GNUC_CONST;

typedef enum
{
  GIMP_CONVERT_DITHER_NONE,
  GIMP_CONVERT_DITHER_FS,
  GIMP_CONVERT_DITHER_FS_LOWBLEED,
  GIMP_CONVERT_DITHER_FIXED
} GimpConvertDitherType;


#define GIMP_TYPE_HISTOGRAM_CHANNEL (gimp_histogram_channel_get_type ())

GType gimp_histogram_channel_get_type (void) G_GNUC_CONST;

typedef enum
{
  GIMP_HISTOGRAM_VALUE,
  GIMP_HISTOGRAM_RED,
  GIMP_HISTOGRAM_GREEN,
  GIMP_HISTOGRAM_BLUE,
  GIMP_HISTOGRAM_ALPHA,
  GIMP_HISTOGRAM_LUMINANCE
} GimpHistogramChannel;


#define GIMP_TYPE_LAYER_COLOR_SPACE (gimp_layer_color_space_get_type ())

GType gimp_layer_color_space_get_type (void) G_GNUC_CONST;

typedef enum
{
  GIMP_LAYER_COLOR_SPACE_AUTO,
  GIMP_LAYER_COLOR_SPACE_RGB_LINEAR,
  GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
} GimpLayerColorSpace;


#define GIMP_TYPE_LAYER_COMPOSITE_MODE (gimp_layer_composite_mode_get_type ())

GType gimp_layer_composite_mode_get_type (void) G_GNUC_CONST;

typedef enum
{
  GIMP_LAYER_COMPOSITE_AUTO,
  GIMP_LAYER_COMPOSITE_SRC_OVER,
  GIMP_LAYER_COMPOSITE_SRC_ATOP,
  GIMP_LAYER_COMPOSITE_SRC_IN,
  GIMP_LAYER_COMPOSITE_DST_ATOP
} GimpLayerCompositeMode;


#define GIMP_TYPE_LAYER_MODE (gimp_layer_mode_get_type ())

GType gimp_layer_mode_get_type (void) G_GNUC_CONST;

typedef enum
{
  GIMP_LAYER_MODE_NORMAL_LEGACY,
  GIMP_LAYER_MODE_DISSOLVE,
  GIMP_LAYER_MODE_BEHIND_LEGACY,
  GIMP_LAYER_MODE_MULTIPLY_LEGACY,
  GIMP_LAYER_MODE_SCREEN_LEGACY,
  GIMP_LAYER_MODE_OVERLAY_LEGACY,
  GIMP_LAYER_MODE_DIFFERENCE_LEGACY,
  GIMP_LAYER_MODE_ADDITION_LEGACY,
  GIMP_LAYER_MODE_SUBTRACT_LEGACY,
  GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY,
  GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY,
  GIMP_LAYER_MODE_HSV_HUE_LEGACY,
  GIMP_LAYER_MODE_HSV_SATURATION_LEGACY,
  GIMP_LAYER_MODE_HSV_COLOR_LEGACY,
  GIMP_LAYER_MODE_HSV_VALUE_LEGACY,
  GIMP_LAYER_MODE_DIVIDE_LEGACY,
  GIMP_LAYER_MODE_DODGE_LEGACY,
  GIMP_LAYER_MODE_BURN_LEGACY,
  GIMP_LAYER_MODE_HARDLIGHT_LEGACY,
  GIMP_LAYER_MODE_SOFTLIGHT_LEGACY,
  GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY,
  GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY,
  GIMP_LAYER_MODE_COLOR_ERASE_LEGACY,
  GIMP_LAYER_MODE_OVERLAY,
  GIMP_LAYER_MODE_LCH_HUE,
  GIMP_LAYER_MODE_LCH_CHROMA,
  GIMP_LAYER_MODE_LCH_COLOR,
  GIMP_LAYER_MODE_LCH_LIGHTNESS,
  GIMP_LAYER_MODE_NORMAL,
  GIMP_LAYER_MODE_BEHIND,
  GIMP_LAYER_MODE_MULTIPLY,
  GIMP_LAYER_MODE_SCREEN,
  GIMP_LAYER_MODE_DIFFERENCE,
  GIMP_LAYER_MODE_ADDITION,
  GIMP_LAYER_MODE_SUBTRACT,
  GIMP_LAYER_MODE_DARKEN_ONLY,
  GIMP_LAYER_MODE_LIGHTEN_ONLY,
  GIMP_LAYER_MODE_HSV_HUE,
  GIMP_LAYER_MODE_HSV_SATURATION,
  GIMP_LAYER_MODE_HSV_COLOR,
  GIMP_LAYER_MODE_HSV_VALUE,
  GIMP_LAYER_MODE_DIVIDE,
  GIMP_LAYER_MODE_DODGE,
  GIMP_LAYER_MODE_BURN,
  GIMP_LAYER_MODE_HARDLIGHT,
  GIMP_LAYER_MODE_SOFTLIGHT,
  GIMP_LAYER_MODE_GRAIN_EXTRACT,
  GIMP_LAYER_MODE_GRAIN_MERGE,
  GIMP_LAYER_MODE_VIVID_LIGHT,
  GIMP_LAYER_MODE_PIN_LIGHT,
  GIMP_LAYER_MODE_LINEAR_LIGHT,
  GIMP_LAYER_MODE_HARD_MIX,
  GIMP_LAYER_MODE_EXCLUSION,
  GIMP_LAYER_MODE_LINEAR_BURN,
  GIMP_LAYER_MODE_LUMA_DARKEN_ONLY,
  GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY,
  GIMP_LAYER_MODE_LUMINANCE,
  GIMP_LAYER_MODE_COLOR_ERASE
} GimpLayerMode;


void           gimp_enums_init           (void);

const gchar ** gimp_enums_get_type_names (gint *n_type_names);


G_END_DECLS

#endif /* __GIMP_ENUMS_H__ */
