# valB or numbers
word aluB = [
  icode in { IOPQ, IRMMOVQ, IMRMOVQ, IPUSHQ, IPOPQ, ICALL, IRET } : valB;
  iocode in { IRRMOVQ, IIRMOVQ } : 0;
];
