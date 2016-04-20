LDA       R15,VARS
WRST      L4T0
WRNL      
RDST      L4T1
WRST      L4T1
WRNL      
RDST      L4T2
WRST      L4T2
WRNL      
WRST      L11T0
WRNL      
RDI       L1T0
RDI       L2T0
RDI       L3T0
WRI       L1T0
WRST      L11T1
WRI       L2T0
WRST      L11T2
WRI       L3T0
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
INT       0
LABEL    LBL3
INT   0
LABEL    L3T0
INT       0
LABEL    LBL4
STRING   ""
LABEL    L4T0
STRING    "Test"
LABEL    L4T1
STRING    ""
LABEL    L4T2
STRING    ""
LABEL    LBL11
STRING   ""
LABEL    L11T0
STRING    "Type 3 Integers (Each separated by a newline)::"
LABEL    L11T1
STRING    " "
LABEL    L11T2
STRING    " "

LABEL     VARS
SKIP      2
