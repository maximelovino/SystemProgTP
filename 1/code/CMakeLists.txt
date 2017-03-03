cmake_minimum_required(VERSION 3.6)
project(code)

set(CMAKE_C_STANDARD 99)


add_executable(ex1 ex1.c)
add_executable(ex2 ex2.c)
add_executable(ex3_a ex3_a.c)
add_executable(ex3_b ex3_b.c)
add_executable(ex4_a ex4_a.c libSocket.c)
add_executable(ex4_b ex4_b.c libSocket.c)
add_executable(ex5_client ex5_client.c libSocket.c)
add_executable(ex5_server ex5_server.c libSocket.c)