# Integer and Character Bit Manipulation

This is a header only library for common bit manipulation and other operations using constexpr and some bitwise operators to provide a low
overhead and efficient interface.

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

## Discussion
All the above functions are implemented using bitwise operators which allows us to certain operations as fast as our computer allows us. They are the most basic of operations and can be simplified to basic circuits on a hardware level.
The constexpr functions are also branchless allowing us to take advantage of CPU pipelining and we also don't have to rely on any branch predictions.

### Examples
The advantage will be shown at the hand of an example. In this case we will look at the isOdd implementation.

```c++
constexpr bool isOdd(const int& i) noexcept{
    return i & 1;
}
```
We are simply checking if the rightmost bit of the integer is a 1, which if set will indicate an odd number
This will compile to following x86 assembly(Intel syntax) with no optimization applied using clang(trunk):

```asm
isOddOptim(int const&): # @isOddOptim(int const&)
    push rbp ; Push base stack pointer
    mov rbp, rsp ; Move stack pointer to base pointer
    mov qword ptr [rbp - 8], rdi ; Move first parameter onto the stack
    mov rax, qword ptr [rbp - 8] ; Move value from stack to rax register
    mov eax, dword ptr [rax] ; Move pointer in rax to eax(32-bit register)
    and eax, 1 ; Perform and operation of eax and 1
    cmp eax, 0 ; Compare eax with 0
    setne al ; If lower byte is not 0 then set byte
    and al, 1 ; And lower byte of eax with 1
    movzx eax, al ; Move(zero extend) the lower byte into eax
    pop rbp ; Restore stack
    ret ; Return from function call
```

If we remove the stack alignment operations for fulfilling the C++ ABI and handling the integer reference we are left with: 

```asm
isOddOptim(int const&): # @isOddOptim(int const&)
    and eax, 1 ; (eax has the value of the first parameter)
    cmp eax, 0 ; Compare eax with 0
    setne al ; If lower byte is not 0 then set byte
    and al, 1 ; And lower byte of eax with 1
    movzx eax, al ; Move(zero extend) the lower byte into eax
```
The main algorithm on an assembly level consists of 5 instructions.

Now looking at how a typical implementation of this would look without bitwise manipulation:

```c++
bool isOddBranch(const int& i) {
    if(i % 2 != 0) {
        return true;
    } else {
        return false;
    }
}

bool isOddTernary(const int& i) {
    return i % 2 != 0 ? true : false;
}
```

```asm
isOddBranch(int const&): # @isOddBranch(int const&)
    push rbp
    mov rbp, rsp
    mov qword ptr [rbp - 16], rdi
    mov rax, qword ptr [rbp - 16]
    mov eax, dword ptr [rax]
    mov ecx, 2
    cdq
    idiv ecx
    cmp edx, 0
    je .LBB1_2
    mov byte ptr [rbp - 1], 1
    jmp .LBB1_3
    .LBB1_2:
    mov byte ptr [rbp - 1], 0
    .LBB1_3:
    mov al, byte ptr [rbp - 1]
    and al, 1
    movzx eax, al
    pop rbp
    ret
```
The instructions used are much simpler we have a few movs, idiv, jmps and something called cdq. This implementation might be able to leverage some
pipelining using branch prediction strategies if we're checking numbers that are odd due to the way we setup the if statement, but as soon as we run into an even number we flush the pipeline.
Then we lose a lot of potential work that could have been done.

Now looking at an implementation using a ternary expression:

```asm
isOddTernary(int const&): # @isOddTernary(int const&)
    push rbp
    mov rbp, rsp
    mov qword ptr [rbp - 8], rdi
    mov rax, qword ptr [rbp - 8]
    mov eax, dword ptr [rax]
    mov edx, eax
    shr edx, 31
    mov ecx, eax
    add ecx, edx
    and ecx, -2
    sub eax, ecx
    setne al
    neg al
    and al, 1
    movzx eax, al
    pop rbp
    ret
```
This looks alot beter, we don't have any visible branches because we got some help from the compiler here, but we have a lot of extra operations happening.

So we can see that the bitwise method is the best of the three. It is however important to know that compilers are very smart and if we apply some optimization flags all three of these implementations compile to exactly the same assembly. 

```c++
isOddOptim(int const&): # @isOddOptim(int const&)
    mov al, byte ptr [rdi]
    and al, 1
    ret

isOddBranch(int const&): # @isOddBranch(int const&)
    mov al, byte ptr [rdi]
    and al, 1
    ret

isOddTernary(int const&): # @isOddTernary(int const&)
    mov al, byte ptr [rdi]
    and al, 1
    ret
```

## Testing
To run the tests written in the Main.cpp, you will need the google test suite installed and available to the compiler that you are using.
```bash
$ make
```
