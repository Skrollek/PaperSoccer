#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "draw.h"
#include <gtk/gtk.h>
GtkWidget *scene[3];
#include "callbacks.h"

int main(int argc,char **argv)
{
    GtkApplication *app;
    int stat;
    app  = gtk_application_new("com.github.Skrollek.PaperSoccer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (app_activate), (gpointer)scene);
    stat = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}