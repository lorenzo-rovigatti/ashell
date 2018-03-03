CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

OPTION(Python "Enable Python bindings" OFF)
OPTION(Debug "Set to ON to compile with debug symbols" OFF)
OPTION(G "Set to ON to compile with optimisations and debug symbols" OFF)
OPTION(INTEL "Use the Intel compiler" OFF)

PROJECT(ashell)

# The default behaviour is to compile with optimisations
SET(CMAKE_BUILD_TYPE Release)

IF(Python)
	ADD_DEFINITIONS(-DASHELL_PYTHON)
	FIND_PACKAGE( PythonLibs 2.7 REQUIRED )
	INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )
	MESSAGE(STATUS "Enabling Python bindings")
ENDIF(Python)

IF(Debug)
	SET(CMAKE_BUILD_TYPE Debug)
	MESSAGE(STATUS "Compiling in Debug mode")
ENDIF(Debug)

IF(G)
	SET(CMAKE_BUILD_TYPE RelWithDebInfo)
	MESSAGE(STATUS "Compiling in Release+Debug symbols mode")
ENDIF(G)

IF(CMAKE_VERSION VERSION_LESS "3.1")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
ELSE()
	SET(CMAKE_CXX_STANDARD 14)
	SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

# the BOOST_LOG_DYN_LINK definition is required in order to build a python-readable
# dynamic library
ADD_DEFINITIONS(-Wall -DBOOST_LOG_DYN_LINK)

IF(NOT CMAKE_BUILD_TYPE MATCHES Debug)
	IF(INTEL)
		ADD_DEFINITIONS(-fast)
	ELSE()
		ADD_DEFINITIONS(-ffast-math)
	ENDIF(INTEL)
ENDIF()

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/extern )

FIND_PACKAGE( Boost COMPONENTS python log signals REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# get the current git revision, if git is installed. Avoid warnings if it isn't
FIND_PACKAGE(Git)
IF(Git_FOUND)
	EXECUTE_PROCESS(COMMAND "git rev-parse --short HEAD" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} OUTPUT_VARIABLE revision OUTPUT_STRIP_TRAILING_WHITESPACE)
ELSE()
	SET(revision GIT_NOT_FOUND)
ENDIF()

# return the current date as day/month/year
MACRO(CURRENT_DATE result)
    IF(WIN32)
        EXECUTE_PROCESS(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE ${result})
        string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${result} ${${result}})
    ELSEIF(UNIX)
        EXECUTE_PROCESS(COMMAND "date" "+%d/%m/%Y" OUTPUT_VARIABLE ${result})
        string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${result} ${${result}})
    ELSE(WIN32)
        MESSAGE(SEND_ERROR "date not implemented")
        SET(${result} 000000)
    ENDIF (WIN32)
ENDMACRO(CURRENT_DATE)

CURRENT_DATE(today)
ADD_DEFINITIONS(-D'GIT_VERSION="${revision}"' -D'BUILD_TIME="${today}"')

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(exec)
