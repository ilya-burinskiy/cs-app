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
 *   7  6  5  4  3  2  1  0
 *   0  0  0  0  0  0  0 76  return addr
 *
 *   saved rbx   (8)
 *   buf         (10) 
 *   return addr (8)
 *
 * */
char *get_line() {
  char buf[4];
  char *result;
  gets(buf);
  result = malloc(strlen(buf));
  strcpy(result, buf);
  return result;
}
