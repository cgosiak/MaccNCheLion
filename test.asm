LDA       R15,VARS
WRST      L6T0
WRI       L1T0
WRNL      
WRST      L6T1
WRI       L2T0
WRNL      
LD        R0,L2T0
STO       R0,L1T0
WRST      L6T2
WRI       L1T0
WRNL      
WRST      L6T3
WRST      L4T0
WRNL
      
LD        R0,L5T0
STO       R0,L4T1

WRST      L6T4
WRST      L4T1

WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       10
LABEL    LBL2
INT   0
LABEL    L2T0
INT       276
LABEL    LBL4
SKIP    50
LABEL    L4T0
STRING    "Test1"
LABEL    L4T1
SKIP      50
LABEL    LBL5
SKIP    50
LABEL    L5T0
STRING    "FIRETRUCK 2 DAWG!"
LABEL    LBL6
SKIP    50
LABEL    L6T0
STRING    "A:: "
LABEL    L6T1
STRING    "B:: "
LABEL    L6T2
STRING    "A = B:: "
LABEL    L6T3
STRING    "Y:: "
LABEL    L6T4
STRING    "Y:: "

LABEL     VARS
SKIP      2
