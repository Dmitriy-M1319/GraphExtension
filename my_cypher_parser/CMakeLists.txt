cmake_minimum_required(VERSION 3.13.4)
project(cypher_parser)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

flex_target(scanner
    cypher_lex.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

bison_target(parser
    cypher.y 
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/astgrammar.tab.hh --debug --graph"
)

add_flex_bison_dependency(scanner parser)

add_executable(${PROJECT_NAME} 
  cypher.cc  
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
