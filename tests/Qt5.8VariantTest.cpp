#include "gtest/gtest.h"

#include "HttpStatusCodes_Qt5.8.h"

#include <QMetaEnum>

namespace Qt5_8VariantTests
{


TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::InternalServerError), 500);
}

TEST(ReasonPhraseTest, testEnumParameter)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::OK),                  QString("OK"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::NotFound),            QString("Not Found"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::InternalServerError), QString("Internal Server Error"));
}

TEST(ReasonPhraseTest, testIntegerParameter)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Created)),        QString("Created"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Unauthorized)),   QString("Unauthorized"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::GatewayTimeout)), QString("Gateway Time-out"));
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


INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                          // info // success // redir // clientErr // serverErr // error
CategoryTesterParams{HttpStatus::SwitchingProtocols,  true,   false,     false,   false,       false,       false},
CategoryTesterParams{HttpStatus::NoContent,           false,  true,      false,   false,       false,       false},
CategoryTesterParams{HttpStatus::SeeOther,            false,  false,     true,    false,       false,       false},
CategoryTesterParams{HttpStatus::Forbidden,           false,  false,     false,   true,        false,       true},
CategoryTesterParams{HttpStatus::NotImplemented,      false,  false,     false,   false,       true,        true}
));


TEST(MetaEnumTest, testKeyToValue)
{
	ASSERT_TRUE(QMetaEnum::fromType<HttpStatus::Code>().isValid());
	ASSERT_EQ(QMetaEnum::fromType<HttpStatus::Code>().keyToValue("RangeNotSatisfiable"), HttpStatus::RangeNotSatisfiable);
}


} // namespace QtVariantTests
