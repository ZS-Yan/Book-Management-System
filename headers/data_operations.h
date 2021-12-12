//
// Created by god on 2021/12/12.
//

#ifndef BOOK_SYSTEM_DATA_OPERATIONS_H
#define BOOK_SYSTEM_DATA_OPERATIONS_H

#include "headers/common.h"

int import_book_data_from_file(FILE *ip, BookInfo *bookInfo);

ResultDisplay *import_reader_Data_from_file(FILE *ip, ReaderInfo *readerInfo);

int import_borrow_data_from_File(FILE *ip, BorrowInfo *borrowInfo);

void insert_book(Book *book, BookInfo *bookInfo);

int insert_reader(Reader *reader, ReaderInfo *readerInfo);

void insert_borrow_book(BorrowBook *borrowBook, BorrowInfo *borrowInfo);

#endif //BOOK_SYSTEM_DATA_OPERATIONS_H
