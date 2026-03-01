quote '#include <stdio.h>'
quote '#include <stdlib.h>'
quote 'long long code_val, s0_val, s1_val;'
quote 'char **data_names;'

## Declarations of signals used in the HCL description and
## the corresponding C expressions.
boolsig s0 's0_val'
boolsig s1 's1_val'
wordsig code 'code_val'
wordsig A 'atoll(data_names[0])'
wordsig B 'atoll(data_names[1])'
wordsig C 'atoll(data_names[2])'
wordsig D 'atoll(data_names[3])'

## HCL descriptions of the logic blocks
bool s1 = code in { 2, 3 };

bool s0 = code in { 1, 3 };

word Out4 = [
  !s1 && !s0 : A; # 00
  !s1        : B; # 01
  !s0        : C; # 10
  1          : D; # 11
];

## More information inserted verbatim into the C code to
## compute the values and print the output
quote 'int main(int argc, char *argv[]) {'
quote ' data_names = argv+2;'
quote ' code_val = atoll(argv[1]);'
quote ' s1_val = gen_s1();'
quote ' s0_val = gen_s0();'
quote ' printf("Out = %lld\n", gen_Out4());'
quote ' return 0;'
quote '}'
