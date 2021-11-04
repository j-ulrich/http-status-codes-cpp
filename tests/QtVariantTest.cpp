#include "gtest/gtest.h"

#include "HttpStatusCodes_Qt.h"
#include "CategoryTesterTest.h"

#if (QT_VERSION >= 0x050800)
#	include <QMetaEnum>
#endif

namespace QtVariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::InternalServerError), 500);
}

#if (QT_VERSION >= 0x050800)

//####### MetaEnum Test #######
TEST(MetaEnumTest, testKeyToValue)
{
	ASSERT_TRUE(QMetaEnum::fromType<HttpStatus::Code>().isValid());
	ASSERT_EQ(QMetaEnum::fromType<HttpStatus::Code>().keyToValue("RangeNotSatisfiable"), HttpStatus::RangeNotSatisfiable);
}

#endif // Qt >= 5.8.0

//####### Reason Phrase Test #######
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
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::GatewayTimeout)), QString("Gateway Timeout"));
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


#ifdef QT_NETWORK_LIB
//####### NetworkError Mapping Test #######
TEST(NetworkErrorMappingTest, testNetworkErrorToStatusCode)
{
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::ContentNotFoundError), HttpStatus::NotFound);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::NoError),              HttpStatus::OK);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::UnknownContentError),  HttpStatus::BadRequest);
#if QT_VERSION >= QT_VERSION_CHECK(5,3,0)
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::UnknownServerError),   HttpStatus::InternalServerError);
#endif // Qt >= 5.3.0
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::ProtocolFailure),      -1);
}

TEST(NetworkErrorMappingTest, testStatusCodeToNetworkError)
{
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Unauthorized),        QNetworkReply::AuthenticationRequiredError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::OK),                  QNetworkReply::NoError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::URITooLong),          QNetworkReply::UnknownContentError);
#if QT_VERSION >= QT_VERSION_CHECK(5,3,0)
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::InsufficientStorage), QNetworkReply::UnknownServerError);
#endif // Qt >= 5.3.0
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(601),                             QNetworkReply::ProtocolFailure);
}
#endif // QT_NETWORK_LIB


} // namespace QtVariantTests
