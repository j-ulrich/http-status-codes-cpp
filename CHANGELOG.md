# Changelog # {#changelog}

\brief The changelog of the http-status-codes library.

This project adheres to [Semantic Versioning](http://semver.org/).

This changelog follows the [Keep a Changelog](http://keepachangelog.com) format.


---


## [1.3.0] - 2019-02-21 ##

### Added ###
- Support for custom (error) codes by ensuring the enums can hold values up to 1023.


---


## [1.2.0] - 2019-01-06 ##

### Added ###
- [#5]{C++11} `toInt()` conversion function.


---


## [1.1.1] - 2018-11-14 ##

### Fixed ###
- {Qt} Some QNetworkReply::NetworkError codes were not available in Qt before 5.3.


---

## [1.1.0] - 2018-10-06 ##
Adds missing status codes from the IANA registry.

### Added ###
- Status codes 103 Early Hints, 208 Already Reported, 508 Loop Detected and 510 Not Extended


### Fixed ###
- {C} Removed redundant "HttpStatus_XXX" documentation comments.


---


## 1.0.0 - 2017-11-02 ##
Initial (actually unversioned) release.

### Added ###
- C, C++, C++11 and Qt variants.
- Status codes
- Category/class tests (`isXXX()` functions)
- Reason phrases
- {Qt} `QNetworkReply::NetworkError` mapping


---


[1.2.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.2.0
[1.1.1]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.1.1
[1.1.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.1.0
