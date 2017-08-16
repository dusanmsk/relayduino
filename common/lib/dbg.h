#ifndef DBG_H_
#define DBG_H_

#include "arduino.h"

#define dbg(format, args...) { char dbg_buf[64]; snprintf(dbg_buf, 63, format, args); Serial.println(dbg_buf); }
//#define dbg(format, args...) ;

#endif
