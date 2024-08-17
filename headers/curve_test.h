#ifndef __CURVE_TEST_H__
#define __CURVE_TEST_H__

#ifdef _WIN32
#ifdef curves_EXPORTS
#define DYN_POLICY __declspec(dllexport)
#else
#define DYN_POLICY __declspec(dllimport)
#endif // curves_EXPORTS
#else
#define DYN_POLICY
#endif // _WIN32

#endif // __CURVE_TEST_H__
