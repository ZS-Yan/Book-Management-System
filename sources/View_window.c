//
// Created by god on 2021/12/11.
//

#include "headers/View_window.h"

GtkWidget *create_view_window() {
    int flag[6] = {0};
    GtkBuilder *builder;//新建一个GtkBuilder对象用于读取GtkBuilder界面文件
    GtkWidget *view_window;
//    GtkWidget *tree_view;
    GtkWidget *scrolled_window;
    GtkWidget *return_button;
    GtkWidget *current_label;
    GtkWidget *borrow_label;
    GtkWidget *delete_button;
    GtkWidget *delete_all_button;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/god/Projects/Book-Management-System/interface/View_window.glade",
                              NULL);//从glade获取控件
    view_window = GTK_WIDGET(gtk_builder_get_object(builder, "view_window"));//获取主窗体
    gtk_window_set_icon(GTK_WINDOW(view_window),
                        create_pixbuf("/home/god/Projects/Book-Management-System/pictures/book_system.png"));//设置软件图标
    gtk_window_set_title(GTK_WINDOW(view_window), "图书信息管理系统");//设置主窗口标题
    scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled_window"));
    delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "delete_button"));
    delete_all_button = GTK_WIDGET(gtk_builder_get_object(builder, "delete_all_button"));
    return_button = GTK_WIDGET(gtk_builder_get_object(builder, "return_button"));
    current_label = GTK_WIDGET(gtk_builder_get_object(builder, "current_label"));
    borrow_label = GTK_WIDGET(gtk_builder_get_object(builder, "borrow_label"));
    GtkTreeStore *store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);//新建树视图
    GtkTreeIter child_iter;
    GtkTreeIter parents_iter[8];

    int borrow_book_num = 0;
    for (int i = 0; i < bookData->booksNum; i++) {
        char *book_type = bookData->books[i]->bookType;
        int index = find_index(book_type, bookType);
        if (flag[index] == 0) {
            gtk_tree_store_append(store, &parents_iter[index], NULL);
            gtk_tree_store_set(store, &parents_iter[index], COLUMN_TYPE, book_type, -1);
        }
        insert_tree_view(store, parents_iter[index], child_iter, bookData->books[i]);
        flag[index] = 1;

        if (bookData->books[i]->status == 1) {
            borrow_book_num++;
        }
    }
    /*设置label*/
    char current_bookNum[5];
    sprintf(current_bookNum, "%d", bookData->booksNum);
    char borrow_bookNum[5];
    sprintf(borrow_bookNum, "%d", borrow_book_num);
    gtk_label_set_label(GTK_LABEL(current_label), current_bookNum);
    gtk_label_set_label(GTK_LABEL(borrow_label), borrow_bookNum);
    /*建立窗口视图*/
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();//使用文本渲染器
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_TYPE, "图书类别", renderer, "text",
                                                COLUMN_TYPE, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_ID, "图书编号", renderer, "text",
                                                COLUMN_ID, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_NAME, "图书名称", renderer, "text",
                                                COLUMN_NAME, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_AUTHOR, "作者", renderer, "text",
                                                COLUMN_AUTHOR, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_PUB, "出版社", renderer, "text",
                                                COLUMN_PUB, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_PAGES, "总页数", renderer, "text",
                                                COLUMN_PAGES, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_STATUS, "借阅状态", renderer, "text",
                                                COLUMN_STATUS, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view), COLUMN_BORROWTIME, "应归还时间", renderer, "text",
                                                COLUMN_BORROWTIME, NULL);
    gtk_tree_view_expand_all(GTK_TREE_VIEW(tree_view));
    //gtk_tree_view_set_column_drag_function(GTK_TREE_VIEW(tree_view),NULL,NULL,NULL);如何使文本居中？如何使列宽可拖拽
    gtk_tree_view_columns_autosize(GTK_TREE_VIEW(tree_view));
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

    //获取当前选中节点并进行相关操作(此时以编号为唯一标识符)
    GtkTreeSelection *tree_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));


    g_signal_connect(return_button, "clicked", G_CALLBACK(on_return_button_clicked), view_window);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(on_delete_button_clicked), view_window);
    g_signal_connect(delete_all_button, "clicked", G_CALLBACK(on_delete_all_button_clicked), view_window);
    return view_window;
}

int find_index(char *book_type, char *BookType[]) {
    for (int i = 0; i < 8; i++) {
        if (strcmp(book_type, BookType[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void insert_tree_view(GtkTreeStore *store, GtkTreeIter parent_iter, GtkTreeIter child_iter, Book *book)//向树形容器中插入数据
{
    char *status;
    if (book->status == 1) {
        status = "已借出";
    } else {
        status = "在馆";
    }
    gtk_tree_store_append(store, &child_iter, &parent_iter);
    gtk_tree_store_set(store, &child_iter, COLUMN_ID, book->bookId, COLUMN_NAME, book->bookName, COLUMN_AUTHOR,
                       book->bookAuthor, COLUMN_PUB, book->bookPub, COLUMN_PAGES, book->bookPages, COLUMN_STATUS,
                       status, COLUMN_BORROWTIME, book->borrowTime, -1);
    //gtk_tree_store_append: assertion 'VALID_ITER (parent, tree_store)' failed报错：父节点或子节点缺失
}

//TODO:在该页面显示馆藏信息，包括图书存储信息，借阅人数，馆藏数量，图书类别等
void on_delete_button_clicked(GtkWidget *button, gpointer window) {
    GtkWidget *dialog;
    gint res;
    dialog = gtk_message_dialog_new(GTK_WINDOW(parameters->window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "您确定要删除该联系人信息吗？");
    gtk_window_set_title(GTK_WINDOW(dialog), "提示");
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_YES);
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_YES) {
        GtkTreeIter iter;
        //参阅https://docs.gtk.org/gtk3/treeview-tutorial.html
        if (gtk_tree_selection_get_selected(parameters->selection, &parameters->model, &iter))//让iter指向选择的节点
        {
            char *num, *name;
            gtk_tree_model_get(parameters->model, &iter, COLUMN_NUM, &num, COLUMN_NAME, &name, -1);
            if (count_linklist_elem_num(system_data, name) == 1) {
                GtkTreeIter parent_iter;
                //GtkTreeIter *final;
                //int index=to_upper(name[0])-'A';
                //g_print("%d",index);
                //GtkTreeIter p_iter=parents_iter[index];
                gtk_tree_model_iter_parent(parameters->model, &parent_iter, &iter);
                //g_print("%d",gtk_tree_model_iter_has_child(parameters->model,&p_iter));
                //gtk_tree_store_remove(parameters->store, &iter);
                gtk_tree_store_remove(parameters->store,
                                      &parent_iter);//&parent_iter);//此处报错！double free or corruption (out)，内存重复释放，释放父节点时再次释放子节点
                //报段错误是由于跨线程传递指针时出错
                //gtk_tree_iter_free(&parent_iter);
            } else {
                gtk_tree_store_remove(parameters->store, &iter);
            }
            delete_data(system_data, num, name);
            //删除后如何立刻刷新联系人列表？
        }
        //gtk_tree_iter_free(&iter);

    }
    gtk_widget_destroy(dialog);
}

void on_delete_all_button_clicked(GtkWidget *button, gpointer window) {
}