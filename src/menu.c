#include<stdio.h>

void showHomeMenu(FILE *stream);

void showHomeMenu(FILE *stream) 
{
    static const char home_menu_text[] = 
        "***************Home Menu***************\n"
        "Please enter: \n"
        "\t1 - Create New File\n"
        "\t2 - Open Existing File\n"
        "\t3 - List Existing File\n"
        "\t0 - Exit\n"
        "******************END******************\n";
    fputs(home_menu_text,stream);
}