#ifndef _USERPARAMETERSDATABASE_H_INCLUDED_
#define _USERPARAMETERSDATABASE_H_INCLUDED_

#include "UserParametersMethods.h"

// Implementation of the user parameter database
class UserParametersDatabase : public UserParametersMethods
{
public:

  // Description: Class destructor
  virtual ~UserParametersDatabase();

  // Description: Object initialization function. Function returns true if the initialization
  // was successful and false otherwise.
  bool init();

  // Description: Function which returns a pointer to the user parameter database.
  static UserParametersDatabase* instance();

private:

  // Pointer to the user parameter database
  static UserParametersDatabase* m_instance;

  // Description: Class constructor
  UserParametersDatabase();
};

#endif  // _USERPARAMETERSDATABASE_H_INCLUDED_