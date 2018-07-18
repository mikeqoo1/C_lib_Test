#include "cmap.h"

void fail(char *message) {
	perror(message);
	exit(1);
}

int delete(const char *key) {
	ENTRY e = {key: (char *)key}, *p;
	p = hsearch(e, FIND);
	if (p) {
		p->key="NULL"; //key不能指向空指標
		p->data=NULL;
		return 1;
	} else
		return 0;
}

int fetch(const char *key, intptr_t *value) {
	ENTRY e = {key: (char *)key}, *p;
	p = hsearch(e, FIND);
	if (p) {
		*value = (intptr_t)p->data;
		return 1;
	} else
		return 0;
}

void store(const char *key, void *value) {
	ENTRY e = {key: (char *)key}, *p;
	p = hsearch(e, ENTER);
	if (p == NULL)
		fail("hsearch");
	p->data = (void *)value;
}