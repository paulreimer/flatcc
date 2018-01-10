#ifndef PPRINTFP_H
#define PPRINTFP_H

#define PDIAGNOSTIC_IGNORE_UNUSED_FUNCTION
#include "pprologue.h"

#ifndef PORTABLE_USE_GRISU3
#define PORTABLE_USE_GRISU3 1
#endif


#if PORTABLE_USE_GRISU3
#include "grisu3_print.h"
#endif

#ifdef grisu3_print_double_is_defined
/* Currently there is not special support for floats. */
#define print_float(n, p) grisu3_print_double((float)(n), (p))
#define print_double(n, p) grisu3_print_double((double)(n), (p))
#else
#include <stdio.h>
#define print_float(n, p) sprintf(p, "%.9g", (float)(n))
#define print_double(n, p) sprintf(p, "%.17g", (double)(n))
#endif

#define print_hex_float(n, p) sprintf(p, "%a", (float)(n))
#define print_hex_double(n, p) sprintf(p, "%a", (double)(n))

#include "pepilogue.h"
#endif /* PPRINTFP_H */
