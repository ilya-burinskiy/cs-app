/*
 * idivq S    R[%rdx] <- R[%rdx]:R[%rax] mod S
 *            R[%rax] <- R[%rdx]:R[%rax] / S
 *
 * x in %rdi, y in %rsi, z in %rdx
 * test:
 *   leaq (%rdx, %rsi), %rax  # rax <- z + y
 *   subq %rdi, %rax          # rax <- z + y - x
 *   cmpq $5, %rdx            # cmp z:5
 *   jle .L2                  # if <= goto .L2
 *   cmpq $2, %rsi            # cmp y:2
 *   jle .L3                  # if <= goto .L3
 *   movq %rdi, %rax          # rax <- x
 *   cqto
 *   idivq %rdx               # rax <- x / z
 *   ret
 * .L3:
 *   movq %rdi, %rax          # rax <- x
 *   idivq %rsi               # rax <- x / y
 *   ret
 * .L2:
 *   cmpq $3, %rdx            # cmp z:3
 *   jge .L4                  # if <= goto .L4
 *   movq %rdx, %rax          # rax <- z
 *   cqto
 *   idivq %rsi               # rax <- z / y
 * .L4:
 *   rep; ret
 * */

long test(long x, long y, long z) {
  short val = z + y - x;
  if (z > 5) {
    if (y > 2) {
      val = x / z;
    } else {
      val = x / y;
    }
  } else if (z > 3) {
    val = z / y;
  }
  return val;
}
