//
// Created by god on 2021/12/16.
//
#include "headers/login_window.h"
#include "headers/user_window.h"
#include "headers/mainWindow.h"

GtkWidget *create_login_window() {
    /*加载系统内读者和管理员身份数据*/
    administratorData = (AdministratorInfo *) malloc(sizeof(AdministratorInfo));
    administratorData->administratorNum = 0;
    FILE *ip1;
    ip1 = fopen("/home/god/Projects/Book-Management-System/Data/administrator_data.txt", "r");
    import_administrator_data_from_file(ip1, administratorData);
    fclose(ip1);
    readerData = (ReaderInfo *) malloc(sizeof(ReaderInfo));
    readerData->readersNum = 0;
    FILE *ip2;
    ip2 = fopen("/home/god/Projects/Book-Management-System/Data/readers.txt", "r");
    import_reader_data_from_file(ip2, readerData);
    fclose(ip2);
    GtkBuilder *builder;
    GtkWidget *login_window;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *login_button;
    GtkWidget *exit_button;
    GtkWidget *choose_switch;
    GtkWidget *register_button;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/Login_window.glade",
                              NULL);
    login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    gtk_window_set_icon(GTK_WINDOW(login_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));
    gtk_window_set_title(GTK_WINDOW(login_window), "图书信息管理系统");
    login_button = GTK_WIDGET(gtk_builder_get_object(builder, "login_button"));
    exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "exit_button"));
    register_button = GTK_WIDGET(gtk_builder_get_object(builder, "register_button"));
    username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    choose_switch = GTK_WIDGET(gtk_builder_get_object(builder, "choose_switch"));

    login_passing_parameters *parameters = (malloc(sizeof(login_passing_parameters)));
    parameters->window = login_window;
    parameters->password_entry = password_entry;
    parameters->username_entry = username_entry;
    parameters->choose_switch = choose_switch;

    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), parameters);
    g_signal_connect(password_entry, "activate", G_CALLBACK(on_password_entry_activate), parameters);
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_button_clicked), parameters);

    return login_window;
}

void on_login_button_clicked(GtkWidget *button, login_passing_parameters *parameters) {
    Identity = gtk_switch_get_active(GTK_SWITCH(parameters->choose_switch));
    if (Identity == true) {
        username = gtk_entry_get_text(GTK_ENTRY(parameters->username_entry));
        int exist_flag = -1;
        for (int i = 0; i < readerData->readersNum; i++) {
            if (strcmp(readerData->readers[i]->username, username) == 0) {
                exist_flag = i;
            }
        }
        if (exist_flag == -1) {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "该用户名不存在！");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        } else {
            const char *password = gtk_entry_get_text(GTK_ENTRY(parameters->password_entry));
            if (strcmp(password, readerData->readers[exist_flag]->password) == 0) {
                GtkWidget *prompt_dialog;
                prompt_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "登录成功！");
                gtk_window_set_title(GTK_WINDOW(prompt_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(prompt_dialog));
                gtk_widget_destroy(prompt_dialog);
                gtk_widget_show_all(create_Enter_window());
            } else {
                GtkWidget *error_dialog;
                error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                      GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "密码输入错误！");
                gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        }
    } else {
        administrator_name = gtk_entry_get_text(GTK_ENTRY(parameters->username_entry));
        int exist_flag = -1;
        for (int i = 0; i < administratorData->administratorNum; i++) {
            if (strcmp(administratorData->administrator[i]->administrator_name, administrator_name) == 0) {
                exist_flag = i;
            }
        }
        if (exist_flag == -1) {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "管理者身份用户名验证失败！");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        } else {
            const char *password = gtk_entry_get_text(GTK_ENTRY(parameters->password_entry));
            if (strcmp(password, administratorData->administrator[exist_flag]->password) == 0) {
                GtkWidget *prompt_dialog;
                prompt_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "登录成功！");
                gtk_window_set_title(GTK_WINDOW(prompt_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(prompt_dialog));
                gtk_widget_destroy(prompt_dialog);
                gtk_widget_show_all(create_Enter_window());
            } else {
                GtkWidget *error_dialog;
                error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                      GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "密码输入错误！");
                gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        }
    }
}

void on_password_entry_activate(GtkWidget *password_entry, login_passing_parameters *parameters) {
    Identity = gtk_switch_get_active(GTK_SWITCH(parameters->choose_switch));
    if (Identity == true) {
        //用户
        username = gtk_entry_get_text(GTK_ENTRY(parameters->username_entry));
        int exist_flag = -1;
        for (int i = 0; i < readerData->readersNum; i++) {
            if (strcmp(readerData->readers[i]->username, username) == 0) {
                exist_flag = i;
            }
        }
        if (exist_flag == -1) {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "该用户名不存在！");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        } else {
            const char *password = gtk_entry_get_text(GTK_ENTRY(parameters->password_entry));
            if (strcmp(password, readerData->readers[exist_flag]->password) == 0) {
                GtkWidget *prompt_dialog;
                prompt_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "登录成功！");
                gtk_window_set_title(GTK_WINDOW(prompt_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(prompt_dialog));
                gtk_widget_destroy(prompt_dialog);
                gtk_widget_show_all(create_Enter_window());
            } else {
                GtkWidget *error_dialog;
                error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                      GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "密码输入错误！");
                gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        }
    } else {
        //管理员
        administrator_name = gtk_entry_get_text(GTK_ENTRY(parameters->username_entry));
        int exist_flag = -1;
        for (int i = 0; i < administratorData->administratorNum; i++) {
            if (strcmp(administratorData->administrator[i]->administrator_name, administrator_name) == 0) {
                exist_flag = i;
            }
        }
        if (exist_flag == -1) {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "管理者身份用户名验证失败！");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        } else {
            const char *password = gtk_entry_get_text(GTK_ENTRY(parameters->password_entry));
            if (strcmp(password, administratorData->administrator[exist_flag]->password) == 0) {
                GtkWidget *prompt_dialog;
                prompt_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "登录成功！");
                gtk_window_set_title(GTK_WINDOW(prompt_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(prompt_dialog));
                gtk_widget_destroy(prompt_dialog);
                gtk_widget_show_all(create_Enter_window());
            } else {
                GtkWidget *error_dialog;
                error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                                      GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "密码输入错误！");
                gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        }
    }
}

void on_register_button_clicked(GtkWidget *button, login_passing_parameters *parameters) {
    if (Identity == true) {
        //TODO:注册窗口
        //TODO:添加用户名、密码格式合法判断，注册时，正则表达式
    } else {
        GtkWidget *error_dialog;
        error_dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "您没有管理员权限\n无法注册管理员身份！");
        gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}

