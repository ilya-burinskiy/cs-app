/*
 * called get_line
 * return addr is 0x400776
 * rbx = 0x0123456789abcdef
 * input = 0123456789012345678901234
 *
 * 0000000000400720 <get_line>:
 *   400720: 53               push %rbx
 *   400721: 48 83 ec 10      sub $0x10, %rsp
 *
 *   # Diagram stack at this point
 *
 *   400725: 48 89 e7         mov %rsp, %rdi
 *   400728: e8 73 ff ff ff   callq 4006a0 <gets>
 *
 *   # Modify diagram to show stack contents at this point
 *
 *
 * A. Diagram before gets +
 * 
 *            7  6  5  4  3  2  1  0
 * ret addr  00 00 00 00 00 40 07 76
 * rbx       01 23 45 67 89 ab cd ef
 * buf       xx xx xx xx xx xx xx xx
 *           xx xx xx xx xx xx xx xx rsp
 *
 * B. Diagram after gets +
 * 
 *            7  6  5  4  3  2  1  0
 * ret addr  00 00 00 00 00 40 07 34
 * rbx       33 32 31 30 39 38 37 36
 * buf       35 34 33 32 31 30 39 38
 *           37 36 35 34 33 32 31 30 rsp
 *
 * C. Return addr = 0x0000000000400734 +
 * D. %rbx, ?%rip (because return addr changed) +-
 * E. malloc returning null pointer +
 *    memory leak -
 *    (should add 1 to strlen(buf) for terminating character)
 * */
char *get_line() {
  char buf[4];
  char *result;
  gets(buf);
  result = malloc(strlen(buf));
  strcpy(result, buf);
  return result;
}
