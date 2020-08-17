#ifndef BLISS_BLISS_COMMAND_H
#define BLISS_BLISS_COMMAND_H

#include <string>
#include <vector>
#include "../bliss_exec/bliss_exec.h"
#include "../bliss_option/bliss_option.h"

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

#endif
