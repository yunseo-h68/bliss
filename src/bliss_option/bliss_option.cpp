#include "bliss_option.h"

using namespace std;

BlissOption::BlissOption() {
	set_name("");
	this->name_short_ = "";
	set_description("");
}

BlissOption::BlissOption(string name) {
	set_name(name);
	this->name_short_ = "";
	set_description("");
}

BlissOption::~BlissOption() {

}

string BlissOption::name_short() {
	return this->name_short_;
}

BlissOption* BlissOption::set_name(string name) {
	BlissExec::set_name(name);
	return this;
}

BlissOption* BlissOption::set_name_short(string name_short) {
	this->name_short_ = name_short;
	return this;
}

BlissOption* BlissOption::set_description(string description) {
	set_description(description);
	return this;
}
