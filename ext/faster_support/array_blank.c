/* Array#blank? implementation */

#include "faster_support.h"

static VALUE rb_ary_blank(VALUE ary)
{
  if (RARRAY_LEN(ary) == 0) {
    return Qtrue;
  }

  return Qfalse;
}

static VALUE rb_ary_present(VALUE ary)
{
  return RB_NEGATE(rb_ary_blank(ary));
}

static VALUE rb_hash_blank(VALUE self)
{
  return RHASH_EMPTY_P(self) ? Qtrue : Qfalse;
}

static VALUE rb_hash_present(VALUE self)
{
  return RB_NEGATE(rb_hash_blank(self));
}

void Init_ary_blank(void)
{
  rb_define_method(rb_cArray, "blank?", rb_ary_blank, 0);
  rb_define_method(rb_cArray, "present?", rb_ary_present, 0);
  rb_define_method(rb_cHash, "blank?", rb_hash_blank, 0);
  rb_define_method(rb_cHash, "present?", rb_hash_present, 0);
}
