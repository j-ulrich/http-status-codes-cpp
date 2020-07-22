
if ( WIN32 AND ( MSVC_TOOLSET_VERSION LESS 140 ) )
	# Visual Studio < 2015
	hunter_config( GTest VERSION 1.8.0-hunter-p11 )
else()
	hunter_config( GTest VERSION 1.8.1 ) # Actually, this results in GTest version 1.9.0
endif()
