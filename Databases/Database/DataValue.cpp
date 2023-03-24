#include "DataValue.h"

//----------------------------------------------------------------------------
DataValue::DataValue()
{
  this->m_value.int32Value = 0;
  this->m_type = TYPE_UNDEFINED;
}

//----------------------------------------------------------------------------
DataValue::~DataValue()
{
}