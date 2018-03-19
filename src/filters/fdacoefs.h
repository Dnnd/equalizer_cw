/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.3 and Signal Processing Toolbox 7.5.
 * Generated on: 18-Mar-2018 18:24:31
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II, Second-Order Sections
 * Number of Sections  : 24
 * Stable              : Yes
 * Linear Phase        : No
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * E:\Soft\Matlab\extern\include\tmwtypes.h 
 */
#define MWSPT_NSEC 49
const int NL[MWSPT_NSEC] = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
                            3, 1, 3, 1,
                            3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1};
const real64_T NUM[MWSPT_NSEC][3] = {
        {
                0.9578819471069,  0,                0
        },
        {
                1,                -1.979713337937,  1
        },
        {
                0.9557559007594,  0,                0
        },
        {
                1,                -1.979539368803,  1
        },
        {
                0.9532350655732,  0,                0
        },
        {
                1,                -1.97918543047,   1
        },
        {
                0.950260543802,   0,                0
        },
        {
                1,                -1.978639079177,  1
        },
        {
                0.9467568020271,  0,                0
        },
        {
                1,                -1.977880483227,  1
        },
        {
                0.9426272436957,  0,                0
        },
        {
                1,                -1.976880852761,  1
        },
        {
                0.9377480988465,  0,                0
        },
        {
                1,                -1.97560002384,   1
        },
        {
                0.9319599681343,  0,                0
        },
        {
                1,                -1.973982834196,  1
        },
        {
                0.9250560426357,  0,                0
        },
        {
                1,                -1.971953698328,  1
        },
        {
                0.916765548791,   0,                0
        },
        {
                1,                -1.96940840411,   1
        },
        {
                0.9067302594744,  0,                0
        },
        {
                1,                -1.966201481447,  1
        },
        {
                0.8944708568177,  0,                0
        },
        {
                1,                -1.962126279752,  1
        },
        {
                0.8793383983941,  0,                0
        },
        {
                1,                -1.956882609871,  1
        },
        {
                0.860444043874,   0,                0
        },
        {
                1,                -1.950022327924,  1
        },
        {
                0.8365577830798,  0,                0
        },
        {
                1,                -1.940854001196,  1
        },
        {
                0.8059656147854,  0,                0
        },
        {
                1,                -1.928267620494,  1
        },
        {
                0.7662798104755,  0,                0
        },
        {
                1,                -1.910393211453,  1
        },
        {
                0.7142255383982,  0,                0
        },
        {
                1,                -1.883888133646,  1
        },
        {
                0.6455278932684,  0,                0
        },
        {
                1,                -1.842317061823,  1
        },
        {
                0.5553174810912,  0,                0
        },
        {
                1,                -1.772058292319,  1
        },
        {
                0.4401716850669,  0,                0
        },
        {
                1,                -1.640490740898,  1
        },
        {
                0.3039227841735,  0,                0
        },
        {
                1,                -1.355985470074,  1
        },
        {
                0.1682080640087,  0,                0
        },
        {
                1,                -0.6143505138494, 1
        },
        {
                0.07802890148474, 0,                0
        },
        {
                1,                1.305138460991,   1
        },
        {
                1,                0,                0
        }
};
const int DL[MWSPT_NSEC] = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
                            3, 1, 3, 1,
                            3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1};
const real64_T DEN[MWSPT_NSEC][3] = {
        {
                1, 0,                0
        },
        {
                1, -1.978716370752,  0.9981485981089
        },
        {
                1, 0,                0
        },
        {
                1, -1.974863206662,  0.9944185756613
        },
        {
                1, 0,                0
        },
        {
                1, -1.970747439213,  0.9905886167644
        },
        {
                1, 0,                0
        },
        {
                1, -1.966279739933,  0.9865781801705
        },
        {
                1, 0,                0
        },
        {
                1, -1.961356488732,  0.9822982916946
        },
        {
                1, 0,                0
        },
        {
                1, -1.955854054022,  0.9776467920607
        },
        {
                1, 0,                0
        },
        {
                1, -1.949621389666,  0.9725024209221
        },
        {
                1, 0,                0
        },
        {
                1, -1.942470169572,  0.9667171265859
        },
        {
                1, 0,                0
        },
        {
                1, -1.934161342973,  0.9601057438078
        },
        {
                1, 0,                0
        },
        {
                1, -1.924386478801,  0.952431799995
        },
        {
                1, 0,                0
        },
        {
                1, -1.912741488764,  0.9433876282617
        },
        {
                1, 0,                0
        },
        {
                1, -1.898689153721,  0.932566092722
        },
        {
                1, 0,                0
        },
        {
                1, -1.881505181395,  0.9194199581738
        },
        {
                1, 0,                0
        },
        {
                1, -1.860200204981,  0.9032031952458
        },
        {
                1, 0,                0
        },
        {
                1, -1.833407456652,  0.8828865022892
        },
        {
                1, 0,                0
        },
        {
                1, -1.799224420137,  0.8570382514857
        },
        {
                1, 0,                0
        },
        {
                1, -1.755002512911,  0.8236663858564
        },
        {
                1, 0,                0
        },
        {
                1, -1.697110586429,  0.7800406466901
        },
        {
                1, 0,                0
        },
        {
                1, -1.620809696208,  0.7225984310936
        },
        {
                1, 0,                0
        },
        {
                1, -1.520702489412,  0.6472825043574
        },
        {
                1, 0,                0
        },
        {
                1, -1.392995090413,  0.5512408867887
        },
        {
                1, 0,                0
        },
        {
                1, -1.241933024169,  0.437663713152
        },
        {
                1, 0,                0
        },
        {
                1, -1.091491724054,  0.3245691415143
        },
        {
                1, 0,                0
        },
        {
                1, -0.9915365130197, 0.2494328363858
        },
        {
                1, 0,                0
        }
};