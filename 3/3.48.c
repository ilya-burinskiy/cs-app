#include <string.h>

int len(char *s) {
  return strlen(s);
}

/* rdi = &s, rsi = &p */
void iptoa(char *s, long *p) {
  long val = *p;
  sprintf(s, "%ld", val);
}

/*
 * (a) Whithout protector
 * x in %rdi
 * intlen:
 *   subq $40, %rsp         alloc 40 bytes
 *   movq %rdi, 24(%rsp)    M[rsp + 24] = x
 *   leaq 24(%rsp), %rsi    rsi = rsp + 24 (&x)
 *   movq %rsp, %rdi        rdi = rsp (&buf)
 *   call iptoa
 *         v             buf
 *  |*********|**********************|
 *  A        A-16                   A-40
 *            &v                    &buf
 *
 * (b) With protector
 * x in %rdi
 * intlen:
 *   subq %40 $56, %rsp    alloc 56 bytes
 *   movq %fs:40, %rax     rax = fs:40
 *   movq %rax, 40(%rsp)   M[rsp + 40] = rax
 *   xorl %eax, %eax       eax = 0
 *   movq %rdi, 8(%rsp)    M[rsp + 8] = v
 *   leaq 8(%rsp), %rsi    rsi = &v
 *   leaq 16(%rsp), %rdi   rdi = &buf
 *   call iptoa
 *          canary          buf             v
 * |*******|******|********************|*********|**********|
 * A      A-8    A-16                 A-40      A-48       A-56
 *              &canary               &buf       &v
 * A. (a) v, buf
 *    (b) canary, buf, v
 * B. buffer overflow will overwrite canary, not v
 * */
int intlen(long x) {
  long v;
  char buf[12];
  v = x;
  iptoa(buf, &v);
  return len(buf);
}
