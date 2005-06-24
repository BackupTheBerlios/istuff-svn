/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_FieldValue.h,v 1.6 2003/07/01 06:40:45 tomoto Exp $ */

#ifndef _EH2_FIELDVALUE_H_
#define _EH2_FIELDVALUE_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <eh2_EventConsts.h>

/** @file
 Definition of eh2_FieldValue class.
 @internal This header belongs to the eh2i_ev package.
 */

class eh2i_ev_FieldValue; // impl

/**
 Represents the values contained by a field.
 Usual applications need not use this class because eh2_Event and eh2_Field class provides
 enough shortcut methods to access to the values directly bypassing this object.

 @todo Setter/getter for non-basic types. See eh2_Event.
 */
class EH2_DECL eh2_FieldValue
: public idk_ut_TProxyObject<eh2i_ev_FieldValue>,
  public eh2_EventConsts
{
private:
	friend class eh2i_ev_FieldValue;
	eh2_FieldValue(eh2i_ev_FieldValue* impl);

public:
	~eh2_FieldValue();

	/**
	 Returns the value type of the field value.
	 */
	FieldValueType getFieldValueType() const;

	/**
	 Sets the value type of the field value.
	 When FVT_ACTUAL is passed, the actual value will be initialized to NULL.
	 */
	void setFieldValueType(FieldValueType type);

	/**
	 Returns non-zero if the field value is virtual.
	 */
	int isVirtual() const;

	/**
	 Copy the value of the give object.
	 */
	void copyValue(const eh2_FieldValue* other);

	/**
	 Sets the value.
	 @throws eh2_FieldOperationException The data type is different.
	 */
	void setIntValue(int value);

	/**
	 Sets the value.
	 If the data type of the field is not string, the value is converted to string type.
	 */
	void setStringValue(const char* value);

	/**
	 Sets the value.
	 @throws eh2_FieldOperationException The data type is different.
	 */
	void setDoubleValue(double value);

	/**
	 Sets the value.
	 @throws eh2_FieldOperationException The data type is different.
	 */
	void setFloatValue(float value);

	/**
	 Sets the value.
	 @throws eh2_FieldOperationException The data type is different.
	 */
	void setBooleanValue(int value);

	/**
	 Sets the value.
	 @throws eh2_FieldOperationException The data type is different.
	 */
	void setLongValue(idk_long value);

	/**
	 Returns non-zero if the value is NULL.
	 @throws eh2_FieldOperationException The value is not actual.
	 */
	int isNull() const;

	/**
	 Returns the value.
	 @throws eh2_FieldOperationException The value is not actual or data type is different.
	 */
	int getIntValue() const;

	/**
	 Returns the value.
	 @throws eh2_FieldOperationException The value is not actual or data type is different.
	 */
	const char* getStringValue() const;

	/**
	 Returns the value.
	 @throws eh2_FieldOperationException The value is not actual or data type is different.
	 */
	double getDoubleValue() const;

	/**
	 Returns the value.
	 @throws eh2_FieldOperationException The value is not actual or data type is different.
	 */
	float getFloatValue() const;

	/**
	 Returns the value.
	 @throws eh2_FieldOperationException The value is not actual or data type is different.
	 */
	int getBooleanValue() const;

	/**
	 Returns the value.
	 @throws eh2_FieldOperationException The value is not actual or data type is different.
	 */
	idk_long getLongValue() const;
};

#endif
