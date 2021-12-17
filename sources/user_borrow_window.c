//
// Created by god on 2021/12/16.
//
#include "headers/user_borrow_window.h"

void create_user_borrow_window() {
    GtkBuilder *builder;//新建一个GtkBuilder对象用于读取GtkBuilder界面文件
    GtkWidget *user_borrow_window;
    GtkWidget *borrow_button;
    GtkWidget *return_button;
    GtkWidget *name_entry;
    user_borrow_passing_parameters *parameters = (user_borrow_passing_parameters *) malloc(
            sizeof(user_borrow_passing_parameters));
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/user_borrow_window.glade",
                              NULL);//从glade获取控件
    user_borrow_window = GTK_WIDGET(gtk_builder_get_object(builder, "user_borrow_window"));//获取主窗体
    gtk_window_set_icon(GTK_WINDOW(user_borrow_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));//设置软件图标
    gtk_window_set_title(GTK_WINDOW(user_borrow_window), "图书信息管理系统");//设置主窗口标题
    borrow_button = GTK_WIDGET(gtk_builder_get_object(builder, "borrow_button"));
    return_button = GTK_WIDGET(gtk_builder_get_object(builder, "return_button"));
    parameters->window = user_borrow_window;
    parameters->name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "name_entry"));
    parameters->id_entry = GTK_WIDGET(gtk_builder_get_object(builder, "id_entry"));
    parameters->type_entry = GTK_WIDGET(gtk_builder_get_object(builder, "type_entry"));
    parameters->pages_entry = GTK_WIDGET(gtk_builder_get_object(builder, "pages_entry"));
    parameters->author_entry = GTK_WIDGET(gtk_builder_get_object(builder, "author_entry"));
    parameters->pub_entry = GTK_WIDGET(gtk_builder_get_object(builder, "pub_entry"));
    borrow_flag = 0;
    g_signal_connect(parameters->name_entry, "leave-notify-event", G_CALLBACK(on_name_entry_leave_notified),
                     parameters);
    //TODO:若动作为'leave_notify_event',一调用就报错，变量丢失
    g_signal_connect(return_button, "clicked", G_CALLBACK(on_return_button_clicked), user_borrow_window);
    gtk_widget_show_all(user_borrow_window);
//    return user_borrow_window;
}

void on_name_entry_leave_notified(GtkWidget *name_entry, GdkEvent *event, user_borrow_passing_parameters *parameters) {
    GdkEventType type = event->type;
    if (type == GDK_LEAVE_NOTIFY) {
        const char *book_name = gtk_entry_get_text(GTK_ENTRY(name_entry));
        int index = search_book_name(bookData->books, bookData->booksNum, book_name);
        //TODO:心灵鸡汤找不到
        if (index != -1) {
            gtk_entry_set_text(GTK_ENTRY(parameters->id_entry), bookData->books[index]->bookId);
            gtk_entry_set_text(GTK_ENTRY(parameters->type_entry), bookData->books[index]->bookType);
//            char *p = gtk_entry_get_text(GTK_ENTRY(parameters->type_entry));
            gtk_entry_set_text(GTK_ENTRY(parameters->pages_entry), bookData->books[index]->bookPages);
            gtk_entry_set_text(GTK_ENTRY(parameters->author_entry), bookData->books[index]->bookAuthor);
            gtk_entry_set_text(GTK_ENTRY(parameters->pub_entry), bookData->books[index]->bookPub);
        }
    }
}