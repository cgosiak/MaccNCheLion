LDA       R15,VARS
WRST      L9T0
WRNL      
WRST      L9T1
WRI       L1T0
WRST      L9T2
WRI       L2T0
WRST      L9T3
WRI       L3T0
WRST      L9T4
WRI       L4T0
WRNL      
LD        R0,L1T0
STO       R0,L1T0
WRST      L9T5
WRNL      
WRST      L9T6
WRI       L1T0
WRST      L9T7
WRI       L2T0
WRST      L9T8
WRI       L3T0
WRST      L9T9
WRI       L4T0
WRNL      
WRST      L9T10
WRNL      
LD        R0,L2T0
STO       R0,L1T0
LD        R0,L4T0
STO       R0,L1T0
LD    R7,L1T0
IA    R7,L1T0
STO   R7,L1T0
WRST      L9T11
WRI       L1T0
WRST      L9T12
WRI       L2T0
WRST      L9T13
WRI       L3T0
WRST      L9T14
WRI       L4T0
WRNL      
WRST      L9T15
WRNL      
LD        R0,L4T0
STO       R0,L1T0
WRST      L9T16
WRI       L1T0
WRST      L9T17
WRI       L2T0
WRST      L9T18
WRI       L3T0
WRST      L9T19
WRI       L4T0
WRNL      
WRST      L9T20
WRNL      
LD    R7,L1T1
IM    R7,L1T2
STO   R7,L1T2
LD    R7,L1T2
IA    R7,L1T3
STO   R7,L1T3
WRST      L9T21
WRI       L1T3
WRST      L9T22
WRI       L2T0
WRST      L9T23
WRI       L3T0
WRST      L9T24
WRI       L4T0
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       1
LABEL    L1T1
INT       2
LABEL    L1T2
INT       3
LABEL    L1T3
INT       4
LABEL    LBL2
INT   0
LABEL    L2T0
INT       5
LABEL    LBL3
INT   0
LABEL    L3T0
INT       10
LABEL    LBL4
INT   0
LABEL    L4T0
INT       20
LABEL    LBL9
SKIP    50
LABEL    L9T0
STRING    "A Should be 1:: "
LABEL    L9T1
STRING    "A::"
LABEL    L9T2
STRING    " B::"
LABEL    L9T3
STRING    " C::"
LABEL    L9T4
STRING    " D::"
LABEL    L9T5
STRING    "A Should be 1:: "
LABEL    L9T6
STRING    "A::"
LABEL    L9T7
STRING    " B::"
LABEL    L9T8
STRING    " C::"
LABEL    L9T9
STRING    " D::"
LABEL    L9T10
STRING    "A Should be 25:: "
LABEL    L9T11
STRING    "A::"
LABEL    L9T12
STRING    " B::"
LABEL    L9T13
STRING    " C::"
LABEL    L9T14
STRING    " D::"
LABEL    L9T15
STRING    "A Should be 20:: "
LABEL    L9T16
STRING    "A::"
LABEL    L9T17
STRING    " B::"
LABEL    L9T18
STRING    " C::"
LABEL    L9T19
STRING    " D::"
LABEL    L9T20
STRING    "A Should be 10:: "
LABEL    L9T21
STRING    "A::"
LABEL    L9T22
STRING    " B::"
LABEL    L9T23
STRING    " C::"
LABEL    L9T24
STRING    " D::"

LABEL     VARS
SKIP      2
