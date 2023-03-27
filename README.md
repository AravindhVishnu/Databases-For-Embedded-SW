# Databases-For-Embedded-SW
This respository contains two implementation examples of databases for embedded SW.

Description:

- Runtime database:
Runtime data is defined as RW data that different modules use and exchange during program execution.
In a data centric SW architecture, it is useful to decrease the coupling between modules, in order to improve
modularity and maintenace. This can be done by having all modules communicating with each other through a runtime database.
In this way, all modules have the dependency to the database (instead of with each other). This is an implementation example 
of a key-value database (each item in the database is accessed thorugh the use of an ID/key). But the data can also be 
accessed through the use of a block and field number which in some cases can be useful (especially when the data needs to be categorized).
All the basic data types are supported as well as the void pointer which means it is possible to write a pointer that points to anything in the database.
This is a static database which means that adding or removing items during program execution is not supported. 
Basic initialize, set, get APIs are provided with suitable return error codes.

- User parameter database:
User parameters are defined as RW data in a product that can be accessed through the HMI, fieldbus, serial console, web browser, etc.
A user parameter has meta data associated with it such as current value, default value, max value, min value, data type, block, field, 
step size, unit, application, number of decimals, read only flag, etc. The same base implementation of the runtime database is used 
for the user parameter database. The difference is that more functionality is added to accomodate the user parameter requirements 
such as more meta data, more return error codes, setting default values of all parameters, locking/unlocking the database, etc. 
When the database APIs are used in a multi-threaded application, it is advised to protect them with a mutex.

An example application is included to provide info of how to use the two databases.

Tools:

- Development environment: Visual Studio Code with the CMake Tools extension

- Build utility: CMake/Ninja

- Compiler: G++/GCC

- Debugger: GDB

Note: Tested on Linux Mint
