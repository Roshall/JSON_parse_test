cmake_minimum_required(VERSION 3.11)
project(JSON_parse_test LANGUAGES CXX)

#set execute path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


# configure noho json
include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://gitee.com/rin-chan/nlohmann_json_cmake_fetchcontent.git
        GIT_TAG v3.7.3)
FetchContent_MakeAvailable(json)

add_executable(json_test
        "src/position_parse.cc"
        "src/solution.cc"
        # "src/thread_test.cc"
    )
target_compile_features(json_test PRIVATE cxx_std_11)
target_link_libraries(json_test PRIVATE nlohmann_json::nlohmann_json ws2_32)
