/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimageconvert_pdb.c
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

#include "config.h"

#include "gimp.h"


/**
 * SECTION: gimpimageconvert
 * @title: gimpimageconvert
 * @short_description: Conversions between RGB, indexed, and grayscale modes.
 *
 * Conversions between RGB, indexed, and grayscale modes.
 **/


/**
 * gimp_image_convert_rgb:
 * @image_ID: The image.
 *
 * Convert specified image to RGB color
 *
 * This procedure converts the specified image to RGB color. This
 * process requires an image in Grayscale or Indexed color mode. No
 * image content is lost in this process aside from the colormap for an
 * indexed image.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_image_convert_rgb (gint32 image_ID)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-convert-rgb",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_convert_grayscale:
 * @image_ID: The image.
 *
 * Convert specified image to grayscale
 *
 * This procedure converts the specified image to grayscale. This
 * process requires an image in RGB or Indexed color mode.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_image_convert_grayscale (gint32 image_ID)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-convert-grayscale",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_convert_indexed:
 * @image_ID: The image.
 * @dither_type: The dither type to use.
 * @palette_type: The type of palette to use.
 * @num_cols: The number of colors to quantize to, ignored unless (palette_type == GIMP_CONVERT_PALETTE_GENERATE).
 * @alpha_dither: Dither transparency to fake partial opacity.
 * @remove_unused: Remove unused or duplicate color entries from final palette, ignored if (palette_type == GIMP_CONVERT_PALETTE_GENERATE).
 * @palette: The name of the custom palette to use, ignored unless (palette_type == GIMP_CONVERT_PALETTE_CUSTOM).
 *
 * Convert specified image to and Indexed image
 *
 * This procedure converts the specified image to 'indexed' color. This
 * process requires an image in RGB or Grayscale mode. The
 * 'palette_type' specifies what kind of palette to use, A type of '0'
 * means to use an optimal palette of 'num_cols' generated from the
 * colors in the image. A type of '1' means to re-use the previous
 * palette (not currently implemented). A type of '2' means to use the
 * so-called WWW-optimized palette. Type '3' means to use only black
 * and white colors. A type of '4' means to use a palette from the gimp
 * palettes directories. The 'dither type' specifies what kind of
 * dithering to use. '0' means no dithering, '1' means standard
 * Floyd-Steinberg error diffusion, '2' means Floyd-Steinberg error
 * diffusion with reduced bleeding, '3' means dithering based on pixel
 * location ('Fixed' dithering).
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_image_convert_indexed (gint32                  image_ID,
                            GimpConvertDitherType   dither_type,
                            GimpConvertPaletteType  palette_type,
                            gint                    num_cols,
                            gboolean                alpha_dither,
                            gboolean                remove_unused,
                            const gchar            *palette)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-convert-indexed",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, dither_type,
                                    GIMP_PDB_INT32, palette_type,
                                    GIMP_PDB_INT32, num_cols,
                                    GIMP_PDB_INT32, alpha_dither,
                                    GIMP_PDB_INT32, remove_unused,
                                    GIMP_PDB_STRING, palette,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_convert_set_dither_matrix:
 * @width: Width of the matrix (0 to reset to default matrix).
 * @height: Height of the matrix (0 to reset to default matrix).
 * @matrix_length: The length of 'matrix'.
 * @matrix: The matrix -- all values must be >= 1.
 *
 * Set dither matrix for conversion to indexed
 *
 * This procedure sets the dither matrix used when converting images to
 * INDEXED mode with positional dithering.
 *
 * Returns: TRUE on success.
 *
 * Since: 2.4
 **/
gboolean
gimp_image_convert_set_dither_matrix (gint          width,
                                      gint          height,
                                      gint          matrix_length,
                                      const guint8 *matrix)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-convert-set-dither-matrix",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32, width,
                                    GIMP_PDB_INT32, height,
                                    GIMP_PDB_INT32, matrix_length,
                                    GIMP_PDB_INT8ARRAY, matrix,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_convert_precision:
 * @image_ID: The image.
 * @precision: The new precision.
 *
 * Convert the image to the specified precision
 *
 * This procedure converts the image to the specified precision. Note
 * that indexed images cannot be converted and are always in
 * GIMP_PRECISION_U8.
 *
 * Returns: TRUE on success.
 *
 * Since: 2.10
 **/
gboolean
gimp_image_convert_precision (gint32        image_ID,
                              GimpPrecision precision)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-convert-precision",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, precision,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}
