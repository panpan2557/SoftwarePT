//
// Created by PUNPIKORN RATTANAWIROJKUL on 2/20/2016 AD.
//

#include "EntryCounter.h"

using namespace std;

namespace EntryCounter
{
    long EntryCounter::getSize(std::vector<SyllableReader::entry*> v) {
        return v.size();
    }
}