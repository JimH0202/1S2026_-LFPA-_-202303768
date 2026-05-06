cmake_minimum_required(VERSION 3.16)
project(TaskScriptAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/Token.cpp
    src/LexicalAnalyzer.cpp
    src/SyntaxAnalyzer.cpp
    src/ErrorManager.cpp
    src/ReportGenerator.cpp
    src/BoardModel.cpp
)

set(HEADERS
    src/MainWindow.h
    src/Token.h
    src/TokenType.h
    src/LexicalAnalyzer.h
    src/SyntaxAnalyzer.h
    src/ErrorManager.h
    src/ReportGenerator.h
    src/BoardModel.h
    src/TreeNode.h
)

qt_add_executable(TaskScriptAnalyzer
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(TaskScriptAnalyzer PRIVATE Qt6::Widgets)

add_executable(ConsoleAnalyzer
    src/console_main.cpp
    src/Token.cpp
    src/LexicalAnalyzer.cpp
    src/SyntaxAnalyzer.cpp
    src/ErrorManager.cpp
    src/ReportGenerator.cpp
    src/BoardModel.cpp
    src/TreeNode.h
)

add_executable(TestAnalyzer
    src/test_main.cpp
    src/Token.cpp
    src/LexicalAnalyzer.cpp
    src/SyntaxAnalyzer.cpp
    src/ErrorManager.cpp
    src/ReportGenerator.cpp
    src/BoardModel.cpp
    src/TreeNode.h
)
