project(MapOfObjects)

set(HEADER_FILES
        map.h
        mapObject.h
        Empty.h
        Food.h
        robot.h
        Wall.h
)

set(SOURCE_FILES
        map.cpp
        mapObject.cpp
        Empty.cpp
        Food.cpp
        robot.cpp
        Wall.cpp
)

add_library(MapOfObjects_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})