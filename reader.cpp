//compile command: g++ -liconv -o reader reader.cpp
//run command: ./reader <number_of_output>
//ex: ./reader 20

#include <iostream>
#include <fstream>
#include <iconv.h>
using namespace std;

#define FILEID_SIZE (256)
#define MAX_SYLLABLE_TEXTSIZE (1023)

typedef union _fileid_fileun
{
    struct fileid_crack_st
    {
        uint16_t ui16MagicKey;
        uint16_t ui16Type;
        uint16_t ui16EntrySize;
        uint16_t _filler;
        uint32_t ui32NumEntry;
        time_t tTimeStamp;
    } crack;
    char szRaw[FILEID_SIZE];
} FILEID;

typedef struct syllable_data_record_st
{
    uint32_t ui32SylID;
    uint16_t ui2Lang:2;
    uint16_t ui10Len:10;
    uint16_t ui1HasTailSpace:1;
    uint16_t ui1IsUnused:1;
    uint16_t ui1Numeric:1;
    uint16_t _filler:1;
    uint32_t ui32MapFilePos;
    time_t tTimeStamp;
    char szText[MAX_SYLLABLE_TEXTSIZE];
} SYLLABLE_DATA_RECORD;

int main(int argc, char* argv[]) {
    //initialization
    int sizeOfRecord;
    char* temp;

    //read file
    ifstream input;
    char path[100] = "/Users/Punpikorn/ClionProjects/SoftwarePT/SyllableDB-V1.dat";
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

//        strcpy(record->szText, temp);
        //translate the input text
        iconv_t charset = iconv_open("UTF8", "CP874");
        size_t inSize = MAX_SYLLABLE_TEXTSIZE;
        size_t outSize = MAX_SYLLABLE_TEXTSIZE;
        char *input = &temp[0];
        char *output = &record->szText[0];
        iconv(charset, &input, &inSize, &output, &outSize);

        //print result
        printf("id: %d, lang: %d, text: %s\n", record->ui32SylID, record->ui2Lang, record->szText);
    }

    return 0;
}

