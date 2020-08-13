#include "bliss_option.h"

BlissOption::BlissOption() {
	BlissExec::set_name("");
	name_short_ = "";
	set_description("");
}

BlissOption::BlissOption(std::string name) {
	BlissExec::set_name(name);
	name_short_ = "";
	BlissExec::set_description("");
}

BlissOption::~BlissOption() {

}

std::string BlissOption::name_short() {
	return name_short_;
}

BlissOption* BlissOption::set_name(std::string name) {
	BlissExec::set_name(name);
	return this;
}

BlissOption* BlissOption::set_name_short(std::string name_short) {
	name_short_ = name_short;
	return this;
}

BlissOption* BlissOption::set_description(std::string description) {
	BlissExec::set_description(description);
	return this;
}
