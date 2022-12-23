#pragma once

#include <list>
#include <mutex>
#include "define.h"
#include "delegate.h"

namespace ti {
namespace base {

#ifdef USING_VARIADIC_TEMPLATES
//TSignal
#define SIGNAL_NUMBER 
#define SIGNAL_CLASS_TYPES  class ...Args
#define SIGNAL_TYPES_COMMA  , Args...
#define SIGNAL_TYPE_ARGS    Args... args
#define SIGNAL_ARGS         args...
#include "detail/signalTemplate.h"
#endif

//TSignal0
#define SIGNAL_NUMBER       0
#define SIGNAL_CLASS_TYPES  class P0 = void
#define SIGNAL_TYPES_COMMA  
#define SIGNAL_TYPE_ARGS   void
#define SIGNAL_ARGS         
#include "detail/signalTemplate.h"

//TSignal1
#define SIGNAL_NUMBER 1
#define SIGNAL_CLASS_TYPES  class P1
#define SIGNAL_TYPES_COMMA  , P1
#define SIGNAL_TYPE_ARGS    P1 p1
#define SIGNAL_ARGS         p1
#include "detail/signalTemplate.h"

//TSignal2
#define SIGNAL_NUMBER 2
#define SIGNAL_CLASS_TYPES  class P1, class P2
#define SIGNAL_TYPES_COMMA  , P1, P2
#define SIGNAL_TYPE_ARGS    P1 p1, P2 p2
#define SIGNAL_ARGS         p1, p2
#include "detail/signalTemplate.h"

//TSignal3
#define SIGNAL_NUMBER 3
#define SIGNAL_CLASS_TYPES  class P1, class P2, class P3
#define SIGNAL_TYPES_COMMA  , P1, P2, P3
#define SIGNAL_TYPE_ARGS    P1 p1, P2 p2, P3 p3
#define SIGNAL_ARGS         p1, p2, p3
#include "detail/signalTemplate.h"

//TSignal4
#define SIGNAL_NUMBER 4
#define SIGNAL_CLASS_TYPES  class P1, class P2, class P3, class P4
#define SIGNAL_TYPES_COMMA  , P1, P2, P3, P4
#define SIGNAL_TYPE_ARGS    P1 p1, P2 p2, P3 p3, P4 p4
#define SIGNAL_ARGS         p1, p2, p3, p4
#include "detail/signalTemplate.h"

//TSignal5
#define SIGNAL_NUMBER 5
#define SIGNAL_CLASS_TYPES  class P1, class P2, class P3, class P4, class P5
#define SIGNAL_TYPES_COMMA  , P1, P2, P3, P4, P5
#define SIGNAL_TYPE_ARGS    P1 p1, P2 p2, P3 p3, P4 p4, P5 p5
#define SIGNAL_ARGS         p1, p2, p3, p4, p5
#include "detail/signalTemplate.h"

//TSignal6
#define SIGNAL_NUMBER 6
#define SIGNAL_CLASS_TYPES  class P1, class P2, class P3, class P4, class P5, class P6
#define SIGNAL_TYPES_COMMA  , P1, P2, P3, P4, P5, P6
#define SIGNAL_TYPE_ARGS    P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6
#define SIGNAL_ARGS         p1, p2, p3, p4, p5, p6
#include "detail/signalTemplate.h"

} // namespace base
} // namespace ti