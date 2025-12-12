/*
 * # My
 * # rdi <- x
 * dw_loop:
 *   movq %rdi, %rax         # rax <- x
 *   cqto
 *   idivq $9                # rax <- x/9
 *   movq %rax, %rcx         # rcx <- x/9 (y)
 *   leaq (,%rdi,4), %rdx    # rdx <- 4*x (rdx := n)
 * .L2:
 *   leaq 5(%rax,%rcx), %rax # rax <- 5 + rax + y
 *   subq $1, %rdx           # rdx <- rdx - 1 (n)
 *   testq %rdx, %rdx
 *   jg .L2                  # if n > 0 goto .L2
 *   rep; ret
 *
 * # Orig
 * dw_loop:
 *   movq %rdi, %rbx          # rbx <- x
 *   movq %rdi, %rcx          # rcx <- x
 *   idivq %9, %rcx           # rcx <- x/9 (y)
 *   leaq (,%rdi,4), %rdx     # rdx <- x*4 (n)
 * .L2:
 *   leaq 5(%rbx,%rcx), %rcx  # rcx <- 5 + x + y
 *   subq $1, %rdx            # rdx <- n - 1
 *   testq %rdx, %rdx
 *   jg .L2                   # if n > 0 goto .L2
 *   rep; ret
 *
 * A. %rax <- x, %rcx <- y, %rdx <- n
 * B. leaq 5(%rax,%rcx), %rax
 * */
long dw_loop(long x) {
  long y = x / 9;
  long *p = &x;
  long n = 4 * x;
  do {
    /* x += 5 + y */
    x += y;
    (*p) += 5;
    n -= 2;
  } while (n > 0);
  return x;
}
