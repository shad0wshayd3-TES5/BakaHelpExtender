set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${ROOT_DIR}/extern/BethesdaCMakeModules/Modules/Papyrus.cmake)

file(GLOB Papyrus_INPUT
	LIST_DIRECTORIES false
	CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.psc
)

add_papyrus(
	"Papyrus"
	GAME ${SkyrimPath}
	IMPORTS ${SkyrimPath}/Data/Source/Scripts
	SOURCES ${Papyrus_INPUT}
)

source_group(
	"Scripts"
	FILES
		${Papyrus_INPUT}
)

if (COPY_BUILD)
	if (DEFINED SkyrimPath)
		foreach(FILE IN LISTS Papyrus_INPUT)
			add_custom_command(
				TARGET "Papyrus"
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy ${FILE} ${SkyrimPath}/Data/Source/Scripts/
			)
		endforeach()

		foreach(FILE IN LISTS Papyrus_OUTPUT)
			add_custom_command(
				TARGET "Papyrus"
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy ${FILE} ${SkyrimPath}/Data/Scripts/
			)
		endforeach()
	else ()
		message(
			WARNING
			"Variable ${SkyrimPath} is not defined. Skipping post-build copy command."
		)
	endif()
endif()