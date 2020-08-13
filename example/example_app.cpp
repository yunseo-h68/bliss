#include <iostream>
#include <string>
#include "../include/bliss.hpp"

class SubHello : public BlissCommand {
	public:
		virtual void Exec() {
			std::cout << "HELLO BLISS SUBCOMMAND\n";
		}
};

class OptionHello : public BlissOption {
	public:
		virtual void Exec() {
			std::cout << "HELLO BLISS OPTION\n";
		}
};

static SubHello* CreateSubHello() {
	SubHello* subcommandHello = new SubHello;
	subcommandHello->set_name("hello")
		           ->set_description("print \'HELLO BLISS SUBCOMMAND\'");

	return subcommandHello;
}

static OptionHello* CreateOptionHello() {
	OptionHello* optionHello = new OptionHello();
	optionHello->set_name("hello")
		       ->set_name_short("h")
			   ->set_description("print \'HELLO BLISS OPTION\'");
	return optionHello;
}

BlissApp* ExampleApp() {
	BlissApp* exampleApp = new BlissApp("exampleApp");
	SubHello* subHello = CreateSubHello();
	OptionHello* optionHello = CreateOptionHello();
	
	exampleApp->set_description("example of bliss")
		      ->set_usage("exampleApp [OPTIONS] [SUBCOMMANDS]")
			  ->AddSubcommand(subHello)
			  ->AddOption(optionHello);

	return exampleApp;
}
