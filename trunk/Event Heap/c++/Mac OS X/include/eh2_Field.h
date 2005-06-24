/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Field.h,v 1.6 2003/07/01 06:40:45 tomoto Exp $ */

#ifndef _EH2_FIELD_H_
#define _EH2_FIELD_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <eh2_EventConsts.h>

/** @file
 Definition of eh2_Field class.
 @internal This header belongs to the eh2i_ev package.
 */

class eh2i_ev_Field; // impl

/**
 Represents a field of an event.

 @todo The implementation is not completed.
 Some operations and errors cause assertion failure.
 @todo Setter/getter for non-basic types. See eh2_Event.
 */
class EH2_DECL eh2_Field
: public idk_ut_TProxyObject<eh2i_ev_Field>,
  public eh2_EventConsts
{
private:
	friend class eh2i_ev_Field;
	eh2_Field(eh2i_ev_Field* impl);

public:
	~eh2_Field();

	/**
	 Returns the type of the field.
	 */
	const eh2_FieldType* getType() const;

	/**
	 Returns the constant eh2_FieldValue object for post value of the field.
	 Shortcut methods like getPostValueInt() would be more convenient in normal use.
	 @returns Constant pointer to eh2_FieldValue object for post value of the field.
	 Never be NULL.
	 */
	const eh2_FieldValue* getPostValue() const;

	/**
	 Returns the mutable eh2_FieldValue object for post value of the field.
	 Shortcut methods like setPostValueInt() would be more convenient in normal use.
	 @returns Mutable pointer to eh2_FieldValue object for post value of the field.
	 Never be NULL.
	 */
	eh2_FieldValue* getPostValue();

	/**
	 Returns the constant eh2_FieldValue object for template value of the field.
	 Shortcut methods like getTemplateValueInt() would be more convenient in normal use.
	 @returns Constant pointer to eh2_FieldValue object for template value of the field.
	 Never be NULL.
	 */
	const eh2_FieldValue* getTemplateValue() const;

	/**
	 Returns the mutable eh2_FieldValue object for template value of the field.
	 Shortcut methods like setTemplateValueInt() would be more convenient in normal use.
	 @returns Mutable pointer to eh2_FieldValue object for template value of the field.
	 Never be NULL.
	 */
	eh2_FieldValue* getTemplateValue();

	/**
	 Returns non-zero if the field is pure-virtual.
	 */
	int isPureVirtual() const;

	//
	// shortcut methods
	//

	/**
	 Sets the post value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setPostValueInt(int value);

	/**
	 Sets the post value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setPostValueString(const char* value);

	/**
	 Sets the post value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setPostValueDouble(double value);
	
	/**
	 Sets the post value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setPostValueFloat(float value);

	/**
	 Sets the post value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setPostValueBoolean(int value);

	/**
	 Sets the post value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setPostValueLong(idk_long value);

	/**
	 Sets the value type of the post value.
	 When FVT_ACTUAL is passed, the actual value will be initialized to NULL.
	 */
	void setPostValueType(FieldValueType valueType);

	/**
	 Returns non-zero if the post value is actual and NULL.
	 @throws eh2_FieldOperationException The value type is not actual.
	 */
	int isPostValueNull() const;

	/**
	 Returns the post value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	int getPostValueInt() const;

	/**
	 Returns the post value as string.
	 If the data type of the field is not string, the value is converted to string type.
	 @throws eh2_FieldOperationException The value type is not actual.
	 */
	const char* getPostValueString() const;

	/**
	 Returns the post value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	double getPostValueDouble() const;

	/**
	 Returns the post value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	float getPostValueFloat() const;

	/**
	 Returns the post value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	int getPostValueBoolean() const;

	/**
	 Returns the post value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	idk_long getPostValueLong() const;

	/**
	 Returns the value type of the post value.
	 */
	FieldValueType getPostValueType() const;

	/**
	 Sets the template value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setTemplateValueInt(int value);

	/**
	 Sets the template value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setTemplateValueString(const char* value);

	/**
	 Sets the template value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setTemplateValueDouble(double value);

	/**
	 Sets the template value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setTemplateValueFloat(float value);

	/**
	 Sets the template value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setTemplateValueBoolean(int value);

	/**
	 Sets the template value.
	 @throws eh2_FieldOperationException The field type is different.
	 */
	void setTemplateValueLong(idk_long value);

	/**
	 Sets the value type of the template value.
	 When FVT_ACTUAL is passed, the actual value will be initialized to NULL.
	 */
	void setTemplateValueType(FieldValueType valueType);

	/**
	 Returns non-zero if the post value is actual and NULL.
	 @throws eh2_FieldOperationException The value is not actual.
	 */
	int isTemplateValueNull() const;

	/**
	 Returns the template value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	int getTemplateValueInt() const;

	/**
	 Returns the template value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	const char* getTemplateValueString() const;

	/**
	 Returns the template value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	double getTemplateValueDouble() const;

	/**
	 Returns the template value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	float getTemplateValueFloat() const;

	/**
	 Returns the template value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	int getTemplateValueBoolean() const;

	/**
	 Returns the template value.
	 @throws eh2_FieldOperationException The value type is not actual or the field type is different.
	 */
	idk_long getTemplateValueLong() const;

	/**
	 Returns the value type of the template value.
	 */
	FieldValueType getTemplateValueType() const;

};

#endif
