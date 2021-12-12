//
// Created by god on 2021/12/11.
//

#include "headers/View_window.h"

GtkWidget *create_view_window() {
    GtkBuilder *builder;//新建一个GtkBuilder对象用于读取GtkBuilder界面文件
    GtkWidget *view_window;
    GtkWidget *Enter_button;
    GtkWidget *Exit_button;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/view_window.glade",
                              NULL);//从glade获取控件

    view_window = GTK_WIDGET(gtk_builder_get_object(builder, "view_window"));//获取主窗体
    gtk_window_set_icon(GTK_WINDOW(view_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));//设置软件图标
    gtk_window_set_title(GTK_WINDOW(view_window), "图书信息管理系统");//设置主窗口标题
//    view_button = GTK_WIDGET(gtk_builder_get_object(builder, "view_button"));

    return view_window;
}

//TODO:图书创建结构体，读者创建结构体，在该页面显示馆藏信息，包括图书存储信息，借阅人数，馆藏数量，图书类别等