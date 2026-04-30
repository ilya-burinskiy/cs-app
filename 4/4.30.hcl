# Instr valid, Need regids, Need valC same for SEQ
# test for a memory error due to an out-of-range instruction address
# detect illegal instruction or halt instruction
# detecting invalid address must be deferred to the memory stage
# SAOK - status code for normal operation
# SADR - status code for address exception
# SINS - status code for illegal instruction exception
# SHLT - status code for halt
word f_stat = [
  !instr_valid : SINS;
  f_icode == IHALT : SHLT;
  imem_error : SADR;
  1 : SAOK;  
];
