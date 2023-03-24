#ifndef _USERPARAMETERS_H_INCLUDED_
#define _USERPARAMETERS_H_INCLUDED_

// Implementation of enumerations related to the user parameter database.
class UserParameters
{
public:

  // Possible return codes when setting the value
  enum ReturnCode
  {
    WRITE_SUCCESS = 0,
    DATA_ITEM_NOT_INITIALIZED,
    WRONG_DATA_TYPE,
    DATA_ITEM_NOT_FOUND,
    VALUE_OUT_OF_RANGE,
    VALUE_READ_ONLY,
    DATABASE_LOCKED,
    RETURN_CODE_SIZE
  };

  enum UserParametersId
  {
    ID_USER_PARAMETER_ONE = 0,
    ID_USER_PARAMETER_TWO,
    ID_USER_PARAMETER_THREE,

    // Add more user parameters here

    DATABASE_LENGTH
  };

  enum Unit
  {
    NO_UNIT = 0,
    N,
    kN,
    T,
    MM,
    S,
    mS,
    V,
    mA,
    UNKNOWN_UNIT,
    UNITS_SIZE
  };

  enum Application
  {
    ALL_APPLICATIONS = 0,
    APPLICATION_ONE,
    APPLICATION_TWO,
    APPLICATION_THREE,
    UNKNOWN_APPLICATION,
    APPLICATION_SIZE
  };

};

#endif  // _USERPARAMETERS_H_INCLUDED_