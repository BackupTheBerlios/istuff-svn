// Tokenizer.h

#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <iostream>
#include <string>
using namespace std;

namespace token {

typedef unsigned char uchar;
typedef uchar CharTokenType;
    
extern CharTokenType WHITESPACE;
extern CharTokenType WORD;
extern CharTokenType SPECIAL;
extern CharTokenType COMMENT;
extern CharTokenType QUOTE;

class Tokenizer
{

public:

    Tokenizer(istream &stream);

    void setCharType(uchar c, CharTokenType type);
    void setCharType(uchar start, uchar end, CharTokenType type);
    void setCharType(const string &s, CharTokenType type);

    bool hasNext();
    string &getNext();
    
protected:

    istream &m_Stream;
    CharTokenType m_CharTokenTypes[256];
    
};

} // namespace token

#endif