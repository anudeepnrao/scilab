// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011-2011 - Gsoc 2011 - Iuri SILVIO
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- JVM NOT MANDATORY -->
// ============================================================================
// Unitary tests for mxGetData and mxSetData mex functions
// ============================================================================

cd(TMPDIR);
ilib_verbose(0);
mputl(["#include ""mex.h""";
"void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])";
"{";
"    void *data = mxGetData(prhs[0]);";
"    mxSetData(prhs[0], data);";
"    plhs[0] = prhs[0];";
"}"],"mexGetSetData.c");
ilib_mex_build("libmextest",["getSetData","mexGetSetData","cmex"], "mexGetSetData.c",[],"","","","");
exec("loader.sce");

r = getSetData(double(1));
assert_checkequal(r(1), 1);
r = getSetData(int8(2));
assert_checkequal(r(1), int8(2));
r = getSetData(int16(3));
assert_checkequal(r(1), int16(3));
r = getSetData(int32(4));
assert_checkequal(r(1), int32(4));
r = getSetData(int64(5));
assert_checkequal(r(1), int64(5));
r = getSetData(uint8(6));
assert_checkequal(r(1), uint8(6));
r = getSetData(uint16(7));
assert_checkequal(r(1), uint16(7));
r = getSetData(uint32(8));
assert_checkequal(r(1), uint32(8));
r = getSetData(uint64(9));
assert_checkequal(r(1), uint64(9));
r = getSetData(%t);
assert_checktrue(r(1));