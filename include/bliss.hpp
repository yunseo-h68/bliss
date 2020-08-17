#ifndef BLISS_H
#define BLISS_H

#include <string>
#include <vector>

class BlissExec {
	public:
		BlissExec();
		~BlissExec();
		std::string name();
		std::string description();
		virtual BlissExec* set_name(std::string name);
		virtual BlissExec* set_description(std::string description);

		virtual void Exec(){}
	private:
		std::string name_;
		std::string description_;
};

class BlissOption : public BlissExec {
	public:
		BlissOption();
		BlissOption(std::string name);
		~BlissOption();
		std::string name_short();
		virtual BlissOption* set_name(std::string name);
		BlissOption* set_name_short(std::string name_short);
		virtual BlissOption* set_description(std::string description);

	private:
		std::string name_short_;
};

class BlissCommand : public BlissExec {
	public:
		BlissCommand();
		BlissCommand(std::string name);
		~BlissCommand();
		std::string usage();
		int options_count();
		virtual BlissCommand* set_name(std::string name);
		virtual BlissCommand* set_description(std::string description);
		virtual BlissCommand* set_usage(std::string usage);
		BlissOption* GetOptionByIndex(int index);
		BlissOption* GetOptionByName(std::string name);
		BlissOption* GetOptionByNameShort(std::string name_short);
		virtual BlissCommand* AddOption(BlissOption* option);
		virtual BlissCommand* DeleteOptionByName(std::string name);

	private:
		std::string usage_;
		std::vector<BlissOption*> options_;
};

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
		std::vector<BlissCommand*> subcommands_;
};

int bliss_run(BlissApp* app, int argc, char* argv[]);

#endif
