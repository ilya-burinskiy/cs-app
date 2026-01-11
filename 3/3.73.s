.globl find_range2

# x in xmm0
find_range2:
  vxorps %xmm1, %xmm1, %xmm1    # xmm1 = 0
  vucomiss %xmm1, %xmm0          # x:0
  jp .nan                          # goto .nan if x is NaN
  jb .below0                       # x < 0
  ja .above0                       # x > 0
  je .zero                         # x = 0
.nan:
  movl $3, %eax                  # res = OTHER
  ret
.below0:
  movl $0, %eax                   # res = NEG
  ret
.above0:
  movl $2, %eax                  # res = POS
  ret
.zero:
  movl $1, % eax                  # res = ZERO
  ret
