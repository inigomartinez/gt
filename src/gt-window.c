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

#include "gt-application.h"
#include "gt-header-bar.h"
#include "gt-window.h"

typedef struct
{
  GtkWidget *header_bar;

  GtkWidget *search_bar;

  GtkWidget *spinner;
} GtWindowPrivate;

struct _GtWindow
{
  GtkApplicationWindow parent;
};

G_DEFINE_TYPE_WITH_PRIVATE (GtWindow, gt_window, GTK_TYPE_APPLICATION_WINDOW)

static gboolean
on_key_press_event (GtkSearchBar *search_bar,
                    GdkEvent     *event,
                    gpointer      user_data)
{
  return gtk_search_bar_handle_event (search_bar, event);
}

static void
gt_window_constructed (GObject *object)
{
  GtWindowPrivate *priv;

  priv = gt_window_get_instance_private (GT_WINDOW (object));

  G_OBJECT_CLASS (gt_window_parent_class)->constructed (object);

  g_object_bind_property (priv->search_bar, "search-mode-enabled",
                          priv->spinner, "active",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
}

static void
gt_window_class_init (GtWindowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->constructed = gt_window_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/test/gt/ui/window.ui");

  g_type_ensure (GT_TYPE_HEADER_BAR);

  gtk_widget_class_bind_template_child_private (widget_class, GtWindow, header_bar);
  gtk_widget_class_bind_template_child_private (widget_class, GtWindow, search_bar);
  gtk_widget_class_bind_template_child_private (widget_class, GtWindow, spinner);

  gtk_widget_class_bind_template_callback (widget_class, on_key_press_event);
}

static void
gt_window_init (GtWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

GtkWidget *
gt_window_new (GtApplication *application)
{
  return g_object_new (GT_TYPE_WINDOW,
                       "application", application,
                       NULL);
}
