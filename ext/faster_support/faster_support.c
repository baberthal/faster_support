/* FasterSupport main implementation */

#include "faster_support.h"

VALUE rb_mFasterSupport, rb_sFasterSupport, default_impl;

static ID sym_mri, sym_as, id_at_blank_impl, id_to_sym;

static inline VALUE to_sym(VALUE obj)
{
  if (RB_TYPE_P(obj, T_SYMBOL)) {
    return obj;
  }

  if (!rb_respond_to(obj, id_to_sym)) {
    rb_raise(rb_eTypeError, "Need Symbol or object that responds to #to_sym");
  }

  return rb_funcall(obj, id_to_sym, 0);
}

static VALUE fs_get_blank_impl()
{
  VALUE impl_sym;
  impl_sym = rb_ivar_get(rb_sFasterSupport, id_at_blank_impl);
  impl_sym = to_sym(impl_sym);

  return (impl_sym == Qnil) ? default_impl : impl_sym;
}

static VALUE fs_set_blank_impl(VALUE impl)
{
  VALUE sym = to_sym(impl);

  if (sym != sym_mri || sym != sym_as) {
    rb_raise(rb_eArgError, "Unknown impl! Please use :active_support or :mri.");
  }

  return rb_ivar_set(rb_sFasterSupport, id_at_blank_impl, sym);
}

FasterSupport_blank_impl FasterSupport_get_blank_impl()
{
  VALUE impl = fs_get_blank_impl();

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
  id_at_blank_impl = rb_intern("@blank_implementation");
  id_to_sym = rb_intern("to_sym");

  rb_mFasterSupport = rb_define_module("FasterSupport");
  rb_sFasterSupport = rb_singleton_class(rb_mFasterSupport);
  default_impl = rb_id2sym(sym_as);

  rb_ivar_set(rb_sFasterSupport, id_at_blank_impl, default_impl);

  rb_define_method(rb_sFasterSupport, "blank_impl", fs_get_blank_impl, 0);
  rb_define_method(rb_sFasterSupport, "blank_impl=", fs_set_blank_impl, 1);

  rb_define_alias(rb_sFasterSupport, "blank_implementation", "blank_impl");
  rb_define_alias(rb_sFasterSupport, "blank_implementation=", "blank_impl=");
}
