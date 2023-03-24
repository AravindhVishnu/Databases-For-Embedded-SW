#include "UserParametersMethods.h"
#include <new>

//----------------------------------------------------------------------------
UserParametersMethods::UserParametersMethods(uint32_t databaseSize)
{
  this->m_dataItemPtr = NULL;
  this->m_databaseSize = databaseSize;
  this->m_dataItemPtr = new (std::nothrow) DataItem[this->m_databaseSize];
  assert(this->m_dataItemPtr != NULL);
  this->m_locked = false;
}

//----------------------------------------------------------------------------
UserParametersMethods::~UserParametersMethods()
{
  delete[] this->m_dataItemPtr;
  this->m_dataItemPtr = NULL;
}