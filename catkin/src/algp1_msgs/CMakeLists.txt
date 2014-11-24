cmake_minimum_required(VERSION 2.8.3)
project(algp1_msgs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nav_msgs
  geometry_msgs
)

add_message_files(
	FILES
	Pose2DWithCovariance.msg
	PoseScan.msg
	PoseScanVector.msg
)

generate_messages(
	DEPENDENCIES
	std_msgs
	geometry_msgs
	nav_msgs
)

catkin_package(
   DEPENDS message_runtime
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)






## Declare a cpp executable
# add_executable(vel_model src/vel_model.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(filters_node filters_generate_messages_cpp)

## Specify libraries to link a library or executable target against
#target_link_libraries(vel_model
#   ${catkin_LIBRARIES}
#)
