cmake_minimum_required(VERSION 2.8.12)

project(VTEDlite_hts_engine)

set (PROJECT_LINK_LIBS1 libbt.a)
link_directories(btree/bt-5.0.0/lib/)

set (PROJECT_LINK_LIBS2 libHTSEngine.a)
link_directories(hts_engine_API-1.10)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(VTEDlite_hts_engine ${SOURCES})
target_link_libraries(VTEDlite_hts_engine ${PROJECT_LINK_LIBS1} ${PROJECT_LINK_LIBS2} -lm)