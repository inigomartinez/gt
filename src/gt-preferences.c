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

#include <gtk/gtk.h>
#include <libpeas-gtk/peas-gtk-plugin-manager.h>

#include "gt-preferences.h"

typedef struct
{
  GtkWidget *plugin_manager;
} GtPreferencesPrivate;

struct _GtPreferences
{
  GtkDialog parent;
};

G_DEFINE_TYPE_WITH_PRIVATE (GtPreferences, gt_preferences, GTK_TYPE_DIALOG)

static void
gt_preferences_class_init (GtPreferencesClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/test/gt/ui/preferences.ui");

  g_type_ensure (PEAS_GTK_TYPE_PLUGIN_MANAGER);

  gtk_widget_class_bind_template_child_private (widget_class, GtPreferences, plugin_manager);
}

static void
gt_preferences_init (GtPreferences *self)
{
  GtPreferencesPrivate *priv;

  priv = gt_preferences_get_instance_private (self);

  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_widget_show_all (priv->plugin_manager);
}

GtkWidget *
gt_preferences_new (GtkWindow *window)
{
  return g_object_new (GT_TYPE_PREFERENCES,
                       "transient-for", window,
                       NULL);
}
