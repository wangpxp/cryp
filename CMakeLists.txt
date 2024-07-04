cmake_minimum_required(VERSION 3.10)
project(crypto_service)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 cpp-httplib
add_subdirectory(cpp-httplib)

# 添加 nlohmann/json
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.5
)
FetchContent_MakeAvailable(json)

find_package(OpenSSL REQUIRED)

# 添加可执行文件
add_executable(crypto_server src/crypto_server.cpp)


# 链接库
target_link_libraries(crypto_server PRIVATE httplib::httplib nlohmann_json::nlohmann_json OpenSSL::SSL OpenSSL::Crypto)