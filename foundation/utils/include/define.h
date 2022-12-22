#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef osNullptr
#define osNullptr    0
#endif

#ifdef _MSC_VER_
#ifdef API_DLL_BUILD
#define EXPORT_API _declspec(dllexport)
#elif  define API_DLL_USE
#define EXPORT_API _declspec(dllimport)
#else
#define EXPORT_API
#endif
#else
#define EXPORT_API
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define BASE_JOIN(X,Y)         BASE_DO_JOIN(X,Y)
#define BASE_DO_JOIN(X,Y)      BASE_DO_JOIN2(X,Y)
#define BASE_DO_JOIN2(X,Y)     X##Y
