LDA       R15,VARS
WRNL
WRST      L5T0
WRI       L1T1
WRNL      
WRNL
WRST      L5T1
WRF       L2T2
WRNL      
WRNL
WRST      L5T2
WRF       L3T2
WRNL      
WRNL
WRST      L5T3
WRI       L4T4
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       3
LABEL    L1T1
INT       5
LABEL    LBL2
REAL   0.0
LABEL    L2T0
REAL      2.3
LABEL    L2T1
REAL      7.1
LABEL    L2T2
REAL      5.0
LABEL    LBL3
REAL   0.0
LABEL    L3T0
REAL      5.0
LABEL    L3T1
REAL      3.6
LABEL    L3T2
REAL      2.9
LABEL    LBL4
INT   0
LABEL    L4T0
INT       2
LABEL    L4T1
INT       6
LABEL    L4T2
INT       9
LABEL    L4T3
INT       8
LABEL    L4T4
INT       7
LABEL    LBL5
SKIP    50
LABEL    L5T0
STRING    "x ="
LABEL    L5T1
STRING    "y ="
LABEL    L5T2
STRING    "z ="
LABEL    L5T3
STRING    "n ="

LABEL     VARS
SKIP      2
