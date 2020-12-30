#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//データを読み込み、各サーバの連続でN回タイムアウトになった期間を出力する
//Nは第一引数で指定する
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: ./exam2.exe [N]\nexample: ./exam2.exe 3\n";
		return 0;
	}
	
	int N = stoi(string(argv[1]));
	//int N = 2;
	int num;
	cin >> num;

	auto in = input(num);
	auto data = convert(in);

	//アドレスの文字列をキーとしてログデータを配列で保管する
	map<string, vector<log_data>> log_map;

	for (const auto& log : data) {
		log_map[log.adr.get_str()].push_back(log);
	}

	//N回連続でタイムアウトになった期間を求める
	auto server_downtimes = calc_server_downtime(&log_map, N);

	//故障期間を出力
	output_server_downtime(&server_downtimes);

	return 0;
}
