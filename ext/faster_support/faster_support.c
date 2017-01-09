#include "faster_support.h"

VALUE rb_mFasterSupport;

void
Init_faster_support(void)
{
  rb_mFasterSupport = rb_define_module("FasterSupport");
}
