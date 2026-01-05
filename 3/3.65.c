/*
 * Inner loop
 * .L6:
 *   movq (%rdx), %rcx  rcx = *rdx
 *   movq (%rax), %rsi  rsi = *rax
 *   movq %rsi, (%rdx)  *rdx = rsi (*rax)
 *   movq %rcx, (%rax)  *rax = rcx (*rdx)
 *   addq $8, %rdx      rdx = rdx + 8
 *   addq $120, %rax    rax = rax + 120
 *   cmpq %rdi, %rax    rax:rdi
 *   jne .L6            if rax != rdi goto .L6
 *
 * &A[i][j] = &A + 8*(M*i + j)
 * M = 15
 * A. %rdx
 * B. %rax
 * C. 8*M = 120 => M = 15
 * */
void transpose(long A[M][M]) {
  long i, j;
  for (i = 0; i < M; i++) {
    for (j = 0; j < i; j++) {
      long t = A[i][j];
      A[i][j] = A[j][i];
      A[j][i] = t;
    }
  }
}
