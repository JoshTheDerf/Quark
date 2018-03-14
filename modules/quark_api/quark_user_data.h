#ifndef QUARK_API_USER_DATA_H
#define QUARK_API_USER_DATA_H
#include <stdint.h>
#include "quark_user_proxy.h"

class QuarkUserProxy;

typedef struct {
	uint32_t id;
	void(*notify_handler)(char*);
	QuarkUserProxy* proxy_object;
} QuarkUserData;

#endif // QUARK_API_USER_DATA_H
