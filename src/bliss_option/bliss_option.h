#ifndef BLISS_BLISS_OPTION_H
#define BLISS_BLISS_OPTION_H

#include <string>
#include "../bliss_exec/bliss_exec.h"

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

#endif
