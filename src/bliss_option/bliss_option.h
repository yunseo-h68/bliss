#ifndef BLISS_BLISS_OPTION_H
#define BLISS_BLISS_OPTION_H

#include <string>
#include "../bliss_exec/bliss_exec.h"

using namespace std;

class BlissOption : public BlissExec {
	public:
		BlissOption();
		BlissOption(string name);
		~BlissOption();
		string name_short();
		virtual BlissOption* set_name(string name);
		 BlissOption* set_name_short(string name_short);
		virtual BlissOption* set_description(string description);

	private:
		string name_short_;
};

#endif
