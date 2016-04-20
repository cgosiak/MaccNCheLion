LDA       R15,VARS
WRST      L4T0
WRI       L2T0
WRI       L3T0
WRST      L5T0
WRI       L10T0
WRNL      
WRST      L4T1
WRNL      
WRST      L4T2
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       1
LABEL    LBL2
INT   0
LABEL    L2T0
INT       2
LABEL    LBL3
INT   0
LABEL    L3T0
INT       3
LABEL    LBL4
STRING   ""
LABEL    L4T0
STRING    "test"
LABEL    L4T1
STRING    "Caleb Says::"
LABEL    L4T2
STRING    "TEST OVER"
LABEL    LBL5
STRING   ""
LABEL    L5T0
STRING    "complete"
LABEL    LBL10
INT   0
LABEL    L10T0
INT       0

LABEL     VARS
SKIP      2
