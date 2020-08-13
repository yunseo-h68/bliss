#include <cstring>
#include "bliss_command.h"

BlissCommand::BlissCommand():BlissCommand("") {
}

BlissCommand::BlissCommand(std::string name):options_count_(0) {
	set_name(name);
	options_ = new BlissOption*[1];
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

BlissCommand* BlissCommand::set_name(std::string name) {
	set_name(name);
	return this;
}

BlissCommand* BlissCommand::set_description(std::string description) {
	set_description(description);
	return this;
}

BlissCommand* BlissCommand::set_usage(std::string usage) {
	usage_ = usage;
	return this;
}

BlissOption* BlissCommand::GetOptionByIndex(int index) {
	if (index < 0 || index >= options_count_) {
		return NULL;
	}
	return options_[index];
}

BlissOption* BlissCommand::GetOptionByName(std::string name) {
	for (int i = 0; i < options_count_; i++) {
		if (name == options_[i]->name()) {
			return options_[i];
		}
	}
	return NULL;
}

BlissOption* BlissCommand::GetOptionByNameShort(std::string name_short) {
	for (int i = 0; i < options_count_; i++) {
		if (name_short == options_[i]->name_short()) {
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
	memcpy(options_, tmp, sizeof(BlissOption*) * (options_count_ -1));
	options_[options_count_ - 1] = option;
	delete[] tmp;

	return this;
}

BlissCommand* BlissCommand::DeleteOptionByName(std::string name) {
	for (int i = 0; i < options_count_; i++) {
		if (name == options_[i]->name() || name == options_[i]->name_short()) {
			delete options_[i];
			options_[i] = NULL;
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
	options_count_--;
	options_ = new BlissOption*[options_count_];
	memcpy(options_, tmp, sizeof(BlissOption*) * (options_count_));
	return this;
}
