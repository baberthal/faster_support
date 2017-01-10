/* String core extensions */

#include "string.h"

static rb_encoding *ascii_8bit_enc;

static VALUE rb_str_to_ascii8bit(VALUE str)
{
  rb_encoding *enc;
  VALUE new_str;

  enc = STR_ENC_GET(str);

  if (enc == ascii_8bit_enc) {
    return str;
  }

  if (OBJ_FROZEN(str)) {
    new_str = rb_obj_dup(str);
  }
  else {
    new_str = str;
  }

  rb_check_frozen(new_str);
  rb_enc_associate(new_str, ascii_8bit_enc);
  ENC_CODERANGE_CLEAR(new_str);

  return new_str;
}

void Init_string(void)
{
  ascii_8bit_enc = rb_ascii8bit_encoding();
  rb_define_method(rb_cString, "ascii_8bit", rb_str_to_ascii8bit, 0);
  rb_define_alias(rb_cString, "as_ascii_8bit", "ascii_8bit");
}
