/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.4 and Signal Processing Toolbox 8.0.
 * Generated on: 18-Jun-2018 00:41:33
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
     0.8803947000322,                 0,                 0 
  },
  {
                   1,    1.915765671952,                 1 
  },
  {
     0.8803947000322,                 0,                 0 
  },
  {
                   1,    1.298597873911,                 1 
  },
  {
     0.8515963250021,                 0,                 0 
  },
  {
                   1,    1.919555331136,                 1 
  },
  {
     0.8515963250021,                 0,                 0 
  },
  {
                   1,    1.270996333106,                 1 
  },
  {
     0.8111824702495,                 0,                 0 
  },
  {
                   1,    1.927318343333,                 1 
  },
  {
     0.8111824702495,                 0,                 0 
  },
  {
                   1,    1.207282234611,                 1 
  },
  {
     0.7531631277171,                 0,                 0 
  },
  {
                   1,    1.939320764201,                 1 
  },
  {
     0.7531631277171,                 0,                 0 
  },
  {
                   1,    1.084145919948,                 1 
  },
  {
     0.6697884082042,                 0,                 0 
  },
  {
                   1,     1.95555696815,                 1 
  },
  {
     0.6697884082042,                 0,                 0 
  },
  {
                   1,   0.8427015795336,                 1 
  },
  {
     0.5556593689538,                 0,                 0 
  },
  {
                   1,    1.974751947613,                 1 
  },
  {
     0.5556593689538,                 0,                 0 
  },
  {
                   1,   0.3254474020465,                 1 
  },
  {
     0.4258499554807,                 0,                 0 
  },
  {
                   1,    1.992377862451,                 1 
  },
  {
     0.4258499554807,                 0,                 0 
  },
  {
                   1,   -0.822101921742,                 1 
  },
  {
     0.3565209249081,                 0,                 0 
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
                   1,    1.344696522955,   0.9668272588939 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.891605533059,   0.9860163604009 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.284921447348,   0.8983231505163 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.866375190708,   0.9571358209091 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.204716907071,   0.8179626360026 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.839570319577,   0.9244331902472 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.097714474215,   0.7141710898387 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.807220414892,   0.8842404146948 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,     1.76355757833,   0.8316554887691 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    0.962648971123,   0.5756175138718 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.699263614637,   0.7595162946319 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   0.8182436214869,   0.4009538328403 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.597383781064,   0.6561877932261 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   0.7308586423755,    0.226143165967 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,    1.123905553087,   0.2869581501837 
  },
  {
                   1,                 0,                 0 
  }
};