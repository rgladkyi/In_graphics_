/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gegl.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpconfig/gimpconfig.h"

#include "core-types.h"

#include "config/gimprc.h"

#include "gimp.h"
#include "gimp-data-factories.h"
#include "gimp-gradients.h"
#include "gimp-memsize.h"
#include "gimp-palettes.h"
#include "gimpcontainer.h"
#include "gimpbrush-load.h"
#include "gimpbrush.h"
#include "gimpbrushclipboard.h"
#include "gimpbrushgenerated-load.h"
#include "gimpbrushpipe-load.h"
#include "gimpdatafactory.h"
#include "gimpdynamics.h"
#include "gimpdynamics-load.h"
#include "gimpgradient-load.h"
#include "gimpgradient.h"
#include "gimpmybrush-load.h"
#include "gimpmybrush.h"
#include "gimppalette-load.h"
#include "gimppalette.h"
#include "gimppattern-load.h"
#include "gimppattern.h"
#include "gimppatternclipboard.h"
#include "gimptagcache.h"
#include "gimptoolpreset.h"
#include "gimptoolpreset-load.h"

#include "gimp-intl.h"


void
gimp_data_factories_init (Gimp *gimp)
{
  static const GimpDataFactoryLoaderEntry brush_loader_entries[] =
  {
    { gimp_brush_load,           GIMP_BRUSH_FILE_EXTENSION,           FALSE },
    { gimp_brush_load,           GIMP_BRUSH_PIXMAP_FILE_EXTENSION,    FALSE },
    { gimp_brush_load_abr,       GIMP_BRUSH_PS_FILE_EXTENSION,        FALSE },
    { gimp_brush_load_abr,       GIMP_BRUSH_PSP_FILE_EXTENSION,       FALSE },
    { gimp_brush_generated_load, GIMP_BRUSH_GENERATED_FILE_EXTENSION, TRUE  },
    { gimp_brush_pipe_load,      GIMP_BRUSH_PIPE_FILE_EXTENSION,      FALSE }
  };

  static const GimpDataFactoryLoaderEntry dynamics_loader_entries[] =
  {
    { gimp_dynamics_load,        GIMP_DYNAMICS_FILE_EXTENSION,        TRUE  }
  };

  static const GimpDataFactoryLoaderEntry mybrush_loader_entries[] =
  {
    { gimp_mybrush_load,         GIMP_MYBRUSH_FILE_EXTENSION,         FALSE }
  };

  static const GimpDataFactoryLoaderEntry pattern_loader_entries[] =
  {
    { gimp_pattern_load,         GIMP_PATTERN_FILE_EXTENSION,         FALSE },
    { gimp_pattern_load_pixbuf,  NULL /* fallback loader */,          FALSE }
  };

  static const GimpDataFactoryLoaderEntry gradient_loader_entries[] =
  {
    { gimp_gradient_load,        GIMP_GRADIENT_FILE_EXTENSION,        TRUE  },
    { gimp_gradient_load_svg,    GIMP_GRADIENT_SVG_FILE_EXTENSION,    FALSE }
  };

  static const GimpDataFactoryLoaderEntry palette_loader_entries[] =
  {
    { gimp_palette_load,         GIMP_PALETTE_FILE_EXTENSION,         TRUE  }
  };

  static const GimpDataFactoryLoaderEntry tool_preset_loader_entries[] =
  {
    { gimp_tool_preset_load,     GIMP_TOOL_PRESET_FILE_EXTENSION,     TRUE  }
  };

  g_return_if_fail (GIMP_IS_GIMP (gimp));

  gimp->brush_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_BRUSH,
                           "brush-path", "brush-path-writable",
                           brush_loader_entries,
                           G_N_ELEMENTS (brush_loader_entries),
                           gimp_brush_new,
                           gimp_brush_get_standard);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->brush_factory),
                               "brush factory");

  gimp->dynamics_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_DYNAMICS,
                           "dynamics-path", "dynamics-path-writable",
                           dynamics_loader_entries,
                           G_N_ELEMENTS (dynamics_loader_entries),
                           gimp_dynamics_new,
                           gimp_dynamics_get_standard);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->dynamics_factory),
                               "dynamics factory");

  gimp->mybrush_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_MYBRUSH,
                           "mypaint-brush-path", "mypaint-brush-path-writable",
                           mybrush_loader_entries,
                           G_N_ELEMENTS (mybrush_loader_entries),
                           NULL,
                           NULL);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->mybrush_factory),
                               "mypaint brush factory");

  gimp->pattern_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_PATTERN,
                           "pattern-path", "pattern-path-writable",
                           pattern_loader_entries,
                           G_N_ELEMENTS (pattern_loader_entries),
                           NULL,
                           gimp_pattern_get_standard);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->pattern_factory),
                               "pattern factory");

  gimp->gradient_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_GRADIENT,
                           "gradient-path", "gradient-path-writable",
                           gradient_loader_entries,
                           G_N_ELEMENTS (gradient_loader_entries),
                           gimp_gradient_new,
                           gimp_gradient_get_standard);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->gradient_factory),
                               "gradient factory");

  gimp->palette_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_PALETTE,
                           "palette-path", "palette-path-writable",
                           palette_loader_entries,
                           G_N_ELEMENTS (palette_loader_entries),
                           gimp_palette_new,
                           gimp_palette_get_standard);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->palette_factory),
                               "palette factory");

  gimp->tool_preset_factory =
    gimp_data_factory_new (gimp,
                           GIMP_TYPE_TOOL_PRESET,
                           "tool-preset-path", "tool-preset-path-writable",
                           tool_preset_loader_entries,
                           G_N_ELEMENTS (tool_preset_loader_entries),
                           gimp_tool_preset_new,
                           NULL);
  gimp_object_set_static_name (GIMP_OBJECT (gimp->tool_preset_factory),
                               "tool preset factory");

  gimp->tag_cache = gimp_tag_cache_new ();
}

void
gimp_data_factories_add_builtin (Gimp *gimp)
{
  GimpData *clipboard_brush;
  GimpData *clipboard_pattern;

  g_return_if_fail (GIMP_IS_GIMP (gimp));

  /*  add the builtin FG -> BG etc. gradients  */
  gimp_gradients_init (gimp);

  /*  add the color history palette  */
  gimp_palettes_init (gimp);

  /*  add the clipboard brush  */
  clipboard_brush = gimp_brush_clipboard_new (gimp);
  gimp_data_make_internal (GIMP_DATA (clipboard_brush),
                           "gimp-brush-clipboard");
  gimp_container_add (gimp_data_factory_get_container (gimp->brush_factory),
                      GIMP_OBJECT (clipboard_brush));
  g_object_unref (clipboard_brush);

  /*  add the clipboard pattern  */
  clipboard_pattern = gimp_pattern_clipboard_new (gimp);
  gimp_data_make_internal (GIMP_DATA (clipboard_pattern),
                           "gimp-pattern-clipboard");
  gimp_container_add (gimp_data_factory_get_container (gimp->pattern_factory),
                      GIMP_OBJECT (clipboard_pattern));
  g_object_unref (clipboard_pattern);
}

void
gimp_data_factories_clear (Gimp *gimp)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

  if (gimp->brush_factory)
    gimp_data_factory_data_free (gimp->brush_factory);

  if (gimp->dynamics_factory)
    gimp_data_factory_data_free (gimp->dynamics_factory);

  if (gimp->mybrush_factory)
    gimp_data_factory_data_free (gimp->mybrush_factory);

  if (gimp->pattern_factory)
    gimp_data_factory_data_free (gimp->pattern_factory);

  if (gimp->gradient_factory)
    gimp_data_factory_data_free (gimp->gradient_factory);

  if (gimp->palette_factory)
    gimp_data_factory_data_free (gimp->palette_factory);

  if (gimp->tool_preset_factory)
    gimp_data_factory_data_free (gimp->tool_preset_factory);
}

void
gimp_data_factories_exit (Gimp *gimp)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

  if (gimp->brush_factory)
    {
      g_object_unref (gimp->brush_factory);
      gimp->brush_factory = NULL;
    }

  if (gimp->dynamics_factory)
    {
      g_object_unref (gimp->dynamics_factory);
      gimp->dynamics_factory = NULL;
    }

  if (gimp->mybrush_factory)
    {
      g_object_unref (gimp->mybrush_factory);
      gimp->mybrush_factory = NULL;
    }

  if (gimp->pattern_factory)
    {
      g_object_unref (gimp->pattern_factory);
      gimp->pattern_factory = NULL;
    }

  if (gimp->gradient_factory)
    {
      g_object_unref (gimp->gradient_factory);
      gimp->gradient_factory = NULL;
    }

  if (gimp->palette_factory)
    {
      g_object_unref (gimp->palette_factory);
      gimp->palette_factory = NULL;
    }

  if (gimp->tool_preset_factory)
    {
      g_object_unref (gimp->tool_preset_factory);
      gimp->tool_preset_factory = NULL;
    }

  if (gimp->tag_cache)
    {
      g_object_unref (gimp->tag_cache);
      gimp->tag_cache = NULL;
    }
}

gint64
gimp_data_factories_get_memsize (Gimp   *gimp,
                                 gint64 *gui_size)
{
  gint64 memsize = 0;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), 0);

  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->named_buffers),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->fonts),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->brush_factory),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->dynamics_factory),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->mybrush_factory),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->pattern_factory),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->gradient_factory),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->palette_factory),
                                      gui_size);
  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->tool_preset_factory),
                                      gui_size);

  memsize += gimp_object_get_memsize (GIMP_OBJECT (gimp->tag_cache),
                                      gui_size);

  return memsize;
}

void
gimp_data_factories_data_clean (Gimp *gimp)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

  gimp_data_factory_data_clean (gimp->brush_factory);
  gimp_data_factory_data_clean (gimp->dynamics_factory);
  gimp_data_factory_data_clean (gimp->mybrush_factory);
  gimp_data_factory_data_clean (gimp->pattern_factory);
  gimp_data_factory_data_clean (gimp->palette_factory);
  gimp_data_factory_data_clean (gimp->gradient_factory);
  gimp_data_factory_data_clean (gimp->tool_preset_factory);
}

void
gimp_data_factories_load (Gimp               *gimp,
                          GimpInitStatusFunc  status_callback)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

  /*  initialize the list of gimp brushes    */
  status_callback (NULL, _("Brushes"), 0.1);
  gimp_data_factory_data_init (gimp->brush_factory, gimp->user_context,
                               gimp->no_data);

  /*  initialize the list of gimp dynamics   */
  status_callback (NULL, _("Dynamics"), 0.15);
  gimp_data_factory_data_init (gimp->dynamics_factory, gimp->user_context,
                               gimp->no_data);

  /*  initialize the list of mypaint brushes    */
  status_callback (NULL, _("MyPaint Brushes"), 0.2);
  gimp_data_factory_data_init (gimp->mybrush_factory, gimp->user_context,
                               gimp->no_data);

  /*  initialize the list of gimp patterns   */
  status_callback (NULL, _("Patterns"), 0.3);
  gimp_data_factory_data_init (gimp->pattern_factory, gimp->user_context,
                               gimp->no_data);

  /*  initialize the list of gimp palettes   */
  status_callback (NULL, _("Palettes"), 0.4);
  gimp_data_factory_data_init (gimp->palette_factory, gimp->user_context,
                               gimp->no_data);

  /*  initialize the list of gimp gradients  */
  status_callback (NULL, _("Gradients"), 0.5);
  gimp_data_factory_data_init (gimp->gradient_factory, gimp->user_context,
                               gimp->no_data);

  /*  initialize the color history   */
  status_callback (NULL, _("Color History"), 0.55);
  gimp_palettes_load (gimp);

  /*  initialize the list of gimp tool presets if we have a GUI  */
  if (! gimp->no_interface)
    {
      status_callback (NULL, _("Tool Presets"), 0.6);
      gimp_data_factory_data_init (gimp->tool_preset_factory, gimp->user_context,
                                   gimp->no_data);
    }

  /* update tag cache */
  status_callback (NULL, _("Updating tag cache"), 0.65);
  gimp_tag_cache_load (gimp->tag_cache);
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->brush_factory));
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->dynamics_factory));
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->mybrush_factory));
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->pattern_factory));
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->gradient_factory));
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->palette_factory));
  gimp_tag_cache_add_container (gimp->tag_cache,
                                gimp_data_factory_get_container (gimp->tool_preset_factory));
}

void
gimp_data_factories_save (Gimp *gimp)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

  gimp_tag_cache_save (gimp->tag_cache);

  gimp_data_factory_data_save (gimp->brush_factory);
  gimp_data_factory_data_save (gimp->dynamics_factory);
  gimp_data_factory_data_save (gimp->mybrush_factory);
  gimp_data_factory_data_save (gimp->pattern_factory);
  gimp_data_factory_data_save (gimp->gradient_factory);
  gimp_data_factory_data_save (gimp->palette_factory);
  gimp_data_factory_data_save (gimp->tool_preset_factory);

  gimp_palettes_save (gimp);
}
