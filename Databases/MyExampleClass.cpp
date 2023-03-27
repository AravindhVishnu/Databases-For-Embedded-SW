#include "MyExampleClass.h"

//----------------------------------------------------------------------------
MyExampleClass::MyExampleClass()
{
  this->m_userParametersPtr = UserParametersDatabase::instance();
  this->m_userParametersPtr->init();
  this->m_runtimeDataPtr = RuntimeDatabase::instance();
  this->m_runtimeDataPtr->init();
}

//----------------------------------------------------------------------------
MyExampleClass::~MyExampleClass()
{
}

//----------------------------------------------------------------------------
void MyExampleClass::init()
{
  this->m_userParameterOne = this->m_userParametersPtr->getMinValue<int32_t>(UserParameters::ID_USER_PARAMETER_ONE);
  this->m_userParameterTwo = this->m_userParametersPtr->getMinValue<uint32_t>(UserParameters::ID_USER_PARAMETER_TWO);
  this->m_userParameterThree = this->m_userParametersPtr->getMinValue<float>(UserParameters::ID_USER_PARAMETER_THREE);

  this->m_runtimeDataOne = 0;
  this->m_runtimeDataTwo = 0U;
  this->m_runtimeDataThree = 0.0f;
}

//----------------------------------------------------------------------------
void MyExampleClass::exec()
{
  // In the code, it is helpful to see the id (name) and type of the data that is written to or read from the database.

  std::cout << "RuntimeDatabase example" << std::endl;

  // Write to database using key
  this->m_runtimeDataPtr->setValue<int32_t>(RuntimeData::ID_RUNTIMEDATA_ONE, this->m_runtimeDataOne);
  std::cout << "Writing runtimeDataOne value " << this->m_runtimeDataOne << " to database" << std::endl;

  this->m_runtimeDataPtr->setValue<uint32_t>(RuntimeData::ID_RUNTIMEDATA_TWO, this->m_runtimeDataTwo);
  std::cout << "Writing runtimeDataTwo value " << this->m_runtimeDataTwo << " to database" << std::endl;

  this->m_runtimeDataPtr->setValue<float>(RuntimeData::ID_RUNTIMEDATA_THREE, this->m_runtimeDataThree);
  std::cout << "Writing runtimeDataThree value " << this->m_runtimeDataThree << " to database" << std::endl;

  // Test code to write and read void pointer
  struct s
  {
    int32_t s1;
    uint32_t s2;
    float s3;
    double s4;
    bool s5;
  };

  s testStruct;
  testStruct.s1 = 1;
  testStruct.s2 = 2U;
  testStruct.s3 = 4.5f;
  testStruct.s4 = 8.2;
  testStruct.s5 = true;

  void* testInputVoidPtr = static_cast<void*>(&testStruct);
  this->m_runtimeDataPtr->setValue<void*>(RuntimeData::ID_RUNTIMEDATA_FOUR, testInputVoidPtr);

  void* testOutputVoidPtr = this->m_runtimeDataPtr->getValue<void*>(RuntimeData::ID_RUNTIMEDATA_FOUR);
  s* testStructPtr = static_cast<s*>(testOutputVoidPtr);

  std::cout << "s1= " << testStructPtr->s1 << ", s2= " << testStructPtr->s2 << ", s3= " << testStructPtr->s3 << ", s4= " << testStructPtr->s4 << ", s5= " << testStructPtr->s5 << std::endl;

  std::cout << std::endl;

  // Change values
  this->m_runtimeDataOne += 1000;
  this->m_runtimeDataTwo += 2000U;
  this->m_runtimeDataThree += 5.5f;

  // Read from database using key
  int32_t runtimeDataOne = this->m_runtimeDataPtr->getValue<int32_t>(RuntimeData::ID_RUNTIMEDATA_ONE);
  std::cout << "Reading runtimeDataOne value " << runtimeDataOne << " from database" << std::endl;

  uint32_t runtimeDataTwo = this->m_runtimeDataPtr->getValue<uint32_t>(RuntimeData::ID_RUNTIMEDATA_TWO);
  std::cout << "Reading runtimeDataTwo value " << runtimeDataTwo << " from database" << std::endl;

  float runtimeDataThree = this->m_runtimeDataPtr->getValue<float>(RuntimeData::ID_RUNTIMEDATA_THREE);
  std::cout << "Reading runtimeDataThree value " << runtimeDataThree << " from database" << std::endl;

  std::cout << std::endl;

  // Read from database using block and field
  runtimeDataOne = this->m_runtimeDataPtr->getValue<int32_t>(1, 10);
  std::cout << "Reading runtimeDataOne value using block and field " << runtimeDataOne << " from database" << std::endl;

  runtimeDataTwo = this->m_runtimeDataPtr->getValue<uint32_t>(2, 3);
  std::cout << "Reading runtimeDataTwo value using block and field " << runtimeDataTwo << " from database" << std::endl;

  runtimeDataThree = this->m_runtimeDataPtr->getValue<float>(3, 7);
  std::cout << "Reading runtimeDataThree value using block and field " << runtimeDataThree << " from database" << std::endl;

  std::cout << std::endl;

  std::cout << "UserParamatersDatabase example" << std::endl;

  // Write to database using key
  this->m_userParametersPtr->setValue<int32_t>(UserParameters::ID_USER_PARAMETER_ONE, this->m_userParameterOne);
  std::cout << "Writing userParameterOne value " << this->m_userParameterOne << " to database" << std::endl;

  this->m_userParametersPtr->setValue<uint32_t>(UserParameters::ID_USER_PARAMETER_TWO, this->m_userParameterTwo);
  std::cout << "Writing userParameterTwo value " << this->m_userParameterTwo << " to database" << std::endl;

  this->m_userParametersPtr->setValue<float>(UserParameters::ID_USER_PARAMETER_THREE, this->m_userParameterThree);
  std::cout << "Writing userParameterThree value " << this->m_userParameterThree << " to database" << std::endl;

  std::cout << std::endl;

  // Change values
  this->m_userParameterOne += 1;
  this->m_userParameterTwo += 2U;
  this->m_userParameterThree += 1.5f;

  // Test code to set default values
  if (this->m_userParameterOne == 3)
  {
    this->m_userParametersPtr->setDefaultValues();
  }

  // Read from database using key
  int32_t userParameterOne = this->m_userParametersPtr->getValue<int32_t>(UserParameters::ID_USER_PARAMETER_ONE);
  std::cout << "Reading userParameterOne value " << userParameterOne << " from database" << std::endl;

  uint32_t userParameterTwo = this->m_userParametersPtr->getValue<uint32_t>(UserParameters::ID_USER_PARAMETER_TWO);
  std::cout << "Reading userParameterTwo value " << userParameterTwo << " from database" << std::endl;

  float userParameterThree = this->m_userParametersPtr->getValue<float>(UserParameters::ID_USER_PARAMETER_THREE);
  std::cout << "Reading userParameterThree value " << userParameterThree << " from database" << std::endl;

  std::cout << std::endl;

  // Read from database using block and field
  userParameterOne = this->m_userParametersPtr->getValue<int32_t>(1, 4);
  std::cout << "Reading userParameterOne value using block and field " << userParameterOne << " from database" << std::endl;

  userParameterTwo = this->m_userParametersPtr->getValue<uint32_t>(1, 5);
  std::cout << "Reading userParameterTwo value using block and field " << userParameterTwo << " from database" << std::endl;

  userParameterThree = this->m_userParametersPtr->getValue<float>(2, 6);
  std::cout << "Reading userParameterThree value using block and field " << userParameterThree << " from database" << std::endl;

  std::cout << std::endl;
}