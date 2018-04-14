#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include "parson.h"

extern int get_system_guid(char* system_guid_out, const char* const payload_json);

#endif