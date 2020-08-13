#include "bliss_exec.h"

BlissExec::BlissExec() {
	name_ = "";
	description_ = "";
}

BlissExec::~BlissExec() {
}

std::string BlissExec::name() {
	return name_;
}

std::string BlissExec::description() {
	return description_;
}

BlissExec* BlissExec::set_name(std::string name) {
	name_ = name;
	return this;
}

BlissExec* BlissExec::set_description(std::string description) {
	description_ = description;
	return this;
}
