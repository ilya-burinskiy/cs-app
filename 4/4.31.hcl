# cnd moves are not considered yet
word d_dstE = [
  D_icode in { IRRMOVQ } : D_rB;
  D_icode in { IIRMOVQ, IOPQ } : D_rB;
  D_icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
  1 : RNONE;
];
