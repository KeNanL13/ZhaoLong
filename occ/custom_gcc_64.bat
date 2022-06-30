echo off

rem CASDEB comes as third argument

if /I "%VCVER%" == "gcc" (
  if "%ARCH%" == "64" (
    rem set environment variables used by OCCT
    set CSF_FPE=0

    set "TCL_DIR=%THIRDPARTY_DIR%/tcltk-8.6.4-mingw-64/bin"
    set "TK_DIR=%THIRDPARTY_DIR%/tcltk-8.6.4-mingw-64/bin"
    set "FREETYPE_DIR=%THIRDPARTY_DIR%/freetype-2.6.3-mingw-64/bin"
    set "FREEIMAGE_DIR="
    set "EGL_DIR="
    set "GLES2_DIR="
    set "TBB_DIR="
    set "VTK_DIR="
    set "FFMPEG_DIR="
    set "OPENVR_DIR="

    if not "E:/Qt/5.12.2/mingw73_64" == "" (
      set "QTDIR=E:/Qt/5.12.2/mingw73_64"
    )
    set "TCL_VERSION_WITH_DOT=8.6"
    set "TK_VERSION_WITH_DOT=8.6"

    set "CSF_OCCTBinPath=%CASROOT%/win64/gcc/bin%3"
    set "CSF_OCCTLibPath=%CASROOT%/win64/gcc/lib%3"

    set "CSF_OCCTIncludePath=%CASROOT%/inc"
    set "CSF_OCCTResourcePath=%CASROOT%/src"
    set "CSF_OCCTDataPath=%CASROOT%/data"
    set "CSF_OCCTSamplesPath=%CASROOT%/samples"
    set "CSF_OCCTTestsPath=%CASROOT%/tests"
    set "CSF_OCCTDocPath=%CASROOT%/doc"
  )
)

