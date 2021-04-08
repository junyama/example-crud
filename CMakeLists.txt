cmake_minimum_required(VERSION 3.1)

set(project_name chick-server) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/controller/StaticController.hpp
        src/controller/UserController.hpp
        src/db/UserDb.hpp
        src/dto/PageDto.hpp
        src/dto/StatusDto.hpp
        src/dto/UserDto.hpp
        src/service/UserService.cpp
        src/service/UserService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp
        
        src/controller/MyController.hpp
        src/dto/MyDTOs.hpp
        src/halcon/Classifyer.hpp
        src/halcon/Classifyer.cpp
        src/halcon/MyDictionary.cpp
        )

## include directories

target_include_directories(${project_name}-lib PUBLIC src)

## link libs

find_package(oatpp          1.2.5 REQUIRED)
find_package(oatpp-swagger  1.2.5 REQUIRED)
find_package(oatpp-sqlite   1.2.5 REQUIRED)

find_package(oatpp-libressl  REQUIRED)

include(FindPkgConfig) # <-- include pkg-config needed by FindLibreSSL.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake") # <-- use FindLibreSSL.cmake in /cmake folder

find_package(LibreSSL 3.0.0 REQUIRED)

target_link_libraries(${project_name}-lib
        # Oat++
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
        
        PUBLIC oatpp::oatpp-libressl # <-- oatpp-libressl adapter

        # LibreSSL libraries
        PUBLIC LibreSSL::TLS
        PUBLIC LibreSSL::SSL
        PUBLIC LibreSSL::Crypto
)

# If CMake can't find SQLite3:
#
# 1. Make sure that you've built oatpp-sqlite with -DOATPP_SQLITE_AMALGAMATION=ON flag
# 2. If you are not willing to use SQLite amalgamation then uncomment the following lines:
#
#find_package(SQLite3 REQUIRED)
#
#target_link_libraries(${project_name}-lib
#        PUBLIC SQLite::SQLite3
#)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
        
        -DCERT_PEM_PATH="${CMAKE_CURRENT_LIST_DIR}/cert/test_key.pem"
        -DCERT_CRT_PATH="${CMAKE_CURRENT_LIST_DIR}/cert/test_cert.crt"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestClient.hpp
        test/app/TestDatabaseComponent.hpp
        test/app/TestComponent.hpp
        test/UserControllerTest.hpp
        test/UserControllerTest.cpp)
target_link_libraries(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(project-tests ${project_name}-test)
