/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    int a=~x;
    int b=~y;
    int c=a|b;
    // 德摩根律：x & y = ~(~x | ~y)
    int d=~c;
    return d;
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int a=x&y;
    int b=(~x)&(~y);
    // x ^ y = ~(x & y) & ~(~x & ~y)
    int c=(~a)&(~b);
    return c;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(x&&y)
    {
        int a=x>>31;
        int b=y>>31;
        // 非零时看符号位是否相同
        return !(a^b);
    }
    else
    {
        // 有 0 时只有两个都为 0 才同号
        return !(x^y);
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int m;
    // 依次探测高 16、8、4、2、1 位中是否还有 1
    m = (v >> 16 > 0) << 4;
    r = r | m;
    v = v >> m;
    m = (v >> 8 > 0) << 3;
    r = r | m;
    v = v >> m;
    m = (v >> 4 > 0) << 2;
    r = r | m;
    v = v >> m;
    m = (v >> 2 > 0) << 1;
    r = r | m;
    v = v >> m;
    r = r | (v >> 1 > 0);
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a=n<<3;
    int b=m<<3;
    // 取出第 n、m 个字节
    int n1=(x>>a)&0xFF;
    int m1=(x>>b)&0xFF;
    // 清空这两个字节
    int mask=~((0xFF<<a)|(0xFF<<b));
    x=mask&x;
    // 交换后放回
    x=x|(n1<<b)|(m1<<a);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    // 分治交换：16位、8位、4位、2位、1位
    v = (v >> 16) | (v << 16);
    v = ((v & 0xFF00FF00) >> 8) | ((v & 0x00FF00FF) << 8);
    v = ((v & 0xF0F0F0F0) >> 4) | ((v & 0x0F0F0F0F) << 4);
    v = ((v & 0xCCCCCCCC) >> 2) | ((v & 0x33333333) << 2);
    v = ((v & 0xAAAAAAAA) >> 1) | ((v & 0x55555555) << 1);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    // 构造低 (32-n) 位为 1 的掩码，清掉算术右移带入的符号位
    int a=(1<<31)>>n;
    a=a<<1;
    a=~a;
    x=x>>n;
    x&=a;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    // 统计左侧连续 1，等价于统计 ~x 左侧连续 0 前面有多少位
    int y = ~x;
    int count = 0;
    int t;

    // 类似二分：先看高 16 位是否全 0
    t = !(y >> 16);
    count += t << 4;
    y = y << (t << 4);

    // 再看接下来的 8 位
    t = !(y >> 24);
    count += t << 3;
    y = y << (t << 3);

    // 再看接下来的 4 位
    t = !(y >> 28);
    count += t << 2;
    y = y << (t << 2);

    // 再看接下来的 2 位
    t = !(y >> 30);
    count += t << 1;
    y = y << (t << 1);

    // 最后看 1 位
    t = !(y >> 31);
    count += t;
    y = y << t;

    // 若 y 已全 0，说明原 x 全 1
    count += !y;

    return count;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;
    unsigned exp = 158;
    unsigned frac;
    unsigned rest;

    if (!x)
        return 0;

    // -2^31 特殊处理，避免取负溢出
    if (x == 0x80000000)
        return 0xCF000000;

    if (sign)
        x = -x;

    // 规格化：把最高有效位移到第 31 位
    while (!(x & 0x80000000)) {
        x = x << 1;
        exp = exp - 1;
    }

    // 取尾数高 23 位，低 8 位用于舍入判断
    frac = (x >> 8) & 0x007FFFFF;
    rest = x & 0xFF;

    // 就近舍入到偶数
    if (rest > 0x80) {
        frac = frac + 1;
    }
    else if (rest == 0x80) {
        if (frac & 1)
            frac = frac + 1;
    }

    // 尾数进位则指数加一
    if (frac & 0x00800000) {
        exp = exp + 1;
        frac = 0;
    }

    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;          // 3 ops: >> & (常量不算)
    unsigned sign = uf & 0x80000000;           // 1 op
    unsigned frac = uf & 0x7FFFFF;             // 1 op

    // NaN 或 INF 直接返回
    if (exp == 0xFF)                           // 1 op
        return uf;

    // 非规格化数：整体左移尾数即可乘 2
    if (exp == 0)                              // 1 op
        return sign | (frac << 1);             // 2 ops: << |

    // 规格化数：指数加一
    return sign | ((exp + 1) << 23) | frac;    // 4 ops: + << | |
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign;
    int exp;
    int E;
    unsigned frac_hi;
    unsigned frac_lo;
    unsigned sig_hi;
    unsigned result;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7FF;
    E = exp - 1023;

    // NaN 或 INF
    if (!(exp-0x7FF))
        return 0x80000000;

    // 太小，向零取整为 0
    if (E < 0)
        return 0;

    // 超出 int 可表示范围
    if (E > 30)
        return 0x80000000;

    frac_hi = uf2 & 0xFFFFF;
    frac_lo = uf1;

    // 补上隐含的 1
    sig_hi = frac_hi | 0x100000;

    // 根据阶码决定有效数字如何拼接
    if (E < 21) {
        result = sig_hi >> (20 - E);
    } else {
        result = (sig_hi << (E - 20))
               | (frac_lo >> (52 - E));
    }

    if (sign)
        result = -result;

    return result;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    // 小于最小非规格化数
    if (x < -149)
        return 0;

    // 非规格化范围
    if (x < -126)
        return 1 << (x + 149);

    // 超出最大规格化数
    if (x > 127)
        return 0x7F800000;

    // 规格化数：指数加上偏置 127
    return (x + 127) << 23;
}