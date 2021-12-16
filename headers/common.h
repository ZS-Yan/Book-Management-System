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
typedef struct {
    char bookId[10];//图书编号
    char bookName[50];//图书名称
    char bookType[20];//图书类型
    char bookAuthor[15];//图书作者
    char bookPub[30];//图书出版社
    char bookPages[4];//总页数
    int status;//借阅状态
    char borrowTime[20];//借出时间
} Book;//图书信息
enum {
    COLUMN_READERID,
    COLUMN_READERNAME,
    COLUMN_READERSEX,
    COLUMN_READERTEL,
    COLUMN_READEREMAIL,
    COLUMN_BORROWEDNUM,
    COLUMN_MAXBORROWNUM,
    N_READER_COLUMNS
};
typedef struct {
    char username[30];
    char password[50];
    char readerId[10];//读者编号
    char readerName[10];//读者姓名
    char readerSex[4];//性别
    char readerTel[13];//电话
    char email[20];//邮箱
    int borrowedNum;//已借阅数量
    int maxBorrowNum;//最大借阅数量
} Reader;//读者信息
enum {
    COLUMN_BORROWID,
    COLUMN_BORROWREADERNAME,
    COLUMN_BORROWBOOKNAME,
    COLUMN_BORROWBOOKAUTHOR,
    COLUMN_BORROWBOOKPUB,
    COLUMN_BORROWBORROWTIME,
    COLUMN_RETURNTIME,
    N_BORROW_COLUMNS
};
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
typedef struct {
    char *bookType[20];
    int typeNum;
} BookType;
typedef struct {
    char administrator_name[30];
    char password[30];
} Administrator;
typedef struct {
    Administrator *administrator[30];
    int administratorNum;
} AdministratorInfo;
BookInfo *bookData;
ReaderInfo *readerData;
BorrowInfo *borrowData;
BookType *bookTypeData;
AdministratorInfo *administratorData;

GdkPixbuf *create_pixbuf(const gchar *filename);

void on_return_button_clicked(GtkWidget *button, gpointer window);

int partition(Book *array[], int low, int high);

void Qsort(Book *array[], int low, int high);

void Quick_sort(Book *array[], int length);

int partition_reader(Reader *array[], int low, int high);

void Qsort_reader(Reader *array[], int low, int high);

void Quick_sort_reader(Reader *array[], int length);

int search_book(Book *array[], int length, const char *book_id);

int search_reader(Reader *array[], int length, const char *reader_id);

#endif //BOOK_SYSTEM_COMMON_H
