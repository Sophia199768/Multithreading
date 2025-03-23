cmake_minimum_required(VERSION 3.30)
project(Labwork)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Labwork client/main.cpp ship/Ship.cpp player/Player.cpp board/Board.cpp board/Board.h player/Player.h game/Game.cpp game/Game.h board/BoardFabric.cpp board/BoardFabric.h health/HealthCalculator.cpp health/HealthCalculator.h playLogic/PlayLogic.cpp playLogic/PlayLogic.h console/Console.cpp console/Console.h ship/Ship.h playLogic/FillingTheBoard.cpp playLogic/FillingTheBoard.h
        game/GameFactory.cpp
        game/GameFactory.h
        server/server.cpp
        server/server.h

)
target_link_libraries(Labwork ${Boost_LIBRARIES})


add_executable(Server server/main.cpp ship/Ship.cpp player/Player.cpp board/Board.cpp board/Board.h player/Player.h game/Game.cpp game/Game.h board/BoardFabric.cpp board/BoardFabric.h health/HealthCalculator.cpp health/HealthCalculator.h playLogic/PlayLogic.cpp playLogic/PlayLogic.h console/Console.cpp console/Console.h ship/Ship.h playLogic/FillingTheBoard.cpp playLogic/FillingTheBoard.h
        game/GameFactory.cpp
        game/GameFactory.h
        server/server.cpp
        server/server.h
)
target_link_libraries(Server ${Boost_LIBRARIES})


add_executable(Client client/main.cpp)

target_link_libraries(Client ${Boost_LIBRARIES})





add_executable(LabworkTests
        tests/main_test.cpp
        tests/play_logic_test.cpp
        tests/test_player.cpp
        tests/test_board.cpp
        ship/Ship.cpp
        player/Player.cpp
        board/Board.cpp
        board/BoardFabric.cpp
        health/HealthCalculator.cpp
        playLogic/PlayLogic.cpp
        playLogic/FillingTheBoard.cpp
        console/Console.cpp
        game/Game.cpp
        game/GameFactory.cpp
        server/server.cpp
        server/server.h
        tests/health_test.cpp
        tests/server_test.cpp
)

target_link_libraries(LabworkTests ${Boost_LIBRARIES} GTest::GTest GTest::Main)