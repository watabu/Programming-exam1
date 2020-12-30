#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//データを読み込み、各サーバの単純なタイムアウト期間を出力する
int main() {
	int num;
	cin >> num;

	auto in = input(num);
	auto data = convert(in);

	//アドレスの文字列をキーとしてログデータを配列で保管する
	map<string, vector<log_data>> log_map;

	for (const auto& log : data) {
		log_map[log.adr.get_str()].push_back(log);
	}

	auto server_downtimes = calc_server_downtime(&log_map);

	//故障期間を出力
	output_server_downtime(&server_downtimes);

	return 0;
}
