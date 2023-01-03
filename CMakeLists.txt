cmake_minimum_required(VERSION 3.10) 

project(FunctionsCaller) 

aux_source_directory(./Calculater DIR_SRCS)

message(STATUS ${DIR_SRCS})

# add the executable 
add_executable(${PROJECT_NAME} ${DIR_SRCS})