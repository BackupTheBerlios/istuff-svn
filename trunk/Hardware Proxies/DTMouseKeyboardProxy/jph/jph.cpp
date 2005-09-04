// jph.cpp

#include "jph.h"

#include "Tokenizer.h"
using namespace token;

namespace jph
{

static string JPH_WHITESPACE(
"\0\1\2\3\4\5\6\7\10\11\12\13\14\15\16\17\20\21\22\23\24\25\26\27\30\31\32\33\34\35\36\37\40=", 34);

static inline bool containsAnyOf(const string &s, const string &chars)
{
    return (s.find_first_of(chars) != string::npos);
}
    
Property::Property()
{
    set(NULL);
}

Property::Property(const char *s)
{
    set(s);
}

Property::Property(const string &s)
{
    set(s);
}

Property::Property(const PropertyList &pl)
{
    set(pl);
}

Property::Property(const PropertyHash &ph)
{
    set(ph);
}

Property::Property(const Property &p)
{
    set(p);
}

Property::~Property()
{
    clear();
}

void Property::clear()
{
    if (m_Type == STRING) delete m_Str;
    else if (m_Type == LIST) delete m_List;
    else if (m_Type == HASH) delete m_Hash;
    m_Type = EMPTY;
    m_Str = NULL;
}

void Property::set(const char *s)
{
    if (s == NULL)
    {
        m_Type = EMPTY;
        m_Str = NULL;
    }
    else
    {
        m_Type = STRING;
        m_Str = new string(s);
    }
}

void Property::set(const string &s)
{
    m_Type = STRING;
    m_Str = new string(s);
}

void Property::set(const PropertyList &pl)
{
    m_Type = LIST;
    m_List = new PropertyList(pl);
}

void Property::set(const PropertyHash &ph)
{
    m_Type = HASH;
    m_Hash = new PropertyHash(ph);
}

void Property::set(const Property &p)
{
    m_Type = p.m_Type;
    if (m_Type == EMPTY) m_Str = NULL;
    else if (m_Type == STRING) m_Str = new string(*p.m_Str);
    else if (m_Type == LIST) m_List = new PropertyList(*p.m_List);
    else if (m_Type == HASH) m_Hash = new PropertyHash(*p.m_Hash);
}

PropertyType Property::type()
{
    return m_Type;
}

string &Property::str()
{
    if (m_Type == STRING) return (*m_Str);
    return *new string();
}

PropertyList &Property::list()
{
    if (m_Type == LIST) return (*m_List);
    return *new PropertyList();
}

PropertyHash &Property::hash()
{
    if (m_Type == HASH) return (*m_Hash);
    return *new PropertyHash();
}

Property &Property::operator=(const char *s)
{
    clear();
    set(s);
    return *this;
}

Property &Property::operator=(const string &s)
{
    clear();
    set(s);
    return *this;
}

Property &Property::operator=(const PropertyList &pl)
{
    clear();
    set(pl);
    return *this;
}

Property &Property::operator=(const PropertyHash &ph)
{
    clear();
    set(ph);
    return *this;
}

Property &Property::operator=(const Property &p)
{
    clear();
    set(p);
    return *this;
}

ostream &operator<<(ostream &stream, Property &p)
{
    switch (p.type())
    {
        case EMPTY: break;
        case STRING:
            if (containsAnyOf(*p.m_Str,JPH_WHITESPACE)) stream << "'" << *p.m_Str << "'";
            else stream << *p.m_Str;
            break;
        case LIST: stream << *p.m_List; break;
        case HASH: stream << *p.m_Hash; break;
    }
    return stream;
}

istream &operator>>(istream &stream, Property &p)
{
    Tokenizer tok(stream);
    tok.setCharType('#', COMMENT);
    tok.setCharType('=', WHITESPACE);
    tok.setCharType("(){}", SPECIAL);
    tok.setCharType("\"\'", QUOTE);

    string &s = tok.getNext();
    if (s == "{") { PropertyHash ph; stream >> ph; p.set(ph); } 
    else if (s == "(") { PropertyList pl; stream >> pl; p.set(pl); }
    else p.set(s);
    
    return stream;
}



ostream &operator<<(ostream &stream, PropertyList &pl)
{
    PropertyList::iterator i;
    stream << "( ";
    for(i = pl.begin(); i != pl.end(); i++)
        stream << *i << " ";
    stream << ")";
    return stream;
}

istream &operator>>(istream &stream, PropertyList &pl)
{
    Property p;
    while (stream)
    {
        stream >> p;
        if (p.type() == STRING && p.str() == ")") break;
        pl.add(p);
    }
    return stream;
}



ostream &operator<<(ostream &stream, PropertyHash &ph)
{
    PropertyHash::iterator i;
    stream << "{" << endl;
    for(i = ph.begin(); i != ph.end(); i++)
    {
        if (containsAnyOf(i->first,JPH_WHITESPACE)) stream << "'" << i->first << "'";
        else stream << i->first;
        stream << " = " << i->second << endl;
    }
    stream << "}";
    return stream;
}

istream &operator>>(istream &stream, PropertyHash &ph)
{
    Tokenizer tok(stream);
    tok.setCharType('#', COMMENT);
    tok.setCharType('=', WHITESPACE);
    tok.setCharType("(){}", SPECIAL);
    tok.setCharType("\"\'", QUOTE);
    
    string s;
    Property p;
    while (stream)
    {
        s = tok.getNext();
        if (stream.eof() || s == "}") break;
        stream >> p;
        if (p.type() == STRING && p.str() == "}") break;
        ph.add(s,p);
    }
    
    return stream;
}

}
