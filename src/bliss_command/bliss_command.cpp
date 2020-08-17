#include <cstring>
#include "bliss_command.h"

BlissCommand::BlissCommand(std::string name) {
	BlissExec::set_name(name);
}

BlissCommand::BlissCommand():BlissCommand("") {
}


BlissCommand::~BlissCommand() {
	for (auto option : options_) {
		delete option;
	}
}

std::string BlissCommand::usage() {
	return usage_;
}

int BlissCommand::options_count() {
	return options_.size();
}

BlissCommand* BlissCommand::set_name(std::string name) {
	BlissExec::set_name(name);
	return this;
}

BlissCommand* BlissCommand::set_description(std::string description) {
	BlissExec::set_description(description);
	return this;
}

BlissCommand* BlissCommand::set_usage(std::string usage) {
	usage_ = usage;
	return this;
}

BlissOption* BlissCommand::GetOptionByIndex(int index) {
	if (index < 0 || index >= options_.size()) {
		return NULL;
	}
	return options_[index];
}

BlissOption* BlissCommand::GetOptionByName(std::string name) {
	for (auto option : options_) {
		if (name == option->name()) {
			return option;
		}
	}
	return NULL;
}

BlissOption* BlissCommand::GetOptionByNameShort(std::string name_short) {
	for (auto option : options_) {
		if (name_short == option->name_short()) {
			return option;
		}
	}
	return NULL;
}

BlissCommand* BlissCommand::AddOption(BlissOption* option) {
	options_.push_back(option);
	return this;
}

BlissCommand* BlissCommand::DeleteOptionByName(std::string name) {
	for (std::vector<BlissOption*>::iterator iter = options_.begin(); iter != options_.end(); iter++) {
		if (name == (*iter)->name() || name == (*iter)->name_short()) {
			delete (*iter);
			options_.erase(iter);
		}
	}
	return this;
}
