/*! \file
 *
 * \date Created on: 29.10.2017
 * \author jochen.ulrich
 */

#ifndef HTTPSTATUSCODES_TESTS_CATEGORYTESTERTEST_H_
#define HTTPSTATUSCODES_TESTS_CATEGORYTESTERTEST_H_

#include "gtest/gtest.h"

// We rely on HttpStatus::Code being defined in the test source files

struct CategoryTesterParams
{
	CategoryTesterParams(HttpStatus::Code code,
	                     bool isInformational,
	                     bool isSuccessful,
	                     bool isRedirection,
	                     bool isClientError,
	                     bool isServerError,
	                     bool isError)
		: code(code)
		, isInformational(isInformational)
		, isSuccessful(isSuccessful)
		, isRedirection(isRedirection)
		, isClientError(isClientError)
		, isServerError(isServerError)
		, isError(isError)
	{ }

	HttpStatus::Code code;
	bool isInformational;
	bool isSuccessful;
	bool isRedirection;
	bool isClientError;
	bool isServerError;
	bool isError;

};

class CategoryTesterTest : public ::testing::TestWithParam<CategoryTesterParams>
{

};

TEST_P(CategoryTesterTest, testEnumParameter)
{
	auto params = GetParam();

	ASSERT_EQ(HttpStatus::isInformational(params.code), params.isInformational);
	ASSERT_EQ(HttpStatus::isSuccessful(params.code),    params.isSuccessful);
	ASSERT_EQ(HttpStatus::isRedirection(params.code),   params.isRedirection);
	ASSERT_EQ(HttpStatus::isClientError(params.code),   params.isClientError);
	ASSERT_EQ(HttpStatus::isServerError(params.code),   params.isServerError);
	ASSERT_EQ(HttpStatus::isError(params.code),         params.isError);
}

TEST_P(CategoryTesterTest, testIntegerParameter)
{
	auto params = GetParam();

	ASSERT_EQ(HttpStatus::isInformational(static_cast<int>(params.code)), params.isInformational);
	ASSERT_EQ(HttpStatus::isSuccessful(static_cast<int>(params.code)),    params.isSuccessful);
	ASSERT_EQ(HttpStatus::isRedirection(static_cast<int>(params.code)),   params.isRedirection);
	ASSERT_EQ(HttpStatus::isClientError(static_cast<int>(params.code)),   params.isClientError);
	ASSERT_EQ(HttpStatus::isServerError(static_cast<int>(params.code)),   params.isServerError);
	ASSERT_EQ(HttpStatus::isError(static_cast<int>(params.code)),         params.isError);
}


#endif /* HTTPSTATUSCODES_TESTS_CATEGORYTESTERTEST_H_ */
