/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.4 and Signal Processing Toolbox 8.0.
 * Generated on: 18-Jun-2018 00:39:20
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II, Second-Order Sections
 * Number of Sections  : 15
 * Stable              : Yes
 * Linear Phase        : No
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * E:\Soft\Matlab2018a\extern\include\tmwtypes.h 
 */
#define MWSPT_NSEC 31
const int NL[MWSPT_NSEC] = { 1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1 };
const real64_T NUM[MWSPT_NSEC][3] = {
  {
     0.8815547092553,                 0,                 0 
  },
  {
                   1,   -1.979785546875,                 1 
  },
  {
     0.8815547092553,                 0,                 0 
  },
  {
                   1,   -1.948965633562,                 1 
  },
  {
     0.8692321303784,                 0,                 0 
  },
  {
                   1,      -1.980202267,                 1 
  },
  {
     0.8692321303784,                 0,                 0 
  },
  {
                   1,   -1.947900023739,                 1 
  },
  {
     0.8447784754455,                 0,                 0 
  },
  {
                   1,   -1.981103902033,                 1 
  },
  {
     0.8447784754455,                 0,                 0 
  },
  {
                   1,   -1.945435766697,                 1 
  },
  {
     0.8011641618822,                 0,                 0 
  },
  {
                   1,   -1.982651875979,                 1 
  },
  {
     0.8011641618822,                 0,                 0 
  },
  {
                   1,   -1.940616512369,                 1 
  },
  {
     0.7239469318015,                 0,                 0 
  },
  {
                   1,   -1.985162293257,                 1 
  },
  {
     0.7239469318015,                 0,                 0 
  },
  {
                   1,   -1.930700377463,                 1 
  },
  {
     0.5858439114753,                 0,                 0 
  },
  {
                   1,   -1.989202434283,                 1 
  },
  {
     0.5858439114753,                 0,                 0 
  },
  {
                   1,   -1.905290133782,                 1 
  },
  {
     0.3497133807947,                 0,                 0 
  },
  {
                   1,    -1.99533292693,                 1 
  },
  {
     0.3497133807947,                 0,                 0 
  },
  {
                   1,   -1.787182977842,                 1 
  },
  {
    0.07333671451699,                 0,                 0 
  },
  {
                   1,                 0,                -1 
  },
  {
                   1,                 0,                 0 
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1 };
const real64_T DEN[MWSPT_NSEC][3] = {
  {
                   1,                 0,                 0 
  },
  {
                   1,    -1.94737595838,   0.9956403921563 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.975787181374,   0.9970925217505 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    -1.93768034012,   0.9862025007309 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.969850325096,   0.9908751477744 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.925078624548,   0.9742815561363 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.962760821624,    0.983288820579 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.907145512876,   0.9573136062921 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.953083597939,   0.9729351831957 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    -1.88062562253,   0.9315189878068 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.938371841432,   0.9575275238081 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.844005260892,   0.8936808547389 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.914278536421,   0.9332817431011 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.874424019175,   0.8956195429531 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.810989314595,   0.8537781371932 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.823536719868,    0.853326570966 
  },
  {
                   1,                 0,                 0 
  }
};
