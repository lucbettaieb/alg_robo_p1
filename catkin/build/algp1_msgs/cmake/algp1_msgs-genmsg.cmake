# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "algp1_msgs: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ialgp1_msgs:/home/luc/ros_workspace/alg_robo_p1/catkin/src/algp1_msgs/msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/hydro/share/geometry_msgs/cmake/../msg;-Inav_msgs:/opt/ros/hydro/share/nav_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/hydro/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(algp1_msgs_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(algp1_msgs
  "/home/luc/ros_workspace/alg_robo_p1/catkin/src/algp1_msgs/msg/Pose2DWithCovariance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/algp1_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(algp1_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/algp1_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(algp1_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(algp1_msgs_generate_messages algp1_msgs_generate_messages_cpp)

# target for backward compatibility
add_custom_target(algp1_msgs_gencpp)
add_dependencies(algp1_msgs_gencpp algp1_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS algp1_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(algp1_msgs
  "/home/luc/ros_workspace/alg_robo_p1/catkin/src/algp1_msgs/msg/Pose2DWithCovariance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/algp1_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(algp1_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/algp1_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(algp1_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(algp1_msgs_generate_messages algp1_msgs_generate_messages_lisp)

# target for backward compatibility
add_custom_target(algp1_msgs_genlisp)
add_dependencies(algp1_msgs_genlisp algp1_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS algp1_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(algp1_msgs
  "/home/luc/ros_workspace/alg_robo_p1/catkin/src/algp1_msgs/msg/Pose2DWithCovariance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/algp1_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(algp1_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/algp1_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(algp1_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(algp1_msgs_generate_messages algp1_msgs_generate_messages_py)

# target for backward compatibility
add_custom_target(algp1_msgs_genpy)
add_dependencies(algp1_msgs_genpy algp1_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS algp1_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/algp1_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/algp1_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(algp1_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(algp1_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(algp1_msgs_generate_messages_cpp nav_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/algp1_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/algp1_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(algp1_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(algp1_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(algp1_msgs_generate_messages_lisp nav_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/algp1_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/algp1_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/algp1_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(algp1_msgs_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(algp1_msgs_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(algp1_msgs_generate_messages_py nav_msgs_generate_messages_py)
