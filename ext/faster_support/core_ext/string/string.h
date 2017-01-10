#ifndef FASTER_SUPPORT_STRING_H
#define FASTER_SUPPORT_STRING_H 1

#include "ruby.h"
#include "ruby/encoding.h"
#include "ruby/re.h"

#define STR_ENC_GET(str) rb_enc_from_index(ENCODING_GET(str))

#endif /* ifndef FASTER_SUPPORT_STRING_H */
