#ifndef BLISS_BLISS_OPTION_H
#define BLISS_BLISS_OPTION_H

struct bliss_option {
	struct option* (*get_option)(struct bliss_option* this);
	struct bliss_option* (*set_name)(struct bliss_option* this, const char* name);
	struct bliss_option* (*set_name_short)(struct bliss_option* this, const char* name_short);
	struct bliss_optoin* (*set_description)(struct bliss_option* this, const char* description);
	struct bliss_option* (*set_exec_func)(
			struct bliss_option* this,
			void (*option_exec_func)(void));
};

struct bliss_option* new_bliss_option(const char* name);
void delete_bliss_option(struct bliss_option* bliss_option_info);

#endif
