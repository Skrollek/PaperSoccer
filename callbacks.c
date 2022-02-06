#include "callbacks.h"

void quitCallback(GtkButton *button, gpointer userData)
{
    ActivationData *data = (ActivationData*)userData;

    gtk_window_destroy (GTK_WINDOW(data->mainWindow));
    gtk_window_destroy (GTK_WINDOW(data->secondaryWindow));
    //g_print("%s\n", data->board->moves);
}
void startCallback(GtkButton *button, gpointer userData)
{
    //g_print("Game started\n");
    ActivationData *data = (ActivationData*)userData;
    startBoardData(data->board);
    GtkWidget *stack = data->scenes;
    g_signal_handler_disconnect(data->mainWindow, data->mainWindowHandlerID);
    g_signal_handler_disconnect(data->secondaryWindow, data->secondaryWindowHandlerID);
    data->mainWindowHandlerID = g_signal_connect(GTK_WIDGET(data->mainWindow), "close-request", G_CALLBACK(destroyWindows), data);
    data->secondaryWindowHandlerID = g_signal_connect(GTK_WIDGET(data->secondaryWindow), "close-request", G_CALLBACK(destroyWindows), data);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Game");
    gtk_widget_show (data->secondaryWindow);
    gtk_window_set_title(GTK_WINDOW(data->mainWindow), "PaperSoccer Player 1");
    gtk_window_set_modal(GTK_WINDOW(data->secondaryWindow), 0);
    gtk_window_set_modal(GTK_WINDOW(data->mainWindow), 1);
}
void optionCallback(GtkButton *button, gpointer userData)
{
    //g_print("Options started\n");
    GtkWidget *stack = ((ActivationData*)userData)->scenes;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Options");
}
void ExitToMenuCallback(GtkButton *button, gpointer userData)
{
    //g_print("Exit to menu\n");
    GtkWidget *stack = ((ActivationData*)userData)->scenes;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Menu");
}

void loadMenuCallback(GtkButton *button, gpointer userData)
{
    //g_print("Exit to menu\n");
    GtkWidget *stack = ((ActivationData*)userData)->scenes;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "Load");
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
        char number[5]; sprintf(number, "%d", data->board->height-3);
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
        char number[5]; sprintf(number, "%d", data->board->height-3);
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
        char number[5]; sprintf(number, "%d", data->board->width-1);
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
        char number[5]; sprintf(number, "%d", data->board->width-1);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);
    }
}

void clickedCallback(GtkGestureClick *gesture, int noPress, double x, double y)
{
    ActivationData *data = g_object_get_data(G_OBJECT(gesture), "ActivationData");
    Board *board = data->board;
    //printf("%d\n", board->playerOnMove);
    double squareSize = 600.0/(board->width-1);
    if(600.0/(board->height+1) < squareSize) squareSize = 600.0/(board->height-1);
    double xTranslate = 400-squareSize*((board->width)/2);
    double yTranslate = 400-squareSize*((board->height)/2);
    int16_t alfa = (int16_t)floor((x - xTranslate + squareSize/2)/squareSize); // ???
    int16_t beta = (int16_t)floor((y - yTranslate + squareSize/2)/squareSize); // ???
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
            board->ballX = alfa;
            board->ballY = beta;
            if(!bounce(board, alfa, beta))
            {
                if(!board->playerOnMove)
                {
                    gtk_window_set_modal(GTK_WINDOW(data->secondaryWindow), 1);
                    gtk_window_set_modal(GTK_WINDOW(data->mainWindow), 0);
                }
                else
                {
                    gtk_window_set_modal(GTK_WINDOW(data->secondaryWindow), 0);
                    gtk_window_set_modal(GTK_WINDOW(data->mainWindow), 1);
                } 
                board->playerOnMove = !board->playerOnMove;
                board->moves[board->it++] = '#';
                board->moves[board->it++] = ' ';
            }
            board->moves[board->it++] = direction + '0';
            board->moves[board->it++] = ' ';
            *boardVisitedAt(board, alfa, beta) = 1;
        }

        if(gameEnded(data->board))
        {
            bool winner = declareWinner(data->board);
            gtk_window_set_modal(GTK_WINDOW(data->secondaryWindow), 0);
            gtk_window_set_modal(GTK_WINDOW(data->mainWindow), 1);
            gtk_widget_hide(data->secondaryWindow);
            gtk_window_set_title(GTK_WINDOW(data->mainWindow), "PaperSoccer");
            gtk_stack_set_visible_child_name(GTK_STACK(data->scenes), "End");
            g_signal_handler_disconnect(data->mainWindow, data->mainWindowHandlerID);
            g_signal_handler_disconnect(data->secondaryWindow, data->secondaryWindowHandlerID);
            data->mainWindowHandlerID = g_signal_connect(GTK_WIDGET(data->mainWindow), "close-request", G_CALLBACK(quitCallback), data);
            data->secondaryWindowHandlerID = g_signal_connect(GTK_WIDGET(data->secondaryWindow), "close-request", G_CALLBACK(quitCallback), data);
            if(winner)
            {
                gtk_label_set_label(GTK_LABEL(data->label), "Player 2 won\nDo you want to save?");
            }
            else
            {
                gtk_label_set_label(GTK_LABEL(data->label), "Player 1 won\nDo you want to save?");
            }
        }
    }
    gtk_widget_queue_draw(gtk_stack_get_child_by_name(GTK_STACK(data->scenes), "Game"));
    gtk_widget_queue_draw(gtk_window_get_child(GTK_WINDOW(data->secondaryWindow)));

}

void saveFileCallback(GtkWidget *widget, gpointer userData)
{
    ActivationData *data = (ActivationData*)userData;
    FILE *saveFile = fopen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget) ) ), "w");
    if(saveFile == NULL)
    {
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), "Could not open or create file!!!", 32);
    }
    else
    {
        fprintf(saveFile, "%d %d\n", data->board->width, data->board->height);
        fputs(data->board->moves, saveFile);
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), "", -1);
        gtk_entry_set_placeholder_text(GTK_ENTRY(widget), "Write file name (with .txt at the end) here and press enter");
        g_print("File saved!");
        fclose(saveFile);
        gtk_stack_set_visible_child_name(GTK_STACK(data->scenes), "Menu");
    }
}

void saveQuitCallback(GtkWidget *widget, gpointer userData)
{
    ActivationData *data = (ActivationData*)userData;
    FILE *saveFile = fopen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget) ) ), "w");
    if(saveFile == NULL)
    {
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), "Could not open or create file!!!", 32);
    }
    else
    {
        fprintf(saveFile, "%d %d\n", data->board->width, data->board->height);
        fputs(data->board->moves, saveFile);
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), "", -1);
        g_print("File saved!");
        fclose(saveFile);
        gtk_window_destroy(GTK_WINDOW(data->saveWindow));
    }
}
void loadMovesFromFile(GtkWindow *widget, gpointer userData)
{  
    ActivationData *data = (ActivationData*)userData;
    FILE *readFile = fopen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget) ) ), "r");
    if(readFile == NULL)
    {
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)), "Could not open or create file!!!", 32);
    }
    else
    {
        uint16_t initialWidth;
        uint16_t initialHeight;
        fscanf(readFile, "%hu %hu", &initialWidth, &initialHeight);
        data->board->width = initialWidth;
        data->board->height = initialHeight;
        startBoardData(data->board);
        int c;
        while((c = fgetc(readFile)) != EOF)
        {
            data->board->moves[data->board->it++] = c;
        }
        boardCatchUpToMoves(data->board);
        GtkWidget *stack = data->scenes;
        g_signal_handler_disconnect(data->mainWindow, data->mainWindowHandlerID);
        g_signal_handler_disconnect(data->secondaryWindow, data->secondaryWindowHandlerID);
        data->mainWindowHandlerID = g_signal_connect(GTK_WIDGET(data->mainWindow), "close-request", G_CALLBACK(destroyWindows), data);
        data->secondaryWindowHandlerID = g_signal_connect(GTK_WIDGET(data->secondaryWindow), "close-request", G_CALLBACK(destroyWindows), data);
        gtk_stack_set_visible_child_name(GTK_STACK(stack), "Game");
        gtk_widget_show (data->secondaryWindow);
        gtk_window_set_title(GTK_WINDOW(data->mainWindow), "PaperSoccer Player 1");

        GtkWidget *label = data->widthLabel;
        char newText[16]; strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        int i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        char number[5]; sprintf(number, "%d", data->board->width-1);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);

        label = data->heightLabel;
        strcpy(newText, gtk_label_get_label(GTK_LABEL(label)));
        i = 16;
        while(newText[--i] != ':') newText[i] = 0;  
        sprintf(number, "%d", data->board->height-3);
        strcat(newText, number);
        gtk_label_set_label(GTK_LABEL(label), newText);

        if(data->board->playerOnMove)
        {
            gtk_window_set_modal(GTK_WINDOW(data->secondaryWindow), 1);
            gtk_window_set_modal(GTK_WINDOW(data->mainWindow), 0);
        }
        else
        {
            gtk_window_set_modal(GTK_WINDOW(data->secondaryWindow), 0);
            gtk_window_set_modal(GTK_WINDOW(data->mainWindow), 1);
        }
        
    }
}

void destroyWindows(GtkWindow *widget, gpointer userData)
{
    ActivationData *data = (ActivationData*)userData;
    GtkWidget *saveWindow = gtk_application_window_new(GTK_APPLICATION(data->app));
    data->saveWindow = saveWindow;
    // creating save screen
    GtkWidget *saveScreen;
    GtkWidget *toAttach;
    saveScreen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_window_set_child(GTK_WINDOW(saveWindow), saveScreen);
    toAttach = gtk_label_new("Do you want to save?");
    gtk_box_append(GTK_BOX(saveScreen), toAttach);
    toAttach = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(toAttach), 64);
    gtk_entry_set_placeholder_text(GTK_ENTRY(toAttach), "Write file name (with .txt at the end) here and press enter");
    g_signal_connect(toAttach, "activate", G_CALLBACK(saveQuitCallback), (gpointer)data);
    gtk_box_append(GTK_BOX(saveScreen), toAttach);
    gtk_widget_show(data->saveWindow);
    quitCallback(NULL, userData);
}

void appActivate (GApplication *app, gpointer userData) 
{
    g_print ("GtkApplication is activated.\n");
    ActivationData *data = (ActivationData*)userData;

    GtkWidget *win = gtk_application_window_new(GTK_APPLICATION(app));
    data->mainWindowHandlerID = g_signal_connect(GTK_WIDGET(win), "close-request", G_CALLBACK(quitCallback), data);
    data->mainWindow = win;
    GtkWidget *secondaryWindow = gtk_application_window_new(GTK_APPLICATION(app));
    data->secondaryWindowHandlerID = g_signal_connect(GTK_WIDGET(secondaryWindow), "close-request", G_CALLBACK(quitCallback), data);
    data->secondaryWindow = secondaryWindow;
    

    GtkWidget *scenes = gtk_stack_new();
    data->scenes = scenes;

    GtkWidget *boxMenu;
    GtkWidget *btnStart;
    GtkWidget *btnLoad;
    GtkWidget *btnOption;
    GtkWidget *btnQuit;

    GtkWidget *optionsGrid;
    GtkWidget *loadBox;

    GtkWidget *gameScene;
    GtkWidget *secondaryWindowGameScene;

    GtkWidget *endScreen;


    Board* board = initializeBoard(8, 12);
    data->board = board;

    gtk_window_set_title(GTK_WINDOW(win), "PaperSoccer");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 800);
    gtk_window_set_resizable(GTK_WINDOW(win), 0);
    gtk_window_set_child(GTK_WINDOW(win), scenes);

    gtk_window_set_title(GTK_WINDOW(secondaryWindow), "PaperSoccer Player 2");
    gtk_window_set_default_size(GTK_WINDOW(secondaryWindow), 800, 800);
    gtk_window_set_resizable(GTK_WINDOW(secondaryWindow), 0);

    data->secondaryWindow = secondaryWindow;

    /// creating main menu
    boxMenu = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_set_homogeneous(GTK_BOX(boxMenu), true);
    
    btnStart = gtk_button_new_with_label("Start Game");
    g_signal_connect(btnStart, "clicked", G_CALLBACK(startCallback), (gpointer)data);

    btnLoad = gtk_button_new_with_label("Load Game");
    g_signal_connect(btnLoad, "clicked", G_CALLBACK(loadMenuCallback), (gpointer)data);

    btnOption = gtk_button_new_with_label("Options");
    g_signal_connect(btnOption, "clicked", G_CALLBACK(optionCallback), (gpointer)data);
    
    btnQuit = gtk_button_new_with_label("Quit");
    g_signal_connect(btnQuit, "clicked", G_CALLBACK(quitCallback), (gpointer)data);
    
    gtk_box_append(GTK_BOX(boxMenu), btnStart);
    gtk_box_append(GTK_BOX(boxMenu), btnLoad);
    gtk_box_append(GTK_BOX(boxMenu), btnOption);
    gtk_box_append(GTK_BOX(boxMenu), btnQuit);
    
    char* css = ".text-button{font-size: 50pt;}";
    GtkCssProvider* fontCSS =  gtk_css_provider_new();
    gtk_css_provider_load_from_data(fontCSS, css, strlen(css));

    char* cssLabel = ".font-size{font-size: 50pt;}";
    GtkCssProvider* labelCSS = gtk_css_provider_new();
    gtk_css_provider_load_from_data(labelCSS, cssLabel, strlen(cssLabel));
    
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnStart)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(btnLoad)), (GtkStyleProvider*)fontCSS, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
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
    //gtk_widget_set_name(toAttach, "Label");
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

    // creating load menu
    loadBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    toAttach = gtk_label_new("Write name of file with moves data in box below");
    data->label = toAttach;
    gtk_box_append(GTK_BOX(loadBox), toAttach);
    toAttach = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(toAttach), 128);
    gtk_entry_set_placeholder_text(GTK_ENTRY(toAttach), "Write file name (with .txt at the end) here and press enter");
    g_signal_connect(toAttach, "activate", G_CALLBACK(loadMovesFromFile), (gpointer)data);
    gtk_box_append(GTK_BOX(loadBox), toAttach);
    toAttach = gtk_button_new_with_label("Menu");
    g_signal_connect(toAttach, "clicked", G_CALLBACK(ExitToMenuCallback), (gpointer)data);
    gtk_box_append(GTK_BOX(loadBox), toAttach);

    gtk_stack_add_named(GTK_STACK(scenes), loadBox, "Load");
    
    // creating game scene
    GtkGesture *clickController = gtk_gesture_click_new();
    g_signal_connect (clickController, "pressed", G_CALLBACK (clickedCallback), (gpointer)data);
    g_object_set_data(G_OBJECT(clickController), "ActivationData", (gpointer)data);
    gameScene = gtk_drawing_area_new();
    gtk_widget_add_controller(gameScene, GTK_EVENT_CONTROLLER(clickController));
    gtk_stack_add_named(GTK_STACK(scenes), gameScene, "Game");
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA (gameScene), draw, (gpointer)data, NULL);

    GtkGesture *sndClickController = gtk_gesture_click_new();
    g_signal_connect (sndClickController, "pressed", G_CALLBACK (clickedCallback), (gpointer)data);
    g_object_set_data(G_OBJECT(sndClickController), "ActivationData", (gpointer)data);
    secondaryWindowGameScene = gtk_drawing_area_new();
    gtk_widget_add_controller(secondaryWindowGameScene, GTK_EVENT_CONTROLLER(sndClickController));
    gtk_window_set_child(GTK_WINDOW(secondaryWindow), secondaryWindowGameScene);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA (secondaryWindowGameScene), draw, (gpointer)data, NULL);

    // creating end screen
    endScreen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    toAttach = gtk_label_new("Player 1 won\nDo you want to save?");
    data->label = toAttach;
    gtk_box_append(GTK_BOX(endScreen), toAttach);
    toAttach = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(toAttach), 128);
    gtk_entry_set_placeholder_text(GTK_ENTRY(toAttach), "Write file name (with .txt at the end) here and press enter");
    g_signal_connect(toAttach, "activate", G_CALLBACK(saveFileCallback), (gpointer)data);
    gtk_box_append(GTK_BOX(endScreen), toAttach);
    toAttach = gtk_button_new_with_label("Menu");
    g_signal_connect(toAttach, "clicked", G_CALLBACK(ExitToMenuCallback), (gpointer)data);
    gtk_box_append(GTK_BOX(endScreen), toAttach);
    
    gtk_stack_add_named(GTK_STACK(scenes), endScreen, "End");
    
    gtk_stack_set_visible_child_name(GTK_STACK(scenes), "Menu");
    gtk_widget_show (win);
}