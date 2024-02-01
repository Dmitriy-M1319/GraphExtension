cmake_minimum_required(VERSION 3.13.4)
project(cypher_lex)

find_package(FLEX REQUIRED)

flex_target(scanner
  cypher_lex.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

add_executable(${PROJECT_NAME} 
  cypher_lex.cc  
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
