#ifndef BLISS_BLISS_EXEC_H
#define BLISS_BLISS_EXEC_H

#include <string>
using namespace std;

class BlissExec {
	public:
		BlissExec();
		~BlissExec();
		void Init();
		string name();
		string description();
		void set_name(string name);
		void set_description(string description);

		virtual void Exec(){}
	private:
		string name_;
		string description_;
};

#endif
