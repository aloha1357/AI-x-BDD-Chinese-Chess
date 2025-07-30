#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    std::cout << "Running Chinese Chess BDD Tests..." << std::endl;
    
    int result = RUN_ALL_TESTS();
    
    if (result != 0) {
        std::cout << "Tests failed - this is expected for BDD red-green-refactor cycle" << std::endl;
    }
    
    return result;
}
