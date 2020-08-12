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
		BlissExec* set_name(string name);
		BlissExec* set_description(string description);

		virtual void Exec(){}
	private:
		string name_;
		string description_;
};

#endif
