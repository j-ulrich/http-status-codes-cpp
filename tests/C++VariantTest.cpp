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

TEST(ReasonPhraseTest, testEnumParameterEx)
{
	ASSERT_EQ(HttpStatus::reasonPhraseEx(HttpStatus::OK),                  std::string("HTTP 200: OK"));
	ASSERT_EQ(HttpStatus::reasonPhraseEx(HttpStatus::NotFound),            std::string("HTTP 404: Not Found"));
	ASSERT_EQ(HttpStatus::reasonPhraseEx(HttpStatus::InternalServerError), std::string("HTTP 500: Internal Server Error"));
}

TEST(ReasonPhraseTest, testIntegerParameterEx)
{
	ASSERT_EQ(HttpStatus::reasonPhraseEx(static_cast<int>(HttpStatus::Created)),        std::string("HTTP 201: Created"));
	ASSERT_EQ(HttpStatus::reasonPhraseEx(static_cast<int>(HttpStatus::Unauthorized)),   std::string("HTTP 401: Unauthorized"));
	ASSERT_EQ(HttpStatus::reasonPhraseEx(static_cast<int>(HttpStatus::GatewayTimeout)), std::string("HTTP 504: Gateway Time-out"));
	ASSERT_EQ(HttpStatus::reasonPhraseEx(999), std::string("HTTP 999"));
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
