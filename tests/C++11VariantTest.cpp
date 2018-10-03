#include "gtest/gtest.h"

#include "HttpStatusCodes_C++11.h"
#include "CategoryTesterTest.h"

namespace Cpp11VariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::InternalServerError), 500);
}


//####### Reason Phrase Test #######
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

TEST(ReasonPhraseTest, testEnumOverloadExtended)
{
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(HttpStatus::Code::OK),
		std::string("Indicates that the request has succeeded."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(HttpStatus::Code::NotFound),
		std::string("Indicates that the origin server did not find a current representation for the target resource or is not willing to disclose that one exists."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(HttpStatus::Code::InternalServerError),
		std::string("A generic error message, given when an unexpected condition was encountered and no more specific message is suitable."));
}

TEST(ReasonPhraseTest, testIntegerOverloadExtended)
{
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(static_cast<int>(HttpStatus::Code::Accepted)),
		std::string("Indicates that the request has been accepted for processing, but the processing has not been completed."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(static_cast<int>(HttpStatus::Code::MethodNotAllowed)),
		std::string("Indicates that the method specified in the request-line is known by the origin server but not supported by the target resource."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(static_cast<int>(HttpStatus::Code::ServiceUnavailable)),
		std::string("Indicates that the server is currently unable to handle the request due to a temporary overload or scheduled maintenance, which will likely be alleviated after some delay."));
}

//####### Category Tester Test #######

INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                                        // info // success // redir // clientErr // serverErr // error
CategoryTesterParams(HttpStatus::Code::Processing,                  true,   false,     false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::ResetContent,                false,  true,      false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::Found,                       false,  false,     true,    false,       false,       false),
CategoryTesterParams(HttpStatus::Code::ProxyAuthenticationRequired, false,  false,     false,   true,        false,       true),
CategoryTesterParams(HttpStatus::Code::HTTPVersionNotSupported,     false,  false,     false,   false,       true,        true)
));



} // namespace Cpp11VariantTests
