//
// Created by Letton on 30.09.2023.
//

#ifndef INC_2_PRACTICE_BOOK_H
#define INC_2_PRACTICE_BOOK_H

#include <istream>

struct Book {
    long long isbn;
    std::string author;
    std::string title;

    Book(long long isbn, std::string author, std::string title);
};


#endif //INC_2_PRACTICE_BOOK_H
