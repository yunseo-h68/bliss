#ifndef BLISS_BLISS_EXEC_H
#define BLISS_BLISS_EXEC_H

#include <string>
using namespace std;

class BlissExec {
	public:
		BlissExec();
		~BlissExec();
		string name();
		string description();
		virtual BlissExec* set_name(string name);
		virtual BlissExec* set_description(string description);

		virtual void Exec(){}
	private:
		string name_;
		string description_;
};

#endif
