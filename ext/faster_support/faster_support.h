#ifndef FASTER_SUPPORT_H
#define FASTER_SUPPORT_H 1

#include "ruby.h"

extern VALUE rb_mFasterSupport;

typedef enum {
  Impl_MRI,
  Impl_ActiveSupport,
  Impl_UNKNOWN,
} FasterSupport_blank_impl;

FasterSupport_blank_impl FasterSupport_get_blank_impl();

inline int FasterSupport_uses_mri();
inline int FasterSupport_uses_as();

#endif /* FASTER_SUPPORT_H */
