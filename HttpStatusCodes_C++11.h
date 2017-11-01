/*! \file
 *
 * HTTP Status Codes for C/C++
 *
 * https://github.com/j-ulrich/http-status-codes-cpp
 *
 * \date Created on 06.10.2017
 * \author Jochen Ulrich <jochenulrich@t-online.de>
 * \copyright Licensed under Creative Commons CC0 (http://creativecommons.org/publicdomain/zero/1.0/)
 */

#ifndef HTTPSTATUSCODES_CPP_H_
#define HTTPSTATUSCODES_CPP_H_

/*####### Configuration #######*/

/*! \def HTTPSTATUSCODES_USE_STRONG_ENUM_TYPE
 */

/*! \def HTTPSTATUSCODES_USE_STD_STRING
 */

/*! \def HTTPSTATUSCODES_USE_NAMESPACE
 */

/*! \def HTTPSTATUSCODES_NAMESPACE
 */

/*! \def HTTPSTATUSCODES_USE_PREFIX
 */

/*! \def HTTPSTATUSCODES_PREFIX
 */

/*! \def HTTPSTATUSCODES_ENUM_TYPE
 */

/*! \def HTTPSTATUSCODES_STRING_TYPE
 */

/*! \def HTTPSTATUSCODES_NULL_STRING
 */

#if defined(__cplusplus)
/* C++ */

/* Per default, use namespace */
#if !defined(HTTPSTATUSCODES_USE_NAMESPACE)
#	define HTTPSTATUSCODES_USE_NAMESPACE 1
#endif

/* Per default, do not use prefix */
#if !defined(HTTPSTATUSCODES_USE_PREFIX)
#	define HTTPSTATUSCODES_USE_PREFIX 0
#endif

#if __cplusplus >= 201103L && defined(HTTPSTATUSCODES_USE_STRONG_ENUM_TYPE) && HTTPSTATUSCODES_USE_STRONG_ENUM_TYPE
#	define HTTPSTATUSCODES_ENUM_TYPE enum class
#else
#	define HTTPSTATUSCODES_ENUM_TYPE enum
#endif /* enum type */

#if defined(QT_VERSION) && ( !defined(HTTPSTATUSCODES_USE_STD_STRING) || !HTTPSTATUSCODES_USE_STD_STRING )
#	include <QString>
#	define HTTPSTATUSCODES_STRING_TYPE QString
#	define HTTPSTATUSCODES_NULL_STRING QString()
#else
#	include <string>
#	define HTTPSTATUSCODES_STRING_TYPE std::string
#	define HTTPSTATUSCODES_NULL_STRING std::string()
#endif /* string type */


#else
/* C */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	include <stdbool.h>
#else
#	define bool char
#	define true 1
#	define false 0
#endif /* bool */

/* C does not support namespaces */
#define HTTPSTATUSCODES_USE_NAMESPACE 0

/* Per default, use prefix */
#if !defined(HTTPSTATUSCODES_USE_PREFIX)
#	define HTTPSTATUSCODES_USE_PREFIX 1
#endif

#define HTTPSTATUSCODES_STRING_TYPE const char*
#define HTTPSTATUSCODES_NULL_STRING 0


#endif /* defined(__cplusplus) */

/* Default namespace */
#if !defined(HTTPSTATUSCODES_NAMESPACE)
#	define HTTPSTATUSCODES_NAMESPACE HttpStatus
#endif

/* Default prefix */
#if !defined(HTTPSTATUSCODES_PREFIX)
#	define HTTPSTATUSCODES_PREFIX HttpStatus_
#endif

#if defined(HTTPSTATUSCODES_USE_PREFIX) && HTTPSTATUSCODES_USE_PREFIX
#	define HTTPSTATUSCODES__CONCAT(x, y) x ## y
#	define HTTPSTATUSCODES_ADD_PREFIX(x) HTTPSTATUSCODES__CONCAT(HTTPSTATUSCODES_PREFIX, x)
#else
#	define HTTPSTATUSCODES_ADD_PREFIX(x) x
#endif


#if defined(HTTPSTATUSCODES_USE_NAMESPACE)
/*! Namespace for HTTP status codes and reason phrases.
 */
namespace HTTPSTATUSCODES_NAMESPACE
{
#endif // defined(HTTPSTATUSCODES_USE_NAMESPACE)

/*! Enum for the HTTP status codes.
 */
HTTPSTATUSCODES_ENUM_TYPE HTTPSTATUSCODES_ADD_PREFIX(Code)
{
	/*####### 1xx - Informational #######*/
	/* Indicates an interim response for communicating connection status
	 * or request progress prior to completing the requested action and
	 * sending a final response.
	 */
	HTTPSTATUSCODES_ADD_PREFIX(Continue)           = 100, /*!< Indicates that the initial part of a request has been received and has not yet been rejected by the server. */                                                                                                                                                                                                    //!< Continue
	HTTPSTATUSCODES_ADD_PREFIX(SwitchingProtocols) = 101, /*!< Indicates that the server understands and is willing to comply with the client's request, via the Upgrade header field, for a change in the application protocol being used on this connection. */                                                                                                                //!< SwitchingProtocols
	HTTPSTATUSCODES_ADD_PREFIX(Processing)         = 102, /*!< Is an interim response used to inform the client that the server has accepted the complete request, but has not yet completed it. */                                                                                                                                                                              //!< Processing

	/*####### 2xx - Successful #######*/
	/* Indicates that the client's request was successfully received,
	 * understood, and accepted.
	 */
	HTTPSTATUSCODES_ADD_PREFIX(OK)                          = 200, /*!< Indicates that the request has succeeded. */                                                                                                                                                                                                                                                             //!< OK
	HTTPSTATUSCODES_ADD_PREFIX(Created)                     = 201, /*!< Indicates that the request has been fulfilled and has resulted in one or more new resources being created. */                                                                                                                                                                                            //!< Created
	HTTPSTATUSCODES_ADD_PREFIX(Accepted)                    = 202, /*!< Indicates that the request has been accepted for processing, but the processing has not been completed. */                                                                                                                                                                                               //!< Accepted
	HTTPSTATUSCODES_ADD_PREFIX(NonAuthoritativeInformation) = 203, /*!< Indicates that the request was successful but the enclosed payload has been modified from that of the origin server's 200 (OK) response by a transforming proxy. */                                                                                                                                      //!< NonAuthoritativeInformation
	HTTPSTATUSCODES_ADD_PREFIX(NoContent)                   = 204, /*!< Indicates that the server has successfully fulfilled the request and that there is no additional content to send in the response payload body. */                                                                                                                                                        //!< NoContent
	HTTPSTATUSCODES_ADD_PREFIX(ResetContent)                = 205, /*!< Indicates that the server has fulfilled the request and desires that the user agent reset the \"document view\", which caused the request to be sent, to its original state as received from the origin server. */                                                                                       //!< ResetContent
	HTTPSTATUSCODES_ADD_PREFIX(PartialContent)              = 206, /*!< Indicates that the server is successfully fulfilling a range request for the target resource by transferring one or more parts of the selected representation that correspond to the satisfiable ranges found in the requests's Range header field. */                                                   //!< PartialContent
	HTTPSTATUSCODES_ADD_PREFIX(MultiStatus)                 = 207, /*!< Provides status for multiple independent operations. */                                                                                                                                                                                                                                                  //!< MultiStatus
	HTTPSTATUSCODES_ADD_PREFIX(IMUsed)                      = 226, /*!< The server has fulfilled a GET request for the resource, and the response is a representation of the result of one or more instance-manipulations applied to the current instance. */                                                                                                                    //!< IMUsed

	/*####### 3xx - Redirection #######*/
	/* Indicates that further action needs to be taken by the user agent
	 * in order to fulfill the request.
	 */
	HTTPSTATUSCODES_ADD_PREFIX(MultipleChoices)   = 300, /*!< Indicates that the target resource has more than one representation, each with its own more specific identifier, and information about the alternatives is being provided so that the user (or user agent) can select a preferred representation by redirecting its request to one or more of those identifiers. *///!< MultipleChoices
	HTTPSTATUSCODES_ADD_PREFIX(MovedPermanently)  = 301, /*!< Indicates that the target resource has been assigned a new permanent URI and any future references to this resource ought to use one of the enclosed URIs. */                                                                                                                                                      //!< MovedPermanently
	HTTPSTATUSCODES_ADD_PREFIX(Found)             = 302, /*!< Indicates that the target resource resides temporarily under a different URI. */                                                                                                                                                                                                                                   //!< Found
	HTTPSTATUSCODES_ADD_PREFIX(SeeOther)          = 303, /*!< Indicates that the server is redirecting the user agent to a different resource, as indicated by a URI in the Location header field, that is intended to provide an indirect response to the original request. */                                                                                                  //!< SeeOther
	HTTPSTATUSCODES_ADD_PREFIX(NotModified)       = 304, /*!< Indicates that a conditional GET request has been received and would have resulted in a 200 (OK) response if it were not for the fact that the condition has evaluated to false. */                                                                                                                                //!< NotModified
	HTTPSTATUSCODES_ADD_PREFIX(UseProxy)          = 305, /*!< \deprecated */                                                                                                                                                                                                                                                                                                     //!< UseProxy
	HTTPSTATUSCODES_ADD_PREFIX(TemporaryRedirect) = 307, /*!< Indicates that the target resource resides temporarily under a different URI and the user agent MUST NOT change the request method if it performs an automatic redirection to that URI. */                                                                                                                         //!< TemporaryRedirect
	HTTPSTATUSCODES_ADD_PREFIX(PermanentRedirect) = 308, /*!< The target resource has been assigned a new permanent URI and any future references to this resource outght to use one of the enclosed URIs. [...] This status code is similar to 301 Moved Permanently (Section 7.3.2 of rfc7231), except that it does not allow rewriting the request method from POST to GET. *///!< PermanentRedirect

	/*####### 4xx - Client Error #######*/
	/* Indicates that the client seems to have erred.
	 */
	HTTPSTATUSCODES_ADD_PREFIX(BadRequest)                  = 400, /*!< Indicates that the server cannot or will not process the request because the received syntax is invalid, nonsensical, or exceeds some limitation on what the server is willing to process. */                                                                                                            //!< BadRequest
	HTTPSTATUSCODES_ADD_PREFIX(Unauthorized)                = 401, /*!< Indicates that the request has not been applied because it lacks valid authentication credentials for the target resource. */                                                                                                                                                                            //!< Unauthorized
	HTTPSTATUSCODES_ADD_PREFIX(PaymentRequired)             = 402, /*!< *Reserved* */                                                                                                                                                                                                                                                                                            //!< PaymentRequired
	HTTPSTATUSCODES_ADD_PREFIX(Forbidden)                   = 403, /*!< Indicates that the server understood the request but refuses to authorize it. */                                                                                                                                                                                                                         //!< Forbidden
	HTTPSTATUSCODES_ADD_PREFIX(NotFound)                    = 404, /*!< Indicates that the origin server did not find a current representation for the target resource or is not willing to disclose that one exists. */                                                                                                                                                         //!< NotFound
	HTTPSTATUSCODES_ADD_PREFIX(MethodNotAllowed)            = 405, /*!< Indicates that the method specified in the request-line is known by the origin server but not supported by the target resource. */                                                                                                                                                                       //!< MethodNotAllowed
	HTTPSTATUSCODES_ADD_PREFIX(NotAcceptable)               = 406, /*!< Indicates that the target resource does not have a current representation that would be acceptable to the user agent, according to the proactive negotiation header fields received in the request, and the server is unwilling to supply a default representation. */                                   //!< NotAcceptable
	HTTPSTATUSCODES_ADD_PREFIX(ProxyAuthenticationRequired) = 407, /*!< Is similar to 401 (Unauthorized), but indicates that the client needs to authenticate itself in order to use a proxy. */                                                                                                                                                                                 //!< ProxyAuthenticationRequired
	HTTPSTATUSCODES_ADD_PREFIX(RequestTimeout)              = 408, /*!< Indicates that the server did not receive a complete request message within the time that it was prepared to wait. */                                                                                                                                                                                    //!< RequestTimeout
	HTTPSTATUSCODES_ADD_PREFIX(Conflict)                    = 409, /*!< Indicates that the request could not be completed due to a conflict with the current state of the resource. */                                                                                                                                                                                           //!< Conflict
	HTTPSTATUSCODES_ADD_PREFIX(Gone)                        = 410, /*!< Indicates that access to the target resource is no longer available at the origin server and that this condition is likely to be permanent. */                                                                                                                                                           //!< Gone
	HTTPSTATUSCODES_ADD_PREFIX(LengthRequired)              = 411, /*!< Indicates that the server refuses to accept the request without a defined Content-Length. */                                                                                                                                                                                                             //!< LengthRequired
	HTTPSTATUSCODES_ADD_PREFIX(PreconditionFailed)          = 412, /*!< Indicates that one or more preconditions given in the request header fields evaluated to false when tested on the server. */                                                                                                                                                                             //!< PreconditionFailed
	HTTPSTATUSCODES_ADD_PREFIX(PayloadTooLarge)             = 413, /*!< Indicates that the server is refusing to process a request because the request payload is larger than the server is willing or able to process. */                                                                                                                                                       //!< PayloadTooLarge
	HTTPSTATUSCODES_ADD_PREFIX(URITooLong)                  = 414, /*!< Indicates that the server is refusing to service the request because the request-target is longer than the server is willing to interpret. */                                                                                                                                                            //!< URITooLong
	HTTPSTATUSCODES_ADD_PREFIX(UnsupportedMediaType)        = 415, /*!< Indicates that the origin server is refusing to service the request because the payload is in a format not supported by the target resource for this method. */                                                                                                                                          //!< UnsupportedMediaType
	HTTPSTATUSCODES_ADD_PREFIX(RangeNotSatisfiable)         = 416, /*!< Indicates that none of the ranges in the request's Range header field overlap the current extent of the selected resource or that the set of ranges requested has been rejected due to invalid ranges or an excessive request of small or overlapping ranges. */                                         //!< RangeNotSatisfiable
	HTTPSTATUSCODES_ADD_PREFIX(ExpectationFailed)           = 417, /*!< Indicates that the expectation given in the request's Expect header field could not be met by at least one of the inbound servers. */                                                                                                                                                                    //!< ExpectationFailed
	HTTPSTATUSCODES_ADD_PREFIX(ImATeapot)                   = 418, /*!< Any attempt to brew coffee with a teapot should result in the error code 418 I'm a teapot. */                                                                                                                                                                                                            //!< ImATeapot
	HTTPSTATUSCODES_ADD_PREFIX(UnprocessableEntity)         = 422, /*!< Means the server understands the content type of the request entity (hence a 415(Unsupported Media Type) status code is inappropriate), and the syntax of the request entity is correct (thus a 400 (Bad Request) status code is inappropriate) but was unable to process the contained instructions. */ //!< UnprocessableEntity
	HTTPSTATUSCODES_ADD_PREFIX(Locked)                      = 423, /*!< Means the source or destination resource of a method is locked. */                                                                                                                                                                                                                                       //!< Locked
	HTTPSTATUSCODES_ADD_PREFIX(FailedDependency)            = 424, /*!< Means that the method could not be performed on the resource because the requested action depended on another action and that action failed. */                                                                                                                                                          //!< FailedDependency
	HTTPSTATUSCODES_ADD_PREFIX(UpgradeRequired)             = 426, /*!< Indicates that the server refuses to perform the request using the current protocol but might be willing to do so after the client upgrades to a different protocol. */                                                                                                                                  //!< UpgradeRequired
	HTTPSTATUSCODES_ADD_PREFIX(PreconditionRequired)        = 428, /*!< Indicates that the origin server requires the request to be conditional. */                                                                                                                                                                                                                              //!< PreconditionRequired
	HTTPSTATUSCODES_ADD_PREFIX(TooManyRequests)             = 429, /*!< Indicates that the user has sent too many requests in a given amount of time (\"rate limiting\"). */                                                                                                                                                                                                     //!< TooManyRequests
	HTTPSTATUSCODES_ADD_PREFIX(RequestHeaderFieldsTooLarge) = 431, /*!< Indicates that the server is unwilling to process the request because its header fields are too large. */                                                                                                                                                                                                //!< RequestHeaderFieldsTooLarge
	HTTPSTATUSCODES_ADD_PREFIX(UnavailableForLegalReasons)  = 451, /*!< This status code indicates that the server is denying access to the resource in response to a legal demand. */                                                                                                                                                                                           //!< UnavailableForLegalReasons

	/*####### 5xx - Server Error #######*/
	/* Indicates that the server is aware that it has erred
	 * or is incapable of performing the requested method.
	 */
	HTTPSTATUSCODES_ADD_PREFIX(InternalServerError)           = 500, /*!< Indicates that the server encountered an unexpected condition that prevented it from fulfilling the request. */                                                                                                                                                                                        //!< InternalServerError
	HTTPSTATUSCODES_ADD_PREFIX(NotImplemented)                = 501, /*!< Indicates that the server does not support the functionality required to fulfill the request. */                                                                                                                                                                                                       //!< NotImplemented
	HTTPSTATUSCODES_ADD_PREFIX(BadGateway)                    = 502, /*!< Indicates that the server, while acting as a gateway or proxy, received an invalid response from an inbound server it accessed while attempting to fulfill the request. */                                                                                                                             //!< BadGateway
	HTTPSTATUSCODES_ADD_PREFIX(ServiceUnavailable)            = 503, /*!< Indicates that the server is currently unable to handle the request due to a temporary overload or scheduled maintenance, which will likely be alleviated after some delay. */                                                                                                                         //!< ServiceUnavailable
	HTTPSTATUSCODES_ADD_PREFIX(GatewayTimeout)                = 504, /*!< Indicates that the server, while acting as a gateway or proxy, did not receive a timely response from an upstream server it needed to access in order to complete the request. */                                                                                                                      //!< GatewayTimeout
	HTTPSTATUSCODES_ADD_PREFIX(HTTPVersionNotSupported)       = 505, /*!< Indicates that the server does not support, or refuses to support, the protocol version that was used in the request message. */                                                                                                                                                                       //!< HTTPVersionNotSupported
	HTTPSTATUSCODES_ADD_PREFIX(VariantAlsoNegotiates)         = 506, /*!< Indicates that the server has an internal configuration error: the chosen variant resource is configured to engage in transparent content negotiation itself, and is therefore not a proper end point in the negotiation process. */                                                                   //!< VariantAlsoNegotiates
	HTTPSTATUSCODES_ADD_PREFIX(InsufficientStorage)           = 507, /*!< Means the method could not be performed on the resource because the server is unable to store the representation needed to successfully complete the request. */                                                                                                                                       //!< InsufficientStorage
	HTTPSTATUSCODES_ADD_PREFIX(NetworkAuthenticationRequired) = 511  /*!< Indicates that the client needs to authenticate to gain network access. */                                                                                                                                                                                                                             //!< NetworkAuthenticationRequired
};

inline bool HTTPSTATUSCODES_ADD_PREFIX(isInformational)(int code) { return (code >= 100 && code < 200); } /*!< \returns \c true if the given \p code is an informational code. */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isSuccessful)(int code)    { return (code >= 200 && code < 300); } /*!< \returns \c true if the given \p code is a successful code. */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isRedirection)(int code)   { return (code >= 300 && code < 400); } /*!< \returns \c true if the given \p code is a redirectional code. */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isClientError)(int code)   { return (code >= 400 && code < 500); } /*!< \returns \c true if the given \p code is a client error code. */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isServerError)(int code)   { return (code >= 500 && code < 600); } /*!< \returns \c true if the given \p code is a server error code. */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isError)(int code)         { return (code >= 400); }               /*!< \returns \c true if the given \p code is any type of error code. */

#ifdef __cplusplus /* C does not allow overloads */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isInformational)(Code code) { return isInformational(static_cast<int>(code)); } /*!< \overload */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isSuccessful)(Code code)    { return isSuccessful(static_cast<int>(code)); }    /*!< \overload */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isRedirection)(Code code)   { return isRedirection(static_cast<int>(code)); }   /*!< \overload */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isClientError)(Code code)   { return isClientError(static_cast<int>(code)); }   /*!< \overload */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isServerError)(Code code)   { return isServerError(static_cast<int>(code)); }   /*!< \overload */
inline bool HTTPSTATUSCODES_ADD_PREFIX(isError)(Code code)         { return isError(static_cast<int>(code)); }         /*!< \overload */
#endif /* __cplusplus */

/*! Returns the standard HTTP reason phrase for a HTTP status code.
 * \param code An HTTP status code.
 * \return The standard HTTP reason phrase for the given \p code or an HTTPSTATUSCODES_NULL_STRING
 * if no standard phrase for the given \p code is known.
 */
inline HTTPSTATUSCODES_STRING_TYPE HTTPSTATUSCODES_ADD_PREFIX(reasonPhrase)(int code)
{
	switch (code)
	{

	/*####### 1xx - Informational #######*/
	case 100: return "Continue";
	case 101: return "Switching Protocols";
	case 102: return "Processing";

	/*####### 2xx - Successful #######*/
	case 200: return "OK";
	case 201: return "Created";
	case 202: return "Accepted";
	case 203: return "Non-Authoritative Information";
	case 204: return "No Content";
	case 205: return "Reset Content";
	case 206: return "Partial Content";
	case 207: return "Multi-Status";
	case 226: return "IM Used";

	/*####### 3xx - Redirection #######*/
	case 300: return "Multiple Choices";
	case 301: return "Moved Permanently";
	case 302: return "Found";
	case 303: return "See Other";
	case 304: return "Not Modified";
	case 305: return "Use Proxy";
	case 307: return "Temporary Redirect";
	case 308: return "Permanent Redirect";

	/*####### 4xx - Client Error #######*/
	case 400: return "Bad Request";
	case 401: return "Unauthorized";
	case 402: return "Payment Required";
	case 403: return "Forbidden";
	case 404: return "Not Found";
	case 405: return "Method Not Allowed";
	case 406: return "Not Acceptable";
	case 407: return "Proxy Authentication Required";
	case 408: return "Request Timeout";
	case 409: return "Conflict";
	case 410: return "Gone";
	case 411: return "Length Required";
	case 412: return "Precondition Failed";
	case 413: return "Payload Too Large";
	case 414: return "URI Too Long";
	case 415: return "Unsupported Media Type";
	case 416: return "Range Not Satisfiable";
	case 417: return "Expectation Failed";
	case 418: return "I'm a teapot";
	case 422: return "Unprocessable Entity";
	case 423: return "Locked";
	case 424: return "Failed Dependency";
	case 426: return "Upgrade Required";
	case 428: return "Precondition Required";
	case 429: return "Too Many Requests";
	case 431: return "Request Header Fields Too Large";
	case 451: return "Unavailable For Legal Reasons";

	/*####### 5xx - Server Error #######*/
	case 500: return "Internal Server Error";
	case 501: return "Not Implemented";
	case 502: return "Bad Gateway";
	case 503: return "Service Unavailable";
	case 504: return "Gateway Time-out";
	case 505: return "HTTP Version Not Supported";
	case 506: return "Variant Also Negotiates";
	case 507: return "Insufficient Storage";
	case 511: return "Network Authentication Required";

	default: return HTTPSTATUSCODES_NULL_STRING;
	}
}

#ifdef __cplusplus /* C does not allow overloads */
/*! \overload
 *
 * \param code An HttpStatus::Code.
 * \return The standard HTTP reason phrase for the given \p code or an HTTPSTATUSCODES_NULL_STRING
 * if no standard phrase for the given \p code is known.
 */
inline HTTPSTATUSCODES_STRING_TYPE HTTPSTATUSCODES_ADD_PREFIX(reasonPhrase)(Code code)
{
	return HTTPSTATUSCODES_ADD_PREFIX(reasonPhrase)(static_cast<int>(code));
}
#endif /* __cplusplus */

#if defined(HTTPSTATUSCODES_USE_NAMESPACE)
} /* namespace HttpStatus */
#endif // defined(HTTPSTATUSCODES_USE_NAMESPACE)

#endif /* HTTPSTATUSCODES_CPP_H_ */
