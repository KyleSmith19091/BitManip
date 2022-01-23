# Integer and Character Bit Manipulation

This is a header only library for common bit manipulation and other operations using constexpr and some bit manipulation techniques to provide a low
overhead and effiecent interface.

## Possible Operations
### Number Manipulation
1. isOdd → Check if integer is odd => O(1)

2. oppositeSigns → Check if two integers have different signs => O(1)

3. isBitSet → Check if bit is set => O(1)

4. unsetKBit → Unsets K'th bit => O(1)

5. setKBit → Sets K'th Bit => O(1)

6. toggleKBit → Toggles K'th bit => O(1)

7. unsetRightmostBit → Unsets the rightmost bit => O(1)

8. isPowerOf2 → Check if number is a power of 2 => O(1)

9. findOddParity → Check for odd parity => O(1) (Only works for 32 bit integers)

10. abs → Get the absolute value of given number => O(1) 

11. swap → Swaps two integers => O(1)

12. getRightmostBitPosTest → Gets the position of the rightmost set bit => O(n) where n is the number of bits in number(actually constant as function only works with ints)

### Character Manipulation
1. toLowercase → Converts char to lowercase => O(1)

2. toUppercase → Converts char to uppercase => O(1)

3. toggleCharCase → Toggles char case => O(1)

4. getAlphabeticPos → Gets the alphabetic position of given char => O(1)
