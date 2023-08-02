#include<stdio.h>

void showHomeMenu(FILE *stream);

void showHomeMenu(FILE *stream) 
{
    static const char home_menu_text[] = 
        "***************HOME MENU***************\n"
        "PLEASE SELECT: \n"
        "\t1 - NEW FILE\n"
        "\t2 - OPEN FILE\n"
        "\t3 - REMOVE FILE\n"
        "\t4 - HELP\n"
        "\t5 - ABOUT\n"
        "\t0 - EXIT\n"
        "******************END******************\n";
    fputs(home_menu_text,stream);
}