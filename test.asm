LDA       R15,VARS
WRST      L7T0
WRNL      
WRST      L7T1
WRI       L1T0
WRNL      
LD    R4,L1T0
LD    R5,L2T0
IC    R4,R5
JLT    STM0
JMP    JMP0
LABEL    STM0
WRST      L7T2
WRNL      
LABEL    JMP0

LD    R4,L1T0
LD    R5,L2T0
IC    R4,R5
JGT    STM1
JMP    JMP1
LABEL    STM1
WRST      L7T3
WRNL      
LABEL    JMP1

LD    R4,L1T0
LD    R5,L2T0
IC    R4,R5
JEQ    STM2
JMP    JMP2
LABEL    STM2
WRST      L7T4
WRNL      
LABEL    JMP2

LD    R4,L1T0
LD    R5,L2T0
IC    R4,R5
JNE    STM3
JMP    JMP3
LABEL    STM3
WRST      L7T5
WRNL      
LABEL    JMP3

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
INT       9
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
LABEL    L7T4
STRING    "A is equal to b"
LABEL    L7T5
STRING    "A is not equal to b"

LABEL     VARS
SKIP      2
