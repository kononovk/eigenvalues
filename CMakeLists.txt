project(eigenvalues)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -fsanitize=address")

add_executable(eigenvalues main.cpp iohandler.cpp solution.cpp)