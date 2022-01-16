#include <gtk/gtk.h>

extern GtkWidget *scene[3];
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
    GtkWindow *window = userData;
    gtk_window_set_child(window, scene[1]);
}

static void ExitToMenuCallback(GtkButton *button, gpointer userData)
{
    g_print("exit\n");
    GtkWindow *window = userData;
    gtk_window_set_child(window, scene[0]);

}
static void app_activate (GApplication *app, gpointer *user_data) 
{
    g_print ("GtkApplication is activated.\n");

    GtkWidget *win;
    GtkWidget *boxMenu;
    GtkWidget *btnQuit;
    GtkWidget *btnStart;
    GtkWidget *btnOption;

    GtkWidget *optionsGrid;

    win = gtk_application_window_new(GTK_APPLICATION(app));  
    gtk_window_set_title(GTK_WINDOW(win), "PaperSoccer");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
    
    /// creating main menu
    boxMenu = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_set_homogeneous(GTK_BOX(boxMenu), true);
    

    btnStart = gtk_button_new_with_label("Start Game");
    g_signal_connect(btnStart, "clicked", G_CALLBACK(startCallback), NULL);

    btnOption = gtk_button_new_with_label("Options");
    g_signal_connect(btnOption, "clicked", G_CALLBACK(optionCallback), (gpointer)win);
    
    btnQuit = gtk_button_new_with_label("Quit");
    g_signal_connect(btnQuit, "clicked", G_CALLBACK(quitCallback), win);
    
    gtk_box_append(GTK_BOX(boxMenu), btnStart);
    gtk_box_append(GTK_BOX(boxMenu), btnOption);
    gtk_box_append(GTK_BOX(boxMenu), btnQuit);

    char* css = ".text-button{font-size: 50pt;}";
    GtkCssProvider* fontCSS =  gtk_css_provider_new();
    gtk_css_provider_load_from_data(fontCSS, css, strlen(css));
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnStart)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnOption)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnQuit)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    scene[0] = boxMenu;

    optionsGrid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(optionsGrid), 1);
    gtk_grid_set_row_homogeneous(GTK_GRID(optionsGrid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(optionsGrid), 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(optionsGrid), TRUE);

    GtkWidget* toAttach;
    toAttach = gtk_button_new_with_label("<-");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 0, 2, 1);
    toAttach = gtk_label_new("12");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 2, 0, 1, 1);
    toAttach = gtk_button_new_with_label("->");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 3, 0, 2, 1);
    
    toAttach = gtk_button_new_with_label("<-");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 1, 2, 1);
    toAttach = gtk_label_new("8");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 2, 1, 1, 1);
    toAttach = gtk_button_new_with_label("->");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 3, 1, 2, 1);

    toAttach = gtk_button_new_with_label("Exit to menu");
    g_signal_connect(toAttach, "clicked", G_CALLBACK(ExitToMenuCallback), (gpointer)win);
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 2, 5, 1);

    toAttach = gtk_drawing_area_new();

    scene[1] = optionsGrid;
    gtk_window_set_child(GTK_WINDOW(win), scene[0]);
    



    gtk_widget_show (win);
}