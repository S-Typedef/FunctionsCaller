cmake_minimum_required(VERSION 3.16)

project(SubFuncDll)

add_definitions(-DSUBDLL)

set(SRC_LST
	"../Calculater/token.h"
	"sub.cc"
	"sub.h"
)

add_library(${PROJECT_NAME} SHARED ${SRC_LST})