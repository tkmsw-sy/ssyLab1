/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return (x | y) & (~(x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign = x >> 31;
  return sign & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
   int srcShift = src << 3;
  int byte = (x >> srcShift) & 0xFF;
  int dstShift = dst << 3;
  int mask = ~(0xFF << dstShift);
  int result = x & mask;
  return result | (byte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int shifted = x >> n;
  int mask = ~((1 << 31) >> n << 1);
  return shifted & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
   int lowMask = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  int low = (x & lowMask) << 4;
  int high = (x >> 4) & lowMask;
  return low | high;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
   return ~(x | (x + 1)) & ((x | (x + 1)) + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int right = (x >> n) & ~((1 << 31) >> n << 1);
  int left = x << (32 + (~n + 1));
  return right | left;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int mask = (1 << n) + ~0; /* 2^n - 1 */
  int remainder = x & mask;
  int half = 1 << (n + ~0); /* 2^(n-1) */
  int base = x & ~mask;
  /* check if remainder > half, or remainder == half and next bit is 1 */
  int gt = (remainder + (~half + 1)) >> 31; /* remainder < half */
  int eq = !((remainder ^ half) | ((x >> n) & 1)); /* remainder == half and even */
  int roundUp = !gt & !eq;
  return base + (roundUp << n);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
    int xor = x ^ y;
    int avg = (x & y) + (xor >> 1);
    int tie = xor & 1;
    int xSign = x >> 31;
    int ySign = y >> 31;
    int diff = x + (~y + 1);
    int diffSign = diff >> 31;
    int xGtY = ((xSign ^ ySign) & ~xSign) | (~(xSign ^ ySign) & ~diffSign);
    int adjust = tie & xGtY;
      return avg + adjust;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int signX = x >> 31;
  int signA = a >> 31;
  int signB = b >> 31;
  int xa = x + (~a + 1);
  int signXA = xa >> 31;
  int xGeA = ((signX ^ signA) & ~signX) | (~(signX ^ signA) & ~signXA);
  int ax = a + (~x + 1);
  int signAX = ax >> 31;
int xLeA = ((signX ^ signA) & signX) | (~(signX ^ signA) & ~signAX);
     int xb = x + (~b + 1);
     int signXB = xb >> 31;
int xGeB = ((signX ^ signB) & ~signX) | (~(signX ^ signB) & ~signXB);
int bx = b + (~x + 1);
  int signBX = bx >> 31;
int xLeB = ((signX ^ signB) & signX) | (~(signX ^ signB) & ~signBX);
int xEqA = !(x ^ a);
int xEqB = !(x ^ b);

 xGeA = xGeA | xEqA;
 xLeA = xLeA | xEqA;
  xGeB = xGeB | xEqB;
  xLeB = xLeB | xEqB;
 return !!((xGeA & xLeB) | (xGeB & xLeA));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
int a = x << 2;
  int res = a + x;
  int sx = x >> 31;
  int left_overflow = !!(((a >> 2) ^ x));
  int add_overflow = !((a ^ x) >> 31) & ((res ^ x) >> 31);
  int overflow = left_overflow | add_overflow;
  int INT_MAX = (1 << 31) + ~0;
  int INT_MIN = 1 << 31;
  int sat_val = (sx & INT_MIN) | (~sx & INT_MAX);
  int mask_ov = overflow << 31 >> 31;
  return (mask_ov & sat_val) | (~mask_ov & res);

}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
int lo1 = x + y;
  int carry1 = ((x & y) | ((x | y) & ~lo1)) >> 31 & 1;
  int hi1 = (x >> 31) + (y >> 31) + carry1;

  int lo2 = lo1 + z;
  int carry2 = ((lo1 & z) | ((lo1 | z) & ~lo2)) >> 31 & 1;
  int hi2 = hi1 + (z >> 31) + carry2;

  int lo2_sign = (lo2 >> 31) & 1;
  int hi2_sign = (hi2 >> 31) & 1;
  int hi2_zero = !hi2;
  int hi2_minus1 = !(hi2 ^ ~0);

  int hi2_pos = (!hi2_sign) & (!hi2_zero);
  int pos_overflow = hi2_pos | (hi2_zero & lo2_sign);

  int hi2_lt_neg1 = hi2_sign & (!hi2_minus1);
  int neg_overflow = hi2_lt_neg1 | (hi2_minus1 & (!lo2_sign));

  return pos_overflow | (neg_overflow << 31 >> 31);
  }

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  if (exp == 0xFF) {
    return uf; 
  }
  if (exp == 0) {
unsigned temp = frac + (frac << 1);
  unsigned result = temp >> 1;
if ((temp & 1) && ((result & 1) || (temp & 2))){
      result++;
    }
    return sign | result;
}
unsigned m = frac + (1 << 23);
unsigned m3 = m + (m << 1);
if (m3 & (1 << 25)) {
  unsigned rounded = m3 >> 2;
  unsigned rem = m3 & 3;
  if (rem > 2 || (rem == 2 && (rounded & 1))) {
     rounded++;
   }
   exp++;
   frac = rounded & 0x7FFFFF;
   } else {
    unsigned rounded = m3 >> 1;
    if ((m3 & 1) && (rounded & 1)) {
      rounded++;
    }
    frac = rounded & 0x7FFFFF;
    
  }
if (exp >= 0xFF) {
    return sign | 0x7F800000;
  }
  return sign | (exp << 23) | frac;
}
// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
   if (exp == 0xFF) {
    return uf;
  }
  int E = exp - 127;
  if (E < 0) {
   if (E == -1 && frac > 0) {
      return sign | 0x3F800000; 
      } 
    return sign;
  }
  if (E >= 23) {
    return uf;
  }
  unsigned fracBits = 23 - E;
unsigned roundBit = 1 << (fracBits - 1);
unsigned mask = (1 << fracBits) - 1;
unsigned fracPart = frac & mask;
 unsigned result = uf & ~mask;
if (fracPart >roundBit ) {
    result += (1 << fracBits);
  } else if (fracPart == roundBit) {
    if (result & (1 << fracBits)) {
      result += (1 << fracBits);
    }
  }
  if (((result >> 23) & 0xFF) != exp) {
    if (((result >> 23) & 0xFF) == 0xFF) {
      return sign | 0x7F800000; 
    }
  }
  return result;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned absX;
  if (x == 0) {
    return 0;
  }
  if (x < 0) {
    sign = 0x80000000;
    absX = -x;
  } else {
    absX = x;
  }
  int shift = 0;
  unsigned temp = absX;
  while (temp > 1) {
    temp >>= 1;
    shift++;
  }
  unsigned exp = shift + 127;
  unsigned frac;
  if (shift <= 23) {
    frac = (absX << (23 - shift)) & 0x7FFFFF;
  } else {
    int extraBits = shift - 23;
    unsigned fracFull = absX >> extraBits;
    unsigned remainder = absX & ((1 << extraBits) - 1);
    unsigned half = 1 << (extraBits - 1);
    frac = fracFull & 0x7FFFFF;
    if (remainder > half || (remainder == half && (fracFull & 1))) {
      frac++;
      if (frac > 0x7FFFFF) {
        frac = 0;
        exp++;
      }
    }
}
return sign | (exp << 23) | frac;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask1 = 0x55 | (0x55 << 8);
  mask1 = mask1 | (mask1 << 16); 
  int mask2 = 0x33 | (0x33 << 8);
  mask2 = mask2 | (mask2 << 16); 
  int mask3 = 0x0F | (0x0F << 8);
  mask3 = mask3 | (mask3 << 16); 
  int mask4 = 0xFF | (0xFF << 16); 
  int mask5 = 0xFF | (0xFF << 8);
int count = (x & mask1) + ((x >> 1) & mask1);
  count = (count & mask2) + ((count >> 2) & mask2);
  count = (count & mask3) + ((count >> 4) & mask3);
  count = (count & mask4) + ((count >> 8) & mask4); 
  count = (count & mask5) + ((count >> 16) & mask5);
  return count;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
   int mask1 = 0x55 | (0x55 << 8);
  mask1 = mask1 | (mask1 << 16); 
  x = ((x & mask1) << 1) | ((x >> 1) & mask1);
  int mask2 = 0x33 | (0x33 << 8);
  mask2 = mask2 | (mask2 << 16); 
  x = ((x & mask2) << 2) | ((x >> 2) & mask2);
  int mask3 = 0x0F | (0x0F << 8);
  mask3 = mask3 | (mask3 << 16); 
  x = ((x & mask3) << 4) | ((x >> 4) & mask3);
  int mask4 = 0xFF | (0xFF << 16); 
  x = ((x & mask4) << 8) | ((x >> 8) & mask4);

  x = (x << 16) | ((x >> 16) & 0xFFFF);
  return x;
}
