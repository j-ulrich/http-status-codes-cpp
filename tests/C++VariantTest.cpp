#include "gtest/gtest.h"

#include "HttpStatusCodes_C++.h"
#include "CategoryTesterTest.h"

namespace CppVariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(HttpStatus::OK,                  200);
	ASSERT_EQ(HttpStatus::NotFound,            404);
	ASSERT_EQ(HttpStatus::InternalServerError, 500);
}


//####### Reason Phrase Test #######
TEST(ReasonPhraseTest, testEnumParameter)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::OK),                  std::string("OK"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::NotFound),            std::string("Not Found"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::InternalServerError), std::string("Internal Server Error"));
}

TEST(ReasonPhraseTest, testIntegerParameter)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Created)),        std::string("Created"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Unauthorized)),   std::string("Unauthorized"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::GatewayTimeout)), std::string("Gateway Time-out"));
}

TEST(ReasonPhraseTest, testEnumParameterExtended)
{
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(HttpStatus::OK),
		std::string("Indicates that the request has succeeded."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(HttpStatus::NotFound),
		std::string("Indicates that the origin server did not find a current representation for the target resource or is not willing to disclose that one exists."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(HttpStatus::InternalServerError),
		std::string("A generic error message, given when an unexpected condition was encountered and no more specific message is suitable."));
}

TEST(ReasonPhraseTest, testIntegerParameterExtended)
{
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(static_cast<int>(HttpStatus::Accepted)),
		std::string("Indicates that the request has been accepted for processing, but the processing has not been completed."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(static_cast<int>(HttpStatus::MethodNotAllowed)),
		std::string("Indicates that the method specified in the request-line is known by the origin server but not supported by the target resource."));
	ASSERT_EQ(HttpStatus::reasonPhraseExtended(static_cast<int>(HttpStatus::ServiceUnavailable)),
		std::string("Indicates that the server is currently unable to handle the request due to a temporary overload or scheduled maintenance, which will likely be alleviated after some delay."));
}

//####### Category Tester Test #######
INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                          // info // success // redir // clientErr // serverErr // error
CategoryTesterParams(HttpStatus::SwitchingProtocols,  true,   false,     false,   false,       false,       false),
CategoryTesterParams(HttpStatus::NoContent,           false,  true,      false,   false,       false,       false),
CategoryTesterParams(HttpStatus::SeeOther,            false,  false,     true,    false,       false,       false),
CategoryTesterParams(HttpStatus::Forbidden,           false,  false,     false,   true,        false,       true),
CategoryTesterParams(HttpStatus::NotImplemented,      false,  false,     false,   false,       true,        true)
));



} // namespace CppVariantTests
