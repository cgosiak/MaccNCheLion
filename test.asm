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
LDA       R0,L5T0
LD        R1,#50
BKT       R0,L4T1
WRST      L6T4
WRST      L4T1
WRST      L6T5
WRNL      
LDA       R0,L5T1
LD        R1,#50
BKT       R0,L4T2
WRST      L6T6
WRST      L4T2
WRNL      
WRST      L6T7
WRNL      
RDST      L4T3
WRST      L6T8
WRST      L4T3
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
LABEL    L4T2
SKIP      50
LABEL    L4T3
STRING    ""
LABEL    LBL5
SKIP    50
LABEL    L5T0
STRING    "FIRE IS BAD!"
LABEL    L5T1
STRING    "whoa"
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
LABEL    L6T5
STRING    "Caleb"
LABEL    L6T6
STRING    "Y:: "
LABEL    L6T7
STRING    "Please Enter a string::"
LABEL    L6T8
STRING    "Y:: "

LABEL     VARS
SKIP      2
