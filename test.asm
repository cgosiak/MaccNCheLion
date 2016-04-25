LDA       R15,VARS
WRST      L7T0
WRNL      
LD    R7,L1T0
ID    R7,L1T1
STO   R7,L1T1
LD    R7,L1T1
IM    R7,L1T2
STO   R7,L1T2
LD    R7,L1T3
IA    R7,L1T4
STO   R7,L1T4
LD    R7,L1T2
ID    R7,L1T4
STO   R7,L1T4
WRST      L7T1
WRI       L1T4
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       10
LABEL    L1T1
INT       5
LABEL    L1T2
INT       10
LABEL    L1T3
INT       2
LABEL    L1T4
INT       7
LABEL    LBL7
SKIP    50
LABEL    L7T0
STRING    "A should equal 14::"
LABEL    L7T1
STRING    "A::"

LABEL     VARS
SKIP      2
