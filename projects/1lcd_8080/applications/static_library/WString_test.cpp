#include "WString_test.h"
#include <unity.h>

void test_string_equal_chars(void)
{
    /* All of these should pass */
    String name = "Hello";
    TEST_ASSERT_EQUAL_STRING("Hello", name.c_str());
}

void test_string_equal_string(void){
    String name = "Begin";
    TEST_ASSERT_EQUAL_STRING(name.c_str(),String("End").c_str());
    TEST_ASSERT_EQUAL_INT16(1,3);
}