
#define set_bit(a, n)( a |= 1 << n)
#define clear_bit(a, n)( a &= ~(1 << n))
#define flip_bit(a, n)( a ^= 1 << n)
#define has_bit_set(a, n)( a & 1 << n) 
#define write_bit(a, n, b)(b? set_bit(a, n) : clear_bit(a, n))  

#define set_bitmask(x, y)( x |= y)
#define clear_bitmask(x, y)(x &= ~y)
#define flip_bitmask(x, y)( x ^= y)
#define same_bitmask(x, y)(x == y)
#define write_bitmask(x, y)(x = y)

/**************
 * has_bit_set - if set, returns non-zero, not necessarily 1
 * write_bit - write b in bit n of register a
 * flip_bitmask - flip bit in x if corresponding bit in y is set to 1
 * set_bitmask - set bit in x if corresponding bit in y is set to 1
 * clear_bitmask - clear bit in x if corresponding bit in y is set to 1 
 **************/
