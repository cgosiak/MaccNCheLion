LDA       R15,VARS
LD        R0,L1T0
STO       R0,L1T0
LD    R7,L1T0
IA    R7,L1T1
STO   R7,L1T1
WRST      L9T0
WRI       L1T1
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       0
LABEL    L1T1
INT       1
LABEL    LBL8
INT   0
LABEL    L8T0
INT       5
LABEL    LBL9
SKIP    50
LABEL    L9T0
STRING    "TEST"

LABEL     VARS
SKIP      2
