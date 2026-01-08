typedef struct {
  long a[2];
  long *p;
} strA;

typedef struct {
  long u[2];
  long q;
} strB;

/*
 * process:
 *   movq %rdi, %rax        rax = rdi
 *   movq 24(%rsp), %rdx    rdx = &z
 *   movq (%rdx), %rdx      rdx = z
 *   movq 16(%rsp), %rcx    rcx = y
 *   movq %rcx, (%rdi)      M[rsp+64] = y
 *   movq 8(%rsp), %rcx     rcx = x
 *   movq %rcx, 8(%rdi)     M[rdi + 8] = x
 *   movq %rdx, 16(%rdi)    M[rdi + 16] = z
 *   ret
 * */
strB process(strA s) {
  strB r;
  r.u[0] = s.a[1];
  r.u[1] = s.a[0];
  r.q = *s.p;
  return r;
}

/*
 * x in rdi, y in rsi, z in rdx
 * eval:
 *   subq $104, %rsp        rsp = rsp - 104
 *   movq %rdx, 24(%rsp)    M[rsp + 24] = z
 *   leaq 24(%rsp), %rax    rax = &z
 *   movq %rdi, (%rsp)      *rsp = x
 *   movq %rsi, 8(%rsp)     M[rsp + 8] = y
 *   movq %rax, 16(%rsp)    M[rsp + 16] = &z
 *   leaq 64(%rsp), %rdi    rdi = rsp + 64
 *   call process
 *   movq 72(%rsp), %rax    rax = M[rsp + 72]        rax = x
 *   addq 64(%rsp), %rax    rax = rax + M[rsp + 64]  rax = x + y
 *   addq 80(%rsp), %rax    rax = rax + M[rsp + 80]  rax = x + y + z
 *   addq $104, %rsp        rsp = rsp + 104
 *   ret
 * */
long eval(long x, long y, long z) {
  strA s;
  s.a[0] = x;
  s.a[1] = y;
  s.p = &z;
  strB r = process(s);
  return r.u[0] + r.u[1] + r.q;
}

/*
 * A,E. Diagram the stack for eval, showing the values that it stores
 *      on the stack prior to calling process. (+)
 *
 *      rsp+80        z   r.q
 *      rsp+72        x   r.u[1]
 *      rsp+64        y   r.u[0]
 *      (unused)
 *      rsp+24        z
 *      rsp+16        &z  s.(*p)
 *      rsp+8         y   s.a[1]
 *      rsp           x   s.a[0]
 *      rsp-8         ra
 *
 * B. What value does eval pass in its call to process?
 *    Address of local variable `strB r` in <eval> stack frame. (+)
 *
 * C. How does code for process access the elements of structure argument s?
 *    By biasing rsp (before calling <process>). (+)
 *    rsp    = &s.a[0]
 *    rsp+8  = &s.a[1]
 *    rsp+16 = &s.(*p)
 *
 * D. How does the code for process set the fields of result
 *    structure r? By biasing rdi (addr of r). (+)
 *    rdi    = &r.u[0]
 *    rdi+8  = &r.u[1]
 *    rdi+16 = &r.q
 * F. passing structure as argument - callee add bias to rsp to access of structure
 *    that allocated in caller's frame.
 *    returning structure - caller allocates memory for returned structure, callee
 *    writes data in this memory. (+)
 * */
