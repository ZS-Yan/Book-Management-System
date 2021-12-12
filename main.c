//
// Created by god on 2021/12/11.
//
#include "headers/mainWindow.h"

int main(int argc, char *argv[]) {
    GtkWidget *Enter_window;
    gtk_init(&argc, &argv);
    Enter_window = create_Enter_window(); //创建主窗口
    gtk_widget_show_all(Enter_window); //显示主窗口
    gtk_main();
}

