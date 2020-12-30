#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//データを読み込み、各サーバの単純なタイムアウト期間を出力する
int main(int argc, char *argv[]) {
    if (argc != 4) {
		cout << "Usage: ./exam5.exe [N] [m] [t]\nexample: ./exam5.exe 3 3 100\n";
		return 0;
	}
	
	int N = stoi(string(argv[1]));
    int m = stoi(string(argv[2]));
	int t = stoi(string(argv[3]));
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
	auto server_downtimes1 = calc_server_downtime(&log_map);
    //N回連続でタイムアウトになった期間を求める
	auto server_downtimes2 = calc_server_downtime(&log_map, N);
	//m回の平均がt以上の過負荷期間を求める
	auto server_busytimes = calc_server_busytime(&log_map, m, t);
    //N回連続でタイムアウトになった期間を求める
	auto subnet_downtimes = calc_subnet_downtime(&log_map, N);

	//故障期間を出力
    cout << "故障中のサーバ(単一タイムアウト)\n";
	output_server_downtime(&server_downtimes1);
    cout << "\n故障中のサーバ(" <<N << "回連続タイムアウト)\n";
	output_server_downtime(&server_downtimes2);
    cout << "\n過負荷状態のサーバ(" << m << "回平均 " << t << "[ms]以上)\n";
	output_server_downtime(&server_busytimes);
    cout << "\n故障中のサブネット" << N << "回連続タイムアウト)\n";
    output_server_downtime(&subnet_downtimes);

	return 0;
}
