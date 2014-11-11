cmake_minimum_required(VERSION 2.8.3)
project(motion)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  nav_msgs
  std_msgs
  
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES motion
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp executable
 add_executable(simple_movement src/simple_movement.cpp)
 add_executable(laser_sweep src/laser_sweep.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(simple_movement
   ${catkin_LIBRARIES}
)


target_link_libraries(laser_sweep
   ${catkin_LIBRARIES}
)



