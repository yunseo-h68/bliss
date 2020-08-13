#include <string>
#include <cstring>
#include "../bliss_exec/bliss_exec.h"
#include "../bliss_option/bliss_option.h"
#include "bliss_command.h"

using namespace std;

BlissCommand::BlissCommand(string name):options_count_(1) {
	BlissExec::set_name(name);
	options_ = new BlissOption*[1];
	options_count_ = 0;
}

BlissCommand::~BlissCommand() {
	for (int i = 0; i < options_count_; i++) {
		delete options_[i];
	}
	delete[] options_;
}

string BlissCommand::usage() {
	return usage_;
}

int BlissCommand::options_count() {
	return options_count_;
}

BlissOption* BlissCommand::GetOptionByIndex(int index) {
	if (index < 0 || index > options_count_) {
		return NULL;
	}
	return options_[index];
}

BlissOption* BlissCommand::GetOptionByName(string name) {
	for (int i = 0; i < options_count_; i++) {
		if (name == options_[i]->name() || name == options_[i]->name_short()) {
			return options_[i];
		}
	}
	return NULL;
}

BlissCommand* BlissCommand::AddOption(BlissOption* option) {
	BlissOption** tmp = new BlissOption*[options_count_];
	memcpy(tmp, options_, sizeof(BlissOption*) * options_count_);
	
	delete[] options_;
	options_count_++;
	
	options_ = new BlissOption*[options_count_];
	memcpy(options_, tmp, sizeof(BlissOption*) * (options_count_));
	delete[] tmp;

	return this;
}

BlissCommand* BlissCommand::DeleteOptionByName(string name) {
	for (int i = 0; i < options_count_; i++) {
		if (name == options_[i]->name() || name == options_[i]->name_short()) {
			delete options_[i];
			options_[i] = NULL;
			options_count_--;
		}
	}

	BlissOption** tmp = new BlissOption*[options_count_];
	for (int i = 0,j = 0; i < options_count_; i++) {
		if (options_[i] != NULL) {
			tmp[j] = options_[i];
			j++;
		}
	}
	delete[] options_;
	options_ = new BlissOption*[options_count_];
	memcpy(options_, tmp, sizeof(BlissOption*) * (options_count_));
	return this;
}
