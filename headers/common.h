//
// Created by god on 2021/12/11.
//

#ifndef BOOK_SYSTEM_COMMON_H
#define BOOK_SYSTEM_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define N 10000
#define true 1
#define false 0

typedef struct {
    char bookId[5];//图书编号
    char bookName[30];//图书名称
    char bookType[20];//图书类型
    char bookAuthor[15];//图书作者
    char bookPub[30];//图书出版社
    char bookPages[4];//总页数
    int status;//借阅状态
    char borrowTime[20];//借出时间
} Book;//图书信息
typedef struct {
    char readId[10];//读者编号
    char readerName[10];//读者姓名
    char readerSex[4];//性别
    char readerTel[13];//电话
    char email[20];//邮箱
    int borrowedNum;//已借阅数量
    int maxBorrowNum;//最大借阅数量
} Reader;//读者信息
typedef struct {
    char readerName[10];
    char bookName[30];
    char bookAuthor[15];
    char bookPub[20];
    char borrowTime[20];
    char returnTime[20];//应归还时间
} BorrowBook;//借阅表
typedef struct {
    Book *books[50];
    int booksNum;//馆藏图书总数
} BookInfo;
typedef struct {
    Reader *readers[50];
    int readersNum;//注册读者总数
} ReaderInfo;
typedef struct {
    BorrowBook *borrowBook[50];
    int borrowNum;//借阅数量总数
} BorrowInfo;
typedef struct {
    int correctNum;
    int wrongNum;
} ResultDisplay;

BookInfo *bookData;
ReaderInfo *readerData;
BorrowInfo *borrowData;

char *bookType[8];

GdkPixbuf *create_pixbuf(const gchar *filename);

void on_return_button_clicked(GtkWidget *button, gpointer window);

int partition(Book *array[], int low, int high);

void Qsort(Book *array[], int low, int high);

int search_book(Book *array[], int length, char *book_id);
#endif //BOOK_SYSTEM_COMMON_H
