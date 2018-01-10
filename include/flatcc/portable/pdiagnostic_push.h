#ifndef PDIAGNOSTIC_PUSH_H
#define PDIAGNOSTIC_PUSH_H

/*
 * See also comment in "pdiagnostic.h"
 *
 * e.g.
 * #define PDIAGNOSTIC_IGNORE_USED_FUNCTION
 * #define PDIAGNOSTIC_IGNORE_USED_VARIABLE
 * #include "pprologue.h"
 * ...
 * #include "pepilogue.h"
 * <eof>
 *
 * or if push pop isn't desired:
 * #define PDIAGNOSTIC_IGNORE_USED_FUNCTION
 * #define PDIAGNOSTIC_IGNORE_USED_VARIABLE
 * #define PDIAGNOSTIC_PUSH_POP_SKIP // added
 * #include "pprologue.h"
 * ...
 * #include "pepilogue.h"
 * <eof>
 *
 *
 * Some if these warnings cannot be ignored
 * at the #pragma level, but might in the future.
 * Use compiler switches like -Wno-unused-function
 * to work around this.
 */

#if defined(_MSC_VER)
#pragma warning( push )
#define PDIAGNOSTIC_PUSHED_MSVC 1
#elif defined(__clang__)
#pragma clang diagnostic push
#define PDIAGNOSTIC_PUSHED_CLANG 1
#elif ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#pragma GCC diagnostic push
#define PDIAGNOSTIC_PUSHED_GCC 1
#endif

#endif /* PDIAGNOSTIC_PUSH_H */
