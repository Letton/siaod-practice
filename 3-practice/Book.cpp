//
// Created by Letton on 30.09.2023.
//

#include "Book.h"
#include <string>

Book::Book(long long isbn, std::string author, std::string title) : isbn(isbn),
                                                                    author(std::move(author)),
                                                                    title(std::move(title)) {}
