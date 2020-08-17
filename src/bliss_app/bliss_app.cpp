#include <iostream>
#include <cstring>
#include "bliss_app.h"

BlissApp::BlissApp():BlissApp("") {
}

BlissApp::BlissApp(std::string name) {
	set_name(name);
}

BlissApp::~BlissApp() {
	for (auto subcommand : subcommands_) {
		delete subcommand;
	}
}

int BlissApp::subcommands_count() {
	return subcommands_.size();
}

BlissApp* BlissApp::set_name(std::string name) {
	BlissExec::set_name(name);
	return this;
}

BlissApp* BlissApp::set_description(std::string description) {
	BlissExec::set_description(description);
	return this;
}

BlissApp* BlissApp::set_usage(std::string usage) {
	BlissCommand::set_usage(usage);
	return this;
}

BlissApp* BlissApp::AddOption(BlissOption* option) {
	BlissCommand::AddOption(option);
	return this;
}

BlissApp* BlissApp::DeleteOptionByName(std::string name) {
	BlissCommand::DeleteOptionByName(name);
	return this;
}

BlissApp* BlissApp::AddSubcommand(BlissCommand* subcommand) {
	subcommands_.push_back(subcommand);
	return this;
}

BlissApp* BlissApp::DeleteSubcommandByName(std::string name) {
	for (std::vector<BlissCommand*>::iterator iter = subcommands_.begin(); iter != subcommands_.end(); iter++) {
		if (name == (*iter)->name()) {
			delete (*iter);
			subcommands_.erase(iter);
			break;
		}
	}
	return this;
}

BlissCommand* BlissApp::GetSubcommandByIndex(int index) {
	if (index < 0 || index >= subcommands_.size()) {
		return NULL;
	}
	return subcommands_[index];
}

BlissCommand* BlissApp::GetSubcommandByName(std::string name) {
	for (auto subcommand : subcommands_) {
		if (name == subcommand->name()) {
			return subcommand;
		}
	}
	return NULL;
}

void BlissApp::PrintHelp() {
	if (name().length() > 0) {
		std::cout << name();
	}
	if (description().length() > 0) {
		std::cout << " | " << description();
	}
	std::cout << "\n\n";
	
	if (usage().length() > 0) {
		std::cout << "Usage:\n\t" << usage() << "\n\n";
	}

	if (options_count() > 0) {
		std::cout << "Options:\n";
		for (int i = 0; i < options_count(); i++) {
			BlissOption* tmp = GetOptionByIndex(i);
			std::cout << "\t";
			if (tmp->name_short().length() > 0) {
				std::cout << "-" << tmp->name_short();
			}
			if (tmp->name().length() > 0) {
				std::cout << " --" << tmp->name();
			}
			if (tmp->description().length() > 0) {
				std::cout << " : " << tmp->description();
			}
			std::cout << "\n";
		}
	}
	if (subcommands_.size() > 0) {
		std::cout << "\nSubcommands:\n";
		for (int i = 0; i < subcommands_.size(); i++) {
			BlissCommand* tmp = GetSubcommandByIndex(i);
			std::cout << "\t";
			if (tmp->name().length() > 0) {
				std::cout << tmp->name() << " ";
			}
			if (tmp->description().length() > 0) {
				std::cout << ": " << tmp->description();
			}
			std::cout << "\n";
		}
	}
}

void BlissApp::Exec() {
	PrintHelp();
}
