aux_source_directory(. 
	SRC_LST)

include_directories(../header)


add_library(Lexer
    ${SRC_LST}
	${HEADER_LST})

target_include_directories(Lexer
    PUBLIC ${HEADER_LST})