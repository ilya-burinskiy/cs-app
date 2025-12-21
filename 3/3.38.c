#define M 5
#define N 7

long P[M][N];
long Q[N][M];

/*
 * long sum_element(long i, long j)
 * rdi <- i
 * rsi <- j
 * sum_element:
 *   leaq 0(,%rdi,8), %rdx        rdx <- 0 + i * 8
 *   subq %rdi, %rdx              rdx <- rdx - i; rdx <- 7*i
 *   addq %rsi, %rdx              rdx <- rdx + j; rdx <- 7*i + j
 *   leaq (%rsi,%rsi,4), %rax     rax <- j + 4 * j; rax <- 5*j 
 *   addq %rax,%rdi               rdi <- i + 5*j
 *   movq Q(,%rdi,8), %rax        rax <- M[Q + 8*(i + 5*j)]
 *   addq P(,%rdx,8), %rax        rax <- rax + M[P + 8*(7*i + j)]
 *   ret
 *
 * long P[M][N]
 * long Q[N][M]
 * &P[i][j] = x_P + 8*(i*N + j)
 * &Q[j][i] = x_Q + 8*(j*M + i)
 * M = 5
 * N = 7
 * */
long sum_element(long i, long j) {
  return P[i][j] + Q[j][i];
}
