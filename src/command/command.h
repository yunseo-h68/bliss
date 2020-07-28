#ifndef BLISS_COMMAND_H
#define BLISS_COMMAND_H

struct command {
	void (*exec)(struct command* this);
	char* (*get_name)(struct command* this);
	char* (*get_description)(struct command* this);
	char* (*get_usage)(struct command* this);
	int (*get_options_count)(struct command* this);
	int (*get_subcommands_count)(struct command* this);
	struct option* (*get_option_by_index)(struct command* this, int index);
	struct option* (*get_option)(struct command* this, const char* option_name);
	struct command* (*get_subcommand_by_index)(struct command* this, int index);
	struct command* (*get_subcommand)(struct command* this, const char* subcommand_name);
	struct command* (*set_name)(struct command* this, const char* name);
	struct command* (*set_description)(struct command* this, const char* description);
	struct command* (*set_usage)(struct command* this, const char* usage);
	struct command* (*add_subcommand)(struct command* this, struct command subcommand);
	struct command* (*delete_subcommand)(struct command* this, const char* subcommand_name);
	struct command* (*add_option)(struct command* this, struct option option_info);
	struct command* (*delete_option)(struct command* this, const char* option_name);
};

struct  command* new_command(const char* name);
void delete_command(struct command* command_info);

#endif
