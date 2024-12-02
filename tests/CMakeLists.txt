cmake_minimum_required(VERSION 3.5)

# Package Management using CPM
include(cmake/get_cpm.cmake)

project(HttpStatusCodesTests)

set (CMAKE_CXX_STANDARD 11)

CPMAddPackage(
	NAME GTest
	URL "https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz"
	VERSION "1.15.2"
	OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt" )
set( GTEST_MAIN GTest::gtest_main )

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/..)

add_executable(CVariantTest CVariantTest.cpp)
target_link_libraries(CVariantTest ${GTEST_MAIN})
add_test(NAME CVariantTest COMMAND CVariantTest)

add_executable(CVariantCompileTest CVariantCompileTest.c)
add_test(NAME CVariantCompileTest COMMAND CVariantCompileTest)
set_target_properties(CVariantCompileTest PROPERTIES
	LINKER_LANGUAGE "C"
	C_STANDARD 90
	C_STANDARD_REQUIRED ON
)

add_executable(C++VariantTest C++VariantTest.cpp)
target_link_libraries(C++VariantTest ${GTEST_MAIN})
add_test(NAME C++VariantTest COMMAND C++VariantTest)
set_target_properties(C++VariantTest PROPERTIES
	CXX_STANDARD 98
	CXX_STANDARD_REQUIRED ON
)


list(FIND CMAKE_CXX_COMPILE_FEATURES "cxx_strong_enums" CXX_SUPPORTS_STRONG_ENUMS)
if (CXX_SUPPORTS_STRONG_ENUMS GREATER -1)
	set(CXX_SUPPORTS_STRONG_ENUMS ON)
else()
	set(CXX_SUPPORTS_STRONG_ENUMS OFF)
endif()

if(CXX_SUPPORTS_STRONG_ENUMS)
	add_executable(C++11VariantTest C++11VariantTest.cpp)
	target_link_libraries(C++11VariantTest ${GTEST_MAIN})
	add_test(NAME C++11VariantTest COMMAND C++11VariantTest)
	set_target_properties(C++11VariantTest PROPERTIES
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED ON
	)
endif()

set(CMAKE_AUTOMOC ON)
find_package(Qt6 COMPONENTS Core OPTIONAL_COMPONENTS Network)
if (Qt6_FOUND)
	set(QTCORE_LIB Qt6::Core)
	if (Qt6Network_FOUND)
		set(QTNETWORK_LIB Qt6::Network)
	endif()
endif()
if (NOT QTCORE_LIB)
	find_package(Qt5 COMPONENTS Core OPTIONAL_COMPONENTS Network)
	if (Qt5_FOUND)
		set(QTCORE_LIB Qt5::Core)
		if (Qt5Network_FOUND)
			set(QTNETWORK_LIB Qt5::Network)
		endif()
	endif()
endif()
if (NOT QTCORE_LIB)
	find_package(Qt5Core CONFIG)
	if (Qt5Core_FOUND)
		set(QTCORE_LIB Qt5::Core)
		find_package(Qt5Network CONFIG)
		if (Qt5Network_FOUND)
			set(QTNETWORK_LIB Qt5::Network)
		endif()
	endif()
endif()
if (NOT QTCORE_LIB)
	find_package(Qt4 COMPONENTS QtCore OPTIONAL_COMPONENTS QtNetwork)
	if (Qt4_FOUND)
		set(QTCORE_LIB Qt4::QtCore)
		if (QT_NETWORK_FOUND)
			set(QTNETWORK_LIB Qt4::QtNetwork)
		endif()
	endif()
endif()


if (QTCORE_LIB)
	add_executable(QtVariantTest QtVariantTest.cpp "${PROJECT_SOURCE_DIR}/../HttpStatusCodes_Qt.h")
	target_link_libraries(QtVariantTest ${GTEST_MAIN} ${QTCORE_LIB} ${QTNETWORK_LIB})
	add_test(NAME QtVariantTest COMMAND QtVariantTest)
	if (WIN32)
		set_tests_properties( QtVariantTest PROPERTIES ENVIRONMENT "PATH=$<TARGET_FILE_DIR:${QTCORE_LIB}>;$ENV{PATH}" )
	endif()

	add_executable(QtC++11VariantTest QtC++11VariantTest.cpp "${PROJECT_SOURCE_DIR}/../HttpStatusCodes_Qt_C++11.h")
	target_link_libraries(QtC++11VariantTest ${GTEST_MAIN} ${QTCORE_LIB} ${QTNETWORK_LIB})
	add_test(NAME QtC++11VariantTest COMMAND QtVariantTest)
	if (WIN32)
		set_tests_properties( QtC++11VariantTest PROPERTIES ENVIRONMENT "PATH=$<TARGET_FILE_DIR:${QTCORE_LIB}>;$ENV{PATH}" )
	endif()
endif()
