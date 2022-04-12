###################################################
#                                                 #
#                                                 #
#   Vstdlib CMake build file                      #
#                                                 #
#                                                 #
###################################################

set( PROJECT_NAME vstdlib )

add_sources(
	cvar.cpp
	KeyValuesSystem.cpp
	random.cpp
	commandline.cpp
	stringnormalize.cpp
	vstdlib_strtools.cpp
	${SRC_DIR}/public/interface.cpp
	${SRC_DIR}/public/interface.h
	${SRC_DIR}/public/vstdlib/cvar.h
	${SRC_DIR}/public/vstdlib/IKeyValuesSystem.h
	${SRC_DIR}/public/tier1/mempool.h
	${SRC_DIR}/public/vstdlib/random.h
	${SRC_DIR}/public/vstdlib/vstdlib.h
)

add_subdirectory( ${SRC_DIR}/public/vstdlib public/tier1 )

preprocess_sources()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa " )

add_library( ${PROJECT_NAME} SHARED ${PREP_SRCS} )

target_include_directories( ${PROJECT_NAME} PRIVATE
	${SRC_DIR}/public/tier1
	${SRC_DIR}/public/vstdlib
	${SRC_DIR}/common
	${SRC_DIR}/public
	${SRC_DIR}
)

target_compile_definitions( ${PROJECT_NAME} PRIVATE
	${SHARED_DEFS}
	VSTDLIB_DLL_EXPORT
)

target_link_libraries( ${PROJECT_NAME} 
	tier1
	tier0
)

#CMake places libraries in /Debug or /Release on Windows, so explicitly set the paths for both.
#On Linux, it uses LIBRARY_OUTPUT_DIRECTORY
set_target_properties( ${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${ENGINE_BASE_PATH}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${ENGINE_BASE_PATH}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${ENGINE_BASE_PATH}"
)

set( PROJECT_LINK_FLAGS )

if( NOT MSVC AND NOT APPLE )
	#Generate a map file that provides information about the linking stage.
	set( PROJECT_LINK_FLAGS
		${PROJECT_LINK_FLAGS} "-Wl,-Map,${PROJECT_NAME}_map.txt "
	)
endif()

set_target_properties( ${PROJECT_NAME} PROPERTIES
	COMPILE_FLAGS "${LINUX_32BIT_FLAG}"
	LINK_FLAGS "${SHARED_ENGINE_LINKER_FLAGS} ${PROJECT_LINK_FLAGS} ${LINUX_32BIT_FLAG}"
)

#No lib prefix
set_target_properties( ${PROJECT_NAME} PROPERTIES PREFIX "" )

#Create filters
create_source_groups( "${CMAKE_SOURCE_DIR}" )

clear_sources()
