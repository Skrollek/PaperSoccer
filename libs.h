#ifndef LIBS_H
#define LIBS_H
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "board.h"

typedef struct ActivationData
{
    // to fill section 
    GtkWidget *scenes; /// gtk stack
    Board *board;
    GtkWidget *heightLabel;
    GtkWidget *widthLabel;
} ActivationData;

#endif