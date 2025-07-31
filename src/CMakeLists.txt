
cmake_minimum_required(VERSION 3.12)

project(Aid_Management LANGUAGES CXX)

file(GLOB
    src_files
    "*.cpp"
    "*.h"
)


message("Final source file list : ${src_files}")


add_executable (Aid_Management 
	${src_files}
)


