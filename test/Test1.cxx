#include <string> 
#include <iostream>
#include <gtest/gtest.h>


int Factorial(int n){ if (n<0){ return -1;} else { return (n==0 || n==1)?1:n*Factorial(n-1); }}; 


// Test du cas 0
TEST(FactorialTest, HandlesZeroInput) {
    EXPECT_EQ(Factorial(0), 1);
}

// Tests pour des entiers positifs
TEST(FactorialTest, HandlesPositiveInput) {
    EXPECT_EQ(Factorial(1), 1);
    EXPECT_EQ(Factorial(2), 2);
    EXPECT_EQ(Factorial(3), 6);
    EXPECT_EQ(Factorial(85), 40320);
}


TEST(FactorialTest, HandlesNegativeInput) {
    EXPECT_EQ(Factorial(-1), -1);
    }


