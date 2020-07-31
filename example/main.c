#include <stdio.h>
#include "../include/bliss.h"

static struct bliss_app* my_app;

void print_help_func()
{
	my_app->print_help(my_app);
}

void print_version_func()
{
	struct bliss_version* version_tmp = my_app->get_version(my_app);
	printf("%s Version %s\n", my_app->get_name(my_app), version_tmp->to_string(version_tmp));
}

void add_help_option()
{
	struct bliss_option* help_option = new_bliss_option("help");
	help_option->set_name_short(help_option, "h")
		->set_description(help_option, "Display this information")
		->set_exec_func(help_option, print_help_func);
	my_app->add_option(my_app, help_option);
}

void add_version_option()
{
	struct bliss_option* version_option = new_bliss_option("version");
	version_option->set_name_short(version_option, "v")
		->set_description(version_option, "Display version information")
		->set_exec_func(version_option, print_version_func);
	my_app->add_option(my_app, version_option);
}

void add_hello_subcommand()
{
	struct bliss_app* hello_subcommand = new_bliss_app("hello");
	my_app->add_subcommand(my_app, hello_subcommand);
}

int main(int argc, char* argv[]) {
	int return_value;
	my_app = new_bliss_app("example");

	my_app->set_version(my_app, "1.0.0")
		->set_description(my_app, "this is example of bliss");
	
	add_help_option();
	add_version_option();
	add_hello_subcommand();
	
	return_value = my_app->exec(my_app, argc, argv);

	delete_bliss_app(my_app);
	
	return return_value;
}
