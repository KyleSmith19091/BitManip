#include <iostream>
#include <gtest/gtest.h>

#include "./BitManip.hpp"

TEST(isOddTest, basic) {
    EXPECT_EQ(1, BitManip::isOdd(1));
    EXPECT_EQ(0, BitManip::isOdd(2));
}

TEST(isOddTest, negativeValsBasic) {
    EXPECT_EQ(1, BitManip::isOdd(-1));
    EXPECT_EQ(0, BitManip::isOdd(-2));
}

TEST(oppositeSignsTest, basic) {
    EXPECT_EQ(1, BitManip::oppositeSigns(-1,2));
    EXPECT_EQ(0, BitManip::oppositeSigns(-1,-2));
    EXPECT_EQ(0, BitManip::oppositeSigns(-2,-2));
}

TEST(swapTest, basic) {
    int x = 1, y = 2;
    BitManip::swap(x,y);
    EXPECT_EQ(2,x);
    EXPECT_EQ(1,y);
    
}

TEST(swapTest, sameValues) {
    int x = 2, y = 2;
    BitManip::swap(x,y);
    EXPECT_EQ(2,x);
    EXPECT_EQ(2,y);
}

TEST(unsetKBitTest, basic) {
    EXPECT_EQ(16,BitManip::unsetKBit(20,3));
}

TEST(setKBitTest, basic) {
    EXPECT_EQ(28, BitManip::setKBit(20,4));
}

TEST(isBitSet, basic) {
    EXPECT_EQ(1, BitManip::isBitSet(20,3));
}

TEST(toggleBitTest, basic) {
    EXPECT_EQ(16, BitManip::toggleKBit(20,3));
}

TEST(unsetRightmostBitTest, basic) {
    EXPECT_EQ(16, BitManip::unsetRightmostBit(20));
}

TEST(isPowerOf2Test, basic) {
    EXPECT_EQ(1, BitManip::isPowerOf2(16));
    EXPECT_EQ(0, BitManip::isPowerOf2(15));
    EXPECT_EQ(1, BitManip::isPowerOf2(8));
}

TEST(getRightmostBitPosTest, basic) {
    EXPECT_EQ(3, BitManip::getRightmostBitPos(20));
    EXPECT_EQ(1, BitManip::getRightmostBitPos(21));
}

TEST(findParityTest, basic) {
    EXPECT_EQ(0, BitManip::findOddParity(15));
    EXPECT_EQ(1, BitManip::findOddParity(127));
    EXPECT_EQ(0, BitManip::findOddParity(17));
}

TEST(absTest, basic) {
    EXPECT_EQ(1, BitManip::abs(-1));
    EXPECT_EQ(1, BitManip::abs(1));
}

TEST(toLowercaseTest, basic) {
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        EXPECT_EQ(ch+32, BitManip::StringUtils::toLowercase(ch));
    }
}

TEST(toUppercaseTest, basic) {
    for (char ch = 'a'; ch <= 'z'; ch++) {
        EXPECT_EQ(ch-32, BitManip::StringUtils::toUppercase(ch));
    }
}

TEST(toggleCharCaseTest, basic) {
    for (char ch = 'a'; ch <= 'z'; ch++) {
        EXPECT_EQ(ch-32, BitManip::StringUtils::toggleCharCase(ch));
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        EXPECT_EQ(ch+32, BitManip::StringUtils::toggleCharCase(ch));
    }
}

TEST(getAlphabeticPosTest, basicLowerCase) {
    char c = 'a';
    for(int i = 0; i < 26; i++, c++) {
        EXPECT_EQ(i+1, BitManip::StringUtils::getAlphabeticPos(c));
    }
}

TEST(getAlphabeticPosTest, basicUpperCase) {
    char c = 'A';
    for(int i = 0; i < 26; i++, c++) {
        EXPECT_EQ(i+1, BitManip::StringUtils::getAlphabeticPos(c));
    }
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
