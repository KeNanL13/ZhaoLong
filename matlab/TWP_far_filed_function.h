//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Tue May 17 17:59:28 2022
// Arguments:
// "-B""macro_default""-W""cpplib:TWP_far_filed_function,all,version=1.0""-T""li
// nk:lib""-d""E:\Stuff_For_QtProject\TWP_far_filed_function\for_testing""-v""E:
// \Stuff_For_QtProject\TWP_far_filed_function.m"
//

#ifndef TWP_far_filed_function_h
#define TWP_far_filed_function_h 1

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
#ifndef LIB_TWP_far_filed_function_C_API 
#define LIB_TWP_far_filed_function_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_TWP_far_filed_function_C_API 
bool MW_CALL_CONV TWP_far_filed_functionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_TWP_far_filed_function_C_API 
bool MW_CALL_CONV TWP_far_filed_functionInitialize(void);

extern LIB_TWP_far_filed_function_C_API 
void MW_CALL_CONV TWP_far_filed_functionTerminate(void);

extern LIB_TWP_far_filed_function_C_API 
void MW_CALL_CONV TWP_far_filed_functionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_TWP_far_filed_function_C_API 
bool MW_CALL_CONV mlxTWP_far_filed_function(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                            *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_TWP_far_filed_function
#define PUBLIC_TWP_far_filed_function_CPP_API __declspec(dllexport)
#else
#define PUBLIC_TWP_far_filed_function_CPP_API __declspec(dllimport)
#endif

#define LIB_TWP_far_filed_function_CPP_API PUBLIC_TWP_far_filed_function_CPP_API

#else

#if !defined(LIB_TWP_far_filed_function_CPP_API)
#if defined(LIB_TWP_far_filed_function_C_API)
#define LIB_TWP_far_filed_function_CPP_API LIB_TWP_far_filed_function_C_API
#else
#define LIB_TWP_far_filed_function_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_TWP_far_filed_function_CPP_API void MW_CALL_CONV TWP_far_filed_function(int nargout, mwArray& f, mwArray& gcm, mwArray& hdm, const mwArray& Lz, const mwArray& p, const mwArray& s, const mwArray& h, const mwArray& rw1, const mwArray& rw2, const mwArray& E0, const mwArray& thetaE, const mwArray& thetaP, const mwArray& phiP);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
