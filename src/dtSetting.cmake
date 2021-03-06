
macro(SetBuildType)

    IF(NOT CMAKE_BUILD_TYPE)
        SET(CMAKE_BUILD_TYPE "Release")
    ENDIF(NOT CMAKE_BUILD_TYPE)

    IF((CMAKE_BUILD_TYPE MATCHES "debug") OR (CMAKE_BUILD_TYPE MATCHES "DEBUG"))
        SET(CMAKE_BUILD_TYPE "Debug")
    ENDIF((CMAKE_BUILD_TYPE MATCHES "debug") OR (CMAKE_BUILD_TYPE MATCHES "DEBUG"))
    
    IF((CMAKE_BUILD_TYPE MATCHES "release") OR (CMAKE_BUILD_TYPE MATCHES "RELEASE"))
        SET(CMAKE_BUILD_TYPE "Release")
    ENDIF((CMAKE_BUILD_TYPE MATCHES "release") OR (CMAKE_BUILD_TYPE MATCHES "RELEASE"))

    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        ADD_DEFINITIONS(-DDEBUG )
        ADD_DEFINITIONS("-DBOOST_UBLAS_TYPE_CHECK=0" )
        #we want to be warned in debug mode
        IF(UNIX)
            IF(CMAKE_COMPILER_IS_GNUCC)
                ADD_DEFINITIONS(-Wall)
            ENDIF(CMAKE_COMPILER_IS_GNUCC)
        ENDIF(UNIX)
    ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug")
    
    IF(CMAKE_BUILD_TYPE MATCHES "Release")
        ADD_DEFINITIONS(-DNDEBUG )
        ADD_DEFINITIONS(-DBOOST_UBLAS_NDEBUG )
    ENDIF (CMAKE_BUILD_TYPE MATCHES "Release")

endmacro()

macro(SetProjectName arg)

    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        project(${arg}d CXX C)
    ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug")
    
    IF(CMAKE_BUILD_TYPE MATCHES "Release")
        project(${arg} CXX C)
    ENDIF (CMAKE_BUILD_TYPE MATCHES "Release")

endmacro()

macro(SetOutPath)

    if(WIN32)
        if(MINGW)
            set(OUTPUT_EXT mingw)
        elseif(MSVC)
            set(OUTPUT_EXT msvc)
        elseif(CYGWIN)
            set(OUTPUT_EXT cygwin)
        endif()
    elseif(UNIX)
        if(CYGWIN)
            set(OUTPUT_EXT cygwin)
        else(CYGWIN)
            set(OUTPUT_EXT unix)
        endif()
    endif()

    set(OUTPUT_PATH ${PROJECT_BINARY_DIR})
    set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH}/bin-${OUTPUT_EXT})
    set(LIBRARY_OUTPUT_PATH ${OUTPUT_PATH}/lib-${OUTPUT_EXT})

endmacro()

macro(SetOutFileName filename)

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(output_filename ${filename}d)
    else(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(output_filename ${filename})
    endif(CMAKE_BUILD_TYPE MATCHES "Debug")

endmacro()

macro(InitProject project_name)

    SetBuildType()
    SetProjectName(${project_name})
    SetOutPath()
    
endmacro()
