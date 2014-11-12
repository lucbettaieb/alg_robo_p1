cmake_minimum_required(VERSION 2.8.3)
project(filters)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nav_msgs
  geometry_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES filters
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)


## Declare a cpp executable
add_executable(vel_model src/vel_model.cpp)
add_executable(sense_model src/sense_model.cpp)
add_executable(scan_queue src/scan_queue.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(filters_node filters_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(vel_model
   ${catkin_LIBRARIES}
)

target_link_libraries(sense_model
   ${catkin_LIBRARIES}
)

target_link_libraries(scan_queue
   ${catkin_LIBRARIES}
)
