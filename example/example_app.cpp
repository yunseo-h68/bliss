#include <iostream>
#include <string>
#include "../include/bliss.hpp"

class ExampleApp : public BlissApp {
	public:
		ExampleApp() {
			BlissApp::set_name("exampleApp");
			BlissApp::set_description("example of bliss");
			BlissApp::set_usage("exampleApp [OPTIONS] [SUBCOMMANDS]");
		}
};

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

BlissApp* CreateApp() {
	ExampleApp* app = new ExampleApp;
	SubHello* subHello = new SubHello; 
	OptionHello* optionHello = new OptionHello;
	
	app->AddSubcommand(subHello)
		->AddOption(optionHello);

	return app;
}
