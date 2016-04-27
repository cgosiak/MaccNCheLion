LDA       R15,VARS
WRST      L7T0
WRNL      
WRST      L7T1
WRI       L1T0
WRNL      
LD    R4,L1T0
LD    R5,L8T0
IC    R4,R5
JLT    STM0
JMP    JMP0
LABEL    STM0
WRST      L7T2
WRNL      
JMP    END0
LABEL    JMP0

WRST      L7T3
WRNL      
LABEL    END0
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
INT       4
LABEL    LBL3
INT   0
LABEL    L3T0
INT       2
LABEL    LBL7
SKIP    50
LABEL    L7T0
STRING    "A should equal 11::"
LABEL    L7T1
STRING    "A::"
LABEL    L7T2
STRING    "A is smaller"
LABEL    L7T3
STRING    "A is larger"
LABEL    LBL8
INT   0
LABEL    L8T0
INT       15

LABEL     VARS
SKIP      2
