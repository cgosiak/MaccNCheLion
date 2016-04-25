LDA       R15,VARS
WRST      L7T0
WRNL      
LD    R7,L1T0
IA    R7,L1T1
STO   R7,L1T1
LD    R7,L1T1
IA    R7,L1T2
STO   R7,L1T2
WRST      L7T1
WRI       L1T2
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       10
LABEL    L1T1
INT       1
LABEL    L1T2
INT       3
LABEL    LBL7
SKIP    50
LABEL    L7T0
STRING    "A should equal 4::"
LABEL    L7T1
STRING    "A::"

LABEL     VARS
SKIP      2
