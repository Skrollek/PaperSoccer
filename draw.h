#ifndef DRAW_H
#define DRAW_H
#include <stdio.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include "board.h"

void drawToConsole(Board* board);
void draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, Board *board);//gpointer user_data)

#endif