#include "RuntimeDatabase.h"
#include <new>

RuntimeDatabase* RuntimeDatabase::m_instance = NULL;

//----------------------------------------------------------------------------
RuntimeDatabase* RuntimeDatabase::instance()
{
  if (m_instance == NULL)
  {
    m_instance = new (std::nothrow) RuntimeDatabase();
    assert(m_instance != NULL);
  }
  return m_instance;
}

//----------------------------------------------------------------------------
RuntimeDatabase::RuntimeDatabase() : RuntimeDataMethods(RuntimeData::DATABASE_LENGTH)
{
}

//----------------------------------------------------------------------------
RuntimeDatabase::~RuntimeDatabase()
{
  delete this->m_instance;
  this->m_instance = NULL;
}

//----------------------------------------------------------------------------
bool RuntimeDatabase::init()
{
  if (this->initData<int32_t>(RuntimeData::ID_RUNTIMEDATA_ONE, DataValue::TYPE_INT32, 100, 1, 10) != RuntimeData::WRITE_SUCCESS)
  {
    assert(0);
    return false;
  }
  if (this->initData<uint32_t>(RuntimeData::ID_RUNTIMEDATA_TWO, DataValue::TYPE_UINT32, 250, 2, 3) != RuntimeData::WRITE_SUCCESS)
  {
    assert(0);
    return false;
  }
  if (this->initData<float>(RuntimeData::ID_RUNTIMEDATA_THREE, DataValue::TYPE_FLOAT, 3.0f, 3, 7) != RuntimeData::WRITE_SUCCESS)
  {
    assert(0);
    return false;
  }
  if (this->initData<void*>(RuntimeData::ID_RUNTIMEDATA_FOUR, DataValue::TYPE_VOID_POINTER, NULL, 5, 1) != RuntimeData::WRITE_SUCCESS)
  {
    assert(0);
    return false;
  }

  // Add more runtime data here

  for (uint32_t i = 0U; i < static_cast<uint32_t>(RuntimeData::DATABASE_LENGTH); i++)
  {
    if ((this->getType(static_cast<RuntimeData::RuntimeDataId>(i)) == DataValue::TYPE_UNDEFINED) || 
        (this->isInitialized(static_cast<RuntimeData::RuntimeDataId>(i)) == false))
    {
      assert(0);
      return false;
    }
  }

  return true;
}