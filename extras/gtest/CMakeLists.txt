add_library(rapidcheck_gtest INTERFACE)
target_link_libraries(rapidcheck_gtest INTERFACE rapidcheck)
target_include_directories(rapidcheck_gtest INTERFACE include)
