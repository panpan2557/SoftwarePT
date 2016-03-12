//
// Created by PUNPIKORN RATTANAWIROJKUL on 2/18/2016 AD.
//

#ifndef SOFTWAREPT_SYLLABLEREADER_H
#define SOFTWAREPT_SYLLABLEREADER_H

#include <fstream>
#define FILEID_SIZE (256)
#include <vector>

#define MAX_SYLLABLE_TEXTSIZE (1023)

namespace SyllableReader
{
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

    struct entry {
        int id;
        char word[1023];
    };

    class SyllableReader
    {
        //attributes
    private:
        std::ifstream input;
        int sizeOfRecord;
        char* temp;
        char path[120];
        std::vector<entry*> entryList;
    public:
        //return true if file is available and can be opened
        bool readFile(char* filepath);
        std::vector<entry*> getVector();

    };
}

#endif //SOFTWAREPT_SYLLABLEREADER_H
