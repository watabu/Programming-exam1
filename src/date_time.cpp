#include "date_time.hpp"


date_time::date_time() {
	set("");
}

date_time::date_time(string init) {
	set(init);
}

void date_time::set(string date) {
	origin = date;
}

void date_time::set(ll date) {
	origin = to_string(date);
}
void date_time::reset() {
	origin = "";
}

bool date_time::is_set() {
	return (origin != "");
}

void date_time::show() {
	cout << year() << "年";
	cout << month() << "月";
	cout << day() << "日";
	cout << hour() << "時";
	cout << minute() << "分";
	cout << second() << "秒";
}


int date_time::str2int(string s, int start, int length) {
	if (length <= 0) {
		cout << "error: invalid value\n";
		return 0;
	}
	if (start < 0 || s.size() < start + length) {
		cout << "error: out of range\n";
		return 0;
	}

	string sub = s.substr(start, length);
	int value = stoi(sub);
	return value;
}

int date_time::year() {
	return str2int(origin, 0, 4);
}
	
int date_time::month() {
	return str2int(origin, 4, 2);
}
	
int date_time::day() {
	return str2int(origin, 6, 2);
}
	
int date_time::hour() {
	return str2int(origin, 8, 2);
}
int date_time::minute() {
	return str2int(origin, 10, 2);
}
int date_time::second() {
	return str2int(origin, 12, 2);
}
	
string date_time::get_date_str() {
	return origin;
}
	
ll date_time::get_date_ll() {
	return stoll(origin);
}

string date_time::get_date_str_separated() {
	string result;
	result = to_string(year()) + "年"
		+ to_string(month()) + "月"
		+ to_string(day()) + "日"
		+ to_string(hour()) + "時"
		+ to_string(minute()) + "分"
		+ to_string(second()) + "秒";
	return result;
}