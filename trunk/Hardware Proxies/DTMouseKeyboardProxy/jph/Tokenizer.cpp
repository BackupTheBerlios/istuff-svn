// Tokenizer.cpp

#include "Tokenizer.h"

namespace token {

CharTokenType WHITESPACE = 0;
CharTokenType WORD = 1;
CharTokenType SPECIAL = 2;
CharTokenType COMMENT = 3;
CharTokenType QUOTE = 4;

Tokenizer::Tokenizer(istream &stream) : m_Stream(stream)
{
    setCharType(0x00, 0x20, WHITESPACE);
    setCharType(0x21, 0xFF, WORD);
}

void Tokenizer::setCharType(uchar c, CharTokenType type)
{
    m_CharTokenTypes[c] = type;
}

void Tokenizer::setCharType(uchar start, uchar end, CharTokenType type)
{
    for(int c=start; c<=end; c++) m_CharTokenTypes[(uchar)c] = type;
}

void Tokenizer::setCharType(const string &s, CharTokenType type)
{
    for(unsigned int i=0; i<s.size(); i++) m_CharTokenTypes[(uchar)s[i]] = type;
}

bool Tokenizer::hasNext()
{
    return !m_Stream.eof();
}

string &Tokenizer::getNext()
{
    char c;
    CharTokenType type;
    string *s = new string();

    while (m_Stream.get(c))
    {
        type = m_CharTokenTypes[c];
        if (type == WHITESPACE)
        {
            if(s->size() > 0) break;
        }
        else if (type == WORD)
        {
            s->append(1,c);
        }
        else if (type == SPECIAL)
        {
            if(s->size() > 0) m_Stream.putback(c);
            else s->append(1,c);
            break;
        }
        else if (type == COMMENT)
        {
            m_Stream.ignore(0x7FFFFFFF,'\n');
        }
        else if (type == QUOTE)
        {
            if(s->size() > 0) m_Stream.putback(c);
            char qc = c;
            while(m_Stream.get(c)) { if (c == qc) break; else s->append(1,c); }
            break;
        }
    }
        
    return *s;
}
    
} // namespace token