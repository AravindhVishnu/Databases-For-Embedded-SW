#include "RuntimeDataMethods.h"
#include <new>

//----------------------------------------------------------------------------
RuntimeDataMethods::RuntimeDataMethods(const uint32_t databaseSize)
{
  this->m_dataItemPtr = NULL;
  this->m_databaseSize = databaseSize;
  this->m_dataItemPtr = new (std::nothrow) DataItem[this->m_databaseSize];
  assert(this->m_dataItemPtr != NULL);
}

//----------------------------------------------------------------------------
RuntimeDataMethods::~RuntimeDataMethods()
{
  delete[] this->m_dataItemPtr;
  this->m_dataItemPtr = NULL;
}