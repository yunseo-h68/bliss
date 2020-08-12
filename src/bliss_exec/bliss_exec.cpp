#include "bliss_exec.h"

BlissExec::BlissExec() {
	name_ = "";
	description_ = "";
}

BlissExec::~BlissExec() {
}

string BlissExec::name() {
	return name_;
}

string BlissExec::description() {
	return description_;
}

BlissExec* BlissExec::set_name(string name) {
	name_ = name;
	return this;
}

BlissExec* BlissExec::set_description(string description) {
	description_ = description;
	return this;
}
