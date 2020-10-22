/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MOUSEPAD_UTIL_H__
#define __MOUSEPAD_UTIL_H__

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

G_BEGIN_DECLS

#define MOUSEPAD_TYPE_SEARCH_FLAGS (mousepad_util_search_flags_get_type ())

typedef enum
{
  /* search area */
  MOUSEPAD_SEARCH_FLAGS_ENTIRE_AREA          = 1 << 0,  /* search the whole area */
  MOUSEPAD_SEARCH_FLAGS_AREA_SELECTION       = 1 << 1,  /* search inside selection */
  MOUSEPAD_SEARCH_FLAGS_AREA_ALL_DOCUMENTS   = 1 << 2,  /* search all documents */

  /* iter start point */
  MOUSEPAD_SEARCH_FLAGS_ITER_SEL_START       = 1 << 3,  /* start at from the beginning of the selection */
  MOUSEPAD_SEARCH_FLAGS_ITER_SEL_END         = 1 << 4,  /* start at from the end of the selection */

  /* direction */
  MOUSEPAD_SEARCH_FLAGS_DIR_FORWARD          = 1 << 5,  /* search forward to end of area */
  MOUSEPAD_SEARCH_FLAGS_DIR_BACKWARD         = 1 << 6,  /* search backwards to start of area */

  /* search settings */
  MOUSEPAD_SEARCH_FLAGS_MATCH_CASE           = 1 << 7,  /* match case */
  MOUSEPAD_SEARCH_FLAGS_ENABLE_REGEX         = 1 << 8,  /* enable regex search */
  MOUSEPAD_SEARCH_FLAGS_WHOLE_WORD           = 1 << 9,  /* only match whole words */
  MOUSEPAD_SEARCH_FLAGS_WRAP_AROUND          = 1 << 10, /* wrap around */

  /* actions */
  MOUSEPAD_SEARCH_FLAGS_ACTION_HIGHLIGHT_ON  = 1 << 11, /* enable occurrence highlighting */
  MOUSEPAD_SEARCH_FLAGS_ACTION_HIGHLIGHT_OFF = 1 << 12, /* disable occurrence highlighting */
  MOUSEPAD_SEARCH_FLAGS_ACTION_SELECT        = 1 << 13, /* select the match */
  MOUSEPAD_SEARCH_FLAGS_ACTION_REPLACE       = 1 << 14, /* replace the match */
}
MousepadSearchFlags;

gboolean   mousepad_util_iter_starts_word                 (const GtkTextIter   *iter);

gboolean   mousepad_util_iter_ends_word                   (const GtkTextIter   *iter);

gboolean   mousepad_util_iter_inside_word                 (const GtkTextIter   *iter);

gboolean   mousepad_util_iter_forward_word_end            (GtkTextIter         *iter);

gboolean   mousepad_util_iter_backward_word_start         (GtkTextIter         *iter);

gboolean   mousepad_util_iter_forward_text_start          (GtkTextIter         *iter);

gboolean   mousepad_util_iter_backward_text_start         (GtkTextIter         *iter);

gchar     *mousepad_util_config_name                      (const gchar         *name);

gchar     *mousepad_util_key_name                         (const gchar         *name);

gchar     *mousepad_util_utf8_strcapital                  (const gchar         *str);

gchar     *mousepad_util_utf8_stropposite                 (const gchar         *str);

gchar     *mousepad_util_escape_underscores               (const gchar         *str);

GtkWidget *mousepad_util_image_button                     (const gchar         *icon_name,
                                                           const gchar         *label);

void       mousepad_util_entry_error                      (GtkWidget           *widget,
                                                           gboolean             error);

void       mousepad_util_dialog_create_header             (GtkDialog           *dialog,
                                                           const gchar         *title,
                                                           const gchar         *subtitle,
                                                           const gchar         *icon_name);

void       mousepad_util_dialog_update_header             (GtkDialog           *dialog,
                                                           const gchar         *title,
                                                           const gchar         *subtitle,
                                                           const gchar         *icon_name);

gint       mousepad_util_get_real_line_offset             (const GtkTextIter   *iter,
                                                           gint                 tab_size);

gboolean   mousepad_util_forward_iter_to_text             (GtkTextIter         *iter,
                                                           const GtkTextIter   *limit);

gchar     *mousepad_util_get_save_location                (const gchar         *relpath,
                                                           gboolean             create_parents);

void       mousepad_util_save_key_file                    (GKeyFile            *keyfile,
                                                           const gchar         *filename);

GType      mousepad_util_search_flags_get_type            (void) G_GNUC_CONST;

gint       mousepad_util_search                           (GtkSourceSearchContext *search_context,
                                                           const gchar            *string,
                                                           const gchar            *replace,
                                                           MousepadSearchFlags     flags);

GIcon     *mousepad_util_icon_for_mime_type               (const gchar         *mime_type);

gboolean   mousepad_util_container_has_children           (GtkContainer        *container);

void       mousepad_util_container_clear                  (GtkContainer        *container);

void       mousepad_util_container_move_children          (GtkContainer        *source,
                                                           GtkContainer        *destination);

GSList    *mousepad_util_style_schemes_get_sorted         (void);

GSList    *mousepad_util_get_sorted_section_names         (void);

GSList    *mousepad_util_get_sorted_languages_for_section (const gchar *section);

#if !GLIB_CHECK_VERSION (2, 52, 0)
/*
 * Copied from GLib 2.66.0:
 * https://gitlab.gnome.org/GNOME/glib/-/blob/c2c12e42920d6e06c23c87398996827e53c1fc72/glib/gunicode.h#L934
 */
gchar *g_utf8_make_valid (const gchar *str,
                          gssize       len) G_GNUC_MALLOC;
#endif

/*
 * Copied from Gedit 3.38.0 and slightly modified:
 * https://gitlab.gnome.org/GNOME/gedit/-/blob/21fac3f0c87db0db104d7af7eaeb6f63d8216a14/gedit/gedit-pango.h#L28
 */
gchar *mousepad_pango_font_description_to_css (const PangoFontDescription *font_desc);

G_END_DECLS

#endif /* !__MOUSEPAD_UTIL_H__ */
