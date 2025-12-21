#include<assert.h>

#define N 16

typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val);
void fix_set_diag_opt(fix_matrix A, int val);

int main(void) {
  fix_matrix A = {0};
  fix_matrix B = {0};
  fix_set_diag(A, 1);
  fix_set_diag(B, 1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      assert(A[i][j] == B[i][j]);
    }
  }
  return 0;
}

void fix_set_diag(fix_matrix A, int val) {
  long i;
  for (i = 0; i < N; i++) {
    A[i][i] = val;
  }
}

/*
 * void fix_set_diag(fix_matrix A, int val)
 * rdi <- x_A
 * rsi <- val
 *
 * fix_set_diag:
 *   movl $0, %eax            eax <- 0
 * .L13:
 *   movl %esi, (%rdi, %rax)  M[x_A + rax] <- val
 *   addq %68, %rax           rax <- rax + 68
 *   cmpq $1088, %rax         rax:1088
 *   jne .L13                 if rax != 1088 goto .L13
 *   rep; ret                 return
 *
 * A[i][j] = x_A + 4*(16*i + i) = x_A + 68*i
 * 0 <= i < 16
 * 68 * 16 = 1088
 * x_A + 1088 = x_A + 68*16 = x_A + 4*(16 * 17)
 *            = x_A + 4*(16 * 16 + 16)
 *            = &A[16][16]
 * */
void fix_set_diag_opt(fix_matrix A, int val) {
  int i = 0;
  int *Aptr = &A[0][0];
  int *Aend = &A[N][N];
  do {
    *(Aptr + i) = val;
    Aptr += N + 1;
  } while (Aptr != Aend);
}
