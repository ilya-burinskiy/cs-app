/*
 * A. Offsets:
 * e1.p    0
 * e1.y    8
 * e2.x    0
 * e2.next 8
 *
 * B. sizeof(union ele) = 16
 * */
union ele {
  struct {
    long *p;
    long y;
  } e1;
  struct {
    long x;
    union ele *next;
  } e2;
};

/*
 *   x   next  ...   p      y
 *   ^     ^
 *   |     |
 *  rdi  8(rdi)
 *
 *  rax = M[rdi + 8]
 *  rdx = rdx - M[rax + 8]
 *
 * proc:
 *   movq 8(%rdi), %rax        rax = up->e2.next
 *   movq (%rax), %rdx         rdx = *(up->e2.next)
 *   movq (%rdx), %rdx         rdx = *(up->e2.next->e1.p)
 *   subq 8(%rax), %rdx        rdx = rdx - M[up->e2.next + 8]
 *   movq %rdx, %(rdi)         up->e2.x = rdx
 * */
void proc(union ele *up) {
  up->e2.x = *(up->e2.next.e1->p) - up->e2.y;
}
