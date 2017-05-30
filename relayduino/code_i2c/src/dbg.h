#ifndef DBG_H_
#define DBG_H_

#include "arduino.h"

#define dbg(x) Serial.println(x);
#define dbgf(msg, arg1) { char dbg_buf[64]; snprintf(dbg_buf, 63, msg, arg1); Serial.println(dbg_buf); }
#define dbgf2(msg, arg1, arg2) { char dbg_buf[64]; snprintf(dbg_buf, 63, msg, arg1, arg2); Serial.println(dbg_buf); }
#define dbgf4(msg, arg1, arg2, arg3, arg4) { char dbg_buf[64]; snprintf(dbg_buf, 63, msg, arg1, arg2, arg3, arg4); Serial.println(dbg_buf); }


#endif
