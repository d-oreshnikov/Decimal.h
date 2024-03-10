# Decimal.h

Implementation of Decimal.h library on C

## Contents

0. [Information](#information)
1. [Decimal structure in C language](#decimal-structure-in-c-language)
2. [Decimal functions](#decimal-functions)


## Information

The Decimal value type represents decimal numbers ranging from positive 79,228,162,514,264,337,593,543,950,335 to negative 79,228,162,514,264,337,593,543,950,335. The default value of a Decimal is 0. The Decimal value type is appropriate for financial calculations that require large numbers of significant integral and fractional digits and no round-off errors. The Decimal type does not eliminate the need for rounding. Rather, it minimizes errors due to rounding.

When the result of the division and multiplication is passed to the Round method, the result suffers no loss of precision.

A decimal number is a floating-point value that consists of a sign, a numeric value where each digit in the value ranges from 0 to 9, and a scaling factor that indicates the position of a floating decimal point that separates the integral and fractional 
parts of the numeric value.

The functions of the decimal.h library described [below](#decimal-functions) must be implemented:

- The library was developed in C language of C11 standard using gcc compiler
- The library code was located in the src folder.
- Outdated and legacy language constructions and library functions were not used.
- The programs were developed by POSIX.1-2017 standard.
- The program code written in Google style
- A static library (with the my_decimal.h header file)
- The library was developed according to the principles of structured programming;
- Use prefix my_ before each function
- Full coverage of library functions code with unit-tests using the Check library
- Unit tests cover at least 80% of each function (checked using gcov)  
- Makefile for building the library and tests (with targets all, clean, test, my_decimal.a, gcov_report)
- The gcov_report target generate a gcov report in the form of an html page. Unit tests was run with gcov flags to do this.
- Decimal implemation, sticks to [the binary representation](#binary-representation) with the integer `bits` array as specified in the [example below](#decimal-structure-in-c-language). Observe the position of the digits of a number in the `bits` array
- The __int128 type is not used
- Trailing zeros are as preserved as deleted (except for the `my_truncate` function)
- The defined type must support numbers from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.

### Binary representation

The binary representation of a Decimal value consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the 96-bit integer and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28. Therefore, the binary representation of a Decimal value the form, ((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue, and 2^96-1 is equal to MaxValue.

The scaling factor also can preserve any trailing zeros in a Decimal number. Trailing zeros do not affect the value of a Decimal number in arithmetic or comparison operations. 

The binary representation of a Decimal number consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the integer number and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28.

Decimal number can be implemented as a four-element array of 32-bit signed integers (`int bits[4];`).

`bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.

`bits[3]` contains the scale factor and sign, and consists of following parts:
- Bits 0 to 15, the lower word, are unused and must be zero.
- Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and must be zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

Note that the bit representation differentiates between negative and positive zero. These values can be treated as being equal in all operations.

## Decimal structure in C language

```c
typedef union {
  struct {
    uint32_t : 32;
    uint32_t : 32;
    uint32_t : 32;
    uint32_t : 16;
    uint32_t exp : 8;
    uint32_t : 7;
    uint32_t sign : 1;
  };
  uint32_t bits[4];
} my_decimal;
```

## Decimal functions

### Arithmetic Operators

| Operator name | Operators  | Function                                                                           | 
| ------ | ------ |------------------------------------------------------------------------------------|
| Addition | + | `int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result)`         |
| Subtraction | - | `int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result)` |
| Multiplication | * | `int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result)` | 
| Division | / | `int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result)` |
| Modulo | Mod | `int my_mod(my_decimal value_1, my_decimal value_2, my_decimal *result)` |

The functions return the error code:
- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

*Note on the numbers that do not fit into the mantissa:*
- *When getting numbers that do not fit into the mantissa during arithmetic operations, use bank rounding (for example, 79,228,162,514,264,337,593,543,950,335 - 0.6 = 79,228,162,514,264,337,593,543,950,334)*

### Comparison Operators

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Less than | < | `int my_is_less(my_decimal, my_decimal)` |
| Less than or equal to | <= | `int my_is_less_or_equal(my_decimal, my_decimal)` | 
| Greater than | > |  `int my_is_greater(my_decimal, my_decimal)` |
| Greater than or equal to | >= | `int my_is_greater_or_equal(my_decimal, my_decimal)` | 
| Equal to | == |  `int my_is_equal(my_decimal, my_decimal)` |
| Not equal to | != |  `int my_is_not_equal(my_decimal, my_decimal)` |

Return value:
- 0 - FALSE
- 1 - TRUE

### Convertors and parsers

| Convertor/parser | Function | 
| ------ | ------ |
| From int  | `int my_from_int_to_decimal(int src, my_decimal *dst)` |
| From float  | `int my_from_float_to_decimal(float src, my_decimal *dst)` |
| To int  | `int my_from_decimal_to_int(my_decimal src, int *dst)` |
| To float  | `int my_from_decimal_to_float(my_decimal src, float *dst)` |

Return value - code error:
- 0 - OK
- 1 - convertation error

*Note on the conversion of a float type number:*
- *If the numbers are too small (0 < |x| < 1e-28), return an error and value equal to 0*
- *If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or are equal to infinity, return an error*
- *When processing a number with the float type, convert all the significant decimal digits contained in it. If there are more than 7 such digits, the number is rounded to the closest one that does not have more than 7 significant decimal digits.*

*Note on the conversion from decimal type to int:*
- *If there is a fractional part in a decimal number, it should be discarded (for example, 0.9 is converted to 0)*


### Another functions

| Description | Function| 
| ------ |------------------------------------------------------------------|
| Rounds a specified Decimal number to the closest integer toward negative infinity. | `int my_floor(my_decimal value, my_decimal *result)`|	
| Rounds a decimal value to the nearest integer. | `int my_round(my_decimal value, my_decimal *result)`    |
| Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes. | `int my_truncate(my_decimal value, my_decimal *result)` |
| Returns the result of multiplying the specified Decimal value by negative one. | `int my_negate(my_decimal value, my_decimal *result)`   |

Return value - code error:
- 0 - OK
- 1 - calculation error
