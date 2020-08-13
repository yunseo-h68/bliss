#ifndef BLISS_BLISS_APP_H
#define BLISS_BLISS_APP_H

#include <string>
#include "../bliss_command/bliss_command.h"

class BlissApp : public BlissCommand {
	public:
		BlissApp();
		BlissApp(std::string name);
		~BlissApp();
		int subcommands_count();
		virtual BlissApp* set_name(std::string name);
		virtual BlissApp* set_description(std::string description);
		virtual BlissApp* set_usage(std::string usage);
		virtual BlissApp* AddOption(BlissOption* option);
		virtual BlissApp* DeleteOptionByName(std::string name);
		BlissApp* AddSubcommand(BlissCommand* subcommand);
		BlissApp* DeleteSubcommandByName(std::string name);
		BlissCommand* GetSubcommandByIndex(int index);
		BlissCommand* GetSubcommandByName(std::string name);
		void PrintHelp();
		virtual void Exec();

	private:
		int subcommands_count_;
		BlissCommand** subcommands_;
};

#endif
