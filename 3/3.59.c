#include <stdint.h>

typedef __int128 int128_t;

/*
 * x' = 2^64*x_h + x_l
 * y' = 2^64*y_h + y_l
 * x' * y' mod 2^128
 *   = (2^64*x_h + x_l) * (2^64*y_h + y_l) mod 2^128
 *   = 2^128*x_h*y_h + 2^64*x_h*y_l + 2^64*x_l*y_h + x_l*y_l mod 2^128
 *   = 2^64*x_h*y_l + 2^64*x_l*y_h + x_l*y_l
 *   = 2^64*(x_h*y_l + x_l*y_h) + x_l*y_l
 * x' * y' = p_h * 2^64 + p_l
 * p_h = x_h*y_l + y_h*x_l
 * p_l = x_l * y_l
 *
 * dest in rdi
 * x in rsi
 * y in rdx
 * store_prod:
 *   movq %rdx, %rax       rax = y_l
 *   cqto                  rdx:rax = y_h, y_l
 *   movq %rsi, %rcx       rcx = x_l
 *   sarq $63, %rcx        rcx = x_l >> 63 = x_h
 *   imulq %rax, %rcx      rcx = x_h * y_l
 *   imulq %rsi, %rdx      rdx = y_h * x_l
 *   addq %rdx, %rcx       rcx = x_h * y_l + y_h * x_l = p_h
 *   mulq %rsi             rdx:rax = x_l * y_l
 *   addq %rcx, %rdx       rdx = rdx + rcx
 *   movq %rax, (%rdi)     *dest = rax       (upper)
 *   movq %rdx, 8(%rdi)    *(dest + 8) = rdi (lower)
 *   ret
 * */
void store_prod(int128_t *dest, int64_t x, int64_t y) {
  *dest = x * (int128_t) y;
}
