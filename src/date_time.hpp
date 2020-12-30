#pragma once
#include "header.hpp"

/// <summary>
/// 日付クラス
/// 文字列<->整数や出力用の文字列を取得できる
/// </summary>
class date_time {
private:
	string origin;
public:
	date_time();
	date_time(string init);

	void set(string date);
	void set(ll date);
	void reset();

	int year();
	int month();
	int day();
	int hour();
	int minute();
	int second();

	string get_date_str();
	string get_date_str_separated();
	ll get_date_ll();

	bool is_set();
	
	void show();

private:
	int str2int(string s, int start, int length);
};

