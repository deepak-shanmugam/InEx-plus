#include<stdio.h>

void showHomeMenu(FILE *stream);
void showFileMenu(FILE *stream, const char *name, int isSaved);
void showAddOperationMenu(FILE *stream);
void showViewOperationMenu(FILE *stream);

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
        "\t\n"
        "PRESS 'CTRL + D' FOR EMERGENCY EXIT\n"
        "******************END******************\n";
    fputs(home_menu_text, stream);
}

void showFileMenu(FILE *stream, const char *name, int isSaved)
{
    static char ch = '*';
    static const char file_menu_text[] =
        "***************FILE MENU***************\n"
        "PLEASE SELECT: \n"
        "\t1 - ADD RECORD\n"
        "\t2 - MODIFY RECORD\n"
        "\t3 - VIEW RECORD\n"
        "\t4 - FILTER RECORD\n"
        "\t5 - SAVE\n"
        "\t6 - FILE DETAILS\n"
        "\t7 - CLOSE FILE\n"
        "\t0 - EXIT\n"
        "\t\n"
        "PRESS 'CTRL + D' FOR EMERGENCY EXIT\n"
        "******************END******************\n";
    if (isSaved) {
        ch = ' ';
    } else {
        ch = '*';
    }
    fprintf(stream,"FILE NAME: %c%s\n",ch,name);
    fputs(file_menu_text, stream);
}

void showAddOperationMenu(FILE *stream)
{
    static const char add_op_menu_text[] =
        "PLEASE SELECT: \n"
        "\t1 - INCOME\n"
        "\t2 - EXPENSE\n"
        "\t0 - CANCEL\n"
        "\t\n"
        "PRESS 'CTRL + D' FOR EMERGENCY EXIT\n";
    fputs(add_op_menu_text, stream);
}

void showViewOperationMenu(FILE *stream)
{
    static const char view_op_menu_text[] =
        "PLEASE SELECT: \n"
        "\t1 - INCOME\n"
        "\t2 - EXPENSE\n"
        "\t3 - BOTH\n"
        "\t0 - CANCEL\n"
        "\t\n"
        "PRESS 'CTRL + D' FOR EMERGENCY EXIT\n";
    fputs(view_op_menu_text, stream);
}