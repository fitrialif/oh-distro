################################################################
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(rgbd_primitives)


set(PCL_LIBRARIES  pcl_io-1.7)

add_library(rgbd_primitives SHARED rgbd_primitives.cpp)

pods_use_pkg_config_packages(rgbd_primitives ${PCL_LIBRARIES} eigen3)

# set the library API version.  Increment this every time the public API changes.
set_target_properties(rgbd_primitives PROPERTIES SOVERSION 1)
pods_install_libraries(rgbd_primitives)
pods_install_headers(rgbd_primitives.hpp DESTINATION rgbd_simulation)

#target_link_libraries(rgbd_primitives
#    z)
pods_install_pkg_config_file(rgbd_primitives
    LIBS -lrgbd_primitives
    REQUIRES eigen3 pcl_io-1.7
    VERSION 0.0.1)

    
    
    
################ TEST PROGRAM ###############
add_executable(test-rgbd-primatives test_rgbd_primatives.cpp)
target_link_libraries(test-rgbd-primatives  boost_system  boost_random)
pods_use_pkg_config_packages(test-rgbd-primatives lcm rgbd_primitives pronto_vis
    pronto_math lcmtypes_visualization
    )
pods_install_executables(test-rgbd-primatives)
