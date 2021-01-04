# Core

set(TARGET ${LIBRARY_CORE})
set(INCLUDE_DIRECTORIES ".")
set(SOURCES
	"AdptMoistureSensorDFRobot.cpp"
	"TaskTimer.cpp"
	"TaskPolling.cpp"
    "WaterRegulator.cpp"
    "AdptWaterValveBistable.cpp"
    "Service.cpp"
)

add_library(${TARGET} OBJECT ${SOURCES})
target_link_libraries(${TARGET})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})

# Add documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(
        ${CMAKE_CURRENT_LIST_DIR}/../doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(
        "${PROJECT}_Doc"
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../doc)
endif()