// jph.h

#ifndef _JPH_H_
#define _JPH_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace jph
{

enum PropertyType { EMPTY, STRING, LIST, HASH };

class Property;
class PropertyList;
class PropertyHash;



class Property
{

public:

    Property();
    Property(const char *s);
    Property(const string &s);
    Property(const PropertyList &pl);
    Property(const PropertyHash &ph);
    Property(const Property &p);
    ~Property();

    PropertyType type();
    string &str();
    PropertyList &list();
    PropertyHash &hash();

    Property &operator=(const char *s);
    Property &operator=(const string &s);
    Property &operator=(const PropertyList &pl);
    Property &operator=(const PropertyHash &ph);
    Property &operator=(const Property &p);
    
    friend ostream &operator<<(ostream &stream, Property &p);
    friend istream &operator>>(istream &stream, Property &p);
    
protected:
    
    PropertyType m_Type;
    union {
        string *m_Str;
        PropertyList *m_List;
        PropertyHash *m_Hash;
    } ;

    void clear();
    void set(const char *s);
    void set(const string &s);
    void set(const PropertyList &pl);
    void set(const PropertyHash &ph);
    void set(const Property &p);
    
};



class PropertyList : public vector<Property>
{
public:

    void add(const Property &p)
        { push_back(p); }

    friend ostream &operator<<(ostream &stream, PropertyList &pl);
    friend istream &operator>>(istream &stream, PropertyList &pl);
};



class PropertyHash : public map<string,Property>
{
public:

    bool exists(const string &s) const
        { return (find(s) != end()); }
    void add(const string &s, const Property &p)
        { insert(make_pair<string,Property>(s,p)); }

    friend ostream &operator<<(ostream &stream, PropertyHash &ph);
    friend istream &operator>>(istream &stream, PropertyHash &ph);
};



}

#endif