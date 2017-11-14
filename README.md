# HTTP Status Codes and Reason Phrases for C, C++ and Qt #

[![Linux build status](https://travis-ci.org/j-ulrich/http-status-codes-cpp.svg?branch=master)](https://travis-ci.org/j-ulrich/http-status-codes-cpp)
[![Windows build status](https://ci.appveyor.com/api/projects/status/ijp196mjo0vsover/branch/master?svg=true)](https://ci.appveyor.com/project/j-ulrich/http-status-codes-cpp/branch/master)


This repository provides the HTTP status codes and reason phrases in different variants for C/C++.

Simply take the variant that fits your needs and copy/use/modify it.

Data has been taken from [for-GET/know-your-http-well](https://github.com/for-GET/know-your-http-well).

### Table of Contents ###

> - [Variants](#variants)
> - [Example](#example)
> - [Documentation](#documentation)
>   - [Status Codes Enum](#status-codes-enum)
>   - [Category/Class Tests](#categoryclass-tests)
>   - [Reason Phrases](#reason-phrases)
>   - [QNetworkReply::NetworkError Mapping](#qnetworkreplynetworkerror-mapping)
> - [License](#license)



## Variants ##

| Variant                          | Scoping                | Status Codes                                                                                   | Reason Phrases |
|----------------------------------|------------------------|------------------------------------------------------------------------------------------------|----------------|
| [C](HttpStatusCodes_C.h)         | Prefix `HttpStatus_`   | `enum HttpStatus_Code`                                                                         | `const char*`  |
| [C++](HttpStatusCodes_C++.h)     | Namespace `HttpStatus` | `enum Code`                                                                                    | `std::string`  |
| [C++11](HttpStatusCodes_C++11.h) | Namespace `HttpStatus` | `enum class Code`                                                                              | `std::string`  |
| [Qt](HttpStatusCodes_Qt.h)       | Namespace `HttpStatus` | `enum Code`<br>When using Qt 5.8 or later: registered in meta type system using `Q_ENUM_NS()`  | `QString`      |



## Example ##

```c++
#include "MyHttpReplyClass.h"
#include "HttpStatusCodes_C++.h"
#include <iostream>

void printReplyStatus(MyHttpReplyClass reply)
{
	if (reply.status == HttpStatus::OK)
		std::cout << "Success!";
	else
		std::cerr << reply.status << " " << HttpStatus::reasonPhrase(reply.status);
}
```



## Documentation ##

> **Note:** The header files contain more detailed Doxygen documentation for all types and functions.

### Status Codes Enum ###

For the complete list of defined enums, see one of the header files.

#### C Variant ####
```c
enum HttpStatus_Code
{
	HttpStatus_OK       = 200,
	HttpStatus_NotFound = 404 
	// ...
};
```

#### C++11 Variant ####
```c++
namespace HttpStatus {
enum class Code
{
	OK        = 200,
	Forbidden = 404
	// ...
};
}
```

#### Other Variants ####
```c++
namespace HttpStatus {
enum Code
{
	OK        = 200,
	Forbidden = 404
	// ...
};
}
```


### Category/Class Tests ###

#### C Variant ####
```c
char HttpStatus_isInformational(int code);
char HttpStatus_isSuccessful(int code);
char HttpStatus_isRedirection(int code);
char HttpStatus_isClientError(int code);
char HttpStatus_isServerError(int code);
```
Return `1` if the given _code_ belongs to the corresponding class of status codes (see [RFC7231](https://tools.ietf.org/html/rfc7231#section-6)).
Return `0` otherwise.

```c
char HttpStatus_isError(int code);
```
Returns `1` if the given _code_ is either a client error, a server error or any non-standard error code.
Non-standard error codes are status codes with a value of 600 or higher.
Returns `0` otherwise.

#### Other Variants ####
> **Note:** The C++11 variant also provides overloads for `HttpStatus::Code`. So there is no need to cast.

```c++
bool HttpStatus::isInformational(int code);
bool HttpStatus::isSuccessful(int code);
bool HttpStatus::isRedirection(int code);
bool HttpStatus::isClientError(int code);
bool HttpStatus::isServerError(int code);
```
Return `true` if the given _code_ belongs to the corresponding class of status codes (see [RFC7231](https://tools.ietf.org/html/rfc7231#section-6)).
Return `false` otherwise.



```c++
bool HttpStatus::isError(int code);
```
Returns `true` if the given _code_ is either a client error, a server error or any non-standard error code.
Non-standard error codes are status codes with a value of 600 or higher.
Returns `false` otherwise.


### Reason Phrases ###

#### C Variant ####
```c
const char* HttpStatus_reasonPhrase(int code);
```
Returns the HTTP reason phrase string corresponding to the given _code_.

#### C++/C++11 Variants ####
> **Note:** The C++11 variant also provides an overload for `HttpStatus::Code`. So there is no need to cast.
```c++
std::string HttpStatus::reasonPhrase(int code);
```
Returns the HTTP reason phrase string corresponding to the given _code_.

#### Qt Variant ####
```c++
QString HttpStatus::reasonPhrase(int code);
```
Returns the HTTP reason phrase string corresponding to the given _code_.


### QNetworkReply::NetworkError Mapping ###

> **Note:** Available only in the Qt variant and if the Qt::Network module is available.

#### Qt Variant ####
```c++
int HttpStatus::networkErrorToStatusCode(QNetworkReply::NetworkError error);
```
Returns the HTTP status code corresponding to the given _error_ if there is one.
Otherwise, `-1` is returned.

```c++
QNetworkReply::NetworkError HttpStatus::statusCodeToNetworkError(int code);
```
Returns the `QNetworkReply::NetworkError` corresponding to the given _code_ if there is one.
For codes where there is no exact match, the best matchnig "catch all" code (`QNetworkReply::NoError`,
`QNetworkReply::UnknownContentError`, `QNetworkReply::UnknownServerError` or `QNetworkReply::ProtocolFailure`)
is returned.



## License ##
[![CC0](https://licensebuttons.net/p/zero/1.0/80x15.png)](http://creativecommons.org/publicdomain/zero/1.0/)    
This project is licensed under [Creative Commons CC0](LICENSE).
