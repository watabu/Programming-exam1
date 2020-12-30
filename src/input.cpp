#include "input.hpp"

bool operator<(const log_data& left, const log_data& right) {
	return left.adr.get_str() < right.adr.get_str();
}

//num行の入力を受け取り、三つの文字列に分けて格納する
vector<log_raw_data> input(int num) {
	vector<log_raw_data> out(num);
	for (size_t i = 0; i < num; i++)
	{
		string s;
		cin >> s;
		auto log_strs = split(s, ",");
		if (log_strs.size() != 3) {
			cout << "error: invalid input\n";
			return vector<log_raw_data>();
		}
		log_raw_data log;
		out[i].date= log_strs[0];
		out[i].address= log_strs[1];
		out[i].result = log_strs[2];
	}
	return out;
}

//扱いやすいようにクラスへ変換する
vector<log_data> convert(vector<log_raw_data> raw_data) {
	const int num = raw_data.size();
	vector<log_data> out(num);

	for (size_t i = 0; i < num; i++)
	{
		out[i].date.set(raw_data[i].date);
		out[i].adr.set(raw_data[i].address);
		out[i].result = raw_data[i].result;
	}

	return out;
}
