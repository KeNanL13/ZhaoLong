//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Thu May 12 20:39:56 2022
// Arguments:
// "-B""macro_default""-W""cpplib:far_field_two_cables_function,all,version=1.0"
// "-T""link:lib""-d""E:\Stuff_For_QtProject\far_field_two_cables_function\for_t
// esting""-v""E:\Stuff_For_QtProject\far_field_two_cables_function.m"
//

#ifndef far_field_two_cables_function_h
#define far_field_two_cables_function_h 1

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
#ifndef LIB_far_field_two_cables_function_C_API 
#define LIB_far_field_two_cables_function_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_far_field_two_cables_function_C_API 
bool MW_CALL_CONV far_field_two_cables_functionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_far_field_two_cables_function_C_API 
bool MW_CALL_CONV far_field_two_cables_functionInitialize(void);

extern LIB_far_field_two_cables_function_C_API 
void MW_CALL_CONV far_field_two_cables_functionTerminate(void);

extern LIB_far_field_two_cables_function_C_API 
void MW_CALL_CONV far_field_two_cables_functionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_far_field_two_cables_function_C_API 
bool MW_CALL_CONV mlxFar_field_two_cables_function(int nlhs, mxArray *plhs[], int nrhs, 
                                                   mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_far_field_two_cables_function
#define PUBLIC_far_field_two_cables_function_CPP_API __declspec(dllexport)
#else
#define PUBLIC_far_field_two_cables_function_CPP_API __declspec(dllimport)
#endif

#define LIB_far_field_two_cables_function_CPP_API PUBLIC_far_field_two_cables_function_CPP_API

#else

#if !defined(LIB_far_field_two_cables_function_CPP_API)
#if defined(LIB_far_field_two_cables_function_C_API)
#define LIB_far_field_two_cables_function_CPP_API LIB_far_field_two_cables_function_C_API
#else
#define LIB_far_field_two_cables_function_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_far_field_two_cables_function_CPP_API void MW_CALL_CONV far_field_two_cables_function(int nargout, mwArray& f, mwArray& gcm, mwArray& hdm, const mwArray& s, const mwArray& h, const mwArray& rw1, const mwArray& rw2, const mwArray& L, const mwArray& E0, const mwArray& thetaE, const mwArray& thetaP, const mwArray& phiP);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
