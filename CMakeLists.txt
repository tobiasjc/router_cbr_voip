cmake_minimum_required(VERSION 3.1)
project(router_cbr_voip C)

set(CMAKE_C_STANDARD 11)

include_directories(./include)

add_executable(router_cbr_voip main.c src/IO_manager.c include/IO_manager.h src/queue.c include/queue.h src/voip_tunnel.c include/voip_tunnel.h include/validation.h src/validation.c src/generators.c include/generators.h src/helpers.c include/helpers.h src/execution.c include/execution.h include/types.h)
target_link_libraries(router_cbr_voip m)
