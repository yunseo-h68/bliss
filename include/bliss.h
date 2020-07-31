#ifndef BLISS_H
#define BLISS_H

struct bliss_option {
	struct bliss_option* (*set_name)(
			struct bliss_option* this,
			const char* name);
	struct bliss_option* (*set_name_short)(
			struct bliss_option* this,
			const char* name_short);
	struct bliss_option* (*set_description)(
			struct bliss_option* this,
			const char* description);
	struct bliss_option* (*set_exec_func)(
			struct bliss_option* this,
			void (*option_exec_func)(void));
};

struct bliss_app {
	int (*exec)(struct bliss_app* this, int argc, char* argv[]);
	void (*print_help)(struct bliss_app* this);
	char* (*get_name)(struct bliss_app* this);
	char* (*get_description)(struct bliss_app* this);
	char* (*get_usage)(struct bliss_app* this);
	struct bliss_version* (*get_version)(struct bliss_app* this);
	struct bliss_app* (*set_version)(
			struct bliss_app* this, 
			const char* version_string);
	struct bliss_app* (*add_subcommand)(
			struct bliss_app* this,
			struct bliss_app* subcommand);
	struct bliss_app* (*add_option)(
			struct bliss_app* this,
			struct bliss_option* option);
};

struct bliss_version {
	char* (*to_string)(struct bliss_version* this);
	int (*release)(struct bliss_version* this);
	int (*major)(struct bliss_version* this);
	int (*minor)(struct bliss_version* this);
	struct bliss_version* (*set_version)(
			struct bliss_version* this,
			const char* version_string);
};

struct bliss_app* new_bliss_app(const char* name);
void delete_bliss_app(struct bliss_app* bliss_app_info);

struct bliss_option* new_bliss_option(const char* name);
void delete_bliss_option(struct bliss_option* bliss_option_info);

struct bliss_version* new_bliss_version(const char* version_string);
void delete_bliss_version(struct bliss_version* bliss_version_info);

#endif
