#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
//#include "board.h"
#include "draw.h"

static void quitCallback(GtkButton *button, gpointer userData)
{
    GtkWindow *win = GTK_WINDOW (userData);
    gtk_window_destroy (win);
}
static void startCallback(GtkButton *button, gpointer userData)
{
    g_print("Game started\n");
}
static void optionCallback(GtkButton *button, gpointer userData)
{
    g_print("Options started\n");
}

static void app_activate (GApplication *app, gpointer *user_data) 
{
    g_print ("GtkApplication is activated.\n");

    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *btnQuit;
    GtkWidget *btnStart;
    GtkWidget *btnOption;

    win = gtk_application_window_new(GTK_APPLICATION(app));  
    gtk_window_set_title(GTK_WINDOW(win), "PaperSoccer");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_set_homogeneous(GTK_BOX(box), true);
    gtk_window_set_child(GTK_WINDOW(win), box);

    btnStart = gtk_button_new_with_label("Start Game");
    g_signal_connect(btnStart, "clicked", G_CALLBACK(startCallback), NULL);

    btnOption = gtk_button_new_with_label("Options");
    g_signal_connect(btnOption, "clicked", G_CALLBACK(optionCallback), NULL);
    
    btnQuit = gtk_button_new_with_label("Quit");
    g_signal_connect(btnQuit, "clicked", G_CALLBACK(quitCallback), win);
    
    gtk_box_append(GTK_BOX(box), btnStart);
    gtk_box_append(GTK_BOX(box), btnOption);
    gtk_box_append(GTK_BOX(box), btnQuit);
    char* css = ".text-button{font-size: 50pt;}";
    GtkCssProvider* fontCSS=  gtk_css_provider_new();
    gtk_css_provider_load_from_data(fontCSS, css, strlen(css));
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnStart)), fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnOption)), fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnQuit)), fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_widget_show (win);
}


int main(int argc,char **argv)
{
    GtkApplication *app;
    int stat;

    app  = gtk_application_new("com.github.Skrollek.PaperSoccer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
    stat = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}