#include <cmath>
#include <iostream>

namespace CL { namespace math {

// exact factorial for 0 <= N <= 20
// double precision for 21 <= N <= 40
// 8 significant figures for N >= 41
double dFactorial(const int & N) {
    if (N < 2) {
        return 1.0;
    }
    else {
        switch (N) {
            case  2: return 2.0;
            case  3: return 6.0;
            case  4: return 24.0;
            case  5: return 120.0;
            case  6: return 720.0;
            case  7: return 5040.0;
            case  8: return 40320.0;
            case  9: return 362880.0;
            case 10: return 3628800.0;
            case 11: return 39916800.0;
            case 12: return 479001600.0;
            case 13: return 6227020800.0;
            case 14: return 87178291200.0;
            case 15: return 1307674368e3;
            case 16: return 20922789888e3;
            case 17: return 355687428096e3;
            case 18: return 6402373705728e3;
            case 19: return 121645100408832e3;
            case 20: return 243290200817664e4;
            case 21: return 5109094217170944e4;
            case 22: return 112400072777760768e4;
            case 23: return 2585201673888497664e4;
            case 24: return 62044840173323943936e4;
            case 25: return 15511210043330985984e6;
            case 26: return 403291461126605635584e6;
            case 27: return 10888869450418352160768e6;
            case 28: return 304888344611713860501504e6;
            case 29: return 8841761993739701954543616e6;
            case 30: return 26525285981219105863630848e7;
            case 31: return 822283865417792281772556288e7;
            case 32: return 26313083693369353016721801216e7;
            case 33: return 868331761881188649551819440128e7;
            case 34: return 29523279903960414084761860964352e7;
            case 35: return 103331479663861449296666513375232e8;
            case 36: return 3719933267899012174679994481508352e8;
            case 37: return 137637530912263450463159795815809024e8;
            case 38: return 5230226174666011117600072241000742912e8;
            case 39: return 203978820811974433586402817399028973568e8;
            case 40: return 815915283247897734345611269596115894272e9;
            default:
                double temp = pow(9 * N, 3.141592653589793);
                return sqrt(6.283185307179586 * N) * pow(N / 2.718281828459045, N)
                * exp(1.0 / 12.0 / N - log(9 * N) / (temp - 1.0 / temp));
        }
    }
}

// exact double factorial for -1 <= N <= 30
// double precision for 31 <= N <= 40
// depending on factorial for N >= 41
double dFactorial2(const int & N) {
    if (N < 2) {
        return 1.0;
    }
    else {
        switch (N) {
            case  2: return 2.0;
            case  3: return 3.0;
            case  4: return 8.0;
            case  5: return 15.0;
            case  6: return 48.0;
            case  7: return 105.0;
            case  8: return 384.0;
            case  9: return 945.0;
            case 10: return 3840.0;
            case 11: return 10395.0;
            case 12: return 46080.0;
            case 13: return 135135.0;
            case 14: return 645120.0;
            case 15: return 2027025.0;
            case 16: return 10321920.0;
            case 17: return 34459425.0;
            case 18: return 185794560.0;
            case 19: return 654729075.0;
            case 20: return 3715891200.0;
            case 21: return 13749310575.0;
            case 22: return 81749606400.0;
            case 23: return 316234143225.0;
            case 24: return 1961990553600.0;
            case 25: return 7905853580625.0;
            case 26: return 51011754393600.0;
            case 27: return 213458046676875.0;
            case 28: return 14283291230208e2;
            case 29: return 6190283353629375.0;
            case 30: return 42849873690624e3;
            case 31: return 191898783962510625.0;
            case 32: return 1371195958099968000.0;
            case 33: return 6332659870762850625.0;
            case 34: return 46620662575398912000.0;
            case 35: return 221643095476699771875.0;
            case 36: return 1678343852714360832000.0;
            case 37: return 8200794532637891559375.0;
            case 38: return 63777066403145711616000.0;
            case 39: return 319830986772877770815625.0;
            case 40: return 2551082656125828464640000.0;
            default:
                if(N % 2 ==1) {
                    return dFactorial(N + 1) / (pow(2, (N + 1) / 2) * dFactorial((N + 1) / 2));
                }
                else {
                    return pow(2, N / 2) * dFactorial(N / 2);
                }
        }
    }
}

// exact permutation for 0 <= M <= 10 or N < 10
// depending on factorial otherwise
double dPermutation(const int & M, const int & N) {
    if (M < 2 || N == 0) {
        return 1.0;
    }
    else if (N == 1) {
        return (double)M;
    }
    else if (N == M || N == M - 1) {
        return dFactorial(M);
    }
    else {
        switch (M) {
        case 4: return 12.0;
        case 5:
            switch (N) {
            case 2: return 20.0;
            case 3: return 60.0;
            }
        case 6:
            switch (N) {
            case 2: return 30.0;
            case 3: return 120.0;
            case 4: return 360.0;
            }
        case 7:
            switch (N) {
            case 2: return 42.0;
            case 3: return 210.0;
            case 4: return 840.0;
            case 5: return 2520.0;
            }
        case 8:
            switch (N) {
            case 2: return 56.0;
            case 3: return 336.0;
            case 4: return 1680.0;
            case 5: return 6720.0;
            case 6: return 20160.0;
            }
        case 9:
            switch (N) {
            case 2: return 72.0;
            case 3: return 504.0;
            case 4: return 3024.0;
            case 5: return 15120.0;
            case 6: return 60480.0;
            case 7: return 181440.0;
            }
        case 10:
            switch (N) {
            case 2: return 90.0;
            case 3: return 720.0;
            case 4: return 5040.0;
            case 5: return 30240.0;
            case 6: return 151200.0;
            case 7: return 604800.0;
            case 8: return 1814400.0;
            }
        default:
            if (M < 20 && N < 10) {
                double value = M * (M - 1);
                for (size_t i = M - 2; i > M - N; i--) value *= i;
                return value;
            }
            else {
                return dFactorial(M) / dFactorial(M - N);
            }
        }
    }
}

// exact combination for 0 <= M <= 11 or (N = 0 or N = 1 or N = M - 1 or N = M)
// depending on permutation and factorial otherwise
double dCombination(const int & M, const int & N) {
    int ntemp;
    if (M < 2 || N == 0 || N == M) {
        return 1.0;
    }
    else if (N == 1 || N == M - 1) {
        return (double)M;
    }
    else {
        switch (M) {
        case 4: return 6.0;
        case 5: return 10.0;
        default:
            if (N < M / 2) {
                ntemp = M - N;
            }
            else {
                ntemp = N;
            }
            switch (M) {
            case 6:
                switch (ntemp) {
                case 4: return 15.0;
                case 3: return 20.0;
                }
            case 7:
                switch (ntemp) {
                case 5: return 21.0;
                case 4: return 35.0;
                }
            case 8:
                switch (ntemp) {
                case 6: return 28.0;
                case 5: return 56.0;
                case 4: return 70.0;
                }
            case 9:
                switch (ntemp) {
                case 7: return 36.0;
                case 6: return 84.0;
                case 5: return 126.0;
                }
            case 10:
                switch (ntemp) {
                case 8: return 45.0;
                case 7: return 120.0;
                case 6: return 210.0;
                case 5: return 252.0;
                }
            case 11:
                switch (ntemp) {
                case 9: return 55.0;
                case 8: return 165.0;
                case 7: return 330.0;
                case 6: return 462.0;
                }
            default:
                return dPermutation(M, N) / dFactorial(N);
            }
        }
    }
}

// exact factorial for N <= 20
// 8 bytes integer cannot represent N >= 21
unsigned long long iFactorial(const int & N) {
    if (N < 2) {
        return 1;
    }
    else {
        switch (N) {
        case  2: return 2;
        case  3: return 6;
        case  4: return 24;
        case  5: return 120;
        case  6: return 720;
        case  7: return 5040;
        case  8: return 40320;
        case  9: return 362880;
        case 10: return 3628800;
        case 11: return 39916800;
        case 12: return 479001600;
        case 13: return 6227020800;
        case 14: return 87178291200;
        case 15: return 1307674368000;
        case 16: return 20922789888000;
        case 17: return 355687428096000;
        case 18: return 6402373705728000;
        case 19: return 121645100408832000;
        case 20: return 2432902008176640000;
        default:
            std::cerr << "Failed integer factorial: 8 bytes integer upper limit exceeded!";
            return -1;
        }
    }
}

// exact double factorial for N <= 33
// 8 bytes integer cannot represent N >= 34
unsigned long long iFactorial2(const int & N) {
    if (N < 2) {
        return 1;
    }
    else {
        switch (N) {
            case  2: return 2;
            case  3: return 3;
            case  4: return 8;
            case  5: return 15;
            case  6: return 48;
            case  7: return 105;
            case  8: return 384;
            case  9: return 945;
            case 10: return 3840;
            case 11: return 10395;
            case 12: return 46080;
            case 13: return 135135;
            case 14: return 645120;
            case 15: return 2027025;
            case 16: return 10321920;
            case 17: return 34459425;
            case 18: return 185794560;
            case 19: return 654729075;
            case 20: return 3715891200;
            case 21: return 13749310575;
            case 22: return 81749606400;
            case 23: return 316234143225;
            case 24: return 1961990553600;
            case 25: return 7905853580625;
            case 26: return 51011754393600;
            case 27: return 213458046676875;
            case 28: return 1428329123020800;
            case 29: return 6190283353629375;
            case 30: return 42849873690624000;
            case 31: return 191898783962510625;
            case 32: return 1371195958099968000;
            case 33: return 6332659870762850625;
            default:
                std::cerr << "Failed integer double factorial: 8 bytes integer upper limit exceeded!";
                return -1;
        }
    }
}

// exact permutation for 0 <= M <= 10 or N < 10
// depending on factorial otherwise
unsigned long long iPermutation(const int & M, const int & N) {
    if (M < 2 || N == 0) {
        return 1;
    }
    else if (N == 1) {
        return M;
    }
    else if (N == M || N == M - 1) {
        return iFactorial(M);
    }
    else {
        switch (M) {
        case 4: return 12;
        case 5:
            switch (N) {
            case 2: return 20;
            case 3: return 60;
            }
        case 6:
            switch (N) {
            case 2: return 30;
            case 3: return 120;
            case 4: return 360;
            }
        case 7:
            switch (N) {
            case 2: return 42;
            case 3: return 210;
            case 4: return 840;
            case 5: return 2520;
            }
        case 8:
            switch (N) {
            case 2: return 56;
            case 3: return 336;
            case 4: return 1680;
            case 5: return 6720;
            case 6: return 20160;
            }
        case 9:
            switch (N) {
            case 2: return 72;
            case 3: return 504;
            case 4: return 3024;
            case 5: return 15120;
            case 6: return 60480;
            case 7: return 181440;
            }
        case 10:
            switch (N) {
            case 2: return 90;
            case 3: return 720;
            case 4: return 5040;
            case 5: return 30240;
            case 6: return 151200;
            case 7: return 604800;
            case 8: return 1814400;
            }
        default:
            if (M < 20 && N < 10) {
                unsigned long long value = M * (M - 1);
                for (unsigned long long i = M - 2; i > M - N; i--) value *= i;
                return value;
            }
            else {
                return iFactorial(M) / iFactorial(M - N);
            }
        }
    }
}

// exact combination for 0 <= M <= 11 or (N = 0 or N = 1 or N = M - 1 or N = M)
// depending on permutation and factorial otherwise
unsigned long long iCombination(const int & M, const int & N) {
    int ntemp;
    if (M < 2 || N == 0 || N == M) {
        return 1;
    }
    else if (N == 1 || N == M - 1) {
        return (double)M;
    }
    else {
        switch (M) {
        case 4: return 6;
        case 5: return 10;
        default:
            if (N < M / 2) {
                ntemp = M - N;
            }
            else {
                ntemp = N;
            }
            switch (M) {
            case 6:
                switch (ntemp) {
                case 4: return 15;
                case 3: return 20;
                }
            case 7:
                switch (ntemp) {
                case 5: return 21;
                case 4: return 35;
                }
            case 8:
                switch (ntemp) {
                case 6: return 28;
                case 5: return 56;
                case 4: return 70;
                }
            case 9:
                switch (ntemp) {
                case 7: return 36;
                case 6: return 84;
                case 5: return 126;
                }
            case 10:
                switch (ntemp) {
                case 8: return 45;
                case 7: return 120;
                case 6: return 210;
                case 5: return 252;
                }
            case 11:
                switch (ntemp) {
                case 9: return 55;
                case 8: return 165;
                case 7: return 330;
                case 6: return 462;
                }
            default:
                return iPermutation(M, N) / iFactorial(N);
            }
        }
    }
}

} // namespace math
} // namespace CL
