#include "gtest/gtest.h"

#include "HttpStatusCodes_Qt_C++11.h"
#include "CategoryTesterTest.h"

#if (QT_VERSION >= 0x050800)
#	include <QMetaEnum>
#endif

namespace QtVariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::Invalid),             -1);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::Code::InternalServerError), 500);
}

#if (QT_VERSION >= 0x050800)

//####### MetaEnum Test #######
TEST(MetaEnumTest, testKeyToValue)
{
	ASSERT_TRUE(QMetaEnum::fromType<HttpStatus::Code>().isValid());
	ASSERT_EQ(QMetaEnum::fromType<HttpStatus::Code>().keyToValue("RangeNotSatisfiable"), static_cast<int>(HttpStatus::Code::RangeNotSatisfiable));
}

#endif // Qt >= 5.8.0

//####### Reason Phrase Test #######
TEST(ReasonPhraseTest, testEnumParameter)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::Invalid),             QString());
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::OK),                  QString("OK"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::NotFound),            QString("Not Found"));
	ASSERT_EQ(HttpStatus::reasonPhrase(HttpStatus::Code::InternalServerError), QString("Internal Server Error"));
}

TEST(ReasonPhraseTest, testIntegerParameter)
{
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::Created)),        QString("Created"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::Unauthorized)),   QString("Unauthorized"));
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::Code::GatewayTimeout)), QString("Gateway Timeout"));
}


//####### Category Tester Test #######
INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                                // info // success // redir // clientErr // serverErr // error
CategoryTesterParams(HttpStatus::Code::Invalid,             false,  false,     false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::SwitchingProtocols,  true,   false,     false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::NoContent,           false,  true,      false,   false,       false,       false),
CategoryTesterParams(HttpStatus::Code::SeeOther,            false,  false,     true,    false,       false,       false),
CategoryTesterParams(HttpStatus::Code::Forbidden,           false,  false,     false,   true,        false,       true),
CategoryTesterParams(HttpStatus::Code::NotImplemented,      false,  false,     false,   false,       true,        true)
));


#ifdef QT_NETWORK_LIB
//####### NetworkError Mapping Test #######
TEST(NetworkErrorMappingTest, testNetworkErrorToStatusCode)
{
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::ContentNotFoundError), HttpStatus::Code::NotFound);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::NoError),              HttpStatus::Code::OK);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::UnknownContentError),  HttpStatus::Code::BadRequest);
#if QT_VERSION >= QT_VERSION_CHECK(5,3,0)
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::UnknownServerError),   HttpStatus::Code::InternalServerError);
#endif // Qt >= 5.3.0
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::ProtocolFailure),      HttpStatus::Code::Invalid);
}

TEST(NetworkErrorMappingTest, testStatusCodeToNetworkError)
{
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Code::Unauthorized),        QNetworkReply::AuthenticationRequiredError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Code::Invalid),             QNetworkReply::NoError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Code::OK),                  QNetworkReply::NoError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Code::URITooLong),          QNetworkReply::UnknownContentError);
#if QT_VERSION >= QT_VERSION_CHECK(5,3,0)
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Code::InsufficientStorage), QNetworkReply::UnknownServerError);
#endif // Qt >= 5.3.0
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(static_cast<HttpStatus::Code>( 601 )),  QNetworkReply::ProtocolFailure);
}

TEST(NetworkErrorMappingTest, testStatusCodeToNetworkErrorIntegerParameter)
{
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(static_cast<int>(HttpStatus::Code::Unauthorized)), QNetworkReply::AuthenticationRequiredError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(static_cast<int>(HttpStatus::Code::Invalid)),      QNetworkReply::NoError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(static_cast<int>(HttpStatus::Code::OK)),           QNetworkReply::NoError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError( 601 ),                                            QNetworkReply::ProtocolFailure);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(static_cast<int>(HttpStatus::Code::xxx_max) + 1 ), QNetworkReply::ProtocolFailure);
}
#endif // QT_NETWORK_LIB


} // namespace QtVariantTests
