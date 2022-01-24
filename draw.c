#include "draw.h"
void drawToConsole(Board* board)
{
    for(int x = 1; x < board->width; ++x)
    {
            putchar(' ');
            putchar('_');
    }
    for(int y = 1; y < board->height; ++y)
    {
        putchar('\n');
        for(int x = 1; x < board->width; ++x)
        {
            putchar('|');
            putchar('_');
        }
        putchar('|');
    }
}

void draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, Board *board)
{
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_translate(cr, 100, 100);
    //drawing board section
    for(int y = 0; y < board->height; ++y)
    {
        cairo_move_to(cr, 0, (600.0/(board->height-1))*y);
        cairo_line_to(cr, 600, (600.0/(board->height-1))*y);
        for(int x = 0; x < board->width; ++x)
        {
            cairo_move_to(cr, (600.0/(board->width-1))*x, (600.0/(board->height))*y);
            cairo_line_to(cr, (600.0/(board->width-1))*x, (600.0/(board->height))*(y+1));
        }
        
    }
    cairo_stroke(cr);
    // drawing possible moves section

    // drawing used moves section

    // drawing ball section
    cairo_set_source_rgb(cr, 255, 0, 0);
    cairo_set_line_width(cr, 1);
    cairo_arc(cr, (600.0/(board->width-1))*((board->width)/2), (600.0/(board->height-1))*((board->height)/2), 4, 0, 6.2830);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);
}