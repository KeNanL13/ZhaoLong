//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Tue May 17 17:58:01 2022
// Arguments:
// "-B""macro_default""-W""cpplib:cascade_cable_and_connector_function,all,versi
// on=1.0""-T""link:lib""-d""E:\Stuff_For_QtProject\cascade_cable_and_connector_
// function\for_testing""-v""E:\Stuff_For_QtProject\cascade_cable_and_connector_
// function.m"
//

#ifndef cascade_cable_and_connector_function_h
#define cascade_cable_and_connector_function_h 1

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
#ifndef LIB_cascade_cable_and_connector_function_C_API 
#define LIB_cascade_cable_and_connector_function_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_cascade_cable_and_connector_function_C_API 
bool MW_CALL_CONV cascade_cable_and_connector_functionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_cascade_cable_and_connector_function_C_API 
bool MW_CALL_CONV cascade_cable_and_connector_functionInitialize(void);

extern LIB_cascade_cable_and_connector_function_C_API 
void MW_CALL_CONV cascade_cable_and_connector_functionTerminate(void);

extern LIB_cascade_cable_and_connector_function_C_API 
void MW_CALL_CONV cascade_cable_and_connector_functionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_cascade_cable_and_connector_function_C_API 
bool MW_CALL_CONV mlxCascade_cable_and_connector_function(int nlhs, mxArray *plhs[], int 
                                                          nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_cascade_cable_and_connector_function
#define PUBLIC_cascade_cable_and_connector_function_CPP_API __declspec(dllexport)
#else
#define PUBLIC_cascade_cable_and_connector_function_CPP_API __declspec(dllimport)
#endif

#define LIB_cascade_cable_and_connector_function_CPP_API PUBLIC_cascade_cable_and_connector_function_CPP_API

#else

#if !defined(LIB_cascade_cable_and_connector_function_CPP_API)
#if defined(LIB_cascade_cable_and_connector_function_C_API)
#define LIB_cascade_cable_and_connector_function_CPP_API LIB_cascade_cable_and_connector_function_C_API
#else
#define LIB_cascade_cable_and_connector_function_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_cascade_cable_and_connector_function_CPP_API void MW_CALL_CONV cascade_cable_and_connector_function(int nargout, mwArray& X, mwArray& SDD1, mwArray& SDD2, mwArray& SDD3, mwArray& SDD4, mwArray& SDC1, mwArray& SDC2, mwArray& SDC3, mwArray& SDC4, mwArray& SCD1, mwArray& SCD2, mwArray& SCD3, mwArray& SCD4, mwArray& SCC1, mwArray& SCC2, mwArray& SCC3, mwArray& SCC4, const mwArray& path1, const mwArray& path2);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
