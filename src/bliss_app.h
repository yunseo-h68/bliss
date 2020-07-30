#ifndef BLISS_BLISS_APP_H
#define BLISS_BLISS_APP_H

struct bliss_app {
	void (*print_help)(struct bliss_app* this);
	char* (*get_name)(struct bliss_app* this);
	char* (*get_description)(struct bliss_app* this);
	char* (*get_usage)(struct bliss_app* this);
	struct bliss_version* (*get_version)(struct bliss_app* this);
	struct bliss_app* (*set_version)(struct bliss_app* this, const char* version_string);
	struct bliss_app* (*add_subcommand)(struct bliss_app* this, struct bliss_app* subcommand);
	struct bliss_app* (*add_option)(struct bliss_app* this, struct bliss_option* option);
};

struct bliss_app* new_bliss_app(const char* name);
void delete_bliss_app(struct bliss_app* bliss_app_info);
#endif
