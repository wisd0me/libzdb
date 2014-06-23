
#include <errno.h>

#include "Config.h"
#include "Thread.h"

static void (*_CREATE_FUNC)(ThreadData_T *key);
static void (*_SET_FUNC)(ThreadData_T key, void *value);
static void *(*_GET_FUNC)(ThreadData_T key);

void ThreadData_define_create_func(void (*func)(ThreadData_T *)) {
	_CREATE_FUNC = func;
}

void ThreadData_define_set_func(void (*func)(ThreadData_T, void *)) {
	_SET_FUNC = func;
}

void ThreadData_define_get_func(void *(*func)(ThreadData_T)) {
	_GET_FUNC = func;
}

void ThreadData_create(ThreadData_T *key) {
	if (_CREATE_FUNC) {
		_CREATE_FUNC(key);
		return;
	}

	wrapper(pthread_key_create(key, NULL));
}

void ThreadData_set(ThreadData_T key, void *value) {
	if (_SET_FUNC) {
		_SET_FUNC(key, value);
		return;
	}

	pthread_setspecific(key, value);
}

void *ThreadData_get(ThreadData_T key) {
	if (_GET_FUNC)
		return _GET_FUNC(key);

	return pthread_getspecific(key);
}
