#include "TestFramework.h"

std::vector<std::function<void()>> TestFramework::tests;
std::vector<std::string> TestFramework::testNames;
int TestFramework::totalTests = 0;
int TestFramework::passedTests = 0;
int TestFramework::failedTests = 0;

void TestFramework::registerTest(const std::string& name, std::function<void()> test) {
    testNames.push_back(name);
    tests.push_back(test);
}

int TestFramework::runAllTests() {
    totalTests = tests.size();
    passedTests = 0;
    failedTests = 0;
    
    std::cout << "Running " << totalTests << " tests..." << std::endl;
    std::cout << "======================================" << std::endl;
    
    for (size_t i = 0; i < tests.size(); ++i) {
        std::cout << "[" << (i + 1) << "/" << totalTests << "] " << testNames[i] << " ... ";
        
        try {
            tests[i]();
            std::cout << "PASSED" << std::endl;
            passedTests++;
        } catch (const std::exception& e) {
            std::cout << "FAILED - " << e.what() << std::endl;
            failedTests++;
        } catch (...) {
            std::cout << "FAILED - Unknown exception" << std::endl;
            failedTests++;
        }
    }
    
    std::cout << "======================================" << std::endl;
    std::cout << "Results: " << passedTests << " passed, " << failedTests << " failed" << std::endl;
    
    return failedTests > 0 ? 1 : 0;
}

void TestFramework::assertEqual(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void TestFramework::assertTrue(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void TestFramework::assertFalse(bool condition, const std::string& message) {
    if (condition) {
        throw std::runtime_error(message);
    }
}
