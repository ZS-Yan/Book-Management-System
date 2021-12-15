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
    bookTypeData = (BookType *) malloc(sizeof(BookType));
//    for (int i = 0; i < 20; i++) {
//        bookTypeData->bookType[i] = (char*)malloc(sizeof(char)*20);
//    }
    bookTypeData->bookType[0] = "计算机类";
    bookTypeData->bookType[1] = "生活类";
    bookTypeData->bookType[2] = "文学类";
    bookTypeData->bookType[3] = "历史类";
    bookTypeData->bookType[4] = "体育类";
    bookTypeData->bookType[5] = "艺术类";
    bookTypeData->bookType[6] = "杂志";
    bookTypeData->bookType[7] = "其他";
    bookTypeData->typeNum = 8;

    bookData = (BookInfo *) malloc(sizeof(BookInfo));
    bookData->booksNum = 0;
    FILE *ip;
    ip = fopen("/home/god/Projects/Book-Management-System/Data/book.txt", "r");
    import_book_data_from_file(ip, bookData);
    fclose(ip);

    readerData = (ReaderInfo *) malloc(sizeof(ReaderInfo));
    FILE *ip2;
    ip2 = fopen("/home/god/Projects/Book-Management-System/Data/readers.txt", "r");
    import_reader_data_from_file(ip2, readerData);
    fclose(ip2);
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
    GtkWidget *export_button;
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
    export_button = GTK_WIDGET(gtk_builder_get_object(builder, "export_button"));//获取主窗口中的进入按钮
    Exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Exit_button"));

    g_signal_connect(view_button, "clicked", G_CALLBACK(on_view_button_clicked), main_window);
    g_signal_connect(create_button, "clicked", G_CALLBACK(on_create_button_clicked), main_window);
    g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_button_clicked), main_window);
    g_signal_connect(person_button, "clicked", G_CALLBACK(on_person_button_clicked), main_window);
    g_signal_connect(export_button, "clicked", G_CALLBACK(on_export_button_clicked), main_window);
    g_signal_connect(Exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);//设置“退出按钮”的连接动作
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);//设置主窗口关闭信号链接
    return main_window;
}

void on_view_button_clicked(GtkWidget *button, gpointer window) {
    gtk_widget_show_all(create_view_window());
}

void on_create_button_clicked(GtkWidget *button, gpointer window) {
    gtk_widget_show_all(create_add_window());
}

void on_search_button_clicked(GtkWidget *button, gpointer window) {
    gtk_widget_show_all(create_search_window());
}

void on_person_button_clicked(GtkWidget *button, gpointer window) {
    gtk_widget_show_all(create_view_readers_window());
}

void on_export_button_clicked(GtkWidget *button, gpointer window) {
    GtkWidget *dialog;
    GtkWidget *export_file_button;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_CANCEL, "请选择导出文件位置");
    gtk_window_set_title(GTK_WINDOW(dialog), "提示");
    export_file_button = gtk_dialog_add_button(GTK_DIALOG(dialog), "选择文件夹../", 0);

    g_signal_connect(export_file_button, "clicked", G_CALLBACK(on_export_file_button_clicked), dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


void on_export_file_button_clicked(GtkWidget *button, gpointer dialog) {
    GtkWidget *folder_select_dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;
    folder_select_dialog = gtk_file_chooser_dialog_new("Open Folder", GTK_WINDOW(dialog), action, "_取消",
                                                       GTK_RESPONSE_CANCEL, "_确定", GTK_RESPONSE_ACCEPT, NULL);
    res = gtk_dialog_run(GTK_DIALOG(folder_select_dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *foldername;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(folder_select_dialog);
        foldername = gtk_file_chooser_get_current_folder(chooser);
        if (foldername == NULL) {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "请选择正确的路径！");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        } else {
            char *output_file_location_book = (char *) malloc(sizeof(char) * 200);
            strcpy(output_file_location_book, foldername);
            output_file_location_book = strcat(output_file_location_book, "/book_information.txt");
            //TODO:如何新建文件夹
            FILE *op;
            op = fopen(output_file_location_book, "w");
            for (int i = 0; i < bookData->booksNum; i++) {
                char *status;
                if (bookData->books[i]->status == 1) {
                    status = "已借出";
                } else {
                    status = "在馆";
                }
                fprintf(op, "%s %s %s %s %s %s %s\n", bookData->books[i]->bookId, bookData->books[i]->bookName,
                        bookData->books[i]->bookType, bookData->books[i]->bookAuthor, bookData->books[i]->bookPub,
                        status, bookData->books[i]->borrowTime);
            }
            char *output_file_location_reader = (char *) malloc(sizeof(char) * 200);
            strcpy(output_file_location_reader, foldername);
            output_file_location_reader = strcat(output_file_location_reader, "/reader_information.txt");
            //TODO:如何新建文件夹
            FILE *op2;
            op2 = fopen(output_file_location_reader, "w");
            for (int i = 0; i < readerData->readersNum; i++) {
                char borrowed_num[5];
                sprintf(borrowed_num, "%d", readerData->readers[i]->borrowedNum);
                char max_borrow_num[5];
                sprintf(max_borrow_num, "%d", readerData->readers[i]->maxBorrowNum);
                fprintf(op2, "%s %s %s %s %s %s %s\n", readerData->readers[i]->readerId,
                        readerData->readers[i]->readerName, readerData->readers[i]->readerSex,
                        readerData->readers[i]->readerTel,
                        readerData->readers[i]->email, borrowed_num, max_borrow_num);
            }
            fclose(op);
            fclose(op2);

            GtkWidget *promptdialog;
            promptdialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "导出成功！");
            gtk_window_set_title(GTK_WINDOW(promptdialog), "提示");
            gtk_dialog_run(GTK_DIALOG(promptdialog));
            gtk_widget_destroy(promptdialog);
        }
        g_free(foldername); //TODO:内存释放时出现错误，考虑是重复释放指针或指针值为空的原因
    }
    gtk_widget_destroy(folder_select_dialog);
}