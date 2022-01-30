#include "callbacks.h"
#include "draw.h"

void quitCallback(GtkButton *button, gpointer userData)
{
    GtkWindow *window = GTK_WINDOW (userData);
    gtk_window_destroy (window);
}
void startCallback(GtkButton *button, gpointer userData)
{
    g_print("Game started\n");
    ActivationData *data = (ActivationData*)userData;
    startBoardData(data->board);
    GtkWidget *stack = data->scenes;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Game");

}
void optionCallback(GtkButton *button, gpointer userData)
{
    g_print("Options started\n");
    GtkWidget *stack = ((ActivationData*)userData)->scenes;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Options");
}
void ExitToMenuCallback(GtkButton *button, gpointer userData)
{
    g_print("Exit to menu\n");
    GtkWidget *stack = ((ActivationData*)userData)->scenes;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Menu");
}

void increaseBoardSizeHeight(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->heightLabel;
    if(data->board->height - 3 < 40)
    {
        data->board->height += 2;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; itoa(data->board->height-3, number, 10);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
    
    
}
void decreaseBoardSizeHeight(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->heightLabel;
    if(data->board->height - 3 > 4)
    {
        data->board->height -= 2;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; itoa(data->board->height-3, number, 10);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
}

void increaseBoardSizeWidth(GtkButton *button, gpointer userData)
{
    ActivationData *data = userData;
    GtkWidget *label = data->widthLabel;
    if(data->board->width < 40)
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
    if(data->board->width > 6)
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

void drawCallback(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data)
{
    draw(area, cr, width, height, data);
}

void clickedCallback(GtkGestureClick *gesture, int noPress, double x, double y)
{
    ActivationData *data = g_object_get_data(G_OBJECT(gesture), "ActivationData");
    Board *board = data->board;
    double squareSize = 600.0/(board->width-1);
    if(600.0/(board->height+1) < squareSize) squareSize = 600.0/(board->height-1);
    double xTranslate = 400-squareSize*((board->width)/2);
    double yTranslate = 400-squareSize*((board->height)/2);
    int32_t alfa = (int32_t)floor((x - xTranslate + squareSize/2)/squareSize); // ???
    int32_t beta = (int32_t)floor((y - yTranslate + squareSize/2)/squareSize); // ???
    //printf("%f %f\n", xTranslate, yTranslate);
    //printf("%f %f\n", x, y);
    //printf("%d %d\n", alfa, beta);
    uint8_t possibleMoves = calculatePossibleMoves(board, board->ballX, board->ballY);
    Direction direction = coordsToDirection(board->ballX, board->ballY, alfa, beta);
    if(direction != Error)
    {
        if((possibleMoves & (1 << direction)) && isMovePossible(board, board->ballX, board->ballY, direction))
        {
            *boardDirectionUsedAt(board, board->ballX, board->ballY, direction) = 1;
            *boardDirectionUsedAt(board, alfa, beta, oppositeDirection(direction)) = 1;
            *boardVisitedAt(board, alfa, beta) = 1;
            board->ballX = alfa;
            board->ballY = beta;
        }
    }
    gtk_widget_queue_draw(gtk_stack_get_child_by_name(GTK_STACK(data->scenes), "Game"));
}

void appActivate (GApplication *app, gpointer userData) 
{
    g_print ("GtkApplication is activated.\n");
    ActivationData *data = (ActivationData*)userData;

    GtkWidget *scenes = gtk_stack_new();
    data->scenes = scenes;
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
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 800);
    gtk_window_set_resizable(GTK_WINDOW(win), 0);
    gtk_window_set_child(GTK_WINDOW(win), scenes);
    /// creating main menu
   
    boxMenu = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_set_homogeneous(GTK_BOX(boxMenu), true);
    
    btnStart = gtk_button_new_with_label("Start Game");
    g_signal_connect(btnStart, "clicked", G_CALLBACK(startCallback), (gpointer)data);

    btnOption = gtk_button_new_with_label("Options");
    g_signal_connect(btnOption, "clicked", G_CALLBACK(optionCallback), (gpointer)data);
    
    btnQuit = gtk_button_new_with_label("Quit");
    g_signal_connect(btnQuit, "clicked", G_CALLBACK(quitCallback), win);
    
    gtk_box_append(GTK_BOX(boxMenu), btnStart);
    gtk_box_append(GTK_BOX(boxMenu), btnOption);
    gtk_box_append(GTK_BOX(boxMenu), btnQuit);

    char* css = ".text-button{font-size: 50pt;}";
    GtkCssProvider* fontCSS =  gtk_css_provider_new();
    gtk_css_provider_load_from_data(fontCSS, css, strlen(css));

    char* cssLabel = ".title{font-size: 50pt;}";
    GtkCssProvider* labelCSS = gtk_css_provider_new();
    gtk_css_provider_load_from_data(labelCSS, cssLabel, strlen(cssLabel));

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
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)labelCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    toAttach = gtk_button_new_with_label("<-");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 0, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(decreaseBoardSizeHeight), (gpointer)data);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    toAttach = gtk_button_new_with_label("->");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 3, 0, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(increaseBoardSizeHeight), (gpointer)data);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    toAttach = gtk_label_new("Width:8");
    data->widthLabel = toAttach;
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 2, 1, 1, 1);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)labelCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    toAttach = gtk_button_new_with_label("<-");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 1, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(decreaseBoardSizeWidth), (gpointer)data);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    toAttach = gtk_button_new_with_label("->");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 3, 1, 2, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(increaseBoardSizeWidth), (gpointer)data);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    toAttach = gtk_button_new_with_label("Exit to menu");
    gtk_grid_attach(GTK_GRID(optionsGrid), toAttach, 0, 2, 5, 1);
    g_signal_connect(toAttach, "clicked", G_CALLBACK(ExitToMenuCallback), (gpointer)data);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(toAttach)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_stack_add_named(GTK_STACK(scenes), optionsGrid, "Options");

    // creating game scene
    GtkGesture *clickController = gtk_gesture_click_new();
    g_object_set_data(G_OBJECT(clickController), "ActivationData", (gpointer)data);
    g_signal_connect (clickController, "pressed", G_CALLBACK (clickedCallback), (gpointer)data);
    gameScene = gtk_drawing_area_new();
    gtk_widget_add_controller(gameScene, GTK_EVENT_CONTROLLER(clickController));
    gtk_stack_add_named(GTK_STACK(scenes), gameScene, "Game");
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA (gameScene), drawCallback, (gpointer)data, NULL);

    gtk_widget_show (win);
}