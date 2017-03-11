/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
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

#include <gegl.h>
#include <gtk/gtk.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "actions-types.h"

#include "operations/layer-modes/gimp-layer-modes.h"

#include "core/gimpchannel.h"
#include "core/gimpimage.h"
#include "core/gimplayer.h"
#include "core/gimplayer-floating-selection.h"

#include "text/gimptextlayer.h"

#include "widgets/gimphelp-ids.h"
#include "widgets/gimpactiongroup.h"
#include "widgets/gimpwidgets-utils.h"

#include "actions.h"
#include "image-commands.h"
#include "items-actions.h"
#include "layers-actions.h"
#include "layers-commands.h"

#include "gimp-intl.h"


static const GimpActionEntry layers_actions[] =
{
  { "layers-popup", GIMP_ICON_DIALOG_LAYERS,
    NC_("layers-action", "Layers Menu"), NULL, NULL, NULL,
    GIMP_HELP_LAYER_DIALOG },

  { "layers-blend-space-menu", NULL,
    NC_("layers-action", "Blend Space"), NULL, NULL, NULL,
    NULL },

  { "layers-composite-space-menu", NULL,
    NC_("layers-action", "Composite Space"), NULL, NULL, NULL,
    NULL },

  { "layers-composite-mode-menu", NULL,
    NC_("layers-action", "Composite Mode"), NULL, NULL, NULL,
    NULL },

  { "layers-color-tag-menu", GIMP_ICON_CLOSE /* abused */,
    NC_("layers-action", "Color Tag"), NULL, NULL, NULL,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-menu",                   NULL,
    NC_("layers-action", "_Layer")        },
  { "layers-stack-menu",             NULL,
    NC_("layers-action", "Stac_k")        },
  { "layers-mask-menu",              NULL,
    NC_("layers-action", "_Mask")         },
  { "layers-transparency-menu",      NULL,
    NC_("layers-action", "Tr_ansparency") },
  { "layers-transform-menu",         NULL,
    NC_("layers-action", "_Transform")    },
  { "layers-properties-menu",        GIMP_ICON_DOCUMENT_PROPERTIES,
    NC_("layers-action", "_Properties")   },
  { "layers-opacity-menu",           GIMP_ICON_TRANSPARENCY,
    NC_("layers-action", "_Opacity")      },
  { "layers-mode-menu",              GIMP_ICON_TOOL_PENCIL,
    NC_("layers-action", "Layer _Mode")   },

  { "layers-text-tool", GIMP_ICON_TOOL_TEXT,
    NC_("layers-action", "Te_xt Tool"), NULL,
    NC_("layers-action", "Activate the text tool on this text layer"),
    G_CALLBACK (layers_text_tool_cmd_callback),
    GIMP_HELP_TOOL_TEXT },

  { "layers-edit-attributes", GIMP_ICON_EDIT,
    NC_("layers-action", "_Edit Layer Attributes..."), NULL,
    NC_("layers-action", "Edit the layer's name"),
    G_CALLBACK (layers_edit_attributes_cmd_callback),
    GIMP_HELP_LAYER_EDIT },

  { "layers-new", GIMP_ICON_DOCUMENT_NEW,
    NC_("layers-action", "_New Layer..."), "<primary><shift>N",
    NC_("layers-action", "Create a new layer and add it to the image"),
    G_CALLBACK (layers_new_cmd_callback),
    GIMP_HELP_LAYER_NEW },

  { "layers-new-last-values", GIMP_ICON_DOCUMENT_NEW,
    NC_("layers-action", "_New Layer"), NULL,
    NC_("layers-action", "Create a new layer with last used values"),
    G_CALLBACK (layers_new_last_vals_cmd_callback),
    GIMP_HELP_LAYER_NEW },

  { "layers-new-from-visible", NULL,
    NC_("layers-action", "New from _Visible"), NULL,
    NC_("layers-action",
        "Create a new layer from what is visible in this image"),
    G_CALLBACK (layers_new_from_visible_cmd_callback),
    GIMP_HELP_LAYER_NEW_FROM_VISIBLE },

  { "layers-new-group", GIMP_ICON_FOLDER_NEW,
    NC_("layers-action", "New Layer _Group"), NULL,
    NC_("layers-action", "Create a new layer group and add it to the image"),
    G_CALLBACK (layers_new_group_cmd_callback),
    GIMP_HELP_LAYER_NEW },

  { "layers-duplicate", GIMP_ICON_OBJECT_DUPLICATE,
    NC_("layers-action", "D_uplicate Layer"), "<primary><shift>D",
    NC_("layers-action",
        "Create a duplicate of the layer and add it to the image"),
    G_CALLBACK (layers_duplicate_cmd_callback),
    GIMP_HELP_LAYER_DUPLICATE },

  { "layers-delete", GIMP_ICON_EDIT_DELETE,
    NC_("layers-action", "_Delete Layer"), NULL,
    NC_("layers-action", "Delete this layer"),
    G_CALLBACK (layers_delete_cmd_callback),
    GIMP_HELP_LAYER_DELETE },

  { "layers-raise", GIMP_ICON_GO_UP,
    NC_("layers-action", "_Raise Layer"), NULL,
    NC_("layers-action", "Raise this layer one step in the layer stack"),
    G_CALLBACK (layers_raise_cmd_callback),
    GIMP_HELP_LAYER_RAISE },

  { "layers-raise-to-top", GIMP_ICON_GO_TOP,
    NC_("layers-action", "Layer to _Top"), NULL,
    NC_("layers-action", "Move this layer to the top of the layer stack"),
    G_CALLBACK (layers_raise_to_top_cmd_callback),
    GIMP_HELP_LAYER_RAISE_TO_TOP },

  { "layers-lower", GIMP_ICON_GO_DOWN,
    NC_("layers-action", "_Lower Layer"), NULL,
    NC_("layers-action", "Lower this layer one step in the layer stack"),
    G_CALLBACK (layers_lower_cmd_callback),
    GIMP_HELP_LAYER_LOWER },

  { "layers-lower-to-bottom", GIMP_ICON_GO_BOTTOM,
    NC_("layers-action", "Layer to _Bottom"), NULL,
    NC_("layers-action", "Move this layer to the bottom of the layer stack"),
    G_CALLBACK (layers_lower_to_bottom_cmd_callback),
    GIMP_HELP_LAYER_LOWER_TO_BOTTOM },

  { "layers-anchor", GIMP_ICON_LAYER_ANCHOR,
    NC_("layers-action", "_Anchor Layer"), "<primary>H",
    NC_("layers-action", "Anchor the floating layer"),
    G_CALLBACK (layers_anchor_cmd_callback),
    GIMP_HELP_LAYER_ANCHOR },

  { "layers-merge-down", GIMP_ICON_LAYER_MERGE_DOWN,
    NC_("layers-action", "Merge Do_wn"), NULL,
    NC_("layers-action", "Merge this layer with the first visible layer below it"),
    G_CALLBACK (layers_merge_down_cmd_callback),
    GIMP_HELP_LAYER_MERGE_DOWN },

  { "layers-merge-group", NULL,
    NC_("layers-action", "Merge Layer Group"), NULL,
    NC_("layers-action", "Merge the layer group's layers into one normal layer"),
    G_CALLBACK (layers_merge_group_cmd_callback),
    GIMP_HELP_LAYER_MERGE_GROUP },

  { "layers-merge-layers", NULL,
    NC_("layers-action", "Merge _Visible Layers..."), NULL,
    NC_("layers-action", "Merge all visible layers into one layer"),
    G_CALLBACK (image_merge_layers_cmd_callback),
    GIMP_HELP_IMAGE_MERGE_LAYERS },

  { "layers-flatten-image", NULL,
    NC_("layers-action", "_Flatten Image"), NULL,
    NC_("layers-action", "Merge all layers into one and remove transparency"),
    G_CALLBACK (image_flatten_image_cmd_callback),
    GIMP_HELP_IMAGE_FLATTEN },

  { "layers-text-discard", GIMP_ICON_TOOL_TEXT,
    NC_("layers-action", "_Discard Text Information"), NULL,
    NC_("layers-action", "Turn this text layer into a normal layer"),
    G_CALLBACK (layers_text_discard_cmd_callback),
    GIMP_HELP_LAYER_TEXT_DISCARD },

  { "layers-text-to-vectors", GIMP_ICON_TOOL_TEXT,
    NC_("layers-action", "Text to _Path"), NULL,
    NC_("layers-action", "Create a path from this text layer"),
    G_CALLBACK (layers_text_to_vectors_cmd_callback),
    GIMP_HELP_LAYER_TEXT_TO_PATH },

  { "layers-text-along-vectors", GIMP_ICON_TOOL_TEXT,
    NC_("layers-action", "Text alon_g Path"), NULL,
    NC_("layers-action", "Warp this layer's text along the current path"),
    G_CALLBACK (layers_text_along_vectors_cmd_callback),
    GIMP_HELP_LAYER_TEXT_ALONG_PATH },

  { "layers-resize", GIMP_ICON_OBJECT_RESIZE,
    NC_("layers-action", "Layer B_oundary Size..."), NULL,
    NC_("layers-action", "Adjust the layer dimensions"),
    G_CALLBACK (layers_resize_cmd_callback),
    GIMP_HELP_LAYER_RESIZE },

  { "layers-resize-to-image", GIMP_ICON_LAYER_TO_IMAGESIZE,
    NC_("layers-action", "Layer to _Image Size"), NULL,
    NC_("layers-action", "Resize the layer to the size of the image"),
    G_CALLBACK (layers_resize_to_image_cmd_callback),
    GIMP_HELP_LAYER_RESIZE_TO_IMAGE },

  { "layers-scale", GIMP_ICON_OBJECT_SCALE,
    NC_("layers-action", "_Scale Layer..."), NULL,
    NC_("layers-action", "Change the size of the layer content"),
    G_CALLBACK (layers_scale_cmd_callback),
    GIMP_HELP_LAYER_SCALE },

  { "layers-crop-to-selection", GIMP_ICON_TOOL_CROP,
    NC_("layers-action", "_Crop to Selection"), NULL,
    NC_("layers-action", "Crop the layer to the extents of the selection"),
    G_CALLBACK (layers_crop_to_selection_cmd_callback),
    GIMP_HELP_LAYER_CROP },

  { "layers-crop-to-content", GIMP_ICON_TOOL_CROP,
    NC_("layers-action", "Crop to C_ontent"), NULL,
    NC_("layers-action", "Crop the layer to the extents of its content (remove empty borders from the layer)"),
    G_CALLBACK (layers_crop_to_content_cmd_callback),
    GIMP_HELP_LAYER_CROP },

  { "layers-mask-add", GIMP_ICON_LAYER_MASK,
    NC_("layers-action", "Add La_yer Mask..."), NULL,
    NC_("layers-action",
        "Add a mask that allows non-destructive editing of transparency"),
    G_CALLBACK (layers_mask_add_cmd_callback),
    GIMP_HELP_LAYER_MASK_ADD },

  /* this is the same as layers-mask-add, except it's sensitive even if
   * there is a mask on the layer
   */
  { "layers-mask-add-button", GIMP_ICON_LAYER_MASK,
    NC_("layers-action", "Add La_yer Mask..."), NULL,
    NC_("layers-action",
        "Add a mask that allows non-destructive editing of transparency"),
    G_CALLBACK (layers_mask_add_cmd_callback),
    GIMP_HELP_LAYER_MASK_ADD },

  { "layers-mask-add-last-values", GIMP_ICON_LAYER_MASK,
    NC_("layers-action", "Add La_yer Mask"), NULL,
    NC_("layers-action",
        "Add a mask with last used values"),
    G_CALLBACK (layers_mask_add_last_vals_cmd_callback),
    GIMP_HELP_LAYER_MASK_ADD },

  { "layers-alpha-add", GIMP_ICON_TRANSPARENCY,
    NC_("layers-action", "Add Alpha C_hannel"), NULL,
    NC_("layers-action", "Add transparency information to the layer"),
    G_CALLBACK (layers_alpha_add_cmd_callback),
    GIMP_HELP_LAYER_ALPHA_ADD },

  { "layers-alpha-remove", NULL,
    NC_("layers-action", "_Remove Alpha Channel"), NULL,
    NC_("layers-action", "Remove transparency information from the layer"),
    G_CALLBACK (layers_alpha_remove_cmd_callback),
    GIMP_HELP_LAYER_ALPHA_REMOVE }
};

static const GimpToggleActionEntry layers_toggle_actions[] =
{
  { "layers-mask-edit", GIMP_ICON_EDIT,
    NC_("layers-action", "_Edit Layer Mask"), NULL,
    NC_("layers-action", "Work on the layer mask"),
    G_CALLBACK (layers_mask_edit_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_MASK_EDIT },

  { "layers-mask-show", GIMP_ICON_VISIBLE,
    NC_("layers-action", "S_how Layer Mask"), NULL, NULL,
    G_CALLBACK (layers_mask_show_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_MASK_SHOW },

  { "layers-mask-disable", NULL,
    NC_("layers-action", "_Disable Layer Mask"), NULL,
    NC_("layers-action", "Dismiss the effect of the layer mask"),
    G_CALLBACK (layers_mask_disable_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_MASK_DISABLE },

  { "layers-visible", GIMP_ICON_VISIBLE,
    NC_("layers-action", "_Visible"), NULL, NULL,
    G_CALLBACK (layers_visible_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_VISIBLE },

  { "layers-linked", GIMP_ICON_LINKED,
    NC_("layers-action", "_Linked"), NULL, NULL,
    G_CALLBACK (layers_linked_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_LINKED },

  { "layers-lock-content", NULL /* GIMP_ICON_LOCK */,
    NC_("layers-action", "L_ock pixels"), NULL, NULL,
    G_CALLBACK (layers_lock_content_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_LOCK_PIXELS },

  { "layers-lock-position", GIMP_ICON_TOOL_MOVE,
    NC_("layers-action", "L_ock position"), NULL, NULL,
    G_CALLBACK (layers_lock_position_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_LOCK_POSITION },

  { "layers-lock-alpha", GIMP_ICON_TRANSPARENCY,
    NC_("layers-action", "Lock Alph_a Channel"), NULL,
    NC_("layers-action",
        "Keep transparency information on this layer from being modified"),
    G_CALLBACK (layers_lock_alpha_cmd_callback),
    FALSE,
    GIMP_HELP_LAYER_LOCK_ALPHA },
};

static const GimpRadioActionEntry layers_blend_space_actions[] =
{
  { "layers-blend-space-auto", NULL,
    NC_("layers-action", "Auto"), NULL, NULL,
    GIMP_LAYER_COLOR_SPACE_AUTO,
    NULL },

  { "layers-blend-space-rgb-linear", NULL,
    NC_("layers-action", "RGB (linear)"), NULL, NULL,
    GIMP_LAYER_COLOR_SPACE_RGB_LINEAR,
    NULL },

  { "layers-blend-space-rgb-perceptual", NULL,
    NC_("layers-action", "RGB (perceptual)"), NULL, NULL,
    GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL,
    NULL }
};

static const GimpRadioActionEntry layers_composite_space_actions[] =
{
  { "layers-composite-space-auto", NULL,
    NC_("layers-action", "Auto"), NULL, NULL,
    GIMP_LAYER_COLOR_SPACE_AUTO,
    NULL },

  { "layers-composite-space-rgb-linear", NULL,
    NC_("layers-action", "RGB (linear)"), NULL, NULL,
    GIMP_LAYER_COLOR_SPACE_RGB_LINEAR,
    NULL },

  { "layers-composite-space-rgb-perceptual", NULL,
    NC_("layers-action", "RGB (perceptual)"), NULL, NULL,
    GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL,
    NULL }
};

static const GimpRadioActionEntry layers_composite_mode_actions[] =
{
  { "layers-composite-mode-auto", NULL,
    NC_("layers-action", "Auto"), NULL, NULL,
    GIMP_LAYER_COMPOSITE_AUTO,
    NULL },

  { "layers-composite-mode-src-over", NULL,
    NC_("layers-action", "Source over"), NULL, NULL,
    GIMP_LAYER_COMPOSITE_SRC_OVER,
    NULL },

  { "layers-composite-mode-src-atop", NULL,
    NC_("layers-action", "Source atop"), NULL, NULL,
    GIMP_LAYER_COMPOSITE_SRC_ATOP,
    NULL },

  { "layers-composite-mode-src-in", NULL,
    NC_("layers-action", "Source in"), NULL, NULL,
    GIMP_LAYER_COMPOSITE_SRC_IN,
    NULL },

  { "layers-composite-mode-dst-atop", NULL,
    NC_("layers-action", "Destination atop"), NULL, NULL,
    GIMP_LAYER_COMPOSITE_DST_ATOP,
    NULL }
};

static const GimpEnumActionEntry layers_color_tag_actions[] =
{
  { "layers-color-tag-none", GIMP_ICON_CLOSE /* abused */,
    NC_("layers-action", "None"), NULL,
    NC_("layers-action", "Clear color tag"),
    GIMP_COLOR_TAG_NONE, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-blue", NULL,
    NC_("layers-action", "Blue"), NULL,
    NC_("layers-action", "Set color tag to blue"),
    GIMP_COLOR_TAG_BLUE, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-green", NULL,
    NC_("layers-action", "Green"), NULL,
    NC_("layers-action", "Set color tag to green"),
    GIMP_COLOR_TAG_GREEN, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-yellow", NULL,
    NC_("layers-action", "Yellow"), NULL,
    NC_("layers-action", "Set color tag to yellow"),
    GIMP_COLOR_TAG_YELLOW, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-orange", NULL,
    NC_("layers-action", "Orange"), NULL,
    NC_("layers-action", "Set color tag to orange"),
    GIMP_COLOR_TAG_ORANGE, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-brown", NULL,
    NC_("layers-action", "Brown"), NULL,
    NC_("layers-action", "Set color tag to brown"),
    GIMP_COLOR_TAG_BROWN, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-red", NULL,
    NC_("layers-action", "Red"), NULL,
    NC_("layers-action", "Set color tag to red"),
    GIMP_COLOR_TAG_RED, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-violet", NULL,
    NC_("layers-action", "Violet"), NULL,
    NC_("layers-action", "Set color tag to violet"),
    GIMP_COLOR_TAG_VIOLET, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG },

  { "layers-color-tag-gray", NULL,
    NC_("layers-action", "Gray"), NULL,
    NC_("layers-action", "Set color tag to gray"),
    GIMP_COLOR_TAG_GRAY, FALSE,
    GIMP_HELP_LAYER_COLOR_TAG }
};

static const GimpEnumActionEntry layers_mask_apply_actions[] =
{
  { "layers-mask-apply", NULL,
    NC_("layers-action", "Apply Layer _Mask"), NULL,
    NC_("layers-action", "Apply the effect of the layer mask and remove it"),
    GIMP_MASK_APPLY, FALSE,
    GIMP_HELP_LAYER_MASK_APPLY },

  { "layers-mask-delete", GIMP_ICON_EDIT_DELETE,
    NC_("layers-action", "Delete Layer Mas_k"), NULL,
    NC_("layers-action", "Remove the layer mask and its effect"),
    GIMP_MASK_DISCARD, FALSE,
    GIMP_HELP_LAYER_MASK_DELETE }
};

static const GimpEnumActionEntry layers_mask_to_selection_actions[] =
{
  { "layers-mask-selection-replace", GIMP_ICON_SELECTION_REPLACE,
    NC_("layers-action", "_Mask to Selection"), NULL,
    NC_("layers-action", "Replace the selection with the layer mask"),
    GIMP_CHANNEL_OP_REPLACE, FALSE,
    GIMP_HELP_LAYER_MASK_SELECTION_REPLACE },

  { "layers-mask-selection-add", GIMP_ICON_SELECTION_ADD,
    NC_("layers-action", "_Add to Selection"), NULL,
    NC_("layers-action", "Add the layer mask to the current selection"),
    GIMP_CHANNEL_OP_ADD, FALSE,
    GIMP_HELP_LAYER_MASK_SELECTION_ADD },

  { "layers-mask-selection-subtract", GIMP_ICON_SELECTION_SUBTRACT,
    NC_("layers-action", "_Subtract from Selection"), NULL,
    NC_("layers-action", "Subtract the layer mask from the current selection"),
    GIMP_CHANNEL_OP_SUBTRACT, FALSE,
    GIMP_HELP_LAYER_MASK_SELECTION_SUBTRACT },

  { "layers-mask-selection-intersect", GIMP_ICON_SELECTION_INTERSECT,
    NC_("layers-action", "_Intersect with Selection"), NULL,
    NC_("layers-action", "Intersect the layer mask with the current selection"),
    GIMP_CHANNEL_OP_INTERSECT, FALSE,
    GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT }
};

static const GimpEnumActionEntry layers_alpha_to_selection_actions[] =
{
  { "layers-alpha-selection-replace", GIMP_ICON_SELECTION_REPLACE,
    NC_("layers-action", "Al_pha to Selection"), NULL,
    NC_("layers-action",
        "Replace the selection with the layer's alpha channel"),
    GIMP_CHANNEL_OP_REPLACE, FALSE,
    GIMP_HELP_LAYER_ALPHA_SELECTION_REPLACE },

  { "layers-alpha-selection-add", GIMP_ICON_SELECTION_ADD,
    NC_("layers-action", "A_dd to Selection"), NULL,
    NC_("layers-action",
        "Add the layer's alpha channel to the current selection"),
    GIMP_CHANNEL_OP_ADD, FALSE,
    GIMP_HELP_LAYER_ALPHA_SELECTION_ADD },

  { "layers-alpha-selection-subtract", GIMP_ICON_SELECTION_SUBTRACT,
    NC_("layers-action", "_Subtract from Selection"), NULL,
    NC_("layers-action",
        "Subtract the layer's alpha channel from the current selection"),
    GIMP_CHANNEL_OP_SUBTRACT, FALSE,
    GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT },

  { "layers-alpha-selection-intersect", GIMP_ICON_SELECTION_INTERSECT,
    NC_("layers-action", "_Intersect with Selection"), NULL,
    NC_("layers-action",
        "Intersect the layer's alpha channel with the current selection"),
    GIMP_CHANNEL_OP_INTERSECT, FALSE,
    GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT }
};

static const GimpEnumActionEntry layers_select_actions[] =
{
  { "layers-select-top", NULL,
    NC_("layers-action", "Select _Top Layer"), "Home",
    NC_("layers-action", "Select the topmost layer"),
    GIMP_ACTION_SELECT_FIRST, FALSE,
    GIMP_HELP_LAYER_TOP },

  { "layers-select-bottom", NULL,
    NC_("layers-action", "Select _Bottom Layer"), "End",
    NC_("layers-action", "Select the bottommost layer"),
    GIMP_ACTION_SELECT_LAST, FALSE,
    GIMP_HELP_LAYER_BOTTOM },

  { "layers-select-previous", NULL,
    NC_("layers-action", "Select _Previous Layer"), "Prior",
    NC_("layers-action", "Select the layer above the current layer"),
    GIMP_ACTION_SELECT_PREVIOUS, FALSE,
    GIMP_HELP_LAYER_PREVIOUS },

  { "layers-select-next", NULL,
    NC_("layers-action", "Select _Next Layer"), "Next",
    NC_("layers-action", "Select the layer below the current layer"),
    GIMP_ACTION_SELECT_NEXT, FALSE,
    GIMP_HELP_LAYER_NEXT }
};

static const GimpEnumActionEntry layers_opacity_actions[] =
{
  { "layers-opacity-set", GIMP_ICON_TRANSPARENCY,
    "Set Opacity", NULL, NULL,
    GIMP_ACTION_SELECT_SET, TRUE,
    GIMP_HELP_LAYER_OPACITY },
  { "layers-opacity-transparent", GIMP_ICON_TRANSPARENCY,
    "Completely Transparent", NULL, NULL,
    GIMP_ACTION_SELECT_FIRST, FALSE,
    GIMP_HELP_LAYER_OPACITY },
  { "layers-opacity-opaque", GIMP_ICON_TRANSPARENCY,
    "Completely Opaque", NULL, NULL,
    GIMP_ACTION_SELECT_LAST, FALSE,
    GIMP_HELP_LAYER_OPACITY },
  { "layers-opacity-decrease", GIMP_ICON_TRANSPARENCY,
    "More Transparent", NULL, NULL,
    GIMP_ACTION_SELECT_PREVIOUS, FALSE,
    GIMP_HELP_LAYER_OPACITY },
  { "layers-opacity-increase", GIMP_ICON_TRANSPARENCY,
    "More Opaque", NULL, NULL,
    GIMP_ACTION_SELECT_NEXT, FALSE,
    GIMP_HELP_LAYER_OPACITY },
  { "layers-opacity-decrease-skip", GIMP_ICON_TRANSPARENCY,
    "10% More Transparent", NULL, NULL,
    GIMP_ACTION_SELECT_SKIP_PREVIOUS, FALSE,
    GIMP_HELP_LAYER_OPACITY },
  { "layers-opacity-increase-skip", GIMP_ICON_TRANSPARENCY,
    "10% More Opaque", NULL, NULL,
    GIMP_ACTION_SELECT_SKIP_NEXT, FALSE,
    GIMP_HELP_LAYER_OPACITY }
};

static const GimpEnumActionEntry layers_mode_actions[] =
{
  { "layers-mode-first", GIMP_ICON_TOOL_PENCIL,
    "First Layer Mode", NULL, NULL,
    GIMP_ACTION_SELECT_FIRST, FALSE,
    GIMP_HELP_LAYER_MODE },
  { "layers-mode-last", GIMP_ICON_TOOL_PENCIL,
    "Last Layer Mode", NULL, NULL,
    GIMP_ACTION_SELECT_LAST, FALSE,
    GIMP_HELP_LAYER_MODE },
  { "layers-mode-previous", GIMP_ICON_TOOL_PENCIL,
    "Previous Layer Mode", NULL, NULL,
    GIMP_ACTION_SELECT_PREVIOUS, FALSE,
    GIMP_HELP_LAYER_MODE },
  { "layers-mode-next", GIMP_ICON_TOOL_PENCIL,
    "Next Layer Mode", NULL, NULL,
    GIMP_ACTION_SELECT_NEXT, FALSE,
    GIMP_HELP_LAYER_MODE }
};

/**
 * layers_actions_fix_tooltip:
 * @group:
 * @action:
 * @modifiers:
 *
 * Make layer alpha to selection click-shortcuts discoverable, at
 * least in theory.
 **/
static void
layers_actions_fix_tooltip (GimpActionGroup *group,
                            const gchar     *action,
                            GdkModifierType  modifiers)
{
  const gchar *old_hint;
  gchar       *new_hint;

  old_hint = gimp_action_group_get_action_tooltip (group,
                                                   action);
  new_hint = g_strconcat (old_hint,
                          "\n",
                          /* Will be followed with e.g. "Shift-Click
                             on thumbnail"
                           */
                          _("Shortcut: "),
                          gimp_get_mod_string (modifiers),
                          /* Will be prepended with a modifier key
                             string, e.g. "Shift"
                           */
                          _("-Click on thumbnail in Layers dockable"),
                          NULL);

  gimp_action_group_set_action_tooltip (group, action, new_hint);
  g_free (new_hint);
}

void
layers_actions_setup (GimpActionGroup *group)
{
  GdkDisplay      *display = gdk_display_get_default ();
  GdkModifierType  extend_mask;
  GdkModifierType  modify_mask;

  extend_mask =
    gdk_keymap_get_modifier_mask (gdk_keymap_get_for_display (display),
                                  GDK_MODIFIER_INTENT_EXTEND_SELECTION);
  modify_mask =
    gdk_keymap_get_modifier_mask (gdk_keymap_get_for_display (display),
                                  GDK_MODIFIER_INTENT_MODIFY_SELECTION);

  gimp_action_group_add_actions (group, "layers-action",
                                 layers_actions,
                                 G_N_ELEMENTS (layers_actions));

  gimp_action_group_add_toggle_actions (group, "layers-action",
                                        layers_toggle_actions,
                                        G_N_ELEMENTS (layers_toggle_actions));

  gimp_action_group_add_radio_actions (group, "layers-action",
                                       layers_blend_space_actions,
                                       G_N_ELEMENTS (layers_blend_space_actions),
                                       NULL, 0,
                                       G_CALLBACK (layers_blend_space_cmd_callback));

  gimp_action_group_add_radio_actions (group, "layers-action",
                                       layers_composite_space_actions,
                                       G_N_ELEMENTS (layers_composite_space_actions),
                                       NULL, 0,
                                       G_CALLBACK (layers_composite_space_cmd_callback));

  gimp_action_group_add_radio_actions (group, "layers-action",
                                       layers_composite_mode_actions,
                                       G_N_ELEMENTS (layers_composite_mode_actions),
                                       NULL, 0,
                                       G_CALLBACK (layers_composite_mode_cmd_callback));

  gimp_action_group_add_enum_actions (group, "layers-action",
                                      layers_color_tag_actions,
                                      G_N_ELEMENTS (layers_color_tag_actions),
                                      G_CALLBACK (layers_color_tag_cmd_callback));

  gimp_action_group_add_enum_actions (group, "layers-action",
                                      layers_mask_apply_actions,
                                      G_N_ELEMENTS (layers_mask_apply_actions),
                                      G_CALLBACK (layers_mask_apply_cmd_callback));

  gimp_action_group_add_enum_actions (group, "layers-action",
                                      layers_mask_to_selection_actions,
                                      G_N_ELEMENTS (layers_mask_to_selection_actions),
                                      G_CALLBACK (layers_mask_to_selection_cmd_callback));

  gimp_action_group_add_enum_actions (group, "layers-action",
                                      layers_alpha_to_selection_actions,
                                      G_N_ELEMENTS (layers_alpha_to_selection_actions),
                                      G_CALLBACK (layers_alpha_to_selection_cmd_callback));

  layers_actions_fix_tooltip (group, "layers-alpha-selection-replace",
                              GDK_MOD1_MASK);
  layers_actions_fix_tooltip (group, "layers-alpha-selection-add",
                              extend_mask | GDK_MOD1_MASK);
  layers_actions_fix_tooltip (group, "layers-alpha-selection-subtract",
                              modify_mask | GDK_MOD1_MASK);
  layers_actions_fix_tooltip (group, "layers-alpha-selection-intersect",
                              extend_mask | modify_mask | GDK_MOD1_MASK);

  gimp_action_group_add_enum_actions (group, "layers-action",
                                      layers_select_actions,
                                      G_N_ELEMENTS (layers_select_actions),
                                      G_CALLBACK (layers_select_cmd_callback));

  gimp_action_group_add_enum_actions (group, NULL,
                                      layers_opacity_actions,
                                      G_N_ELEMENTS (layers_opacity_actions),
                                      G_CALLBACK (layers_opacity_cmd_callback));

  gimp_action_group_add_enum_actions (group, NULL,
                                      layers_mode_actions,
                                      G_N_ELEMENTS (layers_mode_actions),
                                      G_CALLBACK (layers_mode_cmd_callback));

  items_actions_setup (group, "layers");
}

void
layers_actions_update (GimpActionGroup *group,
                       gpointer         data)
{
  GimpImage     *image          = action_data_get_image (data);
  GimpLayer     *layer          = NULL;
  GimpLayerMask *mask           = NULL;     /*  layer mask             */
  gboolean       fs             = FALSE;    /*  floating sel           */
  gboolean       ac             = FALSE;    /*  active channel         */
  gboolean       sel            = FALSE;
  gboolean       alpha          = FALSE;    /*  alpha channel present  */
  gboolean       indexed        = FALSE;    /*  is indexed             */
  gboolean       lock_alpha     = FALSE;
  gboolean       can_lock_alpha = FALSE;
  gboolean       text_layer     = FALSE;
  gboolean       writable       = FALSE;
  gboolean       movable        = FALSE;
  gboolean       children       = FALSE;
  gboolean       bs_mutable     = FALSE;
  gboolean       cs_mutable     = FALSE;
  gboolean       cm_mutable     = FALSE;
  GList         *next           = NULL;
  GList         *next_visible   = NULL;
  GList         *prev           = NULL;

  if (image)
    {
      fs      = (gimp_image_get_floating_selection (image) != NULL);
      ac      = (gimp_image_get_active_channel (image) != NULL);
      sel     = ! gimp_channel_is_empty (gimp_image_get_mask (image));
      indexed = (gimp_image_get_base_type (image) == GIMP_INDEXED);

      layer = gimp_image_get_active_layer (image);

      if (layer)
        {
          GimpLayerMode  mode   = gimp_layer_get_mode (layer);
          const gchar   *action = NULL;
          GList         *layer_list;
          GList         *list;

          switch (gimp_layer_get_blend_space (layer))
            {
            case GIMP_LAYER_COLOR_SPACE_AUTO:
              action = "layers-blend-space-auto"; break;
            case GIMP_LAYER_COLOR_SPACE_RGB_LINEAR:
              action = "layers-blend-space-rgb-linear"; break;
            case GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL:
              action = "layers-blend-space-rgb-perceptual"; break;
            default:
              action = NULL; break; /* can't happen */
            }

          if (action)
            gimp_action_group_set_action_active (group, action, TRUE);

          switch (gimp_layer_get_composite_space (layer))
            {
            case GIMP_LAYER_COLOR_SPACE_AUTO:
              action = "layers-composite-space-auto"; break;
            case GIMP_LAYER_COLOR_SPACE_RGB_LINEAR:
              action = "layers-composite-space-rgb-linear"; break;
            case GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL:
              action = "layers-composite-space-rgb-perceptual"; break;
            default:
              action = NULL; break; /* can't happen */
            }

          if (action)
            gimp_action_group_set_action_active (group, action, TRUE);

          switch (gimp_layer_get_composite_mode (layer))
            {
            case GIMP_LAYER_COMPOSITE_AUTO:
              action = "layers-composite-mode-auto"; break;
            case GIMP_LAYER_COMPOSITE_SRC_OVER:
              action = "layers-composite-mode-src-over"; break;
            case GIMP_LAYER_COMPOSITE_SRC_ATOP:
              action = "layers-composite-mode-src-atop"; break;
            case GIMP_LAYER_COMPOSITE_SRC_IN:
              action = "layers-composite-mode-src-in"; break;
            case GIMP_LAYER_COMPOSITE_DST_ATOP:
              action = "layers-composite-mode-dst-atop"; break;
            }

          gimp_action_group_set_action_active (group, action, TRUE);

          bs_mutable = gimp_layer_mode_is_blend_space_mutable (mode);
          cs_mutable = gimp_layer_mode_is_composite_space_mutable (mode);
          cm_mutable = gimp_layer_mode_is_composite_mode_mutable (mode);

          mask           = gimp_layer_get_mask (layer);
          lock_alpha     = gimp_layer_get_lock_alpha (layer);
          can_lock_alpha = gimp_layer_can_lock_alpha (layer);
          alpha          = gimp_drawable_has_alpha (GIMP_DRAWABLE (layer));
          writable       = ! gimp_item_is_content_locked (GIMP_ITEM (layer));
          movable        = ! gimp_item_is_position_locked (GIMP_ITEM (layer));

          if (gimp_viewable_get_children (GIMP_VIEWABLE (layer)))
            children = TRUE;

          layer_list = gimp_item_get_container_iter (GIMP_ITEM (layer));

          list = g_list_find (layer_list, layer);

          if (list)
            {
              prev = g_list_previous (list);
              next = g_list_next (list);

              for (next_visible = next;
                   next_visible;
                   next_visible = g_list_next (next_visible))
                {
                  if (gimp_item_get_visible (next_visible->data))
                    {
                      /*  "next_visible" is actually "next_visible" and
                       *  "writable" and "not group"
                       */
                      if (gimp_item_is_content_locked (next_visible->data) ||
                          gimp_viewable_get_children (next_visible->data))
                        next_visible = NULL;

                      break;
                    }
                }
            }

          text_layer = gimp_item_is_text_layer (GIMP_ITEM (layer));
        }
    }

#define SET_VISIBLE(action,condition) \
        gimp_action_group_set_action_visible (group, action, (condition) != 0)
#define SET_SENSITIVE(action,condition) \
        gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
#define SET_ACTIVE(action,condition) \
        gimp_action_group_set_action_active (group, action, (condition) != 0)
#define SET_LABEL(action,label) \
        gimp_action_group_set_action_label (group, action, label)

  SET_VISIBLE   ("layers-text-tool",        text_layer && !ac);
  SET_SENSITIVE ("layers-edit-attributes",  layer && !fs && !ac);

  if (layer && gimp_layer_is_floating_sel (layer))
    {
      SET_LABEL ("layers-new",             C_("layers-action", "To _New Layer"));
      SET_LABEL ("layers-new-last-values", C_("layers-action", "To _New Layer"));
    }
  else
    {
      SET_LABEL ("layers-new",             C_("layers-action", "_New Layer..."));
      SET_LABEL ("layers-new-last-values", C_("layers-action", "_New Layer"));
    }

  SET_SENSITIVE ("layers-new",              image);
  SET_SENSITIVE ("layers-new-last-values",  image);
  SET_SENSITIVE ("layers-new-from-visible", image);
  SET_SENSITIVE ("layers-new-group",        image && !indexed);
  SET_SENSITIVE ("layers-duplicate",        layer && !fs && !ac);
  SET_SENSITIVE ("layers-delete",           layer && !ac);

  SET_SENSITIVE ("layers-select-top",       layer && !fs && !ac && prev);
  SET_SENSITIVE ("layers-select-bottom",    layer && !fs && !ac && next);
  SET_SENSITIVE ("layers-select-previous",  layer && !fs && !ac && prev);
  SET_SENSITIVE ("layers-select-next",      layer && !fs && !ac && next);

  SET_SENSITIVE ("layers-raise",            layer && !fs && !ac && prev);
  SET_SENSITIVE ("layers-raise-to-top",     layer && !fs && !ac && prev);
  SET_SENSITIVE ("layers-lower",            layer && !fs && !ac && next);
  SET_SENSITIVE ("layers-lower-to-bottom",  layer && !fs && !ac && next);

  SET_SENSITIVE ("layers-anchor",           layer &&  fs && !ac);
  SET_SENSITIVE ("layers-merge-down",       layer && !fs && !ac && next_visible);
  SET_VISIBLE   ("layers-merge-group",      children);
  SET_SENSITIVE ("layers-merge-group",      layer && !fs && !ac && children);
  SET_SENSITIVE ("layers-merge-layers",     layer && !fs && !ac);
  SET_SENSITIVE ("layers-flatten-image",    layer && !fs && !ac);

  SET_VISIBLE   ("layers-text-discard",       text_layer && !ac);
  SET_VISIBLE   ("layers-text-to-vectors",    text_layer && !ac);
  SET_VISIBLE   ("layers-text-along-vectors", text_layer && !ac);

  SET_SENSITIVE ("layers-resize",          writable && movable && !ac);
  SET_SENSITIVE ("layers-resize-to-image", writable && movable && !ac);
  SET_SENSITIVE ("layers-scale",           writable && movable && !ac);

  SET_SENSITIVE ("layers-crop-to-selection", writable && movable && sel);
  SET_SENSITIVE ("layers-crop-to-content",   writable && movable);

  SET_SENSITIVE ("layers-alpha-add",    writable && !children && !fs && !alpha);
  SET_SENSITIVE ("layers-alpha-remove", writable && !children && !fs &&  alpha);

  SET_SENSITIVE ("layers-lock-alpha", can_lock_alpha);
  SET_ACTIVE    ("layers-lock-alpha", lock_alpha);

  SET_SENSITIVE ("layers-blend-space-auto",           layer && bs_mutable);
  SET_SENSITIVE ("layers-blend-space-rgb-linear",     layer && bs_mutable);
  SET_SENSITIVE ("layers-blend-space-rgb-perceptual", layer && bs_mutable);

  SET_SENSITIVE ("layers-composite-space-auto",           layer && cs_mutable);
  SET_SENSITIVE ("layers-composite-space-rgb-linear",     layer && cs_mutable);
  SET_SENSITIVE ("layers-composite-space-rgb-perceptual", layer && cs_mutable);

  SET_SENSITIVE ("layers-composite-mode-auto",     layer && cm_mutable);
  SET_SENSITIVE ("layers-composite-mode-src-over", layer && cm_mutable);
  SET_SENSITIVE ("layers-composite-mode-src-atop", layer && cm_mutable);
  SET_SENSITIVE ("layers-composite-mode-src-in",   layer && cm_mutable);
  SET_SENSITIVE ("layers-composite-mode-dst-atop", layer && cm_mutable);

  SET_SENSITIVE ("layers-mask-add",             layer && !fs && !ac && !mask && !children);
  SET_SENSITIVE ("layers-mask-add-button",      layer && !fs && !ac && !children);
  SET_SENSITIVE ("layers-mask-add-last-values", layer && !fs && !ac && !mask && !children);

  SET_SENSITIVE ("layers-mask-apply",  writable && !fs && !ac &&  mask && !children);
  SET_SENSITIVE ("layers-mask-delete", layer    && !fs && !ac &&  mask);

  SET_SENSITIVE ("layers-mask-edit",    layer && !fs && !ac &&  mask);
  SET_SENSITIVE ("layers-mask-show",    layer && !fs && !ac &&  mask);
  SET_SENSITIVE ("layers-mask-disable", layer && !fs && !ac &&  mask);

  SET_ACTIVE ("layers-mask-edit",    mask && gimp_layer_get_edit_mask (layer));
  SET_ACTIVE ("layers-mask-show",    mask && gimp_layer_get_show_mask (layer));
  SET_ACTIVE ("layers-mask-disable", mask && !gimp_layer_get_apply_mask (layer));

  SET_SENSITIVE ("layers-mask-selection-replace",   layer && !fs && !ac && mask);
  SET_SENSITIVE ("layers-mask-selection-add",       layer && !fs && !ac && mask);
  SET_SENSITIVE ("layers-mask-selection-subtract",  layer && !fs && !ac && mask);
  SET_SENSITIVE ("layers-mask-selection-intersect", layer && !fs && !ac && mask);

  SET_SENSITIVE ("layers-alpha-selection-replace",   layer && !fs && !ac);
  SET_SENSITIVE ("layers-alpha-selection-add",       layer && !fs && !ac);
  SET_SENSITIVE ("layers-alpha-selection-subtract",  layer && !fs && !ac);
  SET_SENSITIVE ("layers-alpha-selection-intersect", layer && !fs && !ac);

#undef SET_VISIBLE
#undef SET_SENSITIVE
#undef SET_ACTIVE
#undef SET_LABEL

  items_actions_update (group, "layers", GIMP_ITEM (layer));
}
