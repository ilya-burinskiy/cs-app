# OPq rA, rB       (valB <- R[rB])
# rmmovq rA, D(rB) (valB <- R[rB])
# mrmovq D(rB), rA (valB <- R[rB])
# pushq rA         (valB <- R[%rsp])
# popq rA          (valB <- R[%rsp])
# call Dest        (valB <- R[%rsp])
# ret              (valB <- R[%rsp])
word srcB = [
  icode in { IOPQ, IRMMOVQ, IMRMOVQ } : rB;
  icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
  1 : RNONE;
];
