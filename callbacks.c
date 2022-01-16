#include "callbacks.h"

void quitCallback(GtkButton *button, gpointer userData)
{
    GtkWindow *window = GTK_WINDOW (userData);
    gtk_window_destroy (window);
}
void startCallback(GtkButton *button, gpointer userData)
{
    g_print("Game started\n");
}
void optionCallback(GtkButton *button, gpointer userData)
{
    g_print("Options started\n");
    GtkWidget *stack = GTK_WIDGET(userData);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Options");
}
void ExitToMenuCallback(GtkButton *button, gpointer userData)
{
    g_print("Exit to menu\n");
    GtkWidget *stack = GTK_WIDGET(userData);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Menu");
}

void increaseBoardSizeHeight(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->heightLabel;
    if(data->board->height < 200)
    {
        data->board->height += 2;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; itoa(data->board->height-1, number, 10);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
    
    
}
void decreaseBoardSizeHeight(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->heightLabel;
    if(data->board->height > 6)
    {
        data->board->height -= 2;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; itoa(data->board->height-1, number, 10);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
}

void increaseBoardSizeWidth(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->widthLabel;
    if(data->board->width < 200)
    {
        data->board->width += 2;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; itoa(data->board->width-1, number, 10);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
}

void decreaseBoardSizeWidth(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->widthLabel;
    if(data->board->width >6)
    {
        data->board->width -= 2;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; itoa(data->board->width-1, number, 10);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
}


void appActivate (GApplication *app, gpointer userData) 
{
    g_print ("GtkApplication is activated.\n");
    ActivationData *data = (ActivationData*)userData;

    GtkWidget *scenes = gtk_stack_new();
    GtkWidget *win;
    GtkWidget *boxMenu;
    GtkWidget *btnQuit;
    GtkWidget *btnStart;
    GtkWidget *btnOption;

    GtkWidget *optionsGrid;

    GtkWidget *gameScene;

    Board* board = initializeBoard(8, 12);
    data->board = board;

    win = gtk_application_window_new(GTK_APPLICATION(app));  
    gtk_window_set_title(GTK_WINDOW(win), "PaperSoccer");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(win), 0);
    gtk_window_set_child(GTK_WINDOW(win), scenes);
    /// creating main menu
    boxMenu = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_set_homogeneous(GTK_BOX(boxMenu), true);
    

    btnStart = gtk_button_new_with_label("Start Game");
    g_signal_connect(btnStart, "clicked", G_CALLBACK(startCallback), (gpointer)scenes);

    btnOption = gtk_button_new_with_label("Options");
    g_signal_connect(btnOption, "clicked", G_CALLBACK(optionCallback), (gpointer)scenes);
    
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

    gtk_stack_add_named(GTK_STACK(scenes), boxMenu, "Menu");
   
    // creating options menu
    optionsGrid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(optionsGrid), 1);
    gtk_grid_set_row_homogeneous(GTK_GRID(optionsGrid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(optionsGrid), 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(optionsGrid), TRUE);

    GtkWidget* toAttach;

    toAttach = gtk_label_new("Height:12");
    data->heightLabel = toAttach;
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 2, 0, 1, 1);

    toAttach = gtk_button_new_with_label("<-");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 0, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(decreaseBoardSizeHeight), (gpointer)data);

    toAttach = gtk_button_new_with_label("->");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 3, 0, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(increaseBoardSizeHeight), (gpointer)data);

    
    toAttach = gtk_label_new("Width:8");
    data->widthLabel = toAttach;
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 2, 1, 1, 1);

    toAttach = gtk_button_new_with_label("<-");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 1, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(decreaseBoardSizeWidth), (gpointer)data);
    
    toAttach = gtk_button_new_with_label("->");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 3, 1, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(increaseBoardSizeWidth), (gpointer)data);

    toAttach = gtk_button_new_with_label("Exit to menu");
    g_signal_connect(toAttach, "clicked", G_CALLBACK(ExitToMenuCallback), (gpointer)scenes);
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 2, 5, 1);

    gtk_stack_add_named(GTK_STACK(scenes), optionsGrid, "Options");


    // creating game scene

    //gtk_stack_add_named(GTK_STACK(scenes), gameScene, "Game");

    gtk_widget_show (win);
}