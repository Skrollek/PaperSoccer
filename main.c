#include "libs.h"
#include "callbacks.h"

int main(int argc,char **argv)
{
    GtkApplication *app;
    int stat;

    ActivationData* data = (ActivationData*)malloc(sizeof(ActivationData));
    app  = gtk_application_new("com.github.Skrollek.PaperSoccer", G_APPLICATION_FLAGS_NONE);
    data->app = app;
    g_signal_connect (app, "activate", G_CALLBACK (appActivate), (gpointer)data);
    stat = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}