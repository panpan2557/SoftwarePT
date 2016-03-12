//
// Created by PUNPIKORN RATTANAWIROJKUL on 2/18/2016 AD.
//
#include <stdexcept>
#include <fstream>
#include <iconv.h>
#include "SyllableReader.h"

using namespace std;

class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    int mId;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s, int id);
    bool searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s, int id)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


bool Trie::searchWord(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}

namespace SyllableReader
{

    bool SyllableReader::readFile(char *filepath) {
        Trie* trie = new Trie();

        strcpy(path, filepath);
        input.open(path, ios::in|ios::out);
        input.seekg(256); //skip the header

        SYLLABLE_DATA_RECORD* record = (SYLLABLE_DATA_RECORD*) malloc(sizeof(SYLLABLE_DATA_RECORD));


        //until the end of file or the output exceeds
        while(!input.eof()) {
            //read the record
            input.read(reinterpret_cast<char*>(record), sizeof(SYLLABLE_DATA_RECORD) - (sizeof(char)*1024));

            //read szText
            sizeOfRecord = record->ui10Len + 1;
            temp = (char*)malloc(sizeOfRecord);
            input.read(temp, sizeOfRecord);

            //translate the input text
            iconv_t charset = iconv_open("UTF8", "CP874");
            size_t inSize = MAX_SYLLABLE_TEXTSIZE;
            size_t outSize = MAX_SYLLABLE_TEXTSIZE;
            char *input = &temp[0];
            char *output = &record->szText[0];
            iconv(charset, &input, &inSize, &output, &outSize);

            //add data to trie
            trie->addWord(record->szText);
        }
        return true;
    }

    vector<entry*> SyllableReader::getVector() {
        return entryList;
    }
}
