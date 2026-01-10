#define CNT 7 

typedef struct {
  long idx;
  long x[4];
} a_struct;

typedef struct {
  int first;
  a_struct a[CNT];
  int last;
} b_struct;

/*
 * i in rdi, bp in rsi
 * test:
 *   mov 0x120(%rsi),%ecx        ecx = bp->last
 *   add (%rsi),%ecx             ecx = bp->last + bp->first
 *   lea (%rdi,%rdi,4),%rax      rax = 5*i
 *   lea (%rsi,%rax,8),%rax      rax = bp + 40*i
 *   mov 0x8(%rax),%rdx          rdx = M[bp + 8 + 40*i]                   a[i]
 *   movslq %ecx, %rcx           rcx = (long) (bp->last + bp->first)
 *   mov %rcx,0x10(%rax,%rdx,8)  M[16 + (bp + 40*i) + 8*M[8 + bp + 40*i]] = rcx
 *
 * 4 + padding + CNT*sizeof(a_struct) = 0x120 = 288
 * padding + CNT*sizeof(a_struct) = 0x11c = 284
 * 4 + CNT*40 = 284
 * CNT = 7
 *
 * a[i] = &a[0] + sizeof(a_struct)*i
 * a[i] = &(bp + padding) + sizeof(a_struct)*i
 * padding          = 8
 * sizeof(a_struct) = 40
 * a[i] = bp + 8 + 40*i
 *
 * x[j] = &x[0] + sizeof(x_elem) * j
 * a[i].x[a[i].idx] = a[i].x[bp + 8 + 40*i + idx_bias]
 * = bp + 8 + 40*i + x_bias + sizeof(x_elem)*(bp + 8 + 40*i + idx_bias)
 *
 * idx_bias = 0
 * x_bias = 8
 * sizeof(x_elem) = 8
 *
 * = bp + 8 + 40*i + 8 + 8*(bp + 8 + 40*i)
 * = (bp + 8 + 40*i) + 8 + 8*(bp + 8 + 40*i)
 * */
void test(long i, b_struct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}
