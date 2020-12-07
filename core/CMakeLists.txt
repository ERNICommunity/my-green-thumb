# Core

set(TARGET ${LIBRARY_CORE})
set(INCLUDE_DIRECTORIES ".")
set(SOURCES
	"AdptMoistureSensorDFRobot.cpp"
	"TaskTimer.cpp"
	"TaskPolling.cpp"
	"WaterRegulator.cpp"
)

add_library(${TARGET} OBJECT ${SOURCES})
target_link_libraries(${TARGET})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})
