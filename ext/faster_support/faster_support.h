#ifndef FASTER_SUPPORT_H
#define FASTER_SUPPORT_H 1

#include "ruby.h"
#include "ruby/encoding.h"
#include "ruby/re.h"
#include "ruby/version.h"

#define STR_ENC_GET(str) rb_enc_from_index(ENCODING_GET(str))

#ifndef RUBY_API_VERSION_CODE
#define RUBY_BEFORE_2_2 1
#else
#define RUBY_BEFORE_2_2 (RUBY_API_VERSION_CODE < 20200)
#endif /* ifndef RUBY_API_VERSION_CODE */

#define RB_NEGATE(VAL) (VAL == Qtrue ? Qfalse : Qtrue)

void Init_str_blank(void);
void Init_ary_blank(void);
void Init_obj_blank(void);

#endif /* FASTER_SUPPORT_H */
