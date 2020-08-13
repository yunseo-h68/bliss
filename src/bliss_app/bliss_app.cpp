#include <iostream>
#include <cstring>
#include "bliss_app.h"

BlissApp::BlissApp() {
	set_name("");
}

BlissApp::BlissApp(std::string name) {
	set_name(name);
}

BlissApp::~BlissApp() {
	for (int i = 0; i < subcommands_count_; i++) {
		delete subcommands_[i];
	}
	delete[] subcommands_;
}

BlissApp* BlissApp::set_name(std::string name) {
	set_name(name);
	return this;
}

BlissApp* BlissApp::set_description(std::string description) {
	set_description(description);
	return this;
}

BlissApp* BlissApp::set_usage(std::string usage) {
	set_usage(usage);
	return this;
}

BlissApp* BlissApp::AddOption(BlissOption* option) {
	AddOption(option);
	return this;
}

BlissApp* BlissApp::DeleteOptionByName(std::string name) {
	DeleteOptionByName(name);
	return this;
}

BlissApp* BlissApp::AddSubcommand(BlissCommand* subcommand) {
	BlissCommand** tmp = new BlissCommand*[subcommands_count_];
	memcpy(tmp, subcommands_, sizeof(BlissCommand*) * subcommands_count_);

	delete[] subcommands_;
	subcommands_count_++;

	subcommands_ = new BlissCommand*[subcommands_count_];
	memcpy(subcommands_, tmp, sizeof(BlissCommand*) * (subcommands_count_ - 1));
	subcommands_[subcommands_count_ - 1] = subcommand;
	delete[] tmp;

	return this;
}

BlissApp* BlissApp::DeleteSubcommandByName(std::string name) {
	for (int i = 0; i < subcommands_count_; i++) {
		if (name == subcommands_[i]->name()) {
			delete subcommands_[i];
			subcommands_[i] = NULL;
		}
	}

	BlissCommand** tmp = new BlissCommand*[subcommands_count_ - 1];
	for (int i = 0, j = 0; i < subcommands_count_; i++) {
		if (subcommands_[i] != NULL) {
			tmp[j] = subcommands_[i];
			j++;
		}
	}
	delete[] subcommands_;
	subcommands_count_--;
	subcommands_ = new BlissCommand*[subcommands_count_];
	memcpy(subcommands_, tmp, sizeof(BlissCommand*) * (subcommands_count_));
	return this;
}

BlissCommand* BlissApp::GetSubcommandByIndex(int index) {
	if (index < 0 || index >= subcommands_count_) {
		return NULL;
	}
	return subcommands_[index];
}

BlissCommand* BlissApp::GetSubcommandByName(std::string name) {
	for (int i = 0; i < subcommands_count_; i++) {
		if (name == subcommands_[i]->name()) {
			return subcommands_[i];
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
	if (subcommands_count_ > 0) {
		std::cout << "\nSubcommands:\n";
		for (int i = 0; i < subcommands_count_; i++) {
			BlissCommand* tmp = GetSubcommandByIndex(i);
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
