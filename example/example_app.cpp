#include <iostream>
#include <string>
#include "../include/bliss.hpp"

class SubHello : public BlissCommand {
	public:
		SubHello() {
			BlissCommand::set_name("hello");
			BlissCommand::set_description("print \'Hello BLISS SUBCOMMAND\'");
		}

		virtual void Exec() {
			std::cout << "HELLO BLISS SUBCOMMAND\n";
		}
};

class OptionHello : public BlissOption {
	public:
		OptionHello() {
			BlissOption::set_name("hello");
			BlissOption::set_name_short("h");
			BlissOption::set_description("print \'HELLO BLISS OPTION\'");
		}

		virtual void Exec() {
			std::cout << "HELLO BLISS OPTION\n";
		}
};

BlissApp* ExampleApp() {
	BlissApp* exampleApp = new BlissApp("exampleApp");
	SubHello* subHello = new SubHello; 
	OptionHello* optionHello = new OptionHello;
	
	exampleApp->set_description("example of bliss")
		      ->set_usage("exampleApp [OPTIONS] [SUBCOMMANDS]")
			  ->AddSubcommand(subHello)
			  ->AddOption(optionHello);

	return exampleApp;
}
