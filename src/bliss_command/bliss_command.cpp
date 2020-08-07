#include <string>
#include <cstring>
#include "../bliss_exec/bliss_exec.h"
#include "../bliss_option/bliss_option.h"
#include "bliss_command.h"

BlissCommand::BlissCommand(string name):options_count_(1) {
	BlissExec::set_name(name);
	options_ = new Bliss_option*[1];
}

BlissCommand::~BlissCommand() {
	delete[] this->options_;
}

BlissCommand* Init() {

}

string BlissCommand::usage() {
	return this->usage_;
}

int BlissCommand::options_count() {
	return this->options_count_;
}

BlissOption BlissCommand::GetOptionByIndex(int index) {
	return this->options_[index];
}

BlissOption BlissCommand::GetOptionByName(string name) {
	for (BlissOption* op : this->options_) {
		if (name == op->name() || name == op->name_short()) {
			return op;
		}
	}
	return NULL;
}

BlissCommand* AddOption(BlissOption* option) {
	BlissOption** tmp = new BlissOption*[this->options_count];
	memcpy(tmp, this->options_, sizeof(BlissOption*) * this->options_count);
	
	delete[] this->options_;
	this->options_count++;
	
	this->options_ = new BlissOption*[this->options_count];
	memcpy(this->options_, tmp, sizeof(BlissOption*) * (this->options_count-1));
	delete[] tmp;

	return this;
}
