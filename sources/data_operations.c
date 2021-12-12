//
// Created by god on 2021/12/12.
//

#include "headers/data_operations.h"

int import_book_data_from_file(FILE *ip, BookInfo *bookInfo) {
    const char whitespace[] = " "; //分隔符
    const char linebreak[] = "\n"; //换行符
    char buffer[200];              //缓冲区
    int count = 0;                 //记录读取了多少条数据
    while (fgets(buffer, N, ip))   //按行读取
    {
        Book *book = (Book *) malloc(sizeof(Book));
        unsigned int length = strlen(buffer);
        /*进行字符串分割*/
        strcpy(book->bookId, strtok(buffer, whitespace));
        strcpy(book->bookName, strtok(NULL, whitespace));
        strcpy(book->bookType, strtok(NULL, whitespace));
        strcpy(book->bookAuthor, strtok(NULL, whitespace));
        strcpy(book->bookPub, strtok(NULL, whitespace));
        strcpy(book->bookPages, strtok(NULL, whitespace));
        book->status = strtok(NULL, whitespace)[0] - '0';
        strcpy(book->borrowTime, strtok(NULL, linebreak));
        insert_book(book, bookInfo);
        count++;
    }
    return count;
}

ResultDisplay *import_reader_Data_from_file(FILE *ip, ReaderInfo *readerInfo) {
//    int count = 0;
    ResultDisplay *result = (ResultDisplay *) malloc(sizeof(ResultDisplay));
    char readId[10];//读者编号
    char readerName[10];//读者姓名
    char readerSex[4];//性别
    char readerTel[13];//电话
    char email[20];//邮箱
    int borrowedNum;//已借阅数量
    int maxBorrowNum;//最大借阅数量
    while (EOF != fscanf(ip, "%s %s %s %s %s %d %d", readId, readerName,
                         readerSex, readerTel, email,
                         &borrowedNum, &maxBorrowNum)) {
        Reader *reader = (Reader *) malloc(sizeof(Reader));
        strcpy(reader->readId, readId);
        strcpy(reader->readerName, readerName);
        strcpy(reader->readerSex, readerSex);
        strcpy(reader->readerTel, readerTel);
        strcpy(reader->email, email);
        reader->borrowedNum = borrowedNum;
        reader->maxBorrowNum = maxBorrowNum;
        if (insert_reader(reader, readerInfo) == true) {
            result->correctNum++;
        } else {
            result->wrongNum++;
        }
    }
    return result;
}

int import_borrow_data_from_File(FILE *ip, BorrowInfo *borrowInfo) {
    const char whitespace[] = " "; //分隔符
    const char linebreak[] = "\n"; //换行符
    char buffer[200];              //缓冲区
    int count = 0;                 //记录读取了多少条数据
    while (fgets(buffer, N, ip))   //按行读取
    {
        BorrowBook *borrowBook = (BorrowBook *) malloc(sizeof(BorrowBook));
        unsigned int length = strlen(buffer);
        /*进行字符串分割*/
        strcpy(borrowBook->readerName, strtok(buffer, whitespace));
        strcpy(borrowBook->bookName, strtok(NULL, whitespace));
        strcpy(borrowBook->bookAuthor, strtok(NULL, whitespace));
        strcpy(borrowBook->bookPub, strtok(NULL, whitespace));
        strcpy(borrowBook->borrowTime, strtok(NULL, whitespace));
        strcpy(borrowBook->returnTime, strtok(NULL, linebreak));
        insert_borrow_book(borrowBook, borrowInfo);
        count++;
    }
    return count;
}

void insert_book(Book *book, BookInfo *bookInfo) {
    //检测数据合法性
    int flag = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(book->bookType, bookType[i]) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        strcpy(book->bookType, bookType[5]);
    }
    bookInfo->books[bookInfo->booksNum++] = book;
}

int insert_reader(Reader *reader, ReaderInfo *readerInfo) {
    if (strcmp(reader->readerSex, "man") == 0) {
        strcpy(reader->readerSex, "男");
    }
    if (strcmp(reader->readerSex, "woman") == 0) {
        strcpy(reader->readerSex, "女");
    }
    if (strcmp(reader->readerSex, "男") == 0 || strcmp(reader->readerSex, "女") == 0) {
        readerInfo->readers[readerInfo->readersNum++] = reader;
        return true;
    } else {
        return false;
    }
}

void insert_borrow_book(BorrowBook *borrowBook, BorrowInfo *borrowInfo) {
    borrowInfo->borrowBook[borrowInfo->borrowNum++] = borrowBook;
}




