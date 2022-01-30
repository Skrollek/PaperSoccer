#ifndef DRAW_H
#define DRAW_H
#include "libs.h"
#include "logic.h"

void drawToConsole(Board* board);
void draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer userData);

#endif