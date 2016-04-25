LDA       R15,VARS
WRST      L5T0
WRNL      
RDI       L1T0
WRI       L1T0
WRST      L5T1
WRNL      
LD        R0,L1T0
STO       R0
WRI       
WRST      L5T2
WRNL      
WRI       L1T1
WRST      L5T3
WRNL      
WRST      L5T4
WRNL      
RDST      L3T0
WRST      L3T0
WRST      L5T5
WRNL      
LDA       R0,L3T0
LD        R1,#50
BKT       R0,L4T0
WRST      L4T0
WRST      L5T6
WRNL      
WRST      L3T1
WRST      L5T7
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       0
LABEL    L1T1
INT       17
LABEL    LBL3
SKIP    50
LABEL    L3T0
STRING    ""
LABEL    L3T1
STRING    "$"
LABEL    LBL4

LABEL    L4T0
SKIP      50
LABEL    LBL5
SKIP    50
LABEL    L5T0
STRING    "Enter an integer:: "
LABEL    L5T1
STRING    ""
LABEL    L5T2
STRING    ""
LABEL    L5T3
STRING    ""
LABEL    L5T4
STRING    "Enter a character:: "
LABEL    L5T5
STRING    ""
LABEL    L5T6
STRING    ""
LABEL    L5T7
STRING    ""

LABEL     VARS
SKIP      2
