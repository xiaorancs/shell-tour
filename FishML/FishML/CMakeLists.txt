include_directories ("${PROJECT_SOURCE_DIR}/Common")
add_subdirectory (Common) 
 
# 添加可执行文件
target_link_libraries (Tutorial Common)
