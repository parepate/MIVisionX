
#ifndef _VX_KERNELS_RPP_H_
#define _VX_KERNELS_RPP_H_
#if ENABLE_OPENCL
#include <CL/cl.h>
#endif

#define OPENVX_KHR_RPP   "vx_khr_rpp"
//////////////////////////////////////////////////////////////////////
// SHARED_PUBLIC - shared sybols for export
// STITCH_API_ENTRY - export API symbols
#if _WIN32
#define SHARED_PUBLIC extern "C" __declspec(dllexport)
#else
#define SHARED_PUBLIC extern "C" __attribute__ ((visibility ("default")))
#endif

//! \brief The macro for error checking from OpenVX status.
#define ERROR_CHECK_STATUS(call) { vx_status status = (call); if(status != VX_SUCCESS){ vxAddLogEntry(NULL, status, "ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status, __LINE__); return status; }}
#define STATUS_ERROR_CHECK(call){vx_status status = call; if(status!= VX_SUCCESS) return status;}
#define PARAM_ERROR_CHECK(call){vx_status status = call; if(status!= VX_SUCCESS) goto exit;}
//! \brief The macro for error checking from OpenVX object.
#define ERROR_CHECK_OBJECT(obj)  { vx_status status = vxGetStatus((vx_reference)(obj)); if(status != VX_SUCCESS){ vxAddLogEntry((vx_reference)(obj), status, "ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status, __LINE__); return status; }}

//////////////////////////////////////////////////////////////////////
// common header files
#include <VX/vx.h>
#include <vx_ext_rpp.h>
#include <vx_ext_amd.h>
#include <iostream>
#include <string.h>

#define ERRMSG(status, format, ...) printf("ERROR: " format, __VA_ARGS__), status


#define VX_LIBRARY_RPP         1

enum vx_kernel_ext_amd_rpp_e
{
VX_KERNEL_RPP_BRIGHTNESS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x0,
VX_KERNEL_RPP_BRIGHTNESSBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1,
VX_KERNEL_RPP_BRIGHTNESSBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2,
VX_KERNEL_RPP_BRIGHTNESSBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3,
VX_KERNEL_RPP_GAMMACORRECTION = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4,
VX_KERNEL_RPP_GAMMACORRECTIONBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5,
VX_KERNEL_RPP_GAMMACORRECTIONBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6,
VX_KERNEL_RPP_GAMMACORRECTIONBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7,
VX_KERNEL_RPP_BLEND = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x8,
VX_KERNEL_RPP_BLENDBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9,
VX_KERNEL_RPP_BLENDBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa,
VX_KERNEL_RPP_BLENDBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb,
VX_KERNEL_RPP_BLUR = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc,
VX_KERNEL_RPP_BLURBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd,
VX_KERNEL_RPP_BLURBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe,
VX_KERNEL_RPP_BLURBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf,
VX_KERNEL_RPP_CONTRAST = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x10,
VX_KERNEL_RPP_CONTRASTBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11,
VX_KERNEL_RPP_CONTRASTBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x12,
VX_KERNEL_RPP_CONTRASTBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x13,
VX_KERNEL_RPP_PIXELATE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x14,
VX_KERNEL_RPP_PIXELATEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x15,
VX_KERNEL_RPP_PIXELATEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x16,
VX_KERNEL_RPP_PIXELATEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x17,
VX_KERNEL_RPP_JITTER = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x18,
VX_KERNEL_RPP_JITTERBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x19,
VX_KERNEL_RPP_JITTERBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1a,
VX_KERNEL_RPP_JITTERBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1b,
VX_KERNEL_RPP_OCCLUSION = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1c,
VX_KERNEL_RPP_OCCLUSIONBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1d,
VX_KERNEL_RPP_OCCLUSIONBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1e,
VX_KERNEL_RPP_OCCLUSIONBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x1f,
VX_KERNEL_RPP_SNOW = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x20,
VX_KERNEL_RPP_SNOWBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x21,
VX_KERNEL_RPP_SNOWBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x22,
VX_KERNEL_RPP_SNOWBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x23,
VX_KERNEL_RPP_NOISE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x24,
VX_KERNEL_RPP_NOISEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x25,
VX_KERNEL_RPP_NOISEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x26,
VX_KERNEL_RPP_NOISEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x27,
VX_KERNEL_RPP_RANDOMSHADOW = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x28,
VX_KERNEL_RPP_RANDOMSHADOWBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x29,
VX_KERNEL_RPP_RANDOMSHADOWBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2a,
VX_KERNEL_RPP_RANDOMSHADOWBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2b,
VX_KERNEL_RPP_FOG = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2c,
VX_KERNEL_RPP_FOGBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2d,
VX_KERNEL_RPP_FOGBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2e,
VX_KERNEL_RPP_FOGBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x2f,
VX_KERNEL_RPP_RAIN = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x30,
VX_KERNEL_RPP_RAINBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x31,
VX_KERNEL_RPP_RAINBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x32,
VX_KERNEL_RPP_RAINBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x33,
VX_KERNEL_RPP_RANDOMCROPLETTERBOX = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x34,
VX_KERNEL_RPP_RANDOMCROPLETTERBOXBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x35,
VX_KERNEL_RPP_RANDOMCROPLETTERBOXBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x36,
VX_KERNEL_RPP_RANDOMCROPLETTERBOXBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x37,
VX_KERNEL_RPP_EXPOSURE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x38,
VX_KERNEL_RPP_EXPOSUREBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x39,
VX_KERNEL_RPP_EXPOSUREBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3a,
VX_KERNEL_RPP_EXPOSUREBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3b,
VX_KERNEL_RPP_HISTOGRAMBALANCE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3c,
VX_KERNEL_RPP_HISTOGRAMBALANCEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3d,
VX_KERNEL_RPP_HISTOGRAMBALANCEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3e,
VX_KERNEL_RPP_HISTOGRAMBALANCEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x3f,
VX_KERNEL_RPP_ABSOLUTEDIFFERENCE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x40,
VX_KERNEL_RPP_ABSOLUTEDIFFERENCEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x41,
VX_KERNEL_RPP_ABSOLUTEDIFFERENCEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x42,
VX_KERNEL_RPP_ABSOLUTEDIFFERENCEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x43,
VX_KERNEL_RPP_ACCUMULATEWEIGHTED = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x44,
VX_KERNEL_RPP_ACCUMULATEWEIGHTEDBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x45,
VX_KERNEL_RPP_ACCUMULATEWEIGHTEDBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x46,
VX_KERNEL_RPP_ACCUMULATEWEIGHTEDBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x47,
VX_KERNEL_RPP_ACCUMULATE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x48,
VX_KERNEL_RPP_ACCUMULATEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x49,
VX_KERNEL_RPP_ACCUMULATEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4a,
VX_KERNEL_RPP_ACCUMULATEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4b,
VX_KERNEL_RPP_ADD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4c,
VX_KERNEL_RPP_ADDBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4d,
VX_KERNEL_RPP_ADDBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4e,
VX_KERNEL_RPP_ADDBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x4f,
VX_KERNEL_RPP_SUBTRACT = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x50,
VX_KERNEL_RPP_SUBTRACTBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x51,
VX_KERNEL_RPP_SUBTRACTBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x52,
VX_KERNEL_RPP_SUBTRACTBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x53,
VX_KERNEL_RPP_MAGNITUDE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x54,
VX_KERNEL_RPP_MAGNITUDEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x55,
VX_KERNEL_RPP_MAGNITUDEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x56,
VX_KERNEL_RPP_MAGNITUDEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x57,
VX_KERNEL_RPP_MULTIPLY = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x58,
VX_KERNEL_RPP_MULTIPLYBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x59,
VX_KERNEL_RPP_MULTIPLYBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5a,
VX_KERNEL_RPP_MULTIPLYBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5b,
VX_KERNEL_RPP_PHASE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5c,
VX_KERNEL_RPP_PHASEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5d,
VX_KERNEL_RPP_PHASEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5e,
VX_KERNEL_RPP_PHASEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x5f,
VX_KERNEL_RPP_ACCUMULATESQUARED = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x60,
VX_KERNEL_RPP_ACCUMULATESQUAREDBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x61,
VX_KERNEL_RPP_ACCUMULATESQUAREDBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x62,
VX_KERNEL_RPP_ACCUMULATESQUAREDBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x63,
VX_KERNEL_RPP_BITWISEAND = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x64,
VX_KERNEL_RPP_BITWISEANDBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x65,
VX_KERNEL_RPP_BITWISEANDBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x66,
VX_KERNEL_RPP_BITWISEANDBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x67,
VX_KERNEL_RPP_BITWISENOT = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x68,
VX_KERNEL_RPP_BITWISENOTBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x69,
VX_KERNEL_RPP_BITWISENOTBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6a,
VX_KERNEL_RPP_BITWISENOTBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6b,
VX_KERNEL_RPP_EXCLUSIVEOR = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6c,
VX_KERNEL_RPP_EXCLUSIVEORBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6d,
VX_KERNEL_RPP_EXCLUSIVEORBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6e,
VX_KERNEL_RPP_EXCLUSIVEORBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x6f,
VX_KERNEL_RPP_INCLUSIVEOR = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x70,
VX_KERNEL_RPP_INCLUSIVEORBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x71,
VX_KERNEL_RPP_INCLUSIVEORBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x72,
VX_KERNEL_RPP_INCLUSIVEORBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x73,
VX_KERNEL_RPP_HISTOGRAM = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x74,
VX_KERNEL_RPP_THRESHOLDING = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x78,
VX_KERNEL_RPP_THRESHOLDINGBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x79,
VX_KERNEL_RPP_THRESHOLDINGBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7a,
VX_KERNEL_RPP_THRESHOLDINGBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7b,
VX_KERNEL_RPP_MAX = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7c,
VX_KERNEL_RPP_MAXBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7d,
VX_KERNEL_RPP_MAXBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7e,
VX_KERNEL_RPP_MAXBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x7f,
VX_KERNEL_RPP_MIN = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x80,
VX_KERNEL_RPP_MINBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x81,
VX_KERNEL_RPP_MINBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x82,
VX_KERNEL_RPP_MINBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x83,
VX_KERNEL_RPP_MINMAXLOC = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x84,
VX_KERNEL_RPP_HISTOGRAMEQUALIZE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x8c,
VX_KERNEL_RPP_HISTOGRAMEQUALIZEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x8d,
VX_KERNEL_RPP_HISTOGRAMEQUALIZEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x8e,
VX_KERNEL_RPP_HISTOGRAMEQUALIZEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x8f,
VX_KERNEL_RPP_MEANSTDDEV = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x90,
VX_KERNEL_RPP_FLIP = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x94,
VX_KERNEL_RPP_FLIPBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x95,
VX_KERNEL_RPP_FLIPBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x96,
VX_KERNEL_RPP_FLIPBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x97,
VX_KERNEL_RPP_RESIZE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x98,
VX_KERNEL_RPP_RESIZEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x99,
VX_KERNEL_RPP_RESIZEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9a,
VX_KERNEL_RPP_RESIZEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9b,
VX_KERNEL_RPP_RESIZECROP = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9c,
VX_KERNEL_RPP_RESIZECROPBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9d,
VX_KERNEL_RPP_RESIZECROPBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9e,
VX_KERNEL_RPP_RESIZECROPBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x9f,
VX_KERNEL_RPP_ROTATE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa0,
VX_KERNEL_RPP_ROTATEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa1,
VX_KERNEL_RPP_ROTATEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa2,
VX_KERNEL_RPP_ROTATEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa3,
VX_KERNEL_RPP_WARPAFFINE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa4,
VX_KERNEL_RPP_WARPAFFINEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa5,
VX_KERNEL_RPP_WARPAFFINEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa6,
VX_KERNEL_RPP_WARPAFFINEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa7,
VX_KERNEL_RPP_FISHEYE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa8,
VX_KERNEL_RPP_FISHEYEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xa9,
VX_KERNEL_RPP_FISHEYEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xaa,
VX_KERNEL_RPP_FISHEYEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xab,
VX_KERNEL_RPP_LENSCORRECTION = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xac,
VX_KERNEL_RPP_LENSCORRECTIONBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xad,
VX_KERNEL_RPP_LENSCORRECTIONBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xae,
VX_KERNEL_RPP_LENSCORRECTIONBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xaf,
VX_KERNEL_RPP_SCALE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb0,
VX_KERNEL_RPP_SCALEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb1,
VX_KERNEL_RPP_SCALEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb2,
VX_KERNEL_RPP_SCALEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb3,
VX_KERNEL_RPP_WARPPERSPECTIVE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb4,
VX_KERNEL_RPP_WARPPERSPECTIVEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb5,
VX_KERNEL_RPP_WARPPERSPECTIVEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb6,
VX_KERNEL_RPP_WARPPERSPECTIVEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb7,
VX_KERNEL_RPP_DILATE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb8,
VX_KERNEL_RPP_DILATEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xb9,
VX_KERNEL_RPP_DILATEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xba,
VX_KERNEL_RPP_DILATEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xbb,
VX_KERNEL_RPP_ERODE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xbc,
VX_KERNEL_RPP_ERODEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xbd,
VX_KERNEL_RPP_ERODEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xbe,
VX_KERNEL_RPP_ERODEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xbf,
VX_KERNEL_RPP_HUE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc0,
VX_KERNEL_RPP_HUEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc1,
VX_KERNEL_RPP_HUEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc2,
VX_KERNEL_RPP_HUEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc3,
VX_KERNEL_RPP_SATURATION = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc4,
VX_KERNEL_RPP_SATURATIONBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc5,
VX_KERNEL_RPP_SATURATIONBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc6,
VX_KERNEL_RPP_SATURATIONBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc7,
VX_KERNEL_RPP_COLORTEMPERATURE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc8,
VX_KERNEL_RPP_COLORTEMPERATUREBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xc9,
VX_KERNEL_RPP_COLORTEMPERATUREBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xca,
VX_KERNEL_RPP_COLORTEMPERATUREBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xcb,
VX_KERNEL_RPP_VIGNETTE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xcc,
VX_KERNEL_RPP_VIGNETTEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xcd,
VX_KERNEL_RPP_VIGNETTEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xce,
VX_KERNEL_RPP_VIGNETTEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xcf,
VX_KERNEL_RPP_CHANNELEXTRACT = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd0,
VX_KERNEL_RPP_CHANNELEXTRACTBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd1,
VX_KERNEL_RPP_CHANNELEXTRACTBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd2,
VX_KERNEL_RPP_CHANNELCOMBINE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd4,
VX_KERNEL_RPP_CHANNELCOMBINEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd5,
VX_KERNEL_RPP_CHANNELCOMBINEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd6,
VX_KERNEL_RPP_LOOKUPTABLE = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd8,
VX_KERNEL_RPP_LOOKUPTABLEBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xd9,
VX_KERNEL_RPP_LOOKUPTABLEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xda,
VX_KERNEL_RPP_LOOKUPTABLEBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xdb,
VX_KERNEL_RPP_BILATERALFILTER = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xdc,
VX_KERNEL_RPP_BILATERALFILTERBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xdd,
VX_KERNEL_RPP_BILATERALFILTERBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xde,
VX_KERNEL_RPP_BILATERALFILTERBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xdf,
VX_KERNEL_RPP_BOXFILTER = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe0,
VX_KERNEL_RPP_BOXFILTERBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe1,
VX_KERNEL_RPP_BOXFILTERBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe2,
VX_KERNEL_RPP_BOXFILTERBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe3,
VX_KERNEL_RPP_SOBEL = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe4,
VX_KERNEL_RPP_SOBELBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe5,
VX_KERNEL_RPP_SOBELBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe6,
VX_KERNEL_RPP_SOBELBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe7,
VX_KERNEL_RPP_MEDIANFILTER = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe8,
VX_KERNEL_RPP_MEDIANFILTERBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xe9,
VX_KERNEL_RPP_MEDIANFILTERBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xea,
VX_KERNEL_RPP_MEDIANFILTERBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xeb,
VX_KERNEL_RPP_CUSTOMCONVOLUTION = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xec,
VX_KERNEL_RPP_CUSTOMCONVOLUTIONBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xed,
VX_KERNEL_RPP_CUSTOMCONVOLUTIONBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xee,
VX_KERNEL_RPP_CUSTOMCONVOLUTIONBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xef,
VX_KERNEL_RPP_NONMAXSUPRESSION = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf0,
VX_KERNEL_RPP_NONMAXSUPRESSIONBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf1,
VX_KERNEL_RPP_NONMAXSUPRESSIONBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf2,
VX_KERNEL_RPP_NONMAXSUPRESSIONBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf3,
VX_KERNEL_RPP_GAUSSIANFILTER = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf4,
VX_KERNEL_RPP_GAUSSIANFILTERBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf5,
VX_KERNEL_RPP_GAUSSIANFILTERBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf6,
VX_KERNEL_RPP_GAUSSIANFILTERBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf7,
VX_KERNEL_RPP_NONLINEARFILTER = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf8,
VX_KERNEL_RPP_NONLINEARFILTERBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xf9,
VX_KERNEL_RPP_NONLINEARFILTERBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xfa,
VX_KERNEL_RPP_NONLINEARFILTERBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xfb,
VX_KERNEL_RPP_LOCALBINARYPATTERN = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xfc,
VX_KERNEL_RPP_LOCALBINARYPATTERNBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xfd,
VX_KERNEL_RPP_LOCALBINARYPATTERNBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xfe,
VX_KERNEL_RPP_LOCALBINARYPATTERNBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0xff,
VX_KERNEL_RPP_DATAOBJECTCOPY = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x100,
VX_KERNEL_RPP_DATAOBJECTCOPYBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x101,
VX_KERNEL_RPP_DATAOBJECTCOPYBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x102,
VX_KERNEL_RPP_DATAOBJECTCOPYBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x103,
VX_KERNEL_RPP_GAUSSIANIMAGEPYRAMID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x104,
VX_KERNEL_RPP_GAUSSIANIMAGEPYRAMIDBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x105,
VX_KERNEL_RPP_GAUSSIANIMAGEPYRAMIDBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x106,
VX_KERNEL_RPP_LAPLACIANIMAGEPYRAMID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x108,
VX_KERNEL_RPP_CANNYEDGEDETECTOR = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x10c,
VX_KERNEL_RPP_HARRISCORNERDETECTOR = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x110,
VX_KERNEL_RPP_FASTCORNERDETECTOR = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x114,
VX_KERNEL_RPP_CONTROLFLOW = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x118,
VX_KERNEL_RPP_CONTROLFLOWBATCHPS = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x119,
VX_KERNEL_RPP_CONTROLFLOWBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11a,
VX_KERNEL_RPP_CONTROLFLOWBATCHPDROID = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11b,
VX_KERNEL_RPP_REMAP = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11c,
VX_KERNEL_RPP_TENSORADD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11d,
VX_KERNEL_RPP_TENSORSUBTRACT = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11e,
VX_KERNEL_RPP_TENSORMULTIPLY = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x11f,
VX_KERNEL_RPP_TENSORMATRIXMULTIPLY = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x120,
VX_KERNEL_RPP_TENSORLOOKUP = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x121,
VX_KERNEL_RPP_COLORTWIST = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x122,
VX_KERNEL_RPP_COLORTWISTBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x123,
VX_KERNEL_RPP_CROPMIRRORNORMALIZEBATCHPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x124,
VX_KERNEL_RPP_CROPPD = VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) +0x125,
VX_KERNEL_RPP_COPY,  //= VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) + 0x122,
VX_KERNEL_RPP_NOP  //= VX_KERNEL_BASE(VX_ID_AMD, VX_LIBRARY_RPP) + 0x123,
};

//////////////////////////////////////////////////////////////////////
//! rief Common data shared across all nodes in a graph
struct RPPCommonHandle {
#if ENABLE_OPENCL
    cl_command_queue cmdq;
#endif
    void* cpuHandle = NULL;
    int count;
    bool exhaustiveSearch;
};
//////////////////////////////////////////////////////////////////////
//! rief The utility functions
vx_node createNode(vx_graph graph, vx_enum kernelEnum, vx_reference params[], vx_uint32 num);
vx_status createGraphHandle(vx_node node, RPPCommonHandle ** pHandle);
vx_status releaseGraphHandle(vx_node node, RPPCommonHandle * handle);
int getEnvironmentVariable(const char* name);

#endif //__KERNELS_H__
