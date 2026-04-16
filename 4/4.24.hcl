word dstE = [
  icode == IRRMOVQ && Cnd  : rB;
  icode in { IIRMOVQ, IOPQ } : rB;
  icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
  1 : RNONE;
];
