quote '#include <stdio.h>'
quote '#include <stdlib.h>'
quote '#include <assert.h>'

quote 'long long a_val, b_val, xor_val;'

boolsig a 'a_val'
boolsig b 'b_val'
bool xor = (a || b) && !(a && b);

quote 'int main(int argc, char **argv) {'
quote '   assert(argc == 3);'
quote '   long long a, b;'
quote '   a = atoll(argv[1]);'
quote '   b = atoll(argv[2]);'
quote '   a_val = !!a;'
quote '   b_val = !!b;'
quote '   printf("xor(%lld, %lld) = %lld\n", a, b, gen_xor());'
quote '   return 0;'
quote '}'
