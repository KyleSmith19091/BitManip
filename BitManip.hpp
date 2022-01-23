#include <string> 

namespace BitManip {

    // Generate Parity Lookup Table
    #define P2(n) n, n^1, n^1, n
    #define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
    #define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    #define FIND_PARITY P6(0), P6(1), P6(1), P6(0)

    // 0-255
    #define POSSIBLE_NUM_OF_BYTE_NUMBERS 256

    // Lookup table for all possible 8 bit values, used in parity checking
    constexpr int PARITY_LOOKUP[POSSIBLE_NUM_OF_BYTE_NUMBERS] = { FIND_PARITY };

    /**
     * @brief Checks if given integer is odd 
     * 
     * @param i Number to check 
     * @return true 
     * @return false 
     */
    constexpr bool isOdd(const int& i) noexcept {
        return i & 1;
    }

    /**
     * @brief Checks if the signs of the given integers are different 
     * 
     * @param i Number to use in comparison 
     * @param j Number to use in comparison 
     * @return true 
     * @return false 
     */
    constexpr bool oppositeSigns(const int& i, const int& j) noexcept {
        return (i ^ j) < 0;
    }

    /**
     * @brief Checks if the k'th bit is set 
     * 
     * @param i Number to check 
     * @param k Position of the bit 
     * @return true 
     * @return false 
     */
    constexpr bool isBitSet(const int& i, const int& k) noexcept {
        return i & (1 << (k-1));
    }

    /**
     * @brief Sets k'th bit to 0 
     * 
     * @param i Number which is going to have its bit unset 
     * @param k Position of the bit to be unset  
     * @return constexpr int 
     */
    constexpr int unsetKBit(const int& i, const int& k) noexcept {
        return i & ~(1 << (k-1));
    }

    /**
     * @brief Sets k'th bit to 1  
     * 
     * @param i Number which going to have its bit set 
     * @param k Position of the bit to be set
     * @return constexpr int 
     */
    constexpr int setKBit(const int& i, const int& k) noexcept {
        return i | (1 << (k-1));
    }

    /**
     * @brief Toggles k'th bit 
     * 
     * @param i Number which is going to have its bit toggled
     * @param k Position of the bit to be toggled
     * @return constexpr int 
     */
    constexpr int toggleBit(const int& i, const int& k) noexcept {
        return i ^ (1 << (k-1));
    }

    /**
     * @brief Unsets rightmost bit  
     * 
     * @param i Number which is going to have its rightmost bit unset
     * @return constexpr int 
     */
    constexpr int unsetRightmostBit(const int& i) noexcept {
        return i & (i - 1);
    }

    /**
     * @brief Checks if number is a power of 2 
     * 
     * @param i Number to be checked 
     * @return true 
     * @return false 
     */
    constexpr bool isPowerOf2(const int& i) noexcept {
        return !BitManip::unsetRightmostBit(i);
    }

    /**
     * @brief Checks for odd parity in number 
     * 
     * @param i Number to be checked for odd parity
     * @return true 
     * @return false 
     */
    constexpr bool findOddParity(int i) noexcept {
        return PARITY_LOOKUP[((i ^ (i >> 16)) ^ ((i >> 16) ^ (i >> 24))) & 0xff];
    }

    /**
     * @brief Get absolute value of given number 
     * 
     * @param i Number to be converted 
     * @return constexpr int 
     */
    constexpr int abs(int i) noexcept {
        return (i + (i >> (sizeof(int) * 8 - 1))) ^ (i >> (sizeof(int) * 8 - 1));
    }

    /**
     * @brief Sets k'th bit to 0 using number reference 
     * 
     * @param i Number which is going to have bit unset 
     * @param k Position of the bit in number
     */
    inline void unsetKBit(int& i, int& k) noexcept {
        i = i & ~(1 << (k-1));
    }

    /**
     * @brief Sets k'th bit to 1' using number reference
     * 
     * @param i Number which is going to have bit set
     * @param k Position of the bit in number 
     */
    inline void setKBit(int& i, int& k) noexcept {
        i = i | (1 << (k-1));
    }

    /**
     * @brief Toggles k'tb bit using number reference 
     * 
     * @param i Number which is going to have bit toggled
     * @param k Position of the bit in number
     */
    inline void toggleBit(int& i, const int& k) noexcept {
        i = i ^ (1 << (k-1));
    }

    /**
     * @brief Unset the rightmost bit in number using reference 
     * 
     * @param i Number which is going to have rightmost bit unset
     */
    inline void unsetRightmostBit(int& i) noexcept {
        i = i & (i - 1);
    }

    /**
     * @brief Swaps the two given numbers 
     * 
     * @param i Number to be swapped 
     * @param j Number to be swapped 
     */
    inline void swap(int& i, int& j) noexcept {
        i = i ^ j;
        j = i ^ j;
        i = i ^ j;
    }

    /**
     * @brief Get the Rightmost Bit Position
     * 
     * @param i Number to check 
     * @return int 
     */
    inline int getRightmostBitPos(int i) noexcept {
        if(!BitManip::isOdd(i)) {
            const int iCopy = i;
            i = i ^ BitManip::unsetRightmostBit(iCopy);

            int pos = 0;
            while(i) {
                i = i >> 1;
                pos++;
            }

            return pos;
        } else {
            return 1;
        }
    }

    namespace StringUtils {
        /**
         * @brief Converts char to lowercase 
         * 
         * @param c Char to be converted 
         * @return constexpr char 
         */
        constexpr char toLowercase(const char& c) {
            return c | ' ';
        } 

        /**
         * @brief Converts char to uppercase 
         * 
         * @param c Char to be converted 
         * @return constexpr char 
         */
        constexpr char toUppercase(const char& c) {
            return c & '_';
        }

        /**
         * @brief Toggles the case of the char  
         *  
         * @param c Char to be toggled 
         * @return constexpr char 
         */
        constexpr char toggleCharCase(const char& c) {
            return c ^ ' ';
        }

        /**
         * @brief Get the Alphabetic Position of char
         * 
         * @param c Char to be checked  
         * @return constexpr int 
         */
        constexpr int getAlphabeticPos(const char& c) {
            return c & 31;
        }

    }
    
};
