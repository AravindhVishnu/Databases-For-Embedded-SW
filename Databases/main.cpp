#include <unistd.h>
#include "MyExampleClass.h"

//----------------------------------------------------------------------------
int main()
{
  MyExampleClass obj;
  obj.init();

  while (1)
  {
    obj.exec();
    sleep(5);
  }

  return 0;
}