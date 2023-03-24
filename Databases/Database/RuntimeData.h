#ifndef _RUNTIMEDATA_H_INCLUDED_
#define _RUNTIMEDATA_H_INCLUDED_

// Implementation of enumerations related to the runtime database.
class RuntimeData
{
public:

  // Possible return codes when setting the value
  enum ReturnCode
  {
    WRITE_SUCCESS = 0,
    DATA_ITEM_NOT_INITIALIZED,
    WRONG_DATA_TYPE,
    DATA_ITEM_NOT_FOUND,
    RETURN_CODE_SIZE
  };

  enum RuntimeDataId
  {
    ID_RUNTIMEDATA_ONE = 0,
    ID_RUNTIMEDATA_TWO,
    ID_RUNTIMEDATA_THREE,
    ID_RUNTIMEDATA_FOUR,

    // Add more runtime data here

    DATABASE_LENGTH
  };

};

#endif  // _RUNTIMEDATA_H_INCLUDED_