# CMakeList.txt : CMake project for Databases, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  Databases
  VERSION 0.0.0.0
  DESCRIPTION "Databases example project"
  LANGUAGES C CXX
)

add_executable(Databases)

target_sources(Databases
                PRIVATE
                  ${PROJECT_SOURCE_DIR}/Database/DataValue.cpp
                  ${PROJECT_SOURCE_DIR}/Database/RuntimeDatabase.cpp
                  ${PROJECT_SOURCE_DIR}/Database/RuntimeDataMethods.cpp
                  ${PROJECT_SOURCE_DIR}/Database/UserParametersDatabase.cpp
		              ${PROJECT_SOURCE_DIR}/Database/UserParametersMethods.cpp
	                ${PROJECT_SOURCE_DIR}/MyExampleClass.cpp
		              ${PROJECT_SOURCE_DIR}/main.cpp
                PUBLIC  
                  ${PROJECT_SOURCE_DIR}/Database/DataValue.h
                  ${PROJECT_SOURCE_DIR}/Database/RuntimeDatabase.h
		              ${PROJECT_SOURCE_DIR}/Database/RuntimeDataMethods.h
		              ${PROJECT_SOURCE_DIR}/Database/UserParametersDatabase.h
		              ${PROJECT_SOURCE_DIR}/Database/UserParametersMethods.h
		              ${PROJECT_SOURCE_DIR}/Database/RuntimeData.h
		              ${PROJECT_SOURCE_DIR}/Database/UserParameters.h
		              ${PROJECT_SOURCE_DIR}/MyExampleClass.h
)

target_include_directories(Databases
                            PUBLIC
			                        ${PROJECT_SOURCE_DIR}
                              ${PROJECT_SOURCE_DIR}/Database
)