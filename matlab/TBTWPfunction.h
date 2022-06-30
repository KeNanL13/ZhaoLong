//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Mon May 30 10:34:05 2022
// Arguments:
// "-B""macro_default""-W""cpplib:TBTWPfunction,all,version=1.0""-T""link:lib""-
// d""E:\Stuff_For_QtProject\TBTWPfunction\for_testing""-v""E:\Stuff_For_QtProje
// ct\TBTWP_near_field_electric_dipole_1.m""E:\Stuff_For_QtProject\TBTWP_near_fi
// eld_factors.m""E:\Stuff_For_QtProject\TBTWPfunction.m"
//

#ifndef TBTWPfunction_h
#define TBTWPfunction_h 1

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
#ifndef LIB_TBTWPfunction_C_API 
#define LIB_TBTWPfunction_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_TBTWPfunction_C_API 
bool MW_CALL_CONV TBTWPfunctionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_TBTWPfunction_C_API 
bool MW_CALL_CONV TBTWPfunctionInitialize(void);

extern LIB_TBTWPfunction_C_API 
void MW_CALL_CONV TBTWPfunctionTerminate(void);

extern LIB_TBTWPfunction_C_API 
void MW_CALL_CONV TBTWPfunctionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_TBTWPfunction_C_API 
bool MW_CALL_CONV mlxTBTWP_near_field_electric_dipole_1(int nlhs, mxArray *plhs[], int 
                                                        nrhs, mxArray *prhs[]);

extern LIB_TBTWPfunction_C_API 
bool MW_CALL_CONV mlxTBTWP_near_field_factors(int nlhs, mxArray *plhs[], int nrhs, 
                                              mxArray *prhs[]);

extern LIB_TBTWPfunction_C_API 
bool MW_CALL_CONV mlxTBTWPfunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_TBTWPfunction
#define PUBLIC_TBTWPfunction_CPP_API __declspec(dllexport)
#else
#define PUBLIC_TBTWPfunction_CPP_API __declspec(dllimport)
#endif

#define LIB_TBTWPfunction_CPP_API PUBLIC_TBTWPfunction_CPP_API

#else

#if !defined(LIB_TBTWPfunction_CPP_API)
#if defined(LIB_TBTWPfunction_C_API)
#define LIB_TBTWPfunction_CPP_API LIB_TBTWPfunction_C_API
#else
#define LIB_TBTWPfunction_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_TBTWPfunction_CPP_API void MW_CALL_CONV TBTWP_near_field_electric_dipole_1(int nargout, mwArray& Ex, mwArray& Ey, mwArray& Ez, const mwArray& P0, const mwArray& x0, const mwArray& y0, const mwArray& z0, const mwArray& x, const mwArray& y, const mwArray& z, const mwArray& theta, const mwArray& phi, const mwArray& etta0, const mwArray& c0, const mwArray& f);

extern LIB_TBTWPfunction_CPP_API void MW_CALL_CONV TBTWP_near_field_factors(int nargout, mwArray& F, mwArray& G, const mwArray& R, const mwArray& f, const mwArray& c0);

extern LIB_TBTWPfunction_CPP_API void MW_CALL_CONV TBTWPfunction(int nargout, mwArray& gcm, mwArray& hdm, const mwArray& Lz, const mwArray& rw, const mwArray& h, const mwArray& x0, const mwArray& y0, const mwArray& z0, const mwArray& P0, const mwArray& theta, const mwArray& phi);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
