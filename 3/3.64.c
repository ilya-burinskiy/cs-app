#define R 7
#define S 5
#define T 13

long A[R][S][T];

/*
 * long store_ele(long i, long j, long k, long *dest)
 * i in %rdi, j in %rsi, k in %rdx, dest in %rcx
 * store_ele:
 *   leaq (%rsi,%rsi,2), %rax  rax = 3*j
 *   leaq (%rsi,%rax,4), %rax  rax = 13*j
 *   movq %rdi,%rsi            rsi = i
 *   salq $6, %rsi             rsi = 64*i
 *   addq %rsi, %rdi           rdi = 65*i
 *   addq %rax, %rdi           rdi = 13*j + 65*i
 *   addq %rdi, %rdx           rdx = k + 13*j + 65*i
 *   movq A(,%rdx,8), %rax     rax = A + 8*(k + 13*j + 65*i)
 *   movq %rax, (%rcx)         *dest = A + 8*(k + 13*j + 65*i)
 *   movl $3640 %eax           eax = 3640
 *   ret
 *
 * 8 * R * S * T = 3640
 * R * S * T = 455
 *
 * S*T = 65
 * T = 13
 * S = 5
 * R = 7
 * */
long store_ele(long i, long j, long k, long *dest) {
  *dest = A[i][j][k];
  return sizeof(A);
}
