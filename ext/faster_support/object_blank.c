/* Object#blank? implementation */

#include "faster_support.h"

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

static VALUE rb_nil_blank(VALUE self)
{
  return Qtrue;
}

static VALUE rb_nil_present(VALUE self)
{
  return Qfalse;
}

static VALUE rb_true_blank(VALUE self)
{
  return Qfalse;
}

static VALUE rb_true_present(VALUE self)
{
  return Qtrue;
}

void Init_obj_blank(void)
{
  id_empty = rb_intern("empty?");
  rb_define_method(rb_cObject, "blank?", rb_obj_blank, 0);
  rb_define_method(rb_cObject, "present?", rb_obj_present, 0);
  rb_define_method(rb_cNilClass, "blank?", rb_nil_blank, 0);
  rb_define_method(rb_cNilClass, "present?", rb_nil_present, 0);
  rb_define_method(rb_cFalseClass, "blank?", rb_nil_blank, 0);
  rb_define_method(rb_cFalseClass, "present?", rb_nil_present, 0);
  rb_define_method(rb_cTrueClass, "blank?", rb_true_blank, 0);
  rb_define_method(rb_cTrueClass, "present?", rb_true_present, 0);
  rb_define_method(rb_cNumeric, "blank?", rb_true_blank, 0);
  rb_define_method(rb_cNumeric, "present?", rb_true_present, 0);
  rb_define_method(rb_cTime, "blank?", rb_true_blank, 0);
  rb_define_method(rb_cTime, "present?", rb_true_present, 0);
}
