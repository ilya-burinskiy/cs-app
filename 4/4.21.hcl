word dstM = [
  icode in { IMRMOVQ, IPOPQ } : rA;
  # icode == IRET : pc (because it PC update stage)
  1 : RNONE;
];
