/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TFakeHashTable.h,v 1.7 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TFAKEHASHTABLE_H_
#define _IDK_UT_TFAKEHASHTABLE_H_

#include <idk_ut_Types.h>
#include <algorithm>
#include <idk_ut_TRealIterator.h>

/** @file
 The definition of idk_ut_TFakeHashTable class and other supporting
 classes and macros.
 @see idk_ut_TFakeHashTable,
 idk_ut_TFakeHashTableValueConstIterator,
 idk_ut_TFakeHashTableValueIterator,
 idk_ut_TFakeHashTableKeyConstIterator
 */

/**
 Provides a 'fake' hashtable.
 This class provides a data structure which looks like hashtable,
 but implemented with only one bucket -- <i>O(n)</i> search.
 However, probably this is a bit faster than a normal vector since
 it uses hash values to compare at the first stage.

 @todo I wish someday a genious guy implements a true hashtable and
 we can execute s/FAKEHASHTABLE/HASHTABLE/.

 @param KeyType Type of the key.
 @param DataType Type of the value.
 @param HashFunc A hash function class.
 This class must have member function 'int operator()(const KeyType& key)'
 which returns the hash value of the key.
 @param EqualsFunc A equals function class.
 This class must have member function 'int operator()(const KeyType& lh, const KeyType& rh)'
 which returns non-zero if lh and rh are identical.
 */
template <class KeyType, class DataType, class HashFunc, class EqualsFunc>
class IDK_DECL idk_ut_TFakeHashTable {
public:
	typedef KeyType key_type;
	typedef DataType data_type;
	typedef pair<key_type, data_type> value_type;

private:
	struct Entry {
		int m_hashCode;
		value_type m_value;

		Entry(int hashCode, const value_type& value)
			: m_hashCode(hashCode), m_value(value) {}
		Entry(const Entry& other)
			: m_hashCode(other.m_hashCode), m_value(other.m_value) {}
		Entry& operator=(const Entry& other) {
			m_hashCode = other.m_hashCode;
			m_value = other.m_value;
			return *this;
		}
	};

	typedef IDK_UT_VECTOR(Entry) EntryVector;
	typedef typename EntryVector::iterator EntryVectorIterator;
	typedef typename EntryVector::const_iterator EntryVectorConstIterator;
	EntryVector m_entries;
	HashFunc m_hashFunc;
	EqualsFunc m_equalsFunc;

public:
	/**
	 Mutable iterator to the entries in the table.
	 You can modify the value through this iterator, but never change the key.
	 @todo I have implemented only minimal operations.
	 */
	class iterator {
	friend class idk_ut_TFakeHashTable<KeyType, DataType, HashFunc, EqualsFunc>;
	private:
		EntryVectorIterator m_pos;
		iterator(const EntryVectorIterator& ptr) : m_pos(ptr) {}
	public:
		~iterator() {}
		/** Creates an object which points at the end.*/
		iterator() {}
		/** Copy constructor. */
		iterator(const iterator& other) : m_pos(other.m_pos) {}
		/** Returns a mutable reference to the pair of key and value.
		    You can modify the value, but never change the key. */
		value_type& operator*() { return (*m_pos).m_value; }
		/** Increments the iterator.
		    Note that only pre-increment operator is supported. */
		iterator& operator++() { ++m_pos; return *this; } // only pre-increment is supported

		int operator==(const iterator& other) { return m_pos == other.m_pos; }
		int operator!=(const iterator& other) { return m_pos != other.m_pos; }
		iterator& operator=(const iterator& other) { m_pos = other.m_pos; return *this; }
	};

	/**
	 Constant iterator to the entries in the table.
	 @todo I have implemented only minimal operations.
	 */
	class const_iterator {
	friend class idk_ut_TFakeHashTable<KeyType, DataType, HashFunc, EqualsFunc>;
	private:
		EntryVectorConstIterator m_pos;
		const_iterator(const EntryVectorConstIterator& ptr) : m_pos(ptr) {}

	public:
		~const_iterator() {}
		/** Creates an object which points at the end.*/
		const_iterator() {}
		/** Copy constructor. */
		const_iterator(const const_iterator& other) : m_pos(other.m_pos) {}
		/** Returns a const reference to the pair of key and value. */
		const value_type& operator*() { return (*m_pos).m_value; }
		/** Increments the iterator.
		    Note that only pre-increment operator is supported. */
		const_iterator& operator++() { ++m_pos; return *this; }

		int operator==(const const_iterator& other) { return m_pos == other.m_pos; }
		int operator!=(const const_iterator& other) { return m_pos != other.m_pos; }
		const_iterator& operator=(const const_iterator& other) { m_pos = other.m_pos; return *this; }
	};

public:
	~idk_ut_TFakeHashTable() {}

	/**
	 Creates an object.
	 */
	idk_ut_TFakeHashTable() {}

	/**
	 Clears the content.
	 */
	void clear() { m_entries.clear(); }

	/**
	 Inserts a new entry.
	 @param value A pair of key and value.
	 @return A pair of an iterator and an integer.
	 The formar is the iterator which points to the inserted entry.
	 The latter would be non-zero if the entry was newly created,
	 or zero if the existing value was replaced.
	 */
	pair<iterator, int> insert(const value_type& value) {
		int hashCode = m_hashFunc(value.first);
		iterator i = findImpl(value.first, hashCode);
		if (i != end()) {
			(*i).second = value.second;
			return pair<iterator, int>(i, 0);
		} else {
			i = m_entries.insert(m_entries.end(), Entry(hashCode, value));
			return pair<iterator, int>(i, 1);
		}
	}

	/**
	 Inserts a new entry.  See insert(const value_type& value) for more
	 details.
	 */
	pair<iterator, int> insert(const key_type& key, const data_type& data) {
		return insert(value_type(key, data));
	}

	/**
	 Searches the entry whose key is the specified value.
	 @return An iterator which points to the found entry.
	 If no entry was found, it would indicate end().
	 */
	iterator find(const key_type& key) {
		return findImpl(key, m_hashFunc(key));
	}

	/**
	 Searches the entry whose key is the specified value.
	 @return An const_iterator which points to the found entry.
	 If no entry was found, it would indicate end().
	 */
	const_iterator find(const key_type& key) const {
		return findConstImpl(key, m_hashFunc(key));
	}

	/**
	 Erases the entry whose key is the specified value.
	 @return Non-zero if an entry was erased, or zero if no entry was found.
	 */
	int erase(const key_type& key) {
		iterator i = find(key);
		if (i == end()) {
			return 0;
		} else {
			m_entries.erase(i.m_pos);
			return 1;
		}
	}

	/**
	 Erases the entry pointed by the specified iterator.
	 */
	void erase(iterator pos) {
		m_entries.erase(pos.m_pos);
	}

	/**
	 Returns the number of entries in the table.
	 */
	int size() const { return m_entries.size(); }

	/**
	 Returns an iterator which points to the beginning of the entries.
	 */
	iterator begin() { return m_entries.begin(); }

	/**
	 Returns a const_iterator which points to the beginning of the entries.
	 */
	const_iterator begin() const { return m_entries.begin(); }

	/**
	 Returns an iterator which points to the end of the entries.
	 */
	iterator end() { return m_entries.end(); }

	/**
	 Returns a const_iterator which points to the end of the entries.
	 */
	const_iterator end() const { return m_entries.end(); }

private:
	iterator findImpl(const key_type& key, int hashCode) {
		EntryVectorIterator ei = m_entries.begin();
		while (ei != m_entries.end()) {
			if ((*ei).m_hashCode == hashCode &&
				m_equalsFunc((*ei).m_value.first, key)) break;
			++ei;
		}
		return iterator(ei);
	}

	const_iterator findConstImpl(const key_type& key, int hashCode) const {
		EntryVectorConstIterator ei = m_entries.begin();
		while (ei != m_entries.end()) {
			if ((*ei).m_hashCode == hashCode &&
				m_equalsFunc((*ei).m_value.first, key)) break;
			++ei;
		}
		return const_iterator(ei);
	}
};

/**
 Declaration of 'Fake' hashtable type.
 <i>Actually this macro provides no more additional value than
 declaring the template name directly.
 It is only for consistency with other macros for data structure
 type declaration (e.g. IDK_UT_VECTOR).</i>
 */
#define IDK_UT_FAKEHASHTABLE(KeyType, DataType, HashFunc, EqualsFunc) \
	idk_ut_TFakeHashTable<KeyType, DataType, HashFunc, EqualsFunc >

//
// helper iterators
//

/**
 Iterator implementing idk_ut_ITIterator<T> interface which iterates
 values on a constant hashtable.
 <p>Note that this class is reference-semantics unlike STL's iterator.
 You have to allocate this object on the heap, and hold by a
 smartpointer (to keep the ownership) or a pointer (just to reference).
 <p>The type returned by this iterator should not violate the constness of
 the hashtable.  i.e. Non-pointer types (e.g. int) or const pointer types
 can be acceptable.

 @param HashTableType Type of the hashtable to be iterated.
 @param ResultType Type of returned value which must be compatible
 with the value type of the hashtable.
 */
template <class HashTableType, class ResultType>
class idk_ut_TFakeHashTableValueConstIterator : public idk_ut_TRealIterator<ResultType>
{
private:
	typename HashTableType::const_iterator m_cur;
	typename HashTableType::const_iterator m_end;

public:
	~idk_ut_TFakeHashTableValueConstIterator() {}

	/**
	 Creates an object.
	 Allocate the object on the heap, not on the stack.
	 @param table Hashtable to be iterated.
	 */
	idk_ut_TFakeHashTableValueConstIterator(const HashTableType& table) {
		m_cur = table.begin();
		m_end = table.end();
	}

	/**
	 Returns the next value.
	 */
	ResultType next() {
		ResultType result = (*m_cur).second;
		++m_cur;
		return result;
	}

	/**
	 Returns non-zero if there are values left to be iterated.
	 */
	int hasNext() {
		return m_cur != m_end;
	}
};


/**
 Iterator implementing idk_ut_ITIterator<T> interface which iterates
 values on a mutable hashtable.
 <p>Note that this class is reference-semantics unlike STL's iterator.
 You have to allocate this object on the heap, and hold by a
 smartpointer (to keep the ownership) or a pointer (just to reference).
 <p>The type returned by this iterator can mutate the hashtable.
 i.e. Non-constant pointer types or smartpointer types can be acceptable.

 @param HashTableType Type of the hashtable to be iterated.
 @param ResultType Type of returned value which must be compatible
 with the value type of the hashtable.
 */
template <class HashTableType, class ResultType>
class idk_ut_TFakeHashTableValueIterator : public idk_ut_TRealIterator<ResultType>
{
private:
	typename HashTableType::iterator m_cur;
	typename HashTableType::iterator m_end;
public:
	~idk_ut_TFakeHashTableValueIterator() {}

	/**
	 Creates an object.
	 Allocate the object on the heap, not on the stack.
	 @param pTable Pointer to the hashtable to be iterated.
	 (Why pointer? because the iterator may modify the table)
	 */
	idk_ut_TFakeHashTableValueIterator(HashTableType* pTable) {
		m_cur = (*pTable).begin();
		m_end = (*pTable).end();
	}

	/**
	 Returns the next value.
	 */
	ResultType next() {
		ResultType result = (*m_cur).second;
		++m_cur;
		return result;
	}

	/**
	 Returns non-zero if there are values left to be iterated.
	 */
	int hasNext() {
		return m_cur != m_end;
	}
};


/**
 Iterator implementing idk_ut_ITIterator<T> interface which iterates
 keys on a constant hashtable.
 <p>Note that this class is reference-semantics unlike STL's iterator.
 You have to allocate this object on the heap, and hold by a
 smartpointer (to keep the ownership) or a pointer (just to reference).
 <p>The type returned by this iterator should not violate the constness of
 the hashtable.  i.e. Non-pointer types (e.g. int) or const pointer types
 can be acceptable.

 @param HashTableType Type of the hashtable to be iterated.
 @param ResultType Type of returned value which must be compatible
 with the value type of the hashtable.
 */
template <class HashTableType, class ResultType>
class idk_ut_TFakeHashTableKeyConstIterator : public idk_ut_TRealIterator<ResultType>
{
private:
	typename HashTableType::const_iterator m_cur;
	typename HashTableType::const_iterator m_end;
public:
	~idk_ut_TFakeHashTableKeyConstIterator() {}

	/**
	 Creates an object.
	 Allocate the object on the heap, not on the stack.
	 @param table Hashtable to be iterated.
	 */
	idk_ut_TFakeHashTableKeyConstIterator(const HashTableType& table) {
		m_cur = table.begin();
		m_end = table.end();
	}

	/**
	 Returns the next value.
	 */
	ResultType next() {
		const ResultType& result = (*m_cur).first;
		++m_cur;
		return result;
	}

	/**
	 Returns non-zero if there are keys left to be iterated.
	 */
	int hasNext() {
		return m_cur != m_end;
	}
};

//
// 
//

#include <idk_ut_StringHashFuncs.h>

/**
 'Fake' hashtable type where string type is the key.
 @param DataType Type of the value.
 */
#define IDK_UT_STRING_FAKEHASHTABLE(DataType) \
	IDK_UT_FAKEHASHTABLE(idk_string, DataType, \
		idk_ut_StringHashFunc, idk_ut_StringEqualsFunc)

/**
 'Fake' hashtable type where reference to string
 (= const char*) is the key.
 Using this class is not recommended because it is likely to be
 difficult to keep the referenced string objects unchanged
 throughout the lifetime of the entry
 (remember that keys must not be changed).
 Use this class only you really need to avoid overhead of
 creating/destructing strings and the referenced string
 buffers can never be changed.
 Otherwise, use IDK_UT_STRING_FAKEHASHTABLE() instead.
 @param DataType Type of the value.
 */
#define IDK_UT_STRINGREF_FAKEHASHTABLE(DataType) \
	IDK_UT_FAKEHASHTABLE(const char*, DataType, \
		idk_ut_StringRefHashFunc, idk_ut_StringRefEqualsFunc)

#include <idk_ut_IntHashFuncs.h>

/**
 'Fake' hashtable type where integer type is the key.
 @param DataType Type of the value.
 */
#define IDK_UT_INT_FAKEHASHTABLE(DataType) \
	IDK_UT_FAKEHASHTABLE(int, DataType, \
		idk_ut_IntHashFunc, idk_ut_IntEqualsFunc)

/**
 'Fake' hashtable type where pointer type is the key.
 Note that this hashtable uses only the address of the pointer
 to determine the entry, but not the content of the pointed
 object.
 If you want to use the actual value of the pointed objects,
 use IDK_UT_OBJECT_FAKEHASHTABLE() instead.
 @param DataType Type of the value.
 */
#define IDK_UT_PTR_FAKEHASHTABLE(DataType) \
	IDK_UT_FAKEHASHTABLE(void*, DataType, \
		idk_ut_PtrHashFunc, idk_ut_PtrEqualsFunc)

#include <idk_ut_ObjectHashFuncs.h>

/**
 'Fake' hashtable type where pointer or smartpointer type
 to any object is the key.
 This hashtable uses the contents of the pointed objects
 to determine the entry.
 The pointed class must have these two methods:
 'int hashCode() const' which returns the hash value of the
 object and 'int equals(const T* other) const' which returns
 non-zero if the passed object is identical.
 @param DataType Type of the value.
 */
#define IDK_UT_OBJECT_FAKEHASHTABLE(KeyPtrType, ValueType) \
	IDK_UT_FAKEHASHTABLE( \
		KeyPtrType, \
		ValueType, \
		idk_ut_TObjectHashFunc<KeyPtrType>, \
		idk_ut_TObjectEqualsFunc<KeyPtrType> \
		)

#endif

