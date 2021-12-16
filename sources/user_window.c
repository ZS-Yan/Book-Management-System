//
// Created by god on 2021/12/16.
//
#include "headers/user_window.h"

GtkWidget *create_user_window() {
    GtkBuilder *builder;
    GtkWidget *user_window;
    GtkWidget *user_view_button;
    GtkWidget *user_borrow_button;
    GtkWidget *user_return_book_button;
    GtkWidget *user_person_button;
    GtkWidget *user_exit_button;
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/user_window.glade",
                              NULL);
    user_window = GTK_WIDGET(gtk_builder_get_object(builder, "user_window"));
    user_view_button = GTK_WIDGET(gtk_builder_get_object(builder, "user_view_button"));
    user_borrow_button = GTK_WIDGET(gtk_builder_get_object(builder, "user_borrow_button"));
    user_return_book_button = GTK_WIDGET(gtk_builder_get_object(builder, "user_return_book_button"));
    user_person_button = GTK_WIDGET(gtk_builder_get_object(builder, "user_person_button"));
    user_exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "user_exit_button"));
    gtk_window_set_icon(GTK_WINDOW(user_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));
    gtk_window_set_title(GTK_WINDOW(user_window), "图书信息管理系统");
    g_signal_connect(user_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    return user_window;
}
