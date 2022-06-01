if(ANDROID AND NOT TARGET oboe::oboe)
	#set(OBOE_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/libs/android.${CMAKE_ANDROID_ARCH_ABI}/liboboe.so")
	#set(OBOE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
	add_library(oboe::oboe SHARED IMPORTED)
	set_target_properties(oboe::oboe PROPERTIES
		IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/libs/android.${CMAKE_ANDROID_ARCH_ABI}/liboboe.so"
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
	)
	#mark_as_advanced(OBOE_LIBRARY OBOE_INCLUDE_DIR)
endif()

#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Oboe REQUIRED_VARS OBOE_LIBRARY OBOE_INCLUDE_DIR)
