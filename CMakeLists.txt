# 制定cmake支持最低版本
cmake_minimum_required(VERSION 2.8)
# 项目名称
PROJECT(idempotent)

SET(DEPEND_PATH /opt)

# 向C/C++编译器添加-D定义，比如：
ADD_DEFINITIONS(-DENABLE_DEBUG-DABC)
ADD_DEFINITIONS(-g)
ADD_DEFINITIONS(-std=c++11)

# 链接库·
LINK_DIRECTORIES(
        ${DEPEND_PATH}/hiredis/lib
        ${DEPEND_PATH}/MyRedis/lib
        ${DEPEND_PATH}/jsoncpp-0.10.6/lib
        /usr/lib64)

# 依赖头文件
INCLUDE_DIRECTORIES(
        ${DEPEND_PATH}/hiredis/include
        ${DEPEND_PATH}/MyRedis/include
        ${DEPEND_PATH}/jsoncpp-0.10.6/include
        )

AUX_SOURCE_DIRECTORY(./src DIR_SRCS)

#添加目标库
# ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})
ADD_LIBRARY(${PROJECT_NAME} ${DIR_SRCS})

# 安装
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${DEPEND_PATH}/${PROJECT_NAME}/bin
        LIBRARY DESTINATION ${DEPEND_PATH}/${PROJECT_NAME}/lib
        ARCHIVE DESTINATION ${DEPEND_PATH}/${PROJECT_NAME}/lib)

MESSAGE(${PROJECT_SOURCE_DIR})

INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/src/
        DESTINATION ${DEPEND_PATH}/${PROJECT_NAME}/include/${PROJECT_NAME}
        PATTERN ".h")


#INSTALL(FILES ${PROJECT_SOURCE_DIR}/src/common.h ${DESTINATION} include)

# 添加可执行文件的依赖库
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} idempotent)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} /usr/local/xredis/lib/libxredis.so)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} /usr/lib64/libpthread.so)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} /usr/lib64/libhiredis.so)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} libxredis.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libpthread.so)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libhiredis.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libjsoncpp.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} libMyRedis.a)
