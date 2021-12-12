//
// Created by god on 2021/12/11.
//

#ifndef BOOK_SYSTEM_MAINWINDOW_H
#define BOOK_SYSTEM_MAINWINDOW_H


#include "headers/common.h"
#include "headers/View_window.h"
#include "headers/search_window.h"

GtkWidget *create_Enter_window();

void on_Enter_button_clicked(GtkWidget *button, gpointer window);

void on_About_button_clicked(GtkWidget *button, gpointer window);

void on_view_button_clicked(GtkWidget *button, gpointer window);

void on_create_button_clicked(GtkWidget *button, gpointer window);

void on_search_button_clicked(GtkWidget *button, gpointer window);

void on_person_button_clicked(GtkWidget *button, gpointer window);

GtkWidget *create_main_window();

#endif //BOOK_SYSTEM_MAINWINDOW_H
