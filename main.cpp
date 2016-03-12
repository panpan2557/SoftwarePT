//
// Created by PUNPIKORN RATTANAWIROJKUL on 2/19/2016 AD.
//
#include "SyllableReader.h"
#include "EntryCounter.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    char* path = new char;

    if (argc > 1) {
        strcpy(path, argv[1]);
        cout << path << endl;
    } else {
        //default
        cout << "Please enter full path of .dat file" << endl;
        exit(0);
    }

    //read file: using SyllableReader library
    SyllableReader::SyllableReader s;
    vector<SyllableReader::entry*> v;
    if (s.readFile(path)) { //return bool to check if things go well
        v = s.getVector();
    }

    //count the vector: using EntryCounter
    EntryCounter::EntryCounter counter;
    long size = counter.getSize(v);
    cout << "number of entry: " << size << endl;

    //print the result
    for (int i = 0 ; i < size ; i++) {
        SyllableReader::entry *e = v.at(i);
        printf("id: %d, word: %s\n", e->id, e->word);
    }
}
