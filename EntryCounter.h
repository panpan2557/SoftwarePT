//
// Created by PUNPIKORN RATTANAWIROJKUL on 2/20/2016 AD.
//
#include <vector>
#include "SyllableReader.h"
#ifndef SOFTWAREPT_ENTRYCOUNTER_H
#define SOFTWAREPT_ENTRYCOUNTER_H

namespace EntryCounter {
    class EntryCounter {
    public:
        long getSize(std::vector<SyllableReader::entry*> v);
    };
}

#endif //SOFTWAREPT_ENTRYCOUNTER_H
