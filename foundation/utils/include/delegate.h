#pragma once

#include "define.h"
#include "detail/delegate.h"

namespace ti {
namespace base {

#ifdef USING_VARIADIC_TEMPLATES
//TDelegate
#define DELEGATE_NUMBER 
#define DELEGATE_CLASS_TYPES    class R, class... Args
#define DELEGATE_TYPES          Args...
#define DELEGATE_TYPE_ARGS      Args... args
#define DELEGATE_ARGS           args...
#include "detail/delegateTemplate.h"
#endif

//TDelegate0
#define DELEGATE_NUMBER 0
#define DELEGATE_CLASS_TYPES    class R
#define DELEGATE_TYPES          
#define DELEGATE_TYPE_ARGS     
#define DELEGATE_ARGS           
#include "detail/delegateTemplate.h"

//TDelegate1
#define DELEGATE_NUMBER 1
#define DELEGATE_CLASS_TYPES    class R, class P1
#define DELEGATE_TYPES          P1
#define DELEGATE_TYPE_ARGS      P1 p1
#define DELEGATE_ARGS           p1
#include "detail/delegateTemplate.h"

//TDelegate2
#define DELEGATE_NUMBER 2
#define DELEGATE_CLASS_TYPES    class R, class P1, class P2
#define DELEGATE_TYPES          P1, P2
#define DELEGATE_TYPE_ARGS      P1 p1, P2 p2
#define DELEGATE_ARGS           p1, p2
#include "detail/delegateTemplate.h"

//TDelegate3
#define DELEGATE_NUMBER 3
#define DELEGATE_CLASS_TYPES    class R, class P1, class P2, class P3
#define DELEGATE_TYPES          P1, P2, P3
#define DELEGATE_TYPE_ARGS      P1 p1, P2 p2, P3 p3
#define DELEGATE_ARGS           p1, p2, p3
#include "detail/delegateTemplate.h"

//TDelegate4
#define DELEGATE_NUMBER 4
#define DELEGATE_CLASS_TYPES    class R, class P1, class P2, class P3, class P4
#define DELEGATE_TYPES          P1, P2, P3, P4
#define DELEGATE_TYPE_ARGS      P1 p1, P2 p2, P3 p3, P4 p4
#define DELEGATE_ARGS           p1, p2, p3, p4
#include "detail/delegateTemplate.h"

//TDelegate5
#define DELEGATE_NUMBER 5
#define DELEGATE_CLASS_TYPES    class R, class P1, class P2, class P3, class P4, class P5
#define DELEGATE_TYPES          P1, P2, P3, P4, P5
#define DELEGATE_TYPE_ARGS      P1 p1, P2 p2, P3 p3, P4 p4, P5 p5
#define DELEGATE_ARGS           p1, p2, p3, p4, p5
#include "detail/delegateTemplate.h"

//TDelegate6
#define DELEGATE_NUMBER 6
#define DELEGATE_CLASS_TYPES    class R, class P1, class P2, class P3, class P4, class P5, class P6
#define DELEGATE_TYPES          P1, P2, P3, P4, P5, P6
#define DELEGATE_TYPE_ARGS      P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6
#define DELEGATE_ARGS           p1, p2, p3, p4, p5, p6
#include "detail/delegateTemplate.h"

} // namespace base
} // namespace ti
