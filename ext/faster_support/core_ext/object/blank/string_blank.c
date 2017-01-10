/* Faster implementation of String#blank? */

#include "blank.h"
#include "faster_support.h"
#include <stdio.h>

extern VALUE rb_mFasterSupport;

static VALUE rb_str_as_blank(VALUE str)
{
  rb_encoding *enc;
  char *s, *e;

  enc = STR_ENC_GET(str);
  s = RSTRING_PTR(str);

  if (!s || RSTRING_LEN(str) == 0) return Qtrue;

  e = RSTRING_END(str);

  while (s < e) {
    int n;
    unsigned int cc = rb_enc_codepoint_len(s, e, &n, enc);

    switch (cc) {
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x20:
    case 0x85:
    case 0xa0:
    case 0x1680:
    case 0x2000:
    case 0x2001:
    case 0x2002:
    case 0x2003:
    case 0x2004:
    case 0x2005:
    case 0x2006:
    case 0x2007:
    case 0x2008:
    case 0x2009:
    case 0x200a:
    case 0x2028:
    case 0x2029:
    case 0x202f:
    case 0x205f:
    case 0x3000:
#if RUBY_BEFORE_2_2
    case 0x180e:
#endif
      /* found a blank char */
      break;

    default:
      return Qfalse;
    }

    s += n;
  }

  /* if we get here, all chars were blank chars */
  return Qtrue;
}

static VALUE rb_str_mri_blank(VALUE str)
{
  rb_encoding *enc;
  char *s, *e;

  enc = STR_ENC_GET(str);
  s = RSTRING_PTR(str);
  if (!s || RSTRING_LEN(str) == 0) return Qtrue;

  e = RSTRING_END(str);

  while (s < e) {
    int n;
    unsigned int cc = rb_enc_codepoint_len(s, e, &n, enc);

    if (!rb_isspace(cc) && cc != 0) return Qfalse;
    s += n;
  }

  return Qtrue;
}

static VALUE rb_str_blank(VALUE str)
{
  FasterSupport_blank_impl impl = FasterSupport_get_blank_impl();

  switch (impl) {
  case Impl_MRI:
    return rb_str_mri_blank(str);
  case Impl_ActiveSupport:
    return rb_str_as_blank(str);
  default:
    break;
  }

  return rb_str_as_blank(str);
}

static VALUE rb_str_present(VALUE str)
{
  return RB_NEGATE(rb_str_blank(str));
}

void Init_str_blank(void)
{
  rb_define_method(rb_cString, "as_blank?", rb_str_as_blank, 0);
  rb_define_method(rb_cString, "blank?", rb_str_blank, 0);
  rb_define_method(rb_cString, "mri_blank?", rb_str_mri_blank, 0);
  rb_define_method(rb_cString, "present?", rb_str_present, 0);
}
