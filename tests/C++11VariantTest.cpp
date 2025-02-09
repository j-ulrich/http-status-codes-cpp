#include "gtest/gtest.h"

#include "HttpStatusCodes_C++11.h"
#include "CategoryTesterTest.h"

namespace Cpp11VariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::Invalid),             -1);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::InternalServerError), 500);
}


//####### Reason Phrase Test #######
TEST(ReasonPhraseTest, testEnumOverload)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::Invalid),             std::string());
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::OK),                  std::string("OK"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::NotFound),            std::string("Not Found"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::InternalServerError), std::string("Internal Server Error"));
}

TEST(ReasonPhraseTest, testIntegerOverload)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::Invalid)),            std::string());
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::Accepted)),           std::string("Accepted"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::MethodNotAllowed)),   std::string("Method Not Allowed"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::ServiceUnavailable)), std::string("Service Unavailable"));
}


//####### Category Tester Test #######

INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                                        // info // success // redir // clientErr // serverErr // error
CategoryTesterParams(HttpStatus::Code::Invalid,                     false,  false,     false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::Processing,                  true,   false,     false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::ResetContent,                false,  true,      false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::Found,                       false,  false,     true,    false,       false,       false),
CategoryTesterParams(HttpStatus::Code::ProxyAuthenticationRequired, false,  false,     false,   true,        false,       true),
CategoryTesterParams(HttpStatus::Code::HTTPVersionNotSupported,     false,  false,     false,   false,       true,        true)
));


//####### Conversion Function Test #######

TEST(ConversionFunctionTest, testToInt)
{
	ASSERT_EQ(HttpStatus::toInt(HttpStatus::Code::SwitchingProtocols), static_cast<int>(HttpStatus::Code::SwitchingProtocols));
	ASSERT_EQ(HttpStatus::toInt(HttpStatus::Code::Invalid),            static_cast<int>(HttpStatus::Code::Invalid));
	ASSERT_EQ(HttpStatus::toInt(HttpStatus::Code::OK),                 static_cast<int>(HttpStatus::Code::OK));
	ASSERT_EQ(HttpStatus::toInt(HttpStatus::Code::NotExtended),        static_cast<int>(HttpStatus::Code::NotExtended));
}


} // namespace Cpp11VariantTests
