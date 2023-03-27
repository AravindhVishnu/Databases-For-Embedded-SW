#ifndef _RUNTIMEDATABASE_H_INCLUDED_
#define _RUNTIMEDATABASE_H_INCLUDED_

#include "RuntimeDataMethods.h"

// Implementation of the runtime database
class RuntimeDatabase : public RuntimeDataMethods
{
public:

  // Description: Class destructor
  virtual ~RuntimeDatabase();

  // Description: Object initialization function. Function returns true if the initialization
  // was successful and false otherwise.
  bool init();

  // Description: Function which returns a pointer to the runtime database.
  static RuntimeDatabase* instance();

private:

  // Pointer to the runtime database
  static RuntimeDatabase* m_instance;

  // Description: Class constructor
  RuntimeDatabase();
};

#endif  // _RUNTIMEDATABASE_H_INCLUDED_