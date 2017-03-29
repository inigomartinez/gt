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

#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include "gt-header-bar.h"
#include "gt-window.h"

typedef struct
{
  GtkWidget *list_image;
  GtkWidget *grid_image;

  GtkWidget *new_button;
  GtkWidget *back_button;

  GtkWidget *select_button;
  GtkWidget *mode_button;
  GtkWidget *search_button;

  GtkWidget *color_button;
  GtkWidget *menu_button;

  GtkWidget *cancel_button;
  GtkWidget *empty_bin_button;

  GtkWidget *menu_new_button;
  GtkWidget *menu_notebooks_button;

  gboolean   mode;
  gboolean   detached;
} GtHeaderBarPrivate;

struct _GtHeaderBar
{
  GtkHeaderBar parent;
};

G_DEFINE_TYPE_WITH_PRIVATE (GtHeaderBar, gt_header_bar, GTK_TYPE_HEADER_BAR)

static void
header_bar_set_main (GtHeaderBar *self)
{
  GtHeaderBarPrivate *priv;
  GtkWidget *top;
  GtkStyleContext *context;

  priv = gt_header_bar_get_instance_private (self);

  gtk_header_bar_set_title (GTK_HEADER_BAR (self), "New and Recent");

  top = gtk_widget_get_toplevel (GTK_WIDGET (self));
  context = gtk_widget_get_style_context (top);
  gtk_style_context_remove_class (context, "note-window");
  gtk_style_context_remove_class (context, "note-window-custom");

  gtk_container_foreach (GTK_CONTAINER (self), (GtkCallback) gtk_widget_hide, NULL);

  gtk_widget_show (priv->new_button);
  gtk_widget_show (priv->search_button);
  gtk_widget_show (priv->mode_button);
  gtk_widget_show (priv->select_button);
}

static void
on_new_button_clicked (GtHeaderBar *self)
{
  GtHeaderBarPrivate *priv;
  GdkRGBA color;
  GtkWidget *top;
  GtkStyleContext *context;

  priv = gt_header_bar_get_instance_private (self);

  gtk_header_bar_set_title (GTK_HEADER_BAR (self), "Untitled");
  gdk_rgba_parse (&color, "rgb(246,218,18)");

  gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (priv->color_button), &color);

  top = gtk_widget_get_toplevel (GTK_WIDGET (self));
  context = gtk_widget_get_style_context (top);
  gtk_style_context_add_class (context, "note-window");

  gtk_container_foreach (GTK_CONTAINER (self), (GtkCallback) gtk_widget_hide, NULL);

  gtk_widget_show (priv->back_button);
  gtk_widget_show (priv->color_button);
  gtk_widget_show (priv->menu_button);
}

static void
on_mode_button_clicked (GtHeaderBar *self)
{
  GtHeaderBarPrivate *priv;

  priv = gt_header_bar_get_instance_private (self);

  if (priv->mode)
    gtk_button_set_image (GTK_BUTTON (priv->mode_button), priv->list_image);
  else
    gtk_button_set_image (GTK_BUTTON (priv->mode_button), priv->grid_image);

  priv->mode = !priv->mode;
}

static void
on_select_button_clicked (GtHeaderBar *self)
{
  GtHeaderBarPrivate *priv;
  GtkStyleContext *context;

  priv = gt_header_bar_get_instance_private (self);

  context = gtk_widget_get_style_context (GTK_WIDGET (self));
  gtk_style_context_add_class (context, "selection-mode");

  gtk_header_bar_set_title (GTK_HEADER_BAR (self), "Click on items to select them");

  gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (self), FALSE);

  gtk_container_foreach (GTK_CONTAINER (self), (GtkCallback) gtk_widget_hide, NULL);

  gtk_widget_show (priv->search_button);
  gtk_widget_show (priv->cancel_button);
}

static void
on_color_button_color_set (GtkColorButton *widget,
                           gpointer        user_data)
{
  GtkWidget *top;
  GdkRGBA color;
  GdkDisplay *display;
  GdkScreen *screen;
  GtkCssProvider *provider;
  gchar *str, *css;
  GtkStyleContext *context;
  GError *error = NULL;

  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  provider = gtk_css_provider_new ();

  gtk_style_context_add_provider_for_screen (screen,
                                             GTK_STYLE_PROVIDER (provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (widget), &color);
  str = gdk_rgba_to_string (&color);

  css = g_strconcat (".note-window-custom {"
                     " background-color: ", str, ";"
                     "}", NULL);
  g_free (str);

  gtk_css_provider_load_from_data (provider, css, -1, &error);
  g_free (css);
  g_object_unref (provider);

  if (error != NULL)
  {
    g_warning ("%s: %s: %s",
               G_STRFUNC,
               "Error loading CSS from data",
               error->message);
    g_error_free (error);
  }
  else
  {
    top = gtk_widget_get_toplevel (GTK_WIDGET (widget));
    context = gtk_widget_get_style_context (top);
    gtk_style_context_add_class (context, "note-window-custom");
  }
}

static void
on_cancel_button_clicked (GtHeaderBar *self)
{
  GtkStyleContext *context;

  context = gtk_widget_get_style_context (GTK_WIDGET (self));
  gtk_style_context_remove_class (context, "selection-mode");

  gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (self), TRUE);

  header_bar_set_main (self);
}

static void
on_menu_new_button_clicked (GtHeaderBar *self)
{
  GtHeaderBarPrivate *priv;

  priv = gt_header_bar_get_instance_private (self);

  if (!priv->detached)
    gtk_widget_hide (priv->menu_new_button);

  priv->detached = !priv->detached;
}

static void
gt_header_bar_constructed (GObject *object)
{
  GtHeaderBarPrivate *priv;

  G_OBJECT_CLASS (gt_header_bar_parent_class)->constructed (object);

  priv = gt_header_bar_get_instance_private (GT_HEADER_BAR (object));

  priv->mode = FALSE;
  priv->detached = FALSE;

  if (!priv->detached)
    gtk_widget_show (priv->menu_new_button);
}

static void
gt_header_bar_class_init (GtHeaderBarClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->constructed = gt_header_bar_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/test/gt/ui/header-bar.ui");

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, list_image);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, grid_image);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, new_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, back_button);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, search_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, mode_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, select_button);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, color_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, menu_button);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, cancel_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, empty_bin_button);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, menu_new_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, menu_notebooks_button);

  gtk_widget_class_bind_template_callback (widget_class, on_new_button_clicked);
  gtk_widget_class_bind_template_callback (widget_class, header_bar_set_main);

  gtk_widget_class_bind_template_callback (widget_class, on_mode_button_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_select_button_clicked);

  gtk_widget_class_bind_template_callback (widget_class, on_color_button_color_set);

  gtk_widget_class_bind_template_callback (widget_class, on_cancel_button_clicked);

  gtk_widget_class_bind_template_callback (widget_class, on_menu_new_button_clicked);
}

static void
gt_header_bar_init (GtHeaderBar *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

GtkWidget *
gt_header_bar_new (void)
{
  return g_object_new (GT_TYPE_HEADER_BAR, NULL);
}
