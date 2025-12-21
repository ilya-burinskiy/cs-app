/*
 * A. Offsets +
 *   p:    0
 *   s.x:  8
 *   s.y:  12
 *   next: 16
 * B. sizeof(struct prob) = 24 +
 * */
struct prob {
  int *p;
  struct {
    int x;
    int y;
  } s;
  struct prob *next;
};

/*
 * rdi <- sp
 * sp_init:
 *   movl 12(%rdi), %eax        eax      = sp->y
 *   movl %eax, 8(%rdi)         sp.x     = sp->y
 *   leaq 8(%rdi), %rax         rax      = &(sp->x)
 *   movq %rax, (%rdi)          sp->p    = rax
 *   movq %rdi, 16(%rdi)        sp->next = sp        
 *   ret
 * */
void sp_init(struct prob *sp) {
  sp->s.x = sp->y;  /* + */
  sp->p = &(sp->x); /* + */
  sp->next = sp;    /* + */
}
