#include <stdio.h>

int int_size_is_32();
int int_size_is_32_16_bit();
int my_int_size_is_32();

int main(int argc, char **argv) {
  printf("int size is 32: %d\n", int_size_is_32());
  printf("int size is 32 (16 bit): %d\n", int_size_is_32_16_bit());
  printf("int size is 32 (my solution): %d\n", my_int_size_is_32());
  return 0;
}

/*
 * Изначальное решение было таким
 * int int_size_is_32() {
 *   int msb = 1 << 31;
 *   int tmax = ~msb;
 *   return msb && (tmax + 1) < 0;
 * }
 *
 * Ассемблер этого решения
 * my_int_size_is_32:
 *   pushq	%rbp
 *   movq	%rsp, %rbp
 *   # msb
 *   movl	$-2147483648, -8(%rbp) # -8(%rbp) <- 0x80000000
 *   movl	-8(%rbp), %eax
 *   notl	%eax                   # 0x7fffffff
 *   movl	%eax, -4(%rbp)         # -4(%rbp) <- 0x7fffffff
 *   cmpl	$0, -8(%rbp)
 *   je	.L12
 *   cmpl	$-1, -4(%rbp)
 *   jge	.L12
 *   movl	$1, %eax
 *   jmp	.L14
 * .L12:
 *   movl	$0, %eax
 * .L14:
 *   popq	%rbp
 *   ret
 * Почему такой код вернул 0:
 * cmpl $-1, -4(%rbp) вычисляет флаги вот такого выражения
 * 0x7fffffff + 0x1 = 0x80000000
 * При этом SF и OF равны 1. Условие jge ~(SF ^ OF) == 1. Следовательно
 * jge .L12 сработает и вернет 0.
 * */
int int_size_is_32() {
  int msb = 1 << 31;
  int beyond = msb << 1;
  return msb && !beyond;
}

int int_size_is_32_16_bit() {
  int msb = 1 << 15 << 15 << 1;
  int beyond = msb << 1;
  return msb && !beyond;
}

int my_int_size_is_32() {
  int msb = 1 << 31;
  int tmax = ~msb;
  return msb && (tmax + 1) < 0;
}
