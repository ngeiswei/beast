/* GIMP RGBA C-Source image dump 1-byte-run-length-encoded (mic.c) */

#define MIC_WIDTH (64)
#define MIC_HEIGHT (64)
#define MIC_BYTES_PER_PIXEL (4) /* 3:RGB, 4:RGBA */
#define MIC_RLE_PIXEL_DATA ((guint8*) MIC_rle_pixel_data)
#define MIC_RUN_LENGTH_DECODE(image_buf, rle_data, size, bpp) do \
{ guint __bpp; guint8 *__ip; const guint8 *__il, *__rd; \
  __bpp = (bpp); __ip = (image_buf); __il = __ip + (size) * __bpp; \
  __rd = (rle_data); if (__bpp > 3) { /* RGBA */ \
    while (__ip < __il) { guint __l = *(__rd++); \
      if (__l & 128) { __l = __l - 128; \
        do { memcpy (__ip, __rd, 4); __ip += 4; } while (--__l); __rd += 4; \
      } else { __l *= 4; memcpy (__ip, __rd, __l); \
               __ip += __l; __rd += __l; } } \
  } else { /* RGB */ \
    while (__ip < __il) { guint __l = *(__rd++); \
      if (__l & 128) { __l = __l - 128; \
        do { memcpy (__ip, __rd, 3); __ip += 3; } while (--__l); __rd += 3; \
      } else { __l *= 3; memcpy (__ip, __rd, __l); \
               __ip += __l; __rd += __l; } } \
  } } while (0)
static const guint8 MIC_rle_pixel_data[5361] =
("\377\0\0\0\0\377\0\0\0\0\377\0\0\0\0\247\0\0\0\0\204\0\0\0\1\270\0\0\0\0\13"
 "\0\0\0\1\0\0\0\3???\4UUU\6___\10LLL\12\\\\\\\13EEE\13HHH\7\0\0\0\3\0\0\0\1"
 "\263\0\0\0\0\20\0\0\0\1\0\0\0\3\0\0\0\5LLL\12***\"\33\33\33O\25\25\25p\20"
 "\20\20\223\6\6\6\312\7\7\7\276\4\4\4\271\15\15\15H\7\7\7\35""333\5\0\0\0\3"
 "\0\0\0\1\257\0\0\0\0\23\0\0\0\2\0\0\0\4\0\0\0\10""000\25\13\13\13\214\1\1"
 "\1\354\30\30\30\377###\377...\377333\377(((\377\"\"\"\377\11\11\11\377\6\6"
 "\6\267\11\11\11qaaa\15\177\177\177\6\177\177\177\4\177\177\177\2\254\0\0\0"
 "\0\25\0\0\0\2\0\0\0\5\27\27\27\13""888\33\4\4\4\304\33\33\33\377>>>\377``"
 "`\377www\377\201\201\201\377\177\177\177\377}}}\377iii\377QQQ\377555\377\27"
 "\27\27\377\3\3\3\314<<<$uuu\15mmm\7UUU\3\252\0\0\0\0\27\0\0\0\1\0\0\0\4\0"
 "\0\0\11&&&\32\2\2\2\370---\377SSS\377\206\206\206\377\217\217\217\377\177"
 "\177\177\377\230\230\230\377\244\244\244\377\231\231\231\377\206\206\206\377"
 "ttt\377]]]\377CCC\377\33\33\33\377\3\3\3\340===/UUU\22HHH\7\0\0\0\2\251\0"
 "\0\0\0\30\0\0\0\2\0\0\0\6\21\21\21\17\2\2\2\321(((\377ZZZ\377\203\203\203"
 "\377\242\242\242\377\252\252\252\377\243\243\243\377\255\255\255\377\254\254"
 "\254\377\221\221\221\377vvv\377zzz\377jjj\377WWW\377888\377\30\30\30\377\13"
 "\13\13\252;;;%///\20\0\0\0\6\0\0\0\1\250\0\0\0\0\7\0\0\0\3\0\0\0\12\16\16"
 "\16/\26\26\26\377HHH\377ppp\377\224\224\224\377\202\263\263\263\377\20\264"
 "\264\264\377\260\260\260\377\240\240\240\377\217\217\217\377\203\203\203\377"
 "zzz\377lll\377ddd\377XXX\377***\377\7\7\7\377\27\27\27c///\33\0\0\0\12\0\0"
 "\0\2UUU\0\246\0\0\0\0\32\0\0\0\1\0\0\0\5\23\23\23\15\4\4\4\233!!!\377VVV\377"
 "sss\377\222\222\222\377\253\253\253\377\233\233\233\377\254\254\254\377\255"
 "\255\255\377\213\213\213\377\177\177\177\377\206\206\206\377sss\377kkk\377"
 "ddd\377\\\\\\\377@@@\377\22\22\22\377\3\3\3\320\27\27\27*\0\0\0\17\0\0\0\4"
 "HHH\0\246\0\0\0\0\32\0\0\0\2\0\0\0\5\31\31\31\24\0\0\0\367888\377fff\377}"
 "}}\377\227\227\227\377\245\245\245\377\250\250\250\377\264\264\264\377\255"
 "\255\255\377\223\223\223\377\207\207\207\377\177\177\177\377ggg\377eee\377"
 "^^^\377RRR\377<<<\377\31\31\31\377\2\2\2\332\15\15\15O\0\0\0\22\0\0\0\6//"
 "/\0\246\0\0\0\0\32\0\0\0\1\0\0\0\6\3\3\3""8\14\14\14\356===\377```\377rrr"
 "\377\222\222\222\377\216\216\216\377\234\234\234\377\244\244\244\377\232\232"
 "\232\377\207\207\207\377|||\377kkk\377aaa\377]]]\377SSS\377FFF\377777\377"
 "!!!\377\3\3\3\324\5\5\5{\0\0\0\21\0\0\0\5///\0\246\0\0\0\0\16\0\0\0\1\0\0"
 "\0\4\0\0\0\212\12\12\12\361CCC\377^^^\377vvv\377\221\221\221\377\225\225\225"
 "\377\221\221\221\377\204\204\204\377\211\211\211\377\202\202\202\377ooo\377"
 "\202^^^\377\12TTT\377JJJ\377===\377777\377&&&\377\2\2\2\346\3\3\3\201\0\0"
 "\0\17\0\0\0\4\27\27\27\0\247\0\0\0\0\31\0\0\0\13\0\0\0\214\13\13\13\360??"
 "?\377]]]\377ooo\377\205\205\205\377\213\213\213\377}}}\377ooo\377\177\177"
 "\177\377rrr\377^^^\377RRR\377PPP\377FFF\377AAA\377<<<\377222\377$$$\377\1"
 "\1\1\341\2\2\2\204\0\0\0\15\0\0\0\2\15\15\15\0\247\0\0\0\0\31\0\0\0\1\0\0"
 "\0\261\1\1\1\300)))\377^^^\377iii\377sss\377yyy\377qqq\377rrr\377ttt\377c"
 "cc\377XXX\377PPP\377GGG\377<<<\377CCC\377EEE\377222\377\33\33\33\377\1\1\1"
 "\311\0\0\0n\0\0\0\10\0\0\0\1\5\5\5\0\247\0\0\0\0\31\0\0\0\1\24\24\24\3553"
 "33\377777\377555\377aaa\377ppp\377ggg\377\\\\\\\377lll\377iii\377WWW\377O"
 "OO\377HHH\377@@@\377888\377???\377<<<\377---\377\26\26\26\377\0\0\0\362\0"
 "\0\0\25\0\0\0\5\2\2\2\0\3\3\3\0\246\0\0\0\0\32\0\0\0\12\14\14\14\313EEE\377"
 "UUU\377___\377MMM\377$$$\377OOO\377```\377XXX\377]]]\377QQQ\377EEE\377FFF"
 "\377BBB\377;;;\377444\377333\377---\377!!!\377\12\12\12\372\2\2\2v\0\0\0\13"
 "\0\0\0\1\1\1\1\0\2\2\2\0\245\0\0\0\0\32\0\0\0\2\6\6\6\322GGG\377]]]\377ss"
 "s\377{{{\377sss\377SSS\377\34\34\34\377>>>\377PPP\377III\377@@@\377FFF\377"
 "III\377>>>\377666\377...\377'''\377###\377\27\27\27\377\3\3\3\267\0\0\0\27"
 "\0\0\0\5\33\33\33\0\1\1\1\0\246\0\0\0\0\31\0\0\0^###\377VVV\377yyy\377\222"
 "\222\222\377\221\221\221\377\200\200\200\377nnn\377SSS\377\"\"\"\377***\377"
 "@@@\377???\377BBB\377AAA\377;;;\377333\377+++\377!!!\377\30\30\30\377\11\11"
 "\11\322\0\0\0""8\0\0\0\10\0\0\0\1\26\26\26\0\246\0\0\0\0\33\0\0\0""7\20\20"
 "\20\377III\377vvv\377\231\231\231\377\243\243\243\377\227\227\227\377\204"
 "\204\204\377www\377ggg\377KKK\377\34\34\34\377\32\32\32\377888\377===\377"
 "888\377666\377---\377$$$\377\25\25\25\377\11\11\11\306\3\3\3>\0\0\0\13\0\0"
 "\0\2!!!\0\12\12\12\0\2\2\2\0\244\0\0\0\0\20\0\0\0D\7\7\7\377555\377nnn\377"
 "\230\230\230\377\254\254\254\377\242\242\242\377\215\215\215\377\205\205\205"
 "\377~~~\377mmm\377PPP\377:::\377\35\35\35\377\22\22\22\377)))\377\202---\377"
 "\11\37\37\37\377\21\21\21\377\7\7\7\377\11\11\11""0\0\0\0\13\0\0\0\3###\0"
 "\27\27\27\0\3\3\3\0\244\0\0\0\0\33\0\0\0%\6\6\6\377\35\35\35\377eee\377\214"
 "\214\214\377\252\252\252\377\251\251\251\377\223\223\223\377\207\207\207\377"
 "\204\204\204\377zzz\377eee\377QQQ\377BBB\377222\377\30\30\30\377\6\6\6\377"
 "\21\21\21\377\16\16\16\377\11\11\11\377\2\2\2\255\25\25\25\27\31\31\31\12"
 "\0\0\0\3!!!\0\30\30\30\0\11\11\11\0\244\0\0\0\0\34\0\0\0\3\2\2\2\350\14\14"
 "\14\377VVV\377\201\201\201\377\242\242\242\377\252\252\252\377\233\233\233"
 "\377\214\214\214\377\204\204\204\377|||\377ooo\377___\377OOO\377>>>\377))"
 ")\377\26\26\26\377\1\1\1\316\0\0\0\331\1\1\1\305\11\11\11?$$$\16\37\37\37"
 "\10\0\0\0\2$$$\0\25\25\25\0\11\11\11\0\3\3\3\0\243\0\0\0\0\34\0\0\0\6\0\0"
 "\0v\27\27\27\377III\377}}}\377\240\240\240\377\252\252\252\377\240\240\240"
 "\377\221\221\221\377\211\211\211\377\177\177\177\377qqq\377eee\377YYY\377"
 "GGG\377000\377\34\34\34\377\13\13\13\377\1\1\1t\16\16\16\21\7\7\7\35\0\0\0"
 "\15\0\0\0\3\0\0\0\1\37\37\37\0\21\21\21\0\7\7\7\0\11\11\11\0\243\0\0\0\0\23"
 "\0\0\0\11\0\0\0\211\5\5\5\377JJJ\377xxx\377\232\232\232\377\250\250\250\377"
 "\240\240\240\377\223\223\223\377\214\214\214\377\202\202\202\377uuu\377gg"
 "g\377\\\\\\\377MMM\377888\377###\377\17\17\17\377\15\15\15\230\202\0\0\0\2"
 "\202\0\0\0\1\6\21\21\21\0\16\16\16\0\11\11\11\0\2\2\2\0\25\25\25\0\31\31\31"
 "\0\243\0\0\0\0\34\0\0\0S\0\0\0\377\30\30\30\377rrr\377\232\232\232\377\250"
 "\250\250\377\234\234\234\377\220\220\220\377\214\214\214\377\205\205\205\377"
 "vvv\377iii\377\\\\\\\377MMM\377;;;\377!!!\377\22\22\22\377\11\11\11\377\0"
 "\0\0\1>>>\0)))\0\26\26\26\0\1\1\1\0\0\0\0\0\1\1\1\0\11\11\11\0$$$\0\37\37"
 "\37\0\243\0\0\0\0\32\0\0\0'\1\1\1\377\11\11\11\377ggg\377\227\227\227\377"
 "\255\255\255\377\244\244\244\377\221\221\221\377\211\211\211\377\203\203\203"
 "\377yyy\377kkk\377___\377RRR\377>>>\377'''\377\24\24\24\377\0\0\0\307\0\0"
 "\0\7GGG\0""000\0\34\34\34\0\13\13\13\0\1\1\1\0\16\16\16\0\7\7\7\0\245\0\0"
 "\0\0\30\0\0\0\24\2\2\2\377\5\5\5\377___\377\215\215\215\377\254\254\254\377"
 "\252\252\252\377\225\225\225\377\206\206\206\377\202\202\202\377yyy\377mm"
 "m\377___\377TTT\377FFF\377---\377\32\32\32\377\0\0\0\225\0\0\0\31MMM\0""8"
 "88\0###\0\17\17\17\0\15\15\15\0\247\0\0\0\0\30\0\0\0\3\0\0\0\263\2\2\2\377"
 "KKK\377\202\202\202\377\246\246\246\377\255\255\255\377\232\232\232\377\206"
 "\206\206\377~~~\377yyy\377mmm\377bbb\377VVV\377FFF\377222\377\32\32\32\377"
 "\11\11\11\275\0\0\0\40MMM\0;;;\0!!!\0\22\22\22\0\11\11\11\0\250\0\0\0\0\26"
 "\0\0\0s\1\1\1\377222\377rrr\377\232\232\232\377\255\255\255\377\236\236\236"
 "\377\212\212\212\377\177\177\177\377www\377mmm\377ccc\377YYY\377JJJ\37766"
 "6\377\33\33\33\377\16\16\16\377\0\0\0\24RRR\0>>>\0'''\0\24\24\24\0\250\0\0"
 "\0\0\27\0\0\0\1\0\0\0M\4\4\4\376///\377fff\377\216\216\216\377\246\246\246"
 "\377\241\241\241\377\220\220\220\377\201\201\201\377xxx\377ooo\377eee\377"
 "[[[\377MMM\377999\377\35\35\35\377\17\17\17\377\0\0\0""6TTT\0FFF\0---\0\32"
 "\32\32\0\251\0\0\0\0\27\0\0\0*\3\3\3\372!!!\377]]]\377\177\177\177\377\240"
 "\240\240\377\245\245\245\377\223\223\223\377\204\204\204\377{{{\377qqq\377"
 "ggg\377^^^\377OOO\377;;;\377!!!\377\21\21\21\377\0\0\0A\0\0\0\1FFF\0""222"
 "\0\32\32\32\0\11\11\11\0\250\0\0\0\0\27\0\0\0\3\1\1\1\347\25\25\25\377UUU"
 "\377vvv\377\227\227\227\377\245\245\245\377\232\232\232\377\212\212\212\377"
 "\177\177\177\377ttt\377jjj\377___\377QQQ\377>>>\377\"\"\"\377\21\21\21\377"
 "\0\0\0]YYY\0JJJ\0""666\0\33\33\33\0\16\16\16\0\250\0\0\0\0\27\0\0\0\1\2\2"
 "\2\267\15\15\15\377OOO\377qqq\377\231\231\231\377\246\246\246\377\236\236"
 "\236\377\220\220\220\377\205\205\205\377yyy\377lll\377___\377PPP\377>>>\377"
 "###\377\14\14\14\377\0\0\0\224\0\0\0\2MMM\0""999\0\35\35\35\0\17\17\17\0\251"
 "\0\0\0\0\26\0\0\0r\3\3\3\377BBB\377iii\377\226\226\226\377\260\260\260\377"
 "\247\247\247\377\225\225\225\377\212\212\212\377}}}\377nnn\377aaa\377QQQ\377"
 "===\377(((\377\15\15\15\374\0\0\0~\0\0\0\32OOO\0;;;\0!!!\0\21\21\21\0\251"
 "\0\0\0\0\26\0\0\0\15\2\2\2\377000\377]]]\377\213\213\213\377\252\252\252\377"
 "\255\255\255\377\232\232\232\377\215\215\215\377\177\177\177\377ppp\377cc"
 "c\377RRR\377@@@\377...\377\21\21\21\377\0\0\0}\0\0\0\40QQQ\0>>>\0\"\"\"\0"
 "\21\21\21\0\252\0\0\0\0\25\7\7\7\377$$$\377RRR\377yyy\377\236\236\236\377"
 "\247\247\247\377\232\232\232\377\212\212\212\377\202\202\202\377sss\377dd"
 "d\377UUU\377CCC\377000\377\25\25\25\377\4\4\4\235\0\0\0'PPP\0>>>\0###\0\14"
 "\14\14\0\252\0\0\0\0\25\0\0\0\4\33\33\33\377HHH\377ggg\377\206\206\206\377"
 "\233\233\233\377\227\227\227\377\213\213\213\377\201\201\201\377uuu\377gg"
 "g\377XXX\377FFF\377444\377\31\31\31\377\11\11\11\314\0\0\0)\0\0\0\1===\0("
 "((\0\15\15\15\0\253\0\0\0\0\24\0\0\0\32***\377UUU\377sss\377\211\211\211\377"
 "\217\217\217\377\212\212\212\377\205\205\205\377xxx\377jjj\377\\\\\\\377H"
 "HH\377777\377\36\36\36\377\14\14\14\374\0\0\0""7\0\0\0\2@@@\0...\0\21\21\21"
 "\0\254\0\0\0\0\4\0\0\0\1\"\"\"\377444\377rrr\377\202\203\203\203\377\16\200"
 "\200\200\377www\377jjj\377\\\\\\\377LLL\377999\377###\377\13\13\13\377\0\0"
 "\0X\0\0\0\5CCC\0""000\0\25\25\25\0\4\4\4\0\215\0\0\0\0\3\0\0\0\1\0\0\0\12"
 "\0\0\0\30\202\0\0\0\34\3\0\0\0\30\0\0\0\12\0\0\0\1\230\0\0\0\0\22\0\0\0\13"
 "\21\21\21\377000\377uuu\377vvv\377rrr\377hhh\377[[[\377KKK\377<<<\377'''\377"
 "\15\15\15\377\0\0\0R\0\0\0\12FFF\0""444\0\31\31\31\0\11\11\11\0\213\0\0\0"
 "\0\6\0\0\0\2\0\0\0\20\0\0\0\"\0\0\0.\0\0\0Q\0\0\0\214\202\0\0\0\234\5\0\0"
 "\0\214\0\0\0P\0\0\0)\0\0\0\16\0\0\0\2\226\0\0\0\0\21\0\0\0\5\0\0\0""6\37\37"
 "\37\377\"\"\"\377eee\377bbb\377WWW\377JJJ\377<<<\377---\377\7\7\7\376\0\0"
 "\0F\0\0\0\15HHH\0""777\0\36\36\36\0\14\14\14\0\212\0\0\0\0\10\0\0\0\2\0\0"
 "\0\22\0\0\0/\0\0\0i\0\0\0\260\0\0\0\303\0\0\0\273\0\0\0\301\202\0\0\0\304"
 "\6\0\0\0\303\0\0\0\301\0\0\0\266\0\0\0`\0\0\0\26\0\0\0\2\225\0\0\0\0\20\0"
 "\0\0\23\0\0\0r\0\0\0\306&&&\377\22\22\22\377EEE\377FFF\377:::\377///\377\15"
 "\15\15\377\11\11\11q\0\0\0\10LLL\0""999\0###\0\13\13\13\0\212\0\0\0\0\11\0"
 "\0\0\11\0\0\0.\0\0\0r\0\0\0\273\0\0\0\302\0\0\0\300\0\0\0\233\0\0\0L\0\0\0"
 "-\202\0\0\0*\6\0\0\0""3\0\0\0k\0\0\0\274\0\0\0\302\0\0\0]\0\0\0\20\225\0\0"
 "\0\0\17\0\0\0#\0\0\0\266\0\0\0\312\0\0\0""9\0\0\0s\5\5\5\377'''\377---\377"
 "\31\31\31\377\30\30\30,[[[\0KKK\0<<<\0'''\0\15\15\15\0\211\0\0\0\0\12\0\0"
 "\0\2\0\0\0\24\0\0\0H\0\0\0\261\0\0\0\307\0\0\0\262\0\0\0X\0\0\0,\0\0\0\34"
 "\0\0\0\10\203\0\0\0\0\7\0\0\0\2\0\0\0\21\0\0\0?\0\0\0\261\0\0\0\273\0\0\0"
 "@\0\0\0\7\224\0\0\0\0\16\0\0\0(\0\0\0\307\0\0\0\310\0\0\0(\0\0\0\0\0\0\0O"
 "\7\7\7\210###\24bbb\0WWW\0JJJ\0<<<\0---\0\7\7\7\0\211\0\0\0\0\11\0\0\0\5\0"
 "\0\0&\0\0\0p\0\0\0\277\0\0\0\274\0\0\0f\0\0\0*\0\0\0\13\0\0\0\1\207\0\0\0"
 "\0\5\0\0\0\10\0\0\0J\0\0\0\307\0\0\0\227\0\0\0\34\224\0\0\0\0\4\0\0\0'\0\0"
 "\0\306\0\0\0\312\0\0\0)\202\0\0\0\0\10&&&\0\22\22\22\0EEE\0FFF\0:::\0///\0"
 "\15\15\15\0\11\11\11\0\210\0\0\0\0\10\0\0\0\10\0\0\0""5\0\0\0\226\0\0\0\306"
 "\0\0\0\252\0\0\0E\0\0\0\21\0\0\0\2\212\0\0\0\0\4\0\0\0\"\0\0\0\247\0\0\0\277"
 "\0\0\0(\224\0\0\0\0\5\0\0\0\36\0\0\0\242\0\0\0\313\0\0\0@\0\0\0\6\203\0\0"
 "\0\0\5\5\5\5\0'''\0---\0\31\31\31\0\30\30\30\0\207\0\0\0\0\10\0\0\0\1\0\0"
 "\0\15\0\0\0D\0\0\0\256\0\0\0\306\0\0\0\210\0\0\0""1\0\0\0\10\214\0\0\0\0\4"
 "\0\0\0\10\0\0\0B\0\0\0\225\0\0\0\"\224\0\0\0\0\6\0\0\0\10\0\0\0F\0\0\0\305"
 "\0\0\0\240\0\0\0,\0\0\0\4\203\0\0\0\0\2\7\7\7\0###\0\210\0\0\0\0\10\0\0\0"
 "\3\0\0\0\27\0\0\0P\0\0\0\271\0\0\0\301\0\0\0k\0\0\0!\0\0\0\4\216\0\0\0\0\3"
 "\0\0\0\10\0\0\0\34\0\0\0\6\225\0\0\0\0\6\0\0\0\35\0\0\0\223\0\0\0\316\0\0"
 "\0\205\0\0\0+\0\0\0\5\212\0\0\0\0\11\0\0\0\3\0\0\0\23\0\0\0""2\0\0\0u\0\0"
 "\0\303\0\0\0\274\0\0\0W\0\0\0\26\0\0\0\2\247\0\0\0\0\10\0\0\0\5\0\0\0""2\0"
 "\0\0\245\0\0\0\317\0\0\0\233\0\0\0:\0\0\0\23\0\0\0\3\206\0\0\0\0\12\0\0\0"
 "\5\0\0\0\34\0\0\0""4\0\0\0u\0\0\0\275\0\0\0\305\0\0\0\256\0\0\0F\0\0\0\16"
 "\0\0\0\1\251\0\0\0\0\25\0\0\0\6\0\0\0""4\0\0\0\232\0\0\0\311\0\0\0\277\0\0"
 "\0v\0\0\0""6\0\0\0)\0\0\0&\0\0\0!\0\0\0\37\0\0\0!\0\0\0'\0\0\0?\0\0\0\232"
 "\0\0\0\304\0\0\0\302\0\0\0\264\0\0\0[\0\0\0'\0\0\0\10\254\0\0\0\0\14\0\0\0"
 "\5\0\0\0\"\0\0\0Y\0\0\0\261\0\0\0\276\0\0\0\305\0\0\0\311\0\0\0\302\0\0\0"
 "\255\0\0\0\247\0\0\0\262\0\0\0\304\202\0\0\0\306\5\0\0\0\251\0\0\0J\0\0\0"
 "&\0\0\0\14\0\0\0\1\256\0\0\0\0\17\0\0\0\1\0\0\0\14\0\0\0\"\0\0\0=\0\0\0\224"
 "\0\0\0\301\0\0\0\311\0\0\0\310\0\0\0\307\0\0\0\311\0\0\0\300\0\0\0\216\0\0"
 "\0;\0\0\0\40\0\0\0\10\264\0\0\0\0\4\0\0\0\5\0\0\0\32\0\0\0&\0\0\0(\203\0\0"
 "\0)\3\0\0\0&\0\0\0\31\0\0\0\4\377\0\0\0\0\377\0\0\0\0\346\0\0\0\0");

