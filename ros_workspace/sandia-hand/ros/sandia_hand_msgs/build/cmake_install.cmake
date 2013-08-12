# Install script for directory: /home/sisir/sandia-hand/ros/sandia_hand_msgs

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs/manifest.xml")
FILE(INSTALL DESTINATION "/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs" TYPE FILE FILES "/home/sisir/sandia-hand/ros/sandia_hand_msgs/manifest.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs/srv;/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs/srv_gen;/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs/msg;/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs/msg_gen;/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs/src")
FILE(INSTALL DESTINATION "/usr/local/share/sandia-hand-bogus/ros/sandia_hand_msgs" TYPE DIRECTORY FILES
    "/home/sisir/sandia-hand/ros/sandia_hand_msgs/srv"
    "/home/sisir/sandia-hand/ros/sandia_hand_msgs/srv_gen"
    "/home/sisir/sandia-hand/ros/sandia_hand_msgs/msg"
    "/home/sisir/sandia-hand/ros/sandia_hand_msgs/msg_gen"
    "/home/sisir/sandia-hand/ros/sandia_hand_msgs/src"
    REGEX "/\\.[^/]*$" EXCLUDE)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/sisir/sandia-hand/ros/sandia_hand_msgs/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/sisir/sandia-hand/ros/sandia_hand_msgs/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
