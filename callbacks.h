#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "draw.h"
#include "logic.h"
#include "libs.h"


void quitCallback(GtkButton *button, gpointer userData);
void startCallback(GtkButton *button, gpointer userData);
void optionCallback(GtkButton *button, gpointer userData);
void ExitToMenuCallback(GtkButton *button, gpointer userData);
void appActivate (GApplication *app, gpointer userData);
void increaseBoardSizeHeight(GtkButton *button, gpointer userData);
void decreaseBoardSizeHeight(GtkButton *button, gpointer userData);
void increaseBoardSizeWidth(GtkButton *button, gpointer userData);
void decreaseBoardSizeWidth(GtkButton *button, gpointer userData);
void clickedCallback(GtkGestureClick *gesture, int noPress, double x, double y);
void destroyWindows(GtkWindow *widget, gpointer userData);
void saveFileCallback(GtkWidget *widget, gpointer userData);
void saveQuitCallback(GtkWidget *widget, gpointer userData);
void loadMovesFromFile(GtkWindow *widget, gpointer userData);
void destroyWindows(GtkWindow *widget, gpointer userData);


#endif