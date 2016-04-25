LDA       R15,VARS
WRST      L7T0
WRNL      
LD        R0,L2T0
STO       R0,L1T0
LD        R0,L3T0
STO       R0,L2T0
LD    R7,L2T0
IA    R7,L3T0
STO   R7,L3T0
WRST      L7T1
WRI       L1T0
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       0
LABEL    LBL2
INT   0
LABEL    L2T0
INT       9
LABEL    LBL3
INT   0
LABEL    L3T0
INT       2
LABEL    LBL7
SKIP    50
LABEL    L7T0
STRING    "A should equal 2::"
LABEL    L7T1
STRING    "A::"

LABEL     VARS
SKIP      2
