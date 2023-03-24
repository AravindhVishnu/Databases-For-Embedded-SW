#ifndef _MYEXAMPLECLASS_H_INCLUDED_
#define _MYEXAMPLECLASS_H_INCLUDED_

#include <iostream>
#include "Database/RuntimeDatabase.h"
#include "Database/UserParametersDatabase.h"

class MyExampleClass
{
public:

  // Description: Class constructor
  MyExampleClass();

  // Description: Class destructor
  ~MyExampleClass();

  // Description: Object initialization function
  void init();

  // Description: Function used to test the database APIs
  void exec();

private:

  // Pointer to the user parameter database class
  UserParametersDatabase* m_userParametersPtr;

  int32_t m_runtimeDataOne;
  uint32_t m_runtimeDataTwo;
  float m_runtimeDataThree;

  // Pointer to the runtime database class
  RuntimeDatabase* m_runtimeDataPtr;

  int32_t m_userParameterOne;
  uint32_t m_userParameterTwo;
  float m_userParameterThree;

};

#endif  // _MYEXAMPLECLASS_H_INCLUDED_