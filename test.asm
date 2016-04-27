LDA       R15,VARS
LD    R4,L8T0
LD    R5,L5T0
FC    R4,R5
JLT    STM0
JMP    JMP0
LABEL    STM0
WRF       L8T1
WRST      L9T0
WRF       L5T0
WRNL      
JMP    END0
LABEL    JMP0

WRF       L5T0
WRST      L9T1
WRF       L8T2
WRNL      
LABEL    END0
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL4
REAL   0.0
LABEL    L4T0
REAL      1.3
LABEL    LBL5
REAL   0.0
LABEL    L5T0
REAL      1.6
LABEL    LBL8
REAL   0.0
LABEL    L8T0
REAL      1.4
LABEL    L8T1
REAL      1.4
LABEL    L8T2
REAL      1.4
LABEL    LBL9
SKIP    50
LABEL    L9T0
STRING    " is smaller than "
LABEL    L9T1
STRING    " is smaller than "

LABEL     VARS
SKIP      2
