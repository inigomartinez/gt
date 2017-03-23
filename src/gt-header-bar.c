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
  GtkWidget *cancel_button;
  GtkWidget *empty_bin_button;

  GtkWidget *menu_button;
} GtHeaderBarPrivate;

struct _GtHeaderBar
{
  GtkHeaderBar parent;
};

G_DEFINE_TYPE_WITH_PRIVATE (GtHeaderBar, gt_header_bar, GTK_TYPE_HEADER_BAR)

static void
gt_header_bar_class_init (GtHeaderBarClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/test/gt/ui/header-bar.ui");

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, list_image);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, grid_image);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, new_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, search_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, mode_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, select_button);

  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, back_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, cancel_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, empty_bin_button);
  gtk_widget_class_bind_template_child_private (widget_class, GtHeaderBar, menu_button);
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
