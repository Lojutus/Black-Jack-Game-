#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../Console.h"
//CENTRO DE TESTEO UNITARIO
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
