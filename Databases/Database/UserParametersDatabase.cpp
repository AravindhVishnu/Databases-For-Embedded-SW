#include "UserParametersDatabase.h"
#include <new>

UserParametersDatabase* UserParametersDatabase::m_instance = NULL;

//----------------------------------------------------------------------------
UserParametersDatabase* UserParametersDatabase::instance()
{
  if (m_instance == NULL)
  {
    m_instance = new (std::nothrow) UserParametersDatabase();
    assert(m_instance != NULL);
  }
  return m_instance;
}

//----------------------------------------------------------------------------
UserParametersDatabase::UserParametersDatabase() : UserParametersMethods(UserParameters::DATABASE_LENGTH)
{
}

//----------------------------------------------------------------------------
UserParametersDatabase::~UserParametersDatabase()
{
  delete this->m_instance;
  this->m_instance = NULL;
}

//----------------------------------------------------------------------------
bool UserParametersDatabase::init()
{
  this->initData(UserParameters::ID_USER_PARAMETER_ONE, DataValue::TYPE_INT32, 1, 1, 4, 1, 0, 100, 1, UserParameters::mS, UserParameters::ALL_APPLICATIONS, 0, false);
  this->initData(UserParameters::ID_USER_PARAMETER_TWO, DataValue::TYPE_UINT32, 1000U, 1, 5, 1000U, 0U, 100000U, 1U, UserParameters::kN, UserParameters::ALL_APPLICATIONS, 0, false);
  this->initData(UserParameters::ID_USER_PARAMETER_THREE, DataValue::TYPE_FLOAT, 0.0f, 2, 6, 0.0f, 0.0f, 15.0f, 0.1f, UserParameters::V, UserParameters::ALL_APPLICATIONS, 1, false);

  // Add more user parameters here

  for (uint32_t i = 0U; i < static_cast<uint32_t>(UserParameters::DATABASE_LENGTH); i++)
  {
    if ((this->getType(static_cast<UserParameters::UserParametersId>(i)) == DataValue::TYPE_UNDEFINED) ||
        (this->isInitialized(static_cast<UserParameters::UserParametersId>(i)) == false))
    {
      assert(0);
      return false;
    }
  }

  return true;
}