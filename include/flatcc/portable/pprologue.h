#ifndef PPROLOGUE_H
#define PPROLOGUE_H

#if defined(__cplusplus) && !defined(PCPLUSPLUS_GUARD_SKIP)
#ifndef PCPLUSPLUS_GUARD_ACTIVE
#define PCPLUSPLUS_GUARD_ACTIVE
extern "C" {
#endif
#endif

#if !defined(PDIAGNOSTIC_PUSH_POP_SKIP)
#define PDIAGNOSTIC_PUSH_POP_ACTIVE
#include "pdiagnostic_push.h"
#endif /* !PDIAGNOSTIC_PUSH_POP_SKIP */

#endif /* PPROLOGUE_H */

#if !defined(PDIAGNOSTIC_SKIP)
/*
 * We cannot handle nested push, but we can add to the parent context
 * so keep this outside the header include guard.
 */
#include "pdiagnostic.h"
#endif /* !PDIAGNOSTIC_SKIP */
