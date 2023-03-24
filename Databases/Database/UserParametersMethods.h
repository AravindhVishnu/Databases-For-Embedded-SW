#ifndef _USERPARAMETERSMETHODS_H_INCLUDED_
#define _USERPARAMETERSMETHODS_H_INCLUDED_

#include "DataValue.h"
#include "UserParameters.h"
#include <string>
#include <cassert>

// Implementation of the user parameter data item and relates APIs.
class UserParametersMethods
{

public:

  // Description: Class constructor
  UserParametersMethods(const uint32_t databaseSize);

  // Description: Class destructor
  virtual ~UserParametersMethods();

  // Description: Get current value of a specific user parameter.
  template <typename T>
  inline T getValue(const UserParameters::UserParametersId key) const;

  // Description: Set current value of a specific runtime data.
  template <typename T>
  inline UserParameters::ReturnCode setValue(const UserParameters::UserParametersId key, const T value);

  // Description: Get default value of a specific user parameter.
  template <typename T>
  inline T getDefaultValue(const UserParameters::UserParametersId key) const;

  // Description: Get minimum value of a specific user parameter.
  template <typename T>
  inline T getMinValue(const UserParameters::UserParametersId key) const;

  // Description: Get maximum value of a specific user parameter.
  template <typename T>
  inline T getMaxValue(const UserParameters::UserParametersId key) const;

  // Description: Get step size of a specific user parameter.
  template <typename T>
  inline T getStepSize(const UserParameters::UserParametersId key) const;

  // Description: Get current value of a user parameter with a specific block- and field number.
  template <typename T>
  inline T getValue(const uint32_t block, const uint32_t field) const;

  // Description: Get the type of a specific user parameter.
  template <typename T>
  inline UserParameters::ReturnCode setValue(const uint32_t block, const uint32_t field, const T value);

  inline DataValue::Type getType(const UserParameters::UserParametersId key) const;

  // Description: Function returns the unit of a specific user parameter
  inline UserParameters::Unit getUnit(const UserParameters::UserParametersId key) const;

  // Description: Function returns the application of a specific user parameter
  inline UserParameters::Application getApplication(const UserParameters::UserParametersId key) const;

  // Description: Function returns true if a specific user parameter is read only and false otherwise.
  inline bool isReadOnly(const UserParameters::UserParametersId key) const;

  // Description: Function returns true if a specific user parameter is initialized and false otherwise.
  inline bool isInitialized(const UserParameters::UserParametersId key) const;

  // Description: Lock the database
  inline void lockDatabase();

  // Description: Unlock the database
  inline void unlockDatabase();

  // Description: Set default values of all user parameter in the database
  inline void setDefaultValues();

  // Description: Store all user parameter values to EEPROM or Flash
  inline void store();

  // Description: Load all user parameter values from EEPROM or Flash
  inline void load();

protected:

  // Description: Initialize a specific user parameter.
  template <typename T>
  inline void initData(const UserParameters::UserParametersId key, const DataValue::Type type, const T value, const uint32_t block, const uint32_t field, const T defaultValue, const T minValue, const T maxValue, const T stepSize, const UserParameters::Unit unit, const UserParameters::Application application, const uint32_t nbrOfDecimals, const bool readOnly);

private:

  uint32_t m_databaseSize;  // Number of user parameter in the database

  struct DataItem
  {
  public:
    bool m_init = false;
    DataValue m_value;
    DataValue* m_valuePtr = &m_value;
    uint32_t m_block;
    uint32_t m_field;
    DataValue m_defaultValue;
    DataValue* m_defaultValuePtr = &m_defaultValue;
    DataValue m_minValue;
    DataValue* m_minValuePtr = &m_minValue;
    DataValue m_maxValue;
    DataValue* m_maxValuePtr = &m_maxValue;
    DataValue m_stepSize;
    DataValue* m_stepSizePtr = &m_stepSize;
    UserParameters::Unit m_unit;
    UserParameters::Application m_application;
    uint32_t m_nbrOfDecimals;
    bool m_readOnly;
  };

  bool m_locked;  // Flag which is true if the database is locked and false otherwise.

  DataItem* m_dataItemPtr;  // Pointer to the DataItem structure

  // Description: Function returns pointer to the DataItem structure
  inline DataItem* getDataItemPtr(UserParameters::UserParametersId key) const;

  // Description Function returns the user parameter id depending on the block and field numbers.
  inline UserParameters::UserParametersId getKey(uint32_t block, uint32_t field, bool& found) const;

};

//----------------------------------------------------------------------------
template <typename T>
inline void UserParametersMethods::initData(const UserParameters::UserParametersId key, const DataValue::Type type, const T value, const uint32_t block, const uint32_t field, const T defaultValue, const T minValue, const T maxValue, const T stepSize, const UserParameters::Unit unit, const UserParameters::Application application, const uint32_t nbrOfDecimals, const bool readOnly)
{
  this->getDataItemPtr(key)->m_block = block;
  this->getDataItemPtr(key)->m_field = field;
  this->getDataItemPtr(key)->m_valuePtr->setType(type);
  this->getDataItemPtr(key)->m_defaultValuePtr->setType(type);
  this->getDataItemPtr(key)->m_minValuePtr->setType(type);
  this->getDataItemPtr(key)->m_maxValuePtr->setType(type);
  this->getDataItemPtr(key)->m_stepSizePtr->setType(type);
  this->getDataItemPtr(key)->m_valuePtr->setValue(value);
  this->getDataItemPtr(key)->m_defaultValuePtr->setValue(defaultValue);
  this->getDataItemPtr(key)->m_minValuePtr->setValue(minValue);
  this->getDataItemPtr(key)->m_maxValuePtr->setValue(maxValue);
  this->getDataItemPtr(key)->m_stepSizePtr->setValue(stepSize);
  this->getDataItemPtr(key)->m_unit = unit;
  this->getDataItemPtr(key)->m_application = application;
  this->getDataItemPtr(key)->m_nbrOfDecimals = nbrOfDecimals;
  this->getDataItemPtr(key)->m_readOnly = readOnly;
  this->getDataItemPtr(key)->m_init = true;
}

//----------------------------------------------------------------------------
template <typename T>
inline T UserParametersMethods::getValue(UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
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
inline UserParameters::ReturnCode UserParametersMethods::setValue(UserParameters::UserParametersId key, const T value)
{
  if ((key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return UserParameters::DATA_ITEM_NOT_FOUND;
  }

  if (this->getDataItemPtr(key)->m_init == false)
  {
    assert(0);
    return UserParameters::DATA_ITEM_NOT_INITIALIZED;
  }

  if (this->isReadOnly(key) == false)
  {
    if (this->m_locked == false)
    {
      if ((value >= this->getMinValue<T>(key)) && (value <= this->getMaxValue<T>(key)))
      {
        if (this->getDataItemPtr(key)->m_valuePtr->setValue(value) == DataValue::WRONG_DATA_TYPE)
        {
          return UserParameters::WRONG_DATA_TYPE;
        }
        else
        {
          return UserParameters::WRITE_SUCCESS;
        }
      }
      else
      {
        return UserParameters::VALUE_OUT_OF_RANGE;
      }
    }
    else
    {
      return UserParameters::DATABASE_LOCKED;
    }
  }
  else
  {
    return UserParameters::VALUE_READ_ONLY;
  }
}

//----------------------------------------------------------------------------
template <typename T>
inline T UserParametersMethods::getValue(const uint32_t block, const uint32_t field) const
{
  bool found = false;
  UserParameters::UserParametersId id = this->getKey(block, field, found);
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
inline UserParameters::ReturnCode UserParametersMethods::setValue(const uint32_t block, const uint32_t field, const T value)
{
  bool found = false;
  UserParameters::UserParametersId id = this->getKey(block, field, found);
  if (found == true)
  {
    return this->setValue<T>(id, value);
  }
  else
  {
    assert(0);
    return UserParameters::DATA_ITEM_NOT_FOUND;
  }
}

//----------------------------------------------------------------------------
template <typename T>
inline T UserParametersMethods::getDefaultValue(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return static_cast<T>(0);
  }

  T ret;
  this->getDataItemPtr(key)->m_defaultValuePtr->getValue(ret);
  return ret;
}

//----------------------------------------------------------------------------
template <typename T>
inline T UserParametersMethods::getMinValue(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return static_cast<T>(0);
  }

  T ret;
  this->getDataItemPtr(key)->m_minValuePtr->getValue(ret);
  return ret;
}

//----------------------------------------------------------------------------
template <typename T>
inline T UserParametersMethods::getMaxValue(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return static_cast<T>(0);
  }

  T ret;
  this->getDataItemPtr(key)->m_maxValuePtr->getValue(ret);
  return ret;
}

//----------------------------------------------------------------------------
template <typename T>
inline T UserParametersMethods::getStepSize(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return static_cast<T>(0);
  }

  T ret;
  this->getDataItemPtr(key)->m_stepSizePtr->getValue(ret);
  return ret;
}

//----------------------------------------------------------------------------
inline UserParametersMethods::DataItem* UserParametersMethods::getDataItemPtr(const UserParameters::UserParametersId key) const
{
  if ((key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return NULL;
  }
  return &this->m_dataItemPtr[key];
}

//----------------------------------------------------------------------------
inline UserParameters::UserParametersId UserParametersMethods::getKey(const uint32_t block, const uint32_t field, bool& found) const
{
  for (uint32_t i = 0U; i < this->m_databaseSize; i++)
  {
    UserParameters::UserParametersId key = static_cast<UserParameters::UserParametersId>(i);
    if ((this->getDataItemPtr(key)->m_block == block) && (this->getDataItemPtr(key)->m_field == field))
    {
      if (this->getDataItemPtr(key)->m_init == false)
      {
        assert(0);
        found = false;
        return static_cast<UserParameters::UserParametersId>(0);
      }
      found = true;
      return key;
    }
  }
  assert(0);
  found = false;
  return static_cast<UserParameters::UserParametersId>(0);
}

//----------------------------------------------------------------------------
inline DataValue::Type UserParametersMethods::getType(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return DataValue::TYPE_UNDEFINED;
  }
  return this->getDataItemPtr(key)->m_valuePtr->getType();
}

//----------------------------------------------------------------------------
inline UserParameters::Unit UserParametersMethods::getUnit(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return UserParameters::UNKNOWN_UNIT;
  }
  return this->getDataItemPtr(key)->m_unit;
}

//----------------------------------------------------------------------------
inline UserParameters::Application UserParametersMethods::getApplication(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return UserParameters::UNKNOWN_APPLICATION;
  }
  return this->getDataItemPtr(key)->m_application;
}

//----------------------------------------------------------------------------
inline bool UserParametersMethods::isReadOnly(const UserParameters::UserParametersId key) const
{
  if ((this->getDataItemPtr(key)->m_init == false) || (key >= UserParameters::DATABASE_LENGTH) || (key < static_cast<UserParameters::UserParametersId>(0)))
  {
    assert(0);
    return false;
  }
  return this->getDataItemPtr(key)->m_readOnly;
}

//----------------------------------------------------------------------------
inline bool UserParametersMethods::isInitialized(const UserParameters::UserParametersId key) const
{
  return this->getDataItemPtr(key)->m_init;
}

//----------------------------------------------------------------------------
inline void UserParametersMethods::lockDatabase()
{
  this->m_locked = true;
}

//----------------------------------------------------------------------------
inline void UserParametersMethods::unlockDatabase()
{
  this->m_locked = false;
}

//----------------------------------------------------------------------------
inline void UserParametersMethods::setDefaultValues()
{
  for (uint32_t i = 0U; i < this->m_databaseSize; i++)
  {
    UserParameters::UserParametersId key = static_cast<UserParameters::UserParametersId>(i);
    DataValue::Type type = this->getType(key);
    switch (type)
    {
    case DataValue::TYPE_BOOL:
      this->setValue<bool>(key, this->getDefaultValue<bool>(key));
      break;
    case DataValue::TYPE_INT8:
      this->setValue<int8_t>(key, this->getDefaultValue<int8_t>(key));
      break;
    case DataValue::TYPE_UINT8:
      this->setValue<uint8_t>(key, this->getDefaultValue<uint8_t>(key));
      break;
    case DataValue::TYPE_INT16:
      this->setValue<int16_t>(key, this->getDefaultValue<int16_t>(key));
      break;
    case DataValue::TYPE_UINT16:
      this->setValue<uint16_t>(key, this->getDefaultValue<uint16_t>(key));
      break;
    case DataValue::TYPE_INT32:
      this->setValue<int32_t>(key, this->getDefaultValue<int32_t>(key));
      break;
    case DataValue::TYPE_UINT32:
      this->setValue<uint32_t>(key, this->getDefaultValue<uint32_t>(key));
      break;
    case DataValue::TYPE_INT64:
      this->setValue<int64_t>(key, this->getDefaultValue<int64_t>(key));
      break;
    case DataValue::TYPE_UINT64:
      this->setValue<uint64_t>(key, this->getDefaultValue<uint64_t>(key));
      break;
    case DataValue::TYPE_FLOAT:
      this->setValue<float>(key, this->getDefaultValue<float>(key));
      break;
    case DataValue::TYPE_DOUBLE:
      this->setValue<double>(key, this->getDefaultValue<double>(key));
      break;
    default:
      // Do nothing
      break;
    }
  }
}

//----------------------------------------------------------------------------
inline void UserParametersMethods::store()
{
  // Store user parameter current value in EEPROM or Flash.
  // The value is only stored in EEPROM or Flash if it has been changed.
  // This function shall run in a periodical executing thread (for instance once every second).
  // Only the current value need to be to stored in non-volatile memory.
  // All the other meta data can be hard-coded.
  // It is recommended to calculate a CRC (cyclic redundance check) value and store
  // it together with the user parameter current values.
}

//----------------------------------------------------------------------------
inline void UserParametersMethods::load()
{
  // Copy all user parameter current value from EEPROM or Flash to SRAM.
  // This function shall run once during program startup.
  // Calculate the CRC value of the loaded data and compare with the one that is stored.
}

#endif  // _USERPARAMETERSMETHODS_H_INCLUDED_