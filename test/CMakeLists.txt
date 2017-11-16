# 制定cmake支持最低版本
cmake_minimum_required(VERSION 2.8)
# 项目名称
PROJECT(demo)

SET(DEPEND_PATH /opt)

# 向C/C++编译器添加-D定义，比如：
ADD_DEFINITIONS(-DENABLE_DEBUG-DABC)
ADD_DEFINITIONS(-g)
ADD_DEFINITIONS(-std=c++11)

# 链接库·
LINK_DIRECTORIES(
        ${DEPEND_PATH}/idempotent/lib
        ${DEPEND_PATH}/hiredis/lib
        ${DEPEND_PATH}/jsoncpp-0.10.6/lib
        ${DEPEND_PATH}/MyRedis/lib
        /usr/lib64)

# 依赖头文件
INCLUDE_DIRECTORIES(
        ${DEPEND_PATH}/idempotent/include
        ${DEPEND_PATH}/hiredis/include
        ${DEPEND_PATH}/jsoncpp-0.10.6/include
        ${DEPEND_PATH}/MyRedis/include
        )

# 以来源文件
AUX_SOURCE_DIRECTORY(./main.cpp DIR_SRCS)

#添加目标可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ./main.cpp)

# 添加可执行文件的依赖库
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libidempotent.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libMyRedis.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libhiredis.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libjsoncpp.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libpthread.so)
