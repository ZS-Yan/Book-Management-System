//
// Created by god on 2021/12/11.
//
#include "headers/mainWindow.h"
#include "headers/data_operations.h"

GtkWidget *create_Enter_window() {

    GtkBuilder *builder;//新建一个GtkBuilder对象用于读取GtkBuilder界面文件
    GtkWidget *Enter_window;
    GtkWidget *Enter_button;
    GtkWidget *Exit_button;
//    GtkWidget *About_button;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/Enter_window.glade",
                              NULL);//从glade获取控件

    Enter_window = GTK_WIDGET(gtk_builder_get_object(builder, "Enter_window"));//获取主窗体
    gtk_window_set_icon(GTK_WINDOW(Enter_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));//设置软件图标
    gtk_window_set_title(GTK_WINDOW(Enter_window), "图书信息管理系统");//设置主窗口标题
    Enter_button = GTK_WIDGET(gtk_builder_get_object(builder, "Enter_button"));//获取主窗口中的进入按钮
    Exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Exit_button"));//获取主窗口中的退出按钮
//    about_button=GTK_WIDGET(gtk_builder_get_object(builder,"About_button"));//获取主窗口中的按钮

    g_signal_connect(Enter_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);//设置主窗口关闭信号链接
    g_signal_connect(Exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);//设置“退出按钮”的连接动作
    g_signal_connect(Enter_button, "clicked", G_CALLBACK(on_Enter_button_clicked), Enter_window);//设置“进入系统”按钮的回调函数
//    g_signal_connect(About_button, "clicked", G_CALLBACK(on_About_button_clicked), Enter_window);

    return Enter_window;
}

void on_Enter_button_clicked(GtkWidget *button, gpointer window) {
    bookType[0] = "计算机类";
    bookType[1] = "生活类";
    bookType[2] = "文学类";
    bookType[3] = "历史类";
    bookType[4] = "体育类";
    bookType[5] = "艺术类";
    bookType[6] = "杂志";
    bookType[7] = "其他";
    //TODO:杂志类别判断错误
    bookData = (BookInfo *) malloc(sizeof(BookInfo));
//    for (int i = 0; i < 50; i++) {
//        bookData->books[i] = (Book *) malloc(sizeof(Book));
//    }
    bookData->booksNum = 0;
    FILE *ip;
    ip = fopen("/home/god/Projects/Book-Management-System/Data/book.txt", "r");
    import_book_data_from_file(ip, bookData);
    fclose(ip);
    gtk_widget_hide(window);
    gtk_widget_show_all(create_main_window());
}

void on_About_button_clicked(GtkWidget *button, gpointer window) {}

GtkWidget *create_main_window() {
    GtkBuilder *builder;//新建一个GtkBuilder对象用于读取GtkBuilder界面文件
    GtkWidget *main_window;
    GtkWidget *view_button;
    GtkWidget *create_button;
    GtkWidget *search_button;
    GtkWidget *person_button;
    GtkWidget *Exit_button;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/Main_window.glade",
                              NULL);//从glade获取控件

    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));//获取主窗体
    gtk_window_set_icon(GTK_WINDOW(main_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));//设置软件图标
    gtk_window_set_title(GTK_WINDOW(main_window), "图书信息管理系统");//设置主窗口标题
    view_button = GTK_WIDGET(gtk_builder_get_object(builder, "view_button"));
    create_button = GTK_WIDGET(gtk_builder_get_object(builder, "create_button"));
    search_button = GTK_WIDGET(gtk_builder_get_object(builder, "search_button"));//获取主窗口中的进入按钮
    person_button = GTK_WIDGET(gtk_builder_get_object(builder, "person_button"));//获取主窗口中的进入按钮
    Exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Exit_button"));

    g_signal_connect(view_button, "clicked", G_CALLBACK(on_view_button_clicked), main_window);
    g_signal_connect(create_button, "clicked", G_CALLBACK(on_create_button_clicked), main_window);
    g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_button_clicked), main_window);
    g_signal_connect(person_button, "clicked", G_CALLBACK(on_person_button_clicked), main_window);
    g_signal_connect(Exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);//设置“退出按钮”的连接动作
    return main_window;
}

void on_view_button_clicked(GtkWidget *button, gpointer window) {
//    gtk_widget_hide(window);
    gtk_widget_show_all(create_view_window());
}

void on_create_button_clicked(GtkWidget *button, gpointer window) {
//    gtk_widget_show_all()
}

void on_search_button_clicked(GtkWidget *button, gpointer window) {
//    gtk_widget_hide(window);
    gtk_widget_show_all(create_search_window());
}

void on_person_button_clicked(GtkWidget *button, gpointer window) {}