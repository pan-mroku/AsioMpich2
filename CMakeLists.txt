CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(AsioMpich2)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -O3")

FIND_PACKAGE(Boost REQUIRED COMPONENTS system serialization)

SET(LIBS boost_serialization boost_system)

SET(HEADERS payload.hpp)
SET(SOURCES payload.cpp)
SET(H_AND_S ${HEADERS} ${SOURCES})

ADD_EXECUTABLE(${PROJECT_NAME}_client
  ${H_AND_S}
  client.cpp
        )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_client ${LIBS})

ADD_EXECUTABLE(${PROJECT_NAME}_send
  ${H_AND_S}
  send.cpp
        )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_send ${LIBS})

ADD_EXECUTABLE(${PROJECT_NAME}_test EXCLUDE_FROM_ALL
  payload.hpp
  payload.cpp
  test.cpp
  )
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_test ${LIBS} )