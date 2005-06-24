/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_NullableString.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_NULLABLESTRING_H_
#define _IDK_UT_NULLABLESTRING_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_NullableString class.
 */

/**
 Provides string capable to hold NULL.
 <p>Unlike STL's string, this class can hold NULL.
 You can set NULL to the object by passing NULL to constructors or
 assignment operations,
 and you will receive NULL from c_str() when the object holds NULL.
 <p>This class is value-semantics.

 @todo Most of fancy operations which STL's string have are omitted.
 We will add them if users want them and we can afford to do it.
 */
class IDK_DECL idk_ut_NullableString {
private:
	idk_string m_content;
	int m_isNull;

public:
	~idk_ut_NullableString();

	/**
	 Creates a new object which holds NULL.
	 */
	idk_ut_NullableString();

	/**
	 Creates a new object which holds the specified value.
	 @param value The string to be assigned.  May be NULL.
	 */
	idk_ut_NullableString(const char* value);

	/**
	 Creates a new object by copying another.
	 @param other The string to be assigned.
	 */
	idk_ut_NullableString(const idk_ut_NullableString& other);

	/**
	 Assigns a value.
	 @param value The string to be assigned.  May be NULL.
	 */
	idk_ut_NullableString& operator=(const char* value) {
		assign(value);
		return *this;
	}

	/**
	 Assigns a value.
	 @param other The string to be assigned.
	 */
	idk_ut_NullableString& operator=(const idk_ut_NullableString& other) {
		if (this != &other) assign(other);
		return *this;
	}

	/**
	 Returns true if the passed value is identical to the object.
	 @param value The string to be compared.  May be NULL.
	 */
	int operator==(const char* value) {
		return compare(value) == 0;
	}

	/**
	 Returns true if the passed value is identical to the object.
	 @param other The string to be compared.
	 */
	int operator==(const idk_ut_NullableString& other) {
		return compare(other) == 0;
	}

	/**
	 Returns true if the passed value is NOT identical to the object.
	 @param value The string to be compared.  May be NULL.
	 */
	int operator!=(const char* value) {
		return compare(value) != 0;
	}

	/**
	 Returns true if the passed value is NOT identical to the object.
	 @param other The string to be compared.
	 */
	int operator!=(const idk_ut_NullableString& other) {
		return compare(other) != 0;
	}

	/**
	 Returns the containing string as const char*.
	 @return The containing string or NULL.
	 */
	const char* c_str() const {
		return m_isNull ? NULL : m_content.c_str();
	}

	/**
	 Compares the passed value with the object.
	 Null is 'less' than any other values.
	 @param value The string to be compared.  May be NULL.
	 @return -1 if the object < value, 1 if the object > value, 0 if identical.
	 */
	int compare(const char* value);

	/**
	 Compares the passed value with the object.
	 Null is 'less' than any other values.
	 @param value The string to be compared.
	 @return -1 if the object < value, 1 if the object > value, 0 if identical.
	 */
	int compare(const idk_ut_NullableString& other);

private:
	void assign(const char* value);
	void assign(const idk_ut_NullableString& other);
};

#endif
