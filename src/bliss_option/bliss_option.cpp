#include <string>
#include "../bliss_exec/bliss_exec.h"
#include "bliss_option.h"

BlissOption::BlissOption() {
	BlissExec::set_name("");
	this->name_short_ = "";
	BlissExec::set_description("");
}

BlissOption::BlissOption(string name) {
	BlissExec::set_name(name);
	this->name_short_ = "";
	BlissExec::set_description("");
}

BlissOption::~BlissOption() {

}

string BlissOption::name_short() {
	return this->name_short_;
}

BlissOption* set_name(string name) {
	BlissExec::set_name(name);
	return this;
}

BlissOption* set_name_short(string name_short) {
	this->name_short_ = name_short;
	return this;
}

BlissOption* set_description(string description) {
	BlissExec::set_description(description);
	return this;
}
