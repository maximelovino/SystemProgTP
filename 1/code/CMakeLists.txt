cmake_minimum_required(VERSION 3.6)
project(code)

set(CMAKE_C_STANDARD 99)


add_executable(ex1 1/ex1.c)
add_executable(ex2 1/ex2.c)
add_executable(ex3_a 1/ex3_a.c)
add_executable(ex3_b 1/ex3_b.c)
add_executable(ex4_a 1/ex4_a.c libSocket.c)
add_executable(ex4_b 1/ex4_b.c libSocket.c)
add_executable(ex5_client 1/ex5_client.c libSocket.c)
add_executable(ex5_server 1/ex5_server.c libSocket.c)
add_executable(ex7_server 1/ex7_server.c libSocket.c 1/dataStructEx7.h)
add_executable(ex7_client 1/ex7_client.c libSocket.c 1/dataStructEx7.h)
add_executable(ex8_server 1/ex8_server.c libSocket.c)
add_executable(ex8_client 1/ex8_client.c libSocket.c)

add_executable(2_ex1 2/ex1.c)
add_executable(2_ex2 2/ex2.c)