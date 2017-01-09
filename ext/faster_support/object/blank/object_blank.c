/* Object#blank? implementation */

#include "blank.h"

static ID id_empty;

static VALUE rb_obj_blank(VALUE obj)
{
  VALUE empty;

  if (rb_respond_to(obj, id_empty)) {
    empty = rb_funcall(obj, id_empty, 0);
    if (empty == Qnil || empty == Qfalse) {
      return Qfalse;
    }

    return Qtrue;
  }

  empty = (obj == Qnil || obj == Qfalse) ? Qtrue : Qfalse;

  return empty;
}

static VALUE rb_obj_present(VALUE obj)
{
  return RB_NEGATE(rb_obj_blank(obj));
}

static VALUE return_false()
{
  return Qfalse;
}

static VALUE return_true()
{
  return Qtrue;
}

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

void Init_blank(void)
{
  id_empty = rb_intern("empty?");

  rb_define_method(rb_cObject, "blank?", rb_obj_blank, 0);
  rb_define_method(rb_cObject, "present?", rb_obj_present, 0);

  rb_define_method(rb_cNilClass, "blank?", return_true, 0);
  rb_define_method(rb_cNilClass, "present?", return_false, 0);

  rb_define_method(rb_cFalseClass, "blank?", return_true, 0);
  rb_define_method(rb_cFalseClass, "present?", return_false, 0);

  rb_define_method(rb_cArray, "blank?", rb_ary_blank, 0);
  rb_define_method(rb_cArray, "present?", rb_ary_present, 0);

  rb_define_method(rb_cHash, "blank?", rb_hash_blank, 0);
  rb_define_method(rb_cHash, "present?", rb_hash_present, 0);

  rb_define_method(rb_cTrueClass, "blank?", return_false, 0);
  rb_define_method(rb_cTrueClass, "present?", return_true, 0);

  Init_str_blank();

  rb_define_method(rb_cNumeric, "blank?", return_false, 0);
  rb_define_method(rb_cNumeric, "present?", return_true, 0);

  rb_define_method(rb_cTime, "blank?", return_false, 0);
  rb_define_method(rb_cTime, "present?", return_true, 0);
}
