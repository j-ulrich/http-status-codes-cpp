# HTTP Status Codes and Reason Phrases for C/C++ #

This repository provides the HTTP status codes and reason phrases in different variants for C/C++.

Simply take the variant that fits your needs and copy/use/modify it.

Data has been taken from [for-GET/know-your-http-well](https://github.com/for-GET/know-your-http-well).

## Variants ##

| Variant                                    | Scoping                | Status Codes                                                       | Reason Phrases |
|--------------------------------------------|------------------------|--------------------------------------------------------------------|----------------|
| [C](HttpStatusCodes_C.h)                   | Prefix `HttpStatus_`   | `enum HttpStatus_Code`                                             | `const char*`  |
| [C++](HttpStatusCodes_C++.h)               | Namespace `HttpStatus` | `enum Code`                                                        | `std::string`  |
| [C++11](HttpStatusCodes_C++11.h)           | Namespace `HttpStatus` | `enum class Code`                                                  | `std::string`  |
| [Qt](HttpStatusCodes_Qt.h)                 | Namespace `HttpStatus` | `enum Code`                                                        | `QString`      |
| [Qt 5.8 or later](HttpStatusCodes_Qt5.8.h) | Namespace `HttpStatus` | `enum Code`<br>Registered in meta type system using `Q_ENUM_NS()`  | `QString`      |


## License ##
[![CC0](https://licensebuttons.net/p/zero/1.0/80x15.png)](http://creativecommons.org/publicdomain/zero/1.0/)    
This project is licensed under [Creative Commons CC0](LICENSE).