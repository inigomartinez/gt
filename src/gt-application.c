/*
 * Copyright (C) 2017 Iñigo Martínez <inigomartinez@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "config.h"

#include <gtk/gtk.h>

#include "gt-application.h"
#include "gt-preferences.h"
#include "gt-window.h"

typedef struct
{
  GtkCssProvider *provider;

  GtkWidget      *preferences;
  GtkWidget      *window;
} GtApplicationPrivate;

struct _GtApplication
{
  GtkApplication parent;
};

static void gt_application_show_preferences (GSimpleAction *simple,
                                             GVariant      *parameter,
                                             gpointer       user_data);

static void gt_application_show_about       (GSimpleAction *simple,
                                             GVariant      *parameter,
                                             gpointer       user_data);

static void gt_application_quit             (GSimpleAction *simple,
                                             GVariant      *parameter,
                                             gpointer       user_data);

G_DEFINE_TYPE_WITH_PRIVATE (GtApplication, gt_application, GTK_TYPE_APPLICATION)

static const GActionEntry gt_application_entries[] = {
  { "preferences", gt_application_show_preferences },
  { "about",       gt_application_show_about },
  { "quit",        gt_application_quit }
};

static void
gt_application_show_preferences (GSimpleAction *simple,
                                 GVariant      *parameter,
                                 gpointer       user_data)
{
  GtApplicationPrivate *priv;

  g_return_if_fail (GT_IS_APPLICATION (user_data));

  priv = gt_application_get_instance_private (user_data);

  if (!priv->preferences)
    priv->preferences = gt_preferences_new (GTK_WINDOW (priv->window));

  gtk_widget_show (priv->preferences);
}

static void
gt_application_show_about (GSimpleAction *simple,
                           GVariant      *parameter,
                           gpointer       user_data)
{
  GtApplicationPrivate *priv;
  GDateTime *date;
  gint year;
  gchar *copyright;

  static const gchar *authors[] = {
    "Iñigo Martínez <inigomartinez@gmail.com>",
    NULL
  };

  priv = gt_application_get_instance_private (user_data);

  date = g_date_time_new_now_local ();
  year = g_date_time_get_year (date);
  g_date_time_unref (date);

  if (year == GT_CREATED_YEAR)
  {
    copyright = g_strdup_printf ("Copyright \xC2\xA9 %d "
                                 "The " PACKAGE_NAME " authors",
                                 GT_CREATED_YEAR);
  }
  else
  {
    copyright = g_strdup_printf ("Copyright \xC2\xA9 %d\xE2\x80\x93%d "
                                 "The " PACKAGE_NAME " authors",
                                 GT_CREATED_YEAR, year);
  }

  gtk_show_about_dialog (GTK_WINDOW (priv->window),
                         "program-name", PACKAGE_NAME,
                         "version", PACKAGE_VERSION,
                         "copyright", copyright,
                         "license-type", GTK_LICENSE_MIT_X11,
                         "authors", authors,
                         NULL);

  g_free (copyright);
}

static void
gt_application_quit (GSimpleAction *simple,
                     GVariant      *parameter,
                     gpointer       user_data)
{
  GtApplicationPrivate *priv;

  priv = gt_application_get_instance_private (user_data);

  gtk_widget_destroy (priv->preferences);
  gtk_widget_destroy (priv->window);
}

GtApplication *
gt_application_new (void)
{
  g_set_application_name (PACKAGE_NAME);

  return g_object_new (GT_TYPE_APPLICATION,
                       "application-id", "org.test.gt",
                       "flags", G_APPLICATION_FLAGS_NONE,
                       "resource-base-path", "/org/test/gt",
                       NULL);
}

static void
run_window (GtApplication *application)
{
  GtApplicationPrivate *priv;

  g_return_if_fail (GT_IS_APPLICATION (application));

  priv = gt_application_get_instance_private (application);

  if (!priv->window)
    priv->window = gt_window_new (application);

  gtk_widget_show (priv->window);
}

static void
gt_application_activate (GApplication *application)
{
  GtApplicationPrivate *priv;

  priv = gt_application_get_instance_private (GT_APPLICATION (application));

  if (!priv->provider)
  {
    priv->provider = gtk_css_provider_new ();
    gtk_style_context_add_provider_for_screen (gdk_screen_get_default (),
                                               GTK_STYLE_PROVIDER (priv->provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION + 1);

    gtk_css_provider_load_from_resource (priv->provider, "/org/test/gt/theme/Adwaita.css");
  }

  run_window (GT_APPLICATION (application));
}

static void
gt_application_finalize (GObject *object)
{
  G_OBJECT_CLASS (gt_application_parent_class)->finalize (object);
}

static void
gt_application_startup (GApplication *application)
{
  g_action_map_add_action_entries (G_ACTION_MAP (application),
                                   gt_application_entries,
                                   G_N_ELEMENTS (gt_application_entries),
                                   application);

  G_APPLICATION_CLASS (gt_application_parent_class)->startup (application);
}

static gboolean
gt_application_local_command_line (GApplication   *application,
                                   gchar        ***arguments,
                                   gint           *exit_status)
{
  return G_APPLICATION_CLASS (gt_application_parent_class)->local_command_line (application,
                                                                                arguments,
                                                                                exit_status);
}

static void
gt_application_class_init (GtApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *application_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = gt_application_finalize;

  application_class->activate = gt_application_activate;
  application_class->startup = gt_application_startup;
  application_class->local_command_line = gt_application_local_command_line;
}

static void
gt_application_init (GtApplication *self)
{

}
