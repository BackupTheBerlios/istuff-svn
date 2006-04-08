/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_FieldType.h,v 1.4 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_FIELDTYPE_H_
#define _EH2_FIELDTYPE_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_FieldType class.
 @internal This header belongs to the eh2i_ev package.
 */

class eh2i_ev_FieldType; // impl

/**
 Represents the data type of a field.
 There are a number of ways to get a pointer to this object,
 but none of them passes the ownership of the object to the application.
 */
class EH2_DECL eh2_FieldType :
public idk_ut_TProxyObject<eh2i_ev_FieldType>
{
private:
	friend class eh2i_ev_FieldType;
	eh2_FieldType(eh2i_ev_FieldType* impl);

public:
	~eh2_FieldType();

	/**
	 Returns non-zero if the given type is exactly the same.
	 */
	int equals(const eh2_FieldType* other) const;

	/**
	 Returns the type name.
	 This is the same as the string representation of the type
	 inside the Event Heap protocol.
	 */
	const char* getTypeName() const;

	/**
	 Returns non-zero if the type is one of the basic types.
	 */
	int isBasicType() const;

public:
	/**
	 Returns the eh2_FiledType object representing int type.
	 */
	static const eh2_FieldType* cs_int();

	/**
	 Returns the eh2_FiledType object representing string type.
	 */
	static const eh2_FieldType* cs_string();

	/**
	 Returns the eh2_FiledType object representing double type.
	 */
	static const eh2_FieldType* cs_double();

	/**
	 Returns the eh2_FiledType object representing float type.
	 */
	static const eh2_FieldType* cs_float();

	/**
	 Returns the eh2_FiledType object representing long type.
	 */
	static const eh2_FieldType* cs_long();

	/**
	 Returns the eh2_FiledType object representing boolean type.
	 */
	static const eh2_FieldType* cs_boolean();

	/**
	 Returns the eh2_FiledType object representing the given type name.
	 If an unknown type name is passed, it will be registered
	 as a new non-basic type.
	 */
	static const eh2_FieldType* cs_getTypeByName(const char* typeName);
};

#endif
