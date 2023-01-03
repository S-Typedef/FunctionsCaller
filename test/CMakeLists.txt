include_directories(../header)

add_executable(LexerTest
	lexer_test.cc)

target_link_libraries(LexerTest
	Lexer)

add_test(NAME lexerTest COMMAND LexerTest)