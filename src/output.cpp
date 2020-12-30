#include "output.hpp"

//サーバの故障期間を出力する
void output_server_downtime(map<string, vector<period>>* period_map) {
	//故障期間が一つもない
	if (period_map->empty()) {
		cout << "zero-downtime \n";
		return;
	}

	for (auto& item : *period_map) {
		//サーバのアドレス
		string server_adr = item.first;
		//故障期間の配列
		vector<period>* periods = &item.second;

		cout << server_adr << endl;
		
		for (auto& period : *periods) {
			//output_period(period);
			output_period_separated(period);
		}
	}
}

//サーバの過負荷状態になっている期間を出力する
void output_server_busytime(map<string, vector<period>>* period_map) {

}

//サーバの故障期間を出力する
void output_network_downtime(map<string, vector<period>>* period_map) {

}

void output_period(period per) {
	if (per.second.is_set()) {
		cout << per.first.get_date_str() << " ~ " << per.second.get_date_str() << endl;
	}
	else {
		cout << per.first.get_date_str() << " ~ " << "now" << endl;
	}
}

void output_period_separated(period per) {
	if (per.second.is_set()) {
		cout << per.first.get_date_str_separated() << " ~ " << per.second.get_date_str_separated() << endl;
	}
	else {
		cout << per.first.get_date_str_separated() << " ~ " << "now" << endl;
	}
}