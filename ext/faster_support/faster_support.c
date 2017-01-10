/* FasterSupport main implementation */

#include "faster_support.h"

VALUE rb_mFasterSupport, rb_sFasterSupport;

static ID sym_mri, sym_as, id_blank_impl, id_to_sym;

static VALUE get_impl(void)
{
  VALUE val, sym;

  val = rb_funcall(rb_mFasterSupport, id_blank_impl, 0);

  if (NIL_P(val)) {
    printf("Got `nil`, returning sym_as\n");
    sym = sym_as;
  }
  else {
    sym = rb_funcall(val, id_to_sym, 0);
  }

  return sym;
}

FasterSupport_blank_impl FasterSupport_get_blank_impl()
{
  VALUE impl = get_impl();

  if (impl == sym_mri) {
    return Impl_MRI;
  }

  if (impl == sym_as) {
    return Impl_ActiveSupport;
  }

  return Impl_UNKNOWN;
}

inline int FasterSupport_uses_mri()
{
  return (FasterSupport_get_blank_impl() == Impl_MRI);
}

inline int FasterSupport_uses_as()
{
  return (FasterSupport_get_blank_impl() == Impl_ActiveSupport);
}

void Init_faster_support(void)
{
  sym_mri = ID2SYM(rb_intern("mri"));
  sym_as = ID2SYM(rb_intern("active_support"));
  id_blank_impl = rb_intern("blank_implementation");
  id_to_sym = rb_intern("to_sym");

  rb_mFasterSupport = rb_define_module("FasterSupport");
  rb_sFasterSupport = rb_singleton_class(rb_mFasterSupport);
}
