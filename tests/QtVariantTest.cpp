#include "gtest/gtest.h"

#include "HttpStatusCodes_Qt.h"
#include "tests/CategoryTesterTest.h"

namespace QtVariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus::OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus::NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus::InternalServerError), 500);
}


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
	ASSERT_EQ(HttpStatus::reasonPhrase(static_cast<int>(HttpStatus::GatewayTimeout)), QString("Gateway Time-out"));
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


//####### NetworkError Mapping Test #######
TEST(NetworkErrorMappingTest, testNetworkErrorToStatusCode)
{
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::ContentNotFoundError), HttpStatus::NotFound);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::NoError),              HttpStatus::OK);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::UnknownContentError),  HttpStatus::BadRequest);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::UnknownServerError),   HttpStatus::InternalServerError);
	ASSERT_EQ(HttpStatus::networkErrorToStatusCode(QNetworkReply::ProtocolFailure),      -1);
}

TEST(NetworkErrorMappingTest, testStatusCodeToNetworkError)
{
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::Unauthorized),        QNetworkReply::AuthenticationRequiredError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::OK),                  QNetworkReply::NoError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::URITooLong),          QNetworkReply::UnknownContentError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(HttpStatus::InsufficientStorage), QNetworkReply::UnknownServerError);
	ASSERT_EQ(HttpStatus::statusCodeToNetworkError(601),                             QNetworkReply::ProtocolFailure);
}



} // namespace QtVariantTests
