#pragma once
#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "utilities.hpp"
//入力処理とデータの構造体

typedef pair<date_time, date_time> period;

//入力に近い元データ
struct log_raw_data
{
	string date;
	string address;
	string result;
};

//独自クラスで表現されたデータ
struct log_data
{
	date_time date;
	address adr;
	string result;
};

bool operator<(const log_data& right, const log_data& left);

vector<log_raw_data> input(int num);

vector<log_data> convert(vector<log_raw_data> raw_data);
