#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>

class TestFramework {
private:
    static std::vector<std::function<void()>> tests;
    static std::vector<std::string> testNames;
    static int totalTests;
    static int passedTests;
    static int failedTests;
    
public:
    static void registerTest(const std::string& name, std::function<void()> test);
    static int runAllTests();
    static void assertEqual(bool condition, const std::string& message);
    static void assertTrue(bool condition, const std::string& message);
    static void assertFalse(bool condition, const std::string& message);
};

#define TEST(testClass, testName) \
    void testClass##_##testName(); \
    static bool testClass##_##testName##_registered = \
        (TestFramework::registerTest(#testClass "." #testName, testClass##_##testName), true); \
    void testClass##_##testName()

#define EXPECT_TRUE(condition) \
    TestFramework::assertTrue(condition, "Expected true: " #condition)

#define EXPECT_FALSE(condition) \
    TestFramework::assertFalse(condition, "Expected false: " #condition)

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        std::cerr << "ASSERTION FAILED: " << #condition << " at line " << __LINE__ << std::endl; \
        throw std::runtime_error("Assertion failed"); \
    }
