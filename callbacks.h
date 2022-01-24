#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include "draw.h"
#include "board.h"

typedef struct ActivationData
{
    // to fill section 
    GtkWidget *scene[3];
    Board *board;
    GtkWidget *heightLabel;
    GtkWidget *widthLabel;
} ActivationData;

void quitCallback(GtkButton *button, gpointer userData);
void startCallback(GtkButton *button, gpointer userData);
void optionCallback(GtkButton *button, gpointer userData);
void ExitToMenuCallback(GtkButton *button, gpointer userData);
void appActivate (GApplication *app, gpointer userData);
void increaseBoardSizeHeight(GtkButton *button, gpointer userData);
void decreaseBoardSizeHeight(GtkButton *button, gpointer userData);
void increaseBoardSizeWidth(GtkButton *button, gpointer userData);
void decreaseBoardSizeWidth(GtkButton *button, gpointer userData);
#endif