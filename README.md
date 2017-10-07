# HTTP Status Codes and Reason Phrases for C/C++ #

This repository provides the HTTP status codes and reason phrases in different variants for C/C++.

Simply take the variant that fits your needs and copy/use/modify it.

Data has been taken from [for-GET/know-your-http-well](https://github.com/for-GET/know-your-http-well).

## Variants ##

| Variant         | Scoping                | Status Codes                                                       | Reason Phrases |
|-----------------|------------------------|--------------------------------------------------------------------|----------------|
| C               | Prefix `HttpStatus_`   | `enum HttpStatus_Code`                                             | `const char*`  |
| C++             | Namespace `HttpStatus` | `enum Code`                                                        | `std::string`  |
| C++11           | Namespace `HttpStatus` | `enum class Code`                                                  | `std::string`  |
| Qt              | Namespace `HttpStatus` | `enum Code`                                                        | `QString`      |
| Qt 5.8 or later | Namespace `HttpStatus` | `enum Code`<br>Registered in meta type system using `Q_ENUM_NS()`  | `QString`      |


## License ##
Copyright © 2017 Jochen Ulrich

This project is licensed under the [Unlicense](LICENSE).