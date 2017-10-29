#include "gtest/gtest.h"

#include "HttpStatusCodes_C.h"

namespace CVariantTests
{

//####### Enum Test #######
TEST(EnumTest, testEnumValues)
{
	ASSERT_EQ(static_cast<int>(HttpStatus_OK),                  200);
	ASSERT_EQ(static_cast<int>(HttpStatus_NotFound),            404);
	ASSERT_EQ(static_cast<int>(HttpStatus_InternalServerError), 500);
}


//####### Reason Phrase Test #######
TEST(ReasonPhraseTest, testReasonPhrase)
{
	ASSERT_STREQ(HttpStatus_reasonPhrase(HttpStatus_OK),                  "OK");
	ASSERT_STREQ(HttpStatus_reasonPhrase(HttpStatus_NotFound),            "Not Found");
	ASSERT_STREQ(HttpStatus_reasonPhrase(HttpStatus_InternalServerError), "Internal Server Error");
}


//####### Category Tester Test #######
struct CategoryTesterParams
{
	HttpStatus_Code code;
	int isInformational;
	int isSuccessful;
	int isRedirection;
	int isClientError;
	int isServerError;
	int isError;
};

class CategoryTesterTest : public ::testing::TestWithParam<CategoryTesterParams>
{

};

TEST_P(CategoryTesterTest, test)
{
	auto params = GetParam();

	ASSERT_EQ(HttpStatus_isInformational(params.code), params.isInformational);
	ASSERT_EQ(HttpStatus_isSuccessful(params.code),    params.isSuccessful);
	ASSERT_EQ(HttpStatus_isRedirection(params.code),   params.isRedirection);
	ASSERT_EQ(HttpStatus_isClientError(params.code),   params.isClientError);
	ASSERT_EQ(HttpStatus_isServerError(params.code),   params.isServerError);
	ASSERT_EQ(HttpStatus_isError(params.code),         params.isError);
}

INSTANTIATE_TEST_CASE_P(DefaultInstance, CategoryTesterTest, ::testing::Values(
//                   // code                         // info // success // redir // clientErr // serverErr // error
CategoryTesterParams{HttpStatus_Continue,               1,      0,         0,       0,           0,           0},
CategoryTesterParams{HttpStatus_OK,                     0,      1,         0,       0,           0,           0},
CategoryTesterParams{HttpStatus_MovedPermanently,       0,      0,         1,       0,           0,           0},
CategoryTesterParams{HttpStatus_NotFound,               0,      0,         0,       1,           0,           1},
CategoryTesterParams{HttpStatus_InternalServerError,    0,      0,         0,       0,           1,           1}
));



} // namespace CVariantTests
