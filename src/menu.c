#include<stdio.h>

void showHomeMenu(FILE *stream);

void showHomeMenu(FILE *stream) 
{
    static const char home_menu_text[] = 
        "***************Home Menu***************\n"
        "Please select: \n"
        "\t1 - Create File\n"
        "\t2 - Open File\n"
        "\t3 - Delete File\n"
        "\t4 - Help\n"
        "\t5 - About\n"
        "\t0 - Exit\n"
        "******************END******************\n";
    fputs(home_menu_text,stream);
}