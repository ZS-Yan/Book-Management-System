//
// Created by god on 2021/12/16.
//

#ifndef BOOK_SYSTEM_LOGIN_WINDOW_H
#define BOOK_SYSTEM_LOGIN_WINDOW_H

#include "headers/common.h"
#include "headers/data_operations.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *choose_switch;
} login_passing_parameters;

const char *username;
const char *administrator_name;


GtkWidget *create_login_window();

void on_login_button_clicked(GtkWidget *button, login_passing_parameters *parameters);

void on_password_entry_activate(GtkWidget *password_entry, login_passing_parameters *parameters);

void on_register_button_clicked(GtkWidget *button, login_passing_parameters *parameters);


#endif //BOOK_SYSTEM_LOGIN_WINDOW_H
