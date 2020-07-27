#ifndef BLISS_OPTION_H
#define BLISS_OPTION_H

struct option {
	void (*exec)(struct option* this);
	char* (*get_name)(struct option* this);
	char* (*get_name_short)(struct option* this);
	char* (*get_description)(struct option* this);
	struct option* (*set_name)(
			struct option* this, const char* name);
	struct option* (*set_name_short)(
			struct option* this, const char* name_short);
	struct option* (*set_description)(
			struct option* this, const char* description);
	struct option* (*set_exec_func)(
			struct option* this, void (*option_exec_func)(void));
}

struct option* new_option(const char* name);

#endif
