#include "gtest/gtest.h"

#include "HttpStatusCodes_C++11.h"

namespace Cpp11VariantTests
{


TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::InternalServerError), 500);
}

TEST(ReasonPhraseTest, testEnumOverload)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::OK),                  std::string("OK"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::NotFound),            std::string("Not Found"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::InternalServerError), std::string("Internal Server Error"));
}

TEST(ReasonPhraseTest, testIntegerOverload)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::Accepted)),           std::string("Accepted"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::MethodNotAllowed)),   std::string("Method Not Allowed"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::ServiceUnavailable)), std::string("Service Unavailable"));
}

struct CategoryTesterParams
{
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

TEST_P(CategoryTesterTest, testEnumOverload)
{
	auto params = GetParam();

	ASSERT_EQ(HttpStatus::isInformational(params.code), params.isInformational);
	ASSERT_EQ(HttpStatus::isSuccessful(params.code),    params.isSuccessful);
	ASSERT_EQ(HttpStatus::isRedirection(params.code),   params.isRedirection);
	ASSERT_EQ(HttpStatus::isClientError(params.code),   params.isClientError);
	ASSERT_EQ(HttpStatus::isServerError(params.code),   params.isServerError);
	ASSERT_EQ(HttpStatus::isError(params.code),         params.isError);
}

TEST_P(CategoryTesterTest, testIntegerOverload)
{
	auto params = GetParam();

	ASSERT_EQ(HttpStatus::isInformational(static_cast<int>(params.code)), params.isInformational);
	ASSERT_EQ(HttpStatus::isSuccessful(static_cast<int>(params.code)),    params.isSuccessful);
	ASSERT_EQ(HttpStatus::isRedirection(static_cast<int>(params.code)),   params.isRedirection);
	ASSERT_EQ(HttpStatus::isClientError(static_cast<int>(params.code)),   params.isClientError);
	ASSERT_EQ(HttpStatus::isServerError(static_cast<int>(params.code)),   params.isServerError);
	ASSERT_EQ(HttpStatus::isError(static_cast<int>(params.code)),         params.isError);
}


INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                                        // info // success // redir // clientErr // serverErr // error
CategoryTesterParams{HttpStatus::Code::Processing,                  true,   false,     false,   false,       false,       false},
CategoryTesterParams{HttpStatus::Code::ResetContent,                false,  true,      false,   false,       false,       false},
CategoryTesterParams{HttpStatus::Code::Found,                       false,  false,     true,    false,       false,       false},
CategoryTesterParams{HttpStatus::Code::ProxyAuthenticationRequired, false,  false,     false,   true,        false,       true},
CategoryTesterParams{HttpStatus::Code::HTTPVersionNotSupported,     false,  false,     false,   false,       true,        true}
));



} // namespace Cpp11VariantTests
