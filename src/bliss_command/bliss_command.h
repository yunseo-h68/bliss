#ifndef BLISS_BLISS_COMMAND_H
#define BLISS_BLISS_COMMAND_H

#include <string>
#include "../bliss_exec/bliss_exec.h"
#include "../bliss_option/bliss_option.h"

using namespace std;

class BlissCommand : public BlissExec {
	public:
		BlissCommand(string name);
		~BlissCommand();
		string usage();
		int options_count();
		BlissCommand* set_name(string name);
		BlissCommand* set_description(string name);
		BlissCommand* set_usage(string usage);
		BlissOption* GetOptionByIndex(int index);
		BlissOption* GetOptionByName(string name);
		BlissCommand* AddOption(BlissOption* option);
		BlissCommand* DeleteOptionByName(string name);

	private:
		string usage_;
		int options_count_;
		BlissOption** options_;
};

#endif
