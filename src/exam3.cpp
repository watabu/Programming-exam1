#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//データを読み込み、各サーバの連続でN回タイムアウトになった期間を出力する
//Nは第一引数で指定する
int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Usage: ./exam3.exe [m] [t]\nexample: ./exam3.exe 3 100\n";
		return 0;
	}
	int m = stoi(string(argv[1]));
	int t = stoi(string(argv[2]));

	// int m = 2;
	// int t = 100;

	int num;
	cin >> num;

	auto in = input(num);
	auto data = convert(in);

	//アドレスの文字列をキーとしてログデータを配列で保管する
	map<string, vector<log_data>> log_map;

	for (const auto& log : data) {
		log_map[log.adr.get_str()].push_back(log);
	}

	//m回の平均がt以上の過負荷期間を求める
	auto server_busytimes = calc_server_busytime(&log_map, m, t);

	//故障期間を出力
	output_server_downtime(&server_busytimes);

	return 0;
}
