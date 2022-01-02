#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
//#include "board.h"
#include "draw.h"

static void app_activate (GApplication *app, gpointer *user_data) 
{
    g_print ("GtkApplication is activated.\n");
    GtkWidget *win; 
    win = gtk_window_new ();   
    gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
    gtk_widget_show (win);
}


int main(int argc,char **argv)
{
    Board* board = initializeBoard(8,10);
    draw(board);

    return 0;
    GtkApplication *app;
    int stat;

    app  = gtk_application_new("com.github.Skrollek.PaperSoccer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
    stat = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}