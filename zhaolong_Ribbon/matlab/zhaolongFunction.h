//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Thu Dec  1 12:46:59 2022
// Arguments:
// "-B""macro_default""-W""cpplib:zhaolongFunction,all,version=1.0""-T""link:lib
// ""-d""E:\Stuff_For_QtProject\zhaolongFunction\for_testing""-v""E:\Stuff_For_Q
// tProject\cascade_cable_and_connector_function12_1.m""E:\Stuff_For_QtProject\f
// ar_field_two_cables_function.m""E:\Stuff_For_QtProject\TBTWPfunction.m""E:\St
// uff_For_QtProject\TWP_far_filed_function.m""E:\Stuff_For_QtProject\zhaolong_c
// ableFunction12_1.m""E:\Stuff_For_QtProject\zhaolong_twinax_cable_oussama_2.m"
//

#ifndef zhaolongFunction_h
#define zhaolongFunction_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_zhaolongFunction_C_API 
#define LIB_zhaolongFunction_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV zhaolongFunctionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV zhaolongFunctionInitialize(void);

extern LIB_zhaolongFunction_C_API 
void MW_CALL_CONV zhaolongFunctionTerminate(void);

extern LIB_zhaolongFunction_C_API 
void MW_CALL_CONV zhaolongFunctionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV mlxCascade_cable_and_connector_function12_1(int nlhs, mxArray *plhs[], 
                                                              int nrhs, mxArray *prhs[]);

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV mlxFar_field_two_cables_function(int nlhs, mxArray *plhs[], int nrhs, 
                                                   mxArray *prhs[]);

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV mlxTBTWPfunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV mlxTWP_far_filed_function(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                            *prhs[]);

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV mlxZhaolong_cableFunction12_1(int nlhs, mxArray *plhs[], int nrhs, 
                                                mxArray *prhs[]);

extern LIB_zhaolongFunction_C_API 
bool MW_CALL_CONV mlxZhaolong_twinax_cable_oussama_2(int nlhs, mxArray *plhs[], int nrhs, 
                                                     mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_zhaolongFunction
#define PUBLIC_zhaolongFunction_CPP_API __declspec(dllexport)
#else
#define PUBLIC_zhaolongFunction_CPP_API __declspec(dllimport)
#endif

#define LIB_zhaolongFunction_CPP_API PUBLIC_zhaolongFunction_CPP_API

#else

#if !defined(LIB_zhaolongFunction_CPP_API)
#if defined(LIB_zhaolongFunction_C_API)
#define LIB_zhaolongFunction_CPP_API LIB_zhaolongFunction_C_API
#else
#define LIB_zhaolongFunction_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_zhaolongFunction_CPP_API void MW_CALL_CONV cascade_cable_and_connector_function12_1(int nargout, mwArray& sdd11, mwArray& sdd12, mwArray& sdd21, mwArray& sdd22, mwArray& sdc11, mwArray& sdc12, mwArray& sdc21, mwArray& sdc22, mwArray& scd11, mwArray& scd12, mwArray& scd21, mwArray& scd22, mwArray& scc11, mwArray& scc12, mwArray& scc21, mwArray& scc22, const mwArray& path1, const mwArray& path2);

extern LIB_zhaolongFunction_CPP_API void MW_CALL_CONV far_field_two_cables_function(int nargout, mwArray& f, mwArray& gcm, mwArray& hdm, const mwArray& s, const mwArray& h, const mwArray& rw1, const mwArray& rw2, const mwArray& L, const mwArray& E0, const mwArray& thetaE, const mwArray& thetaP, const mwArray& phiP);

extern LIB_zhaolongFunction_CPP_API void MW_CALL_CONV TBTWPfunction(int nargout, mwArray& gcm, mwArray& hdm, const mwArray& Lz, const mwArray& rw, const mwArray& h, const mwArray& x0, const mwArray& y0, const mwArray& z0, const mwArray& P0, const mwArray& theta, const mwArray& phi);

extern LIB_zhaolongFunction_CPP_API void MW_CALL_CONV TWP_far_filed_function(int nargout, mwArray& f, mwArray& gcm, mwArray& hdm, const mwArray& Lz, const mwArray& p, const mwArray& s, const mwArray& h, const mwArray& rw1, const mwArray& rw2, const mwArray& E0, const mwArray& thetaE, const mwArray& thetaP, const mwArray& phiP);

extern LIB_zhaolongFunction_CPP_API void MW_CALL_CONV zhaolong_cableFunction12_1(int nargout, mwArray& sdd11, mwArray& sdd12, mwArray& sdd21, mwArray& sdd22, mwArray& sdc11, mwArray& sdc12, mwArray& sdc21, mwArray& sdc22, mwArray& scd11, mwArray& scd12, mwArray& scd21, mwArray& scd22, mwArray& scc11, mwArray& scc12, mwArray& scc21, mwArray& scc22, mwArray& f, const mwArray& rw, const mwArray& D, const mwArray& rsh, const mwArray& epsir, const mwArray& TanLoss, const mwArray& tsh, const mwArray& Lz, const mwArray& segmaAL, const mwArray& segmaCu, const mwArray& slot_d, const mwArray& name, const mwArray& fmax, const mwArray& fmin, const mwArray& type);

extern LIB_zhaolongFunction_CPP_API void MW_CALL_CONV zhaolong_twinax_cable_oussama_2(int nargout, mwArray& s_params2, mwArray& sscd21, mwArray& sscd11, mwArray& sscc21, mwArray& sscc11, mwArray& ssdd21, mwArray& ssdd11, mwArray& f, const mwArray& rw, const mwArray& rsh, const mwArray& epsir, const mwArray& TanLoss, const mwArray& tsh, const mwArray& Lz, const mwArray& segmaAL, const mwArray& segmaCu, const mwArray& xd1, const mwArray& xd2, const mwArray& slot_d, const mwArray& fmin, const mwArray& fmax, const mwArray& Np, const mwArray& type);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
