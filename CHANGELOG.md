# Changelog #

The changelog of the http-status-codes library.

This project adheres to [Semantic Versioning](http://semver.org/).

This changelog follows the [Keep a Changelog](http://keepachangelog.com) format.


---

## [Unreleased]

### Added ###
- [#28] Added code `Invalid` (-1).
- [#28]{Qt C++11} Qt C++11 variant which uses `enum class` for the codes.

### Changed ###
- {Qt} `networkErrorToStatusCode()` now returns a `Code` instead of `int`.

### Removed ###
- Testing with Visual Studio 2013 because of outdated CMake.


---


## [1.5.0] - 2022-01-03 ##

### Changed ###
- [#21] Code `NotExtended` (510) is marked as obsoleted.


---


## [1.4.0] - 2021-11-05 ##
Updates and adds missing status codes from the IANA registry.

### Added ###
- [#17] Added codes `MisdirectedRequest` (421), `TooEarly` (425), `ContentTooLarge` (413) and `UnprocessableContent` (422).
  The existing codes `PayloadTooLarge` (413) and `UnprocessableEntity` (422) are kept for backward compatibility.

### Changed ###
- [#12] Updated GTest to 1.8.1 to fix deprecation warnings with recent compilers.
- [#17] Updated the reason phrases for `PayloadTooLarge` (413), `UnprocessableEntity` (422) and `GatewayTimeout` (504).

### Fixed ###
- {C++11} Added missing `Code::xxx_max` enumerator.


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
- Status codes `EarlyHints` (103), `AlreadyReported` (208), `LoopDetected` (508) and `NotExtended` (510).


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


[1.5.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.5.0
[1.4.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.4.0
[1.3.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.3.0
[1.2.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.2.0
[1.1.1]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.1.1
[1.1.0]: https://github.com/j-ulrich/http-status-codes-cpp/releases/tag/1.1.0
