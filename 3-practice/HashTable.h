//
// Created by Letton on 30.09.2023.
//

#ifndef INC_2_PRACTICE_HASHTABLE_H
#define INC_2_PRACTICE_HASHTABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "Book.h"

class HashTable {
private:
    struct Entry {
        long long key;
        long long book_index;
        bool occupied;

        Entry();
    };

    Entry *table_;
    long long capacity_;
    long long size_;
    double load_factor_;

    long long Hash(const long long &key) const;

    long long QuadraticProbe(long long index, long long attempt) const;

    void rehash();

public:
    std::vector<Book> data_;

    explicit HashTable(long long initial_capacity);

    ~HashTable();

    void insert(long long isbn, const std::string &author, const std::string &title);

    void remove(long long isbn);

    long long find(long long isbn);

    void display();
};


#endif //INC_2_PRACTICE_HASHTABLE_H
