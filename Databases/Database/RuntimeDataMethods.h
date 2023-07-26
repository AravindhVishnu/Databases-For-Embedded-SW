#ifndef _RUNTIMEDATAMETHODS_H_INCLUDED_
#define _RUNTIMEDATAMETHODS_H_INCLUDED_

#include "DataValue.h"
#include "RuntimeData.h"
#include <string>
#include <cassert>

// This class implements the runtime database item and related APIs.
class RuntimeDataMethods
{

public:

  // Description: Class constructor
  RuntimeDataMethods(const uint32_t databaseSize);

  // Description: Class destructor
  virtual ~RuntimeDataMethods();

  // Description: Get current value of a specific runtime data.
  template <typename T>
  inline T getValue(const RuntimeData::RuntimeDataId key) const;

  // Description: Set current value of a specific runtime data.
  template <typename T>
  inline RuntimeData::ReturnCode setValue(const RuntimeData::RuntimeDataId key, const T value);

  // Description: Get current value of a runtime data with a specific block- and field number.
  template <typename T>
  inline T getValue(const uint32_t block, const uint32_t field) const;

  // Description: Set current value of a runtime data with a specific block- and field number.
  template <typename T>
  inline RuntimeData::ReturnCode setValue(const uint32_t block, const uint32_t field, const T value);

  // Description: Get the type of a specific runtime data.
  inline DataValue::Type getType(const RuntimeData::RuntimeDataId key) const;

  // Description: Function returns true if a specific runtime data is initialized and false otherwise.
  inline bool isInitialized(const RuntimeData::RuntimeDataId key) const;

protected:

  // Description: Initialize a specific runtime data.
  template <typename T>
  inline RuntimeData::ReturnCode initData(const RuntimeData::RuntimeDataId key, const DataValue::Type type, const T value, const uint32_t block, const uint32_t field);

private:

  uint32_t m_databaseSize;  // Number of runtime data in the database

  struct DataItem
  {
  public:
    bool m_init = false;
    DataValue m_value;
    DataValue* m_valuePtr = &m_value;
    uint32_t m_block;
    uint32_t m_field;
  };

  // Pointer to the DataItem struct
  DataItem* m_dataItemPtr;

  // Description: Function returns pointer to the DataItem structure
  inline DataItem* getDataItemPtr(const RuntimeData::RuntimeDataId key) const;

  // Description Function returns the runtime data id depending on the block and field numbers.
  inline RuntimeData::RuntimeDataId getKey(const uint32_t block, const uint32_t field, bool& found) const;

};

//----------------------------------------------------------------------------
template <typename T>
inline RuntimeData::ReturnCode RuntimeDataMethods::initData(const RuntimeData::RuntimeDataId key, const DataValue::Type type, const T value, const uint32_t block, const uint32_t field)
{
  if ((key >= RuntimeData::DATABASE_LENGTH) || (key < static_cast<RuntimeData::RuntimeDataId>(0)))
  {
    assert(0);
    return RuntimeData::DATA_ITEM_NOT_FOUND;
  }
  
  this->getDataItemPtr(key)->m_block = block;
  this->getDataItemPtr(key)->m_field = field;

  if ((type >= DataValue::Type::DATA_TYPE_SIZE) || (type < static_cast<DataValue::Type>(0)))
  {
    assert(0);
    return RuntimeData::WRONG_DATA_TYPE;
  }
  else
  {
    this->getDataItemPtr(key)->m_valuePtr->setType(type);
  }

  if (this->getDataItemPtr(key)->m_valuePtr->setValue(value) == DataValue::WRONG_DATA_TYPE)
  {
    assert(0);
    return RuntimeData::WRONG_DATA_TYPE;
  }

  this->getDataItemPtr(key)->m_init = true;
  
  return RuntimeData::WRITE_SUCCESS;
}

//----------------------------------------------------------------------------
template <typename T>
inline T RuntimeDataMethods::getValue(const RuntimeData::RuntimeDataId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= RuntimeData::DATABASE_LENGTH) || (key < static_cast<RuntimeData::RuntimeDataId>(0)))
  {
    assert(0);
    return static_cast<T>(0);
  }

  T ret = static_cast<T>(0);
  this->getDataItemPtr(key)->m_valuePtr->getValue(ret);
  return ret;
}

//----------------------------------------------------------------------------
template <typename T>
inline RuntimeData::ReturnCode RuntimeDataMethods::setValue(const RuntimeData::RuntimeDataId key, const T value)
{
  if ((key >= RuntimeData::DATABASE_LENGTH) || (key < static_cast<RuntimeData::RuntimeDataId>(0)))
  {
    assert(0);
    return RuntimeData::DATA_ITEM_NOT_FOUND;
  }

  if (this->getDataItemPtr(key)->m_init == false)
  {
    assert(0);
    return RuntimeData::DATA_ITEM_NOT_INITIALIZED;
  }

  if (this->getDataItemPtr(key)->m_valuePtr->setValue(value) == DataValue::WRONG_DATA_TYPE)
  {
    return RuntimeData::WRONG_DATA_TYPE;
  }
  else
  {
    return RuntimeData::WRITE_SUCCESS;
  }
}

//----------------------------------------------------------------------------
template <typename T>
inline T RuntimeDataMethods::getValue(const uint32_t block, const uint32_t field) const
{
  bool found = false;
  RuntimeData::RuntimeDataId id = this->getKey(block, field, found);
  if (found == true)
  {
    return this->getValue<T>(id);
  }
  else
  {
    return static_cast<T>(0);
  }
}

//----------------------------------------------------------------------------
template <typename T>
inline RuntimeData::ReturnCode RuntimeDataMethods::setValue(const uint32_t block, const uint32_t field, const T value)
{
  bool found = false;
  RuntimeData::RuntimeDataId id = this->getKey(block, field, found);
  if (found == true)
  {
    return this->setValue<T>(id , value);
  }
  else
  {
    assert(0);
    return RuntimeData::DATA_ITEM_NOT_FOUND;
  }
}

//----------------------------------------------------------------------------
inline RuntimeDataMethods::DataItem* RuntimeDataMethods::getDataItemPtr(const RuntimeData::RuntimeDataId key) const
{
  if ((key >= RuntimeData::DATABASE_LENGTH) || (key < static_cast<RuntimeData::RuntimeDataId>(0)))
  {
    assert(0);
    return NULL;
  }
  return &this->m_dataItemPtr[key];
}

//----------------------------------------------------------------------------
inline DataValue::Type RuntimeDataMethods::getType(const RuntimeData::RuntimeDataId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= RuntimeData::DATABASE_LENGTH) || (key < static_cast<RuntimeData::RuntimeDataId>(0)))
  {
    assert(0);
    return DataValue::TYPE_UNDEFINED;
  }
  return this->getDataItemPtr(key)->m_valuePtr->getType();
}

//----------------------------------------------------------------------------
inline RuntimeData::RuntimeDataId RuntimeDataMethods::getKey(const uint32_t block, const uint32_t field, bool& found) const
{
  for (uint32_t i = 0U; i < this->m_databaseSize; i++)
  {
    RuntimeData::RuntimeDataId key = static_cast<RuntimeData::RuntimeDataId>(i);
    if ((this->getDataItemPtr(key)->m_block == block) && (this->getDataItemPtr(key)->m_field == field))
    {
      if (this->getDataItemPtr(key)->m_init == false)
      {
        assert(0);
        found = false;
        return static_cast<RuntimeData::RuntimeDataId>(0);
      }
      found = true;
      return key;
    }
  }
  assert(0);
  found = false;
  return static_cast<RuntimeData::RuntimeDataId>(0);
}

//----------------------------------------------------------------------------
inline bool RuntimeDataMethods::isInitialized(const RuntimeData::RuntimeDataId key) const
{
  if ((key >= RuntimeData::DATABASE_LENGTH) || (key < static_cast<RuntimeData::RuntimeDataId>(0)))
  {
    assert(0);
    return false;
  }
  return this->getDataItemPtr(key)->m_init;
}

#endif  // _RUNTIMEDATAMETHODS_H_INCLUDED_
