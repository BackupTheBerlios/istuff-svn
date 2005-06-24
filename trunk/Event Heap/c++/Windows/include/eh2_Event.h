/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Event.h,v 1.8 2003/07/01 18:46:32 tomoto Exp $ */

#ifndef _EH2_EVENT_H_
#define _EH2_EVENT_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <eh2_EventConsts.h>

/** @file
 Definition of eh2_Event class.
 @internal This header belongs to the eh2i_ev component.
 */

class eh2i_ev_Event; // impl

/**
 Represents an event of the Event Heap.

 <p>This class represents an event and provides methods for
 field operations.  
 (This document does not describe about details of event itself
  or standard fields.
  Please see other document such as Java API documentation or
  generic Event Heap specification)

 <p>There are some methods which provide ways to retrieve mutable pointers
 to eh2_Field object like allocateField().  However, shortcut methods like
 setPostValueInt() are more preferable when you want to add or modify a
 field.

 @todo The implementation is not completed.
 Some operations and errors cause assertion failure.
 @todo Setter/getter for non-basic type (i.e. byte-array type) fields.
 I can't do it now since I have not drawn the picture of
 the potential usecases of it.
 */
class EH2_DECL eh2_Event
: public idk_ut_TProxyObject<eh2i_ev_Event>,
  public eh2_EventConsts
{
private:
	friend class eh2i_ev_Event;
	eh2_Event(eh2i_ev_Event* impl);

public:
	~eh2_Event();

	/**
	 Clones the object.
	 */
	eh2_EventPtr clone() const;

	/**
	 Returns non-zero if a field which has the same name as specified exists.
	 */
	int fieldExists(const char* name) const;

	/**
	 Returns the number of fields, including pure-virtual fields.
	 */
	int size() const;

	/**
	 Creates a mutable iterator to walk through the fields contained in the event.
	 @see eh2_IFieldIterator
	 */
	eh2_IFieldIteratorPtr getFieldIterator();

	/**
	 Creates a constant iterator to walk through the fields contained in the event.
	 @see eh2_IConstFieldIterator
	 */
	eh2_IConstFieldIteratorPtr getConstFieldIterator() const;

	/**
	 Gets a mutable pointer to the field which has the specified name.
	 @return Pointer to the field or NULL if there's no such field.
	 */
	eh2_Field* getField(const char* name);

	/**
	 Gets a constant pointer to the field which has the specified name.
	 @return Pointer to the field or NULL if there's no such field.
	 */
	const eh2_Field* getField(const char* name) const;

	/**
	 Removes the field which has the specified name.
	 Does nothing if there's no such field.
	 */
	void removeField(const char* name);

	/**
	 Gets a mutable pointer to the field which has the specified name,
	 creating one if there's no such field.
	 This method returns the field which matches the specified name if one exists.
	 Or, if no such field exists, creates a new one with specified name and type
	 inside the event and returns it.  The value of the new field will be
	 VIRAUTL for both post ane template value.
	 @param name Name of the field
	 @param type The data type of the field.
	 When a new field created, this data type will be used as its type.
	 When the requested field already exists, this data type must match
	 the data type of the field.
	 @return Pointer to the field.  Never be NULL.
	 @throws eh2_FieldOperationException The given type does not match
	 the type of the existing field.
	 */
	eh2_Field* allocateField(
		const char* name,
		const eh2_FieldType* type
		);

	/**
	 Returns the number of non-pure-virtual fields.
	 */
	int nonPureVirtualSize() const;

	/**
	 Returns the event type.
	 This method returns the value of the "EventType" field.
	 */
	const char* getEventType() const;

	/**
	 Sets the event type.
	 This methods sets the given value to the "EventType" field.
	 */
	void setEventType(const char* eventType);

	/**
	 Sets an integer value to the post value of the specified field.
	 Sets the given value to a field whose name is identical with the
	 specified name.
	 If there's no field with the specified name, a field of appropreate
	 type will be newly created.
	 If the field with the specified name exists but its type does not match
	 the type of the value, an exception will be thrown.
	 @throws eh2_FieldOperationException The data type does not match
	 the type of the existing field.
	 */
	void setPostValueInt(const char* name, int value);

	/**
	 Sets a string value to the post value of the specified field.
	 See setPostValueInt() for more detail specification.
	 */
	void setPostValueString(const char* name, const char* value);

	/**
	 Sets a double value to the post value of the specified field.
	 See setPostValueInt() for more detail specification.
	 */
	void setPostValueDouble(const char* name, double value);

	/**
	 Sets a float value to the post value of the specified field.
	 See setPostValueInt() for more detail specification.
	 */
	void setPostValueFloat(const char* name, float value);

	/**
	 Sets a boolean value to the post value of the specified field.
	 See setPostValueInt() for more detail specification.
	 */
	void setPostValueBoolean(const char* name, int value);

	/**
	 Sets a long value to the post value of the specified field.
	 See setPostValueInt() for more detail specification.
	 */
	void setPostValueLong(const char* name, idk_long value);

	/**
	 Sets the value type of the post value of the specified field.
	 If there's no field with the specified name, an exception will be thrown.
	 @throws eh2_FieldOperationException There's no field to be set.
	 */
	void setPostValueType(const char* name, FieldValueType valueType);

	/**
	 Sets an integer value to the template value of the specified field.
	 Sets the given value to a field whose name is identical with the
	 specified name.
	 If there's no field with the specified name, a field of appropreate
	 type will be newly created.
	 If the field with the specified name exists but its type does not match
	 the type of the value, an exception will be thrown.
	 @throws eh2_FieldOperationException The data type does not match
	 the type of the existing field.
	 */
	void setTemplateValueInt(const char* name, int value);

	/**
	 Sets a string value to the template value of the specified field.
	 See setTemplateValueInt() for more detail specification.
	 */
	void setTemplateValueString(const char* name, const char* value);

	/**
	 Sets a double value to the template value of the specified field.
	 See setTemplateValueInt() for more detail specification.
	 */
	void setTemplateValueDouble(const char* name, double value);

	/**
	 Sets a float value to the template value of the specified field.
	 See setTemplateValueInt() for more detail specification.
	 */
	void setTemplateValueFloat(const char* name, float value);

	/**
	 Sets a boolean value to the template value of the specified field.
	 See setTemplateValueInt() for more detail specification.
	 */
	void setTemplateValueBoolean(const char* name, int value);

	/**
	 Sets a long value to the template value of the specified field.
	 See setTemplateValueInt() for more detail specification.
	 */
	void setTemplateValueLong(const char* name, idk_long value);

	/**
	 Sets the value type of the template value of the specified field.
	 If there's no field with the specified name, an exception will be thrown.
	 @throws eh2_FieldOperationException There's no field to be set.
	 */
	void setTemplateValueType(const char* name, FieldValueType valueType);

	/**
	 Returns the post value of the specified field as int.
	 The data type of the field must be the same type with the return value.
	 @throws eh2_FieldOperationException There is no specified field,
	 the data type of the field does not match,
	 or the field does not contain an actual value
	 (i.e. formal, virtual, or null).
	 */
	int getPostValueInt(const char* name) const;

	/**
	 Returns the post value of the specified field as string.
	 If the data type is not string, the value is converted to string type.
	 @throws eh2_FieldOperationException There is no specified field
	 or the field does not contain an actual value
	 (i.e. formal, virtual, or null).
	 */
	const char* getPostValueString(const char* name) const;

	/**
	 Returns the post value of the specified field as double.
	 See getPostValueInt(const char*) const for more detail specification.
	 */
	double getPostValueDouble(const char* name) const;

	/**
	 Returns the post value of the specified field as float.
	 See getPostValueInt(const char*) const for more detail specification.
	 */
	float getPostValueFloat(const char* name) const;

	/**
	 Returns the post value of the specified field as boolean.
	 See getPostValueInt(const char*) const for more detail specification.
	 */
	int getPostValueBoolean(const char* name) const;

	/**
	 Returns the post value of the specified field as long.
	 See getPostValueInt(const char*) const for more detail specification.
	 */
	idk_long getPostValueLong(const char* name) const;

	/**
	 Returns the post value of the specified field as int.
	 The data type of the field must be the same type with the return value.
	 If there is no specified field or the field does not contain an actual value
	 (i.e. formal, virtual, or null), returns the specified default value.
	 @throws eh2_FieldOperationException The data type of the field does not match.
	 <i>Not implemented.  The current implementation returns the default value
	 in this case also.</i>
	 */
	int getPostValueInt(const char* name, int defaultValue) const;

	/**
	 Returns the post value of the specified field as string.
	 If the data type of the field is not string, the value is converted to string type.
	 
	 If there is no specified field or the field does not contain an actual value
	 (i.e. formal, virtual, or null), returns the specified default value.
	 Note that defaultValue is returned as it is without being stored somewhere else.
	 So it is application's responsibility to keep the buffer pointed by
	 defaultValue until the use of the return value of this function ends.
	 */
	const char* getPostValueString(const char* name, const char* defaultValue) const;

	/**
	 Returns the post value of the specified field as double.
	 See getPostValueInt(const char*, int) const for more detail specification.
	 */
	double getPostValueDouble(const char* name, double defaultValue) const;

	/**
	 Returns the post value of the specified field as float.
	 See getPostValueInt(const char*, int) const for more detail specification.
	 */
	float getPostValueFloat(const char* name, float defaultValue) const;

	/**
	 Returns the post value of the specified field as boolean.
	 See getPostValueInt(const char*, int) const for more detail specification.
	 */
	int getPostValueBoolean(const char* name, int defaultValue) const;

	/**
	 Returns the post value of the specified field as long.
	 See getPostValueInt(const char*, int) const for more detail specification.
	 */
	idk_long getPostValueLong(const char* name, idk_long defaultValue) const;

	/**
	 Returns the template value of the specified field as int.
	 The data type of the field must be the same type with the return value.
	 @throws eh2_FieldOperationException There is no specified field,
	 the data type of the field does not match,
	 or the field does not contain an actual value
	 (i.e. formal, virtual, or null).
	 */
	int getTemplateValueInt(const char* name) const;

	/**
	 Returns the template value of the specified field as string.
	 If the data type is not string, the value is converted to string type.
	 @throws eh2_FieldOperationException There is no specified field
	 or the field does not contain an actual value
	 (i.e. formal, virtual, or null).
	 */
	const char* getTemplateValueString(const char* name) const;

	/**
	 Returns the template value of the specified field as double.
	 See getTemplateValueInt(const char*) const for more detail specification.
	 */
	double getTemplateValueDouble(const char* name) const;

	/**
	 Returns the template value of the specified field as float.
	 See getTemplateValueInt(const char*) const for more detail specification.
	 */
	float getTemplateValueFloat(const char* name) const;

	/**
	 Returns the template value of the specified field as boolean.
	 See getTemplateValueInt(const char*) const for more detail specification.
	 */
	int getTemplateValueBoolean(const char* name) const;

	/**
	 Returns the template value of the specified field as long.
	 See getTemplateValueInt(const char*) const for more detail specification.
	 */
	idk_long getTemplateValueLong(const char* name) const;

	/**
	 Returns the template value of the specified field as int.
	 The data type of the field must be the same type with the return value.
	 If there is no specified field or the field does not contain an actual value
	 (i.e. formal, virtual, or null), returns the specified default value.
	 @throws eh2_FieldOperationException The data type of the field does not match.
	 <i>Not implemented.  The current implementation returns the default value
	 in this case also.</i>
	 */
	int getTemplateValueInt(const char* name, int defaultValue) const;

	/**
	 Returns the template value of the specified field as string.
	 If the data type of the field is not string, the value is converted to string type.
	 If there is no specified field or the field does not contain an actual value
	 (i.e. formal, virtual, or null), returns the specified default value.
	 
	 If there is no specified field or the field does not contain an actual value
	 (i.e. formal, virtual, or null), returns the specified default value.
	 Note that defaultValue is returned as it is without being stored somewhere else.
	 So it is application's responsibility to keep the buffer pointed by
	 defaultValue until the use of the return value of this function ends.
	 */
	const char* getTemplateValueString(const char* name, const char* defaultValue) const;

	/**
	 Returns the template value of the specified field as double.
	 See getTemplateValueInt(const char*, int) const for more detail specification.
	 */
	double getTemplateValueDouble(const char* name, double defaultValue) const;

	/**
	 Returns the template value of the specified field as float.
	 See getTemplateValueInt(const char*, int) const for more detail specification.
	 */
	float getTemplateValueFloat(const char* name, float defaultValue) const;

	/**
	 Returns the template value of the specified field as boolean.
	 See getTemplateValueInt(const char*, int) const for more detail specification.
	 */
	int getTemplateValueBoolean(const char* name, int defaultValue) const;

	/**
	 Returns the template value of the specified field as long.
	 See getTemplateValueInt(const char*, int) const for more detail specification.
	 */
	idk_long getTemplateValueLong(const char* name, idk_long defaultValue) const;

	/**
	 Returns non-zero if the event is identical with the given event.
	 Pure-virtual fields will be ignored.
	 If the event includes non-basic types, an exception will be thrown --
	 because the semantics of comparison is undefined.
	 @todo Not implemented yet.
	 */
	int equals(const eh2_Event* other) const;

	/**
	 Returns non-zero if the event matches with the given event.
	 The semantics of matching is defined elsewhere.
	 If the event includes non-basic types, an exception will be thrown --
	 because the semantics of matching is undefined.
	 @throws eh2_FieldOperationException Tried to compare non-basic type values.
	 */
	int matches(const eh2_Event* other) const;

public:
	/**
	 Creates an event with the specified type.
	 @param eventType Event type of the new event.
	 When NULL is specified, the new event has INVALID_EVENT type.
	 */
	static eh2_EventPtr cs_create(const char* eventType = NULL);

};

#endif
