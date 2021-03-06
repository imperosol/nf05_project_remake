cmake_minimum_required(VERSION 3.17)
project(nf05_projet_remake C)

set(CMAKE_C_STANDARD 99)

add_executable(nf05_projet_remake main.c struct.h patient_list_creation.c patient_list_creation.h standard_functions.c standard_functions.h exam.c exam.h patient_list_modification.c patient_list_modification.h)