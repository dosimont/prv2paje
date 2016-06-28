#ifndef PRVPARSER_H
#define PRVPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <boost/tokenizer.hpp>

#include <stdlib.h>

#include "prvreader_config.h"
#include "pcfparser.h"
#include "interpretercomponent.h"
#include "prvmetadata.h"
#include "prvevent.h"
#include "prvevents.h"
#include "prvstate.h"
#include "prvcommunications.h"
#include "prvother.h"




using namespace std;
using namespace boost;

namespace prvreader{

    class PrvParser
    {
    public:
        PrvParser(ifstream* prvStream, PcfParser* pcfParser);
        ~PrvParser();
        PrvEvent* parseLine();
        PrvMetaData *getPrvMetaData() const;
        PcfParser *getPcfParser() const;

    private:
        PrvEvent* parseHeader(tokenizer<escaped_list_separator<char> > *tokens);
        PrvEvent* parseEvents(tokenizer<escaped_list_separator<char> > *tokens, long currentTimestamp, long lineNumber);
        PrvEvent* parseState(tokenizer<escaped_list_separator<char> > *tokens, long currentTimestamp, long lineNumber);
        PrvEvent* parseCommunications(tokenizer<escaped_list_separator<char> > *tokens, long currentTimestamp, long lineNumber);
        enum Mode{Header, Body};
        ifstream* prvStream;
        InterpreterComponent* interpreterComponent;
        PcfParser* pcfParser;
        PrvMetaData* prvMetaData;
        Mode mode;
        long lineNumber;
        long currentTimestamp;
    };

}

#endif // PRVPARSER_H
