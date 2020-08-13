#ifndef BLISS_BLISS_EXEC_H
#define BLISS_BLISS_EXEC_H

#include <string>

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

#endif
