//
// Created by god on 2021/12/11.
//
#include "headers/search_window.h"

GtkWidget *create_search_window() {
    GtkBuilder *builder;//新建一个GtkBuilder对象用于读取GtkBuilder界面文件
    GtkWidget *search_window;
    GtkWidget *Enter_button;
    GtkWidget *Exit_button;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/search_window.glade",
                              NULL);//从glade获取控件

    search_window = GTK_WIDGET(gtk_builder_get_object(builder, "search_window"));//获取主窗体
    gtk_window_set_icon(GTK_WINDOW(search_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));//设置软件图标
    gtk_window_set_title(GTK_WINDOW(search_window), "图书信息管理系统");//设置主窗口标题

    return search_window;
}
