# SAOK - status code for normal operation
# SADR - status code for address exception
# SINS - status code for illegal instruction exception
# SHLT - status code for halt
word Stat = [
  !instr_valid : SINS;
  icode == IHALT : SHLT;
  imem_error || dmem_error : SADR;
  1 : SAOK;  
];
