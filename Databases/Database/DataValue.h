#ifndef _DATAVALUE_H_INCLUDED_
#define _DATAVALUE_H_INCLUDED_

#include <cstdint>
#include <cassert>

// Data value class comprising of the value and type
// as well as get/set functions.
class DataValue
{
public:

  // Possible return codes when setting the value
  enum ReturnCode
  {
    WRITE_SUCCESS = 0,
    WRONG_DATA_TYPE
  };

  // Different type of data that is supported
  enum Type
  {
    TYPE_UNDEFINED = 0,
    TYPE_BOOL,
    TYPE_INT8,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_INT32,
    TYPE_UINT32,
    TYPE_INT64,
    TYPE_UINT64,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_VOID_POINTER,
    DATA_TYPE_SIZE
  };

  // The data values in this union shall correspond to the 
  // different data types defined in the Type enum.
  union Value
  {
    bool boolValue;
    int8_t int8Value;
    uint8_t uint8Value;
    int16_t int16Value;
    uint16_t uint16Value;
    int32_t int32Value;
    uint32_t uint32Value;
    int64_t int64Value;
    uint64_t uint64Value;
    float floatValue;
    double doubleValue;
    void* voidPtrValue;
  };

  // Description: Class constructor
  DataValue();

  // Description: Class destructor
  ~DataValue();

  // Description: Set bool value
  inline ReturnCode setValue(const bool value);

  // Description: Set uint8 value
  inline ReturnCode setValue(const uint8_t value);

  // Description: Set int8 value
  inline ReturnCode setValue(const int8_t value);

  // Description: Set uint16 value
  inline ReturnCode setValue(const uint16_t value);

  // Description: Set int16 value
  inline ReturnCode setValue(const int16_t value);

  // Description: Set uint32 value
  inline ReturnCode setValue(const uint32_t value);

  // Description: Set int32 value
  inline ReturnCode setValue(const int32_t value);

  // Description: Set uint64 value
  inline ReturnCode setValue(const uint64_t value);

  // Description: Set int64 value
  inline ReturnCode setValue(const int64_t value);

  // Description: Set float value
  inline ReturnCode setValue(const float value);

  // Description: Set double value
  inline ReturnCode setValue(const double value);

  // Description: Set void pointer
  inline ReturnCode setValue(void* value);

  // Description: Get bool value
  inline void getValue(bool& value) const;

  // Description: Get uint8 value
  inline void getValue(uint8_t& value) const;

  // Description: Get int8 value
  inline void getValue(int8_t& value) const;

  // Description: Get uint16 value
  inline void getValue(uint16_t& value) const;

  // Description: Get int16 value
  inline void getValue(int16_t& value) const;

  // Description: Get uint32 value
  inline void getValue(uint32_t& value) const;

  // Description: Get int32 value
  inline void getValue(int32_t& value) const;

  // Description: Get uint64 value
  inline void getValue(uint64_t& value) const;

  // Description: Get int64 value
  inline void getValue(int64_t& value) const;

  // Description: Get float value
  inline void getValue(float& value) const;

  // Description: Get double value
  inline void getValue(double& value) const;

  // Description: Get void pointer
  inline void getValue(void*& value) const;

  // Description: Set type
  inline void setType(const Type type);

  // Description: Get type
  inline Type getType() const;

private:

  Value m_value;  // Data value
  Type m_type;  // Data type

};

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const bool value)
{
  if (this->m_type == TYPE_BOOL)
  {
    this->m_value.boolValue = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const uint8_t value)
{
  if (this->m_type == TYPE_UINT8)
  {
    this->m_value.uint8Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const int8_t value)
{
  if (this->m_type == TYPE_INT8)
  {
    this->m_value.int8Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const uint16_t value)
{
  if (this->m_type == TYPE_UINT16)
  {
    this->m_value.uint16Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const int16_t value)
{
  if (this->m_type == TYPE_UINT16)
  {
    this->m_value.uint16Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const uint32_t value)
{
  if (this->m_type == TYPE_UINT32)
  {
    this->m_value.uint32Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const int32_t value)
{
  if (this->m_type == TYPE_INT32)
  {
    this->m_value.int32Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const uint64_t value)
{
  if (this->m_type == TYPE_UINT64)
  {
    this->m_value.uint64Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const int64_t value)
{
  if (this->m_type == TYPE_INT64)
  {
    this->m_value.int64Value = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const float value)
{
  if (this->m_type == TYPE_FLOAT)
  {
    this->m_value.floatValue = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(const double value)
{
  if (this->m_type == TYPE_DOUBLE)
  {
    this->m_value.doubleValue = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline DataValue::ReturnCode DataValue::setValue(void* value)
{
  if (this->m_type == TYPE_VOID_POINTER)
  {
    this->m_value.voidPtrValue = value;
    return WRITE_SUCCESS;
  }
  assert(0);
  return WRONG_DATA_TYPE;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(bool& value) const
{
  value = this->m_value.boolValue;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(uint8_t& value) const
{
  value = this->m_value.uint8Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(int8_t& value) const
{
  value = this->m_value.int8Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(uint16_t& value) const
{
  value = this->m_value.uint16Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(int16_t& value) const
{
  value = this->m_value.int16Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(uint32_t& value) const
{
  value = this->m_value.uint32Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(int32_t& value) const
{
  value = this->m_value.int32Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(uint64_t& value) const
{
  value = this->m_value.uint64Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(int64_t& value) const
{
  value = this->m_value.int64Value;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(float& value) const
{
  value = this->m_value.floatValue;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(double& value) const
{
  value = this->m_value.doubleValue;
}

//----------------------------------------------------------------------------
inline void DataValue::getValue(void*& value) const
{
  value = this->m_value.voidPtrValue;
}

//----------------------------------------------------------------------------
inline void DataValue::setType(const DataValue::Type type)
{
  this->m_type = type;
}

//----------------------------------------------------------------------------
inline DataValue::Type DataValue::getType() const
{
  return this->m_type;
}

#endif  // _RUNTIMEDATAITEM_H_INCLUDED_