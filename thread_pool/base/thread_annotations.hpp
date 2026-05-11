#pragma once

#if defined(__clang__) && (!defined(SWIG))
#define TP_THREAD_ANNOTATION_ATTRIBUTE(x) __attribute__((x))
#else
#define TP_THREAD_ANNOTATION_ATTRIBUTE(x)
#endif

#define GUARDED_BY(x) TP_THREAD_ANNOTATION_ATTRIBUTE(guarded_by(x))

#define PT_GUARDED_BY(x) TP_THREAD_ANNOTATION_ATTRIBUTE(pt_guarded_by(x))
