//
// Created by god on 2021/12/11.
//

#ifndef BOOK_SYSTEM_VIEW_WINDOW_H
#define BOOK_SYSTEM_VIEW_WINDOW_H


#include "headers/common.h"
enum {
    COLUMN_TYPE,
    COLUMN_ID,
    COLUMN_NAME,
    COLUMN_AUTHOR,
    COLUMN_PUB,
    COLUMN_PAGES,
    COLUMN_STATUS,
    COLUMN_BORROWTIME,
    N_COLUMNS
};

GtkWidget *create_view_window();

int find_index(char *book_type, char *BookType[]);

void insert_tree_view(GtkTreeStore *store, GtkTreeIter parent_iter, GtkTreeIter child_iter, Book *book);

void on_delete_button_clicked(GtkWidget *button, gpointer window);

void on_delete_all_button_clicked(GtkWidget *button, gpointer window);

#endif //BOOK_SYSTEM_VIEW_WINDOW_H
