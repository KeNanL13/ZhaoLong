//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Mon May 30 14:19:20 2022
// Arguments:
// "-B""macro_default""-W""cpplib:zhaolong_cableFunction,all,version=1.0""-T""li
// nk:lib""-d""E:\Stuff_For_QtProject\zhaolong_cableFunction\for_testing""-v""E:
// \Stuff_For_QtProject\zhaolong_cableFunction.m""E:\Stuff_For_QtProject\zhaolon
// g_twinax_cable_oussama_1.m"
//

#ifndef zhaolong_cableFunction_h
#define zhaolong_cableFunction_h 1

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
#ifndef LIB_zhaolong_cableFunction_C_API 
#define LIB_zhaolong_cableFunction_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_zhaolong_cableFunction_C_API 
bool MW_CALL_CONV zhaolong_cableFunctionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_zhaolong_cableFunction_C_API 
bool MW_CALL_CONV zhaolong_cableFunctionInitialize(void);

extern LIB_zhaolong_cableFunction_C_API 
void MW_CALL_CONV zhaolong_cableFunctionTerminate(void);

extern LIB_zhaolong_cableFunction_C_API 
void MW_CALL_CONV zhaolong_cableFunctionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_zhaolong_cableFunction_C_API 
bool MW_CALL_CONV mlxZhaolong_cableFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                            *prhs[]);

extern LIB_zhaolong_cableFunction_C_API 
bool MW_CALL_CONV mlxZhaolong_twinax_cable_oussama_1(int nlhs, mxArray *plhs[], int nrhs, 
                                                     mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_zhaolong_cableFunction
#define PUBLIC_zhaolong_cableFunction_CPP_API __declspec(dllexport)
#else
#define PUBLIC_zhaolong_cableFunction_CPP_API __declspec(dllimport)
#endif

#define LIB_zhaolong_cableFunction_CPP_API PUBLIC_zhaolong_cableFunction_CPP_API

#else

#if !defined(LIB_zhaolong_cableFunction_CPP_API)
#if defined(LIB_zhaolong_cableFunction_C_API)
#define LIB_zhaolong_cableFunction_CPP_API LIB_zhaolong_cableFunction_C_API
#else
#define LIB_zhaolong_cableFunction_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_zhaolong_cableFunction_CPP_API void MW_CALL_CONV zhaolong_cableFunction(int nargout, mwArray& sdd11, mwArray& sdd12, mwArray& sdd21, mwArray& sdd22, mwArray& sdc11, mwArray& sdc12, mwArray& sdc21, mwArray& sdc22, mwArray& scd11, mwArray& scd12, mwArray& scd21, mwArray& scd22, mwArray& scc11, mwArray& scc12, mwArray& scc21, mwArray& scc22, mwArray& f, const mwArray& rw, const mwArray& D, const mwArray& rsh, const mwArray& epsir, const mwArray& TanLoss, const mwArray& tsh, const mwArray& Lz, const mwArray& segmaAL, const mwArray& segmaCu, const mwArray& slot_d, const mwArray& name);

extern LIB_zhaolong_cableFunction_CPP_API void MW_CALL_CONV zhaolong_twinax_cable_oussama_1(int nargout, mwArray& s_params2, mwArray& sscd21, mwArray& sscd11, mwArray& sscc21, mwArray& sscc11, mwArray& ssdd21, mwArray& ssdd11, mwArray& f, const mwArray& rw, const mwArray& rsh, const mwArray& epsir, const mwArray& TanLoss, const mwArray& tsh, const mwArray& Lz, const mwArray& segmaAL, const mwArray& segmaCu, const mwArray& xd1, const mwArray& xd2, const mwArray& slot_d, const mwArray& fmin, const mwArray& fmax, const mwArray& Np);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
