/*! \file
 *
 * HTTP Status Codes - Arduino Variant
 *
 * https://github.com/j-ulrich/http-status-codes-cpp
 *
 * \version 1.3.0
 * \author Jochen Ulrich <jochenulrich@t-online.de>
 * \author Arthur Moore <arthur@heatrsd.com>
 * \copyright Licensed under Creative Commons CC0 (http://creativecommons.org/publicdomain/zero/1.0/)
 */

#include "HttpStatusCodes_Arduino.h"

String HttpStatus::reasonPhrase(int code)
{
    switch (code)
    {
        //####### 1xx - Informational #######
        case 100: return F("Continue");
        case 101: return F("Switching Protocols");
        case 102: return F("Processing");
        case 103: return F("Early Hints");

        //####### 2xx - Successful #######
        case 200: return F("OK");
        case 201: return F("Created");
        case 202: return F("Accepted");
        case 203: return F("Non-Authoritative Information");
        case 204: return F("No Content");
        case 205: return F("Reset Content");
        case 206: return F("Partial Content");
        case 207: return F("Multi-Status");
        case 208: return F("Already Reported");
        case 226: return F("IM Used");

            //####### 3xx - Redirection #######
        case 300: return F("Multiple Choices");
        case 301: return F("Moved Permanently");
        case 302: return F("Found");
        case 303: return F("See Other");
        case 304: return F("Not Modified");
        case 305: return F("Use Proxy");
        case 307: return F("Temporary Redirect");
        case 308: return F("Permanent Redirect");

        //####### 4xx - Client Error #######
        case 400: return F("Bad Request");
        case 401: return F("Unauthorized");
        case 402: return F("Payment Required");
        case 403: return F("Forbidden");
        case 404: return F("Not Found");
        case 405: return F("Method Not Allowed");
        case 406: return F("Not Acceptable");
        case 407: return F("Proxy Authentication Required");
        case 408: return F("Request Timeout");
        case 409: return F("Conflict");
        case 410: return F("Gone");
        case 411: return F("Length Required");
        case 412: return F("Precondition Failed");
        case 413: return F("Payload Too Large");
        case 414: return F("URI Too Long");
        case 415: return F("Unsupported Media Type");
        case 416: return F("Range Not Satisfiable");
        case 417: return F("Expectation Failed");
        case 418: return F("I'm a teapot");
        case 422: return F("Unprocessable Entity");
        case 423: return F("Locked");
        case 424: return F("Failed Dependency");
        case 426: return F("Upgrade Required");
        case 428: return F("Precondition Required");
        case 429: return F("Too Many Requests");
        case 431: return F("Request Header Fields Too Large");
        case 451: return F("Unavailable For Legal Reasons");

        //####### 5xx - Server Error #######
        case 500: return F("Internal Server Error");
        case 501: return F("Not Implemented");
        case 502: return F("Bad Gateway");
        case 503: return F("Service Unavailable");
        case 504: return F("Gateway Time-out");
        case 505: return F("HTTP Version Not Supported");
        case 506: return F("Variant Also Negotiates");
        case 507: return F("Insufficient Storage");
        case 508: return F("Loop Detected");
        case 510: return F("Not Extended");
        case 511: return F("Network Authentication Required");

        default: return String();
    }
}
