#include "calculator.hpp"

//サーバの故障期間を算出する
//タイムアウト中の単純な期間
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map) {
	map<string, vector<period>> result;

	for (const auto& log_pair : *log_map) {
		//サーバアドレス
		string adr_str = log_pair.first;
		//pingのログデータ配列
		const vector<log_data>* logs = &log_pair.second;

		bool timeout = false;
		period peri;
		//　タイムアウトだったら次の接続までを取得、故障期間をプッシュする
		for (const auto& log : *logs) {
			//正常
			if (!timeout) {
				//正常->正常
				if (log.result != "-")
					continue;

				//正常->タイムアウト
				timeout = true;
				peri.first = log.date;
				continue;
			}

			//タイムアウト
			if (timeout) {
				//タイムアウト->タイムアウト
				if (log.result == "-") {
					continue;
				}

				//タイムアウト->正常
				peri.second = log.date;
				result[adr_str].push_back(peri);
				timeout = false;
				continue;
			}
		}

		//タイムアウト中のままログが終わった場合
		if (timeout) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}
	}

	return result;
}

//サーバの故障期間を算出する
//N回連続でタイムアウトした期間
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map, int N) {
	map<string, vector<period>> result;

	for (const auto& log_pair : *log_map) {
		//サーバアドレス
		string adr_str = log_pair.first;
		//pingのログデータ配列
		const vector<log_data>* logs = &log_pair.second;

		//連続でタイムアウトになっている回数
		int timeout_count = 0;
		period peri;
		//　タイムアウトだったら次の接続までを取得、故障期間をプッシュする
		for (const auto& log : *logs) {
			//正常
			if (timeout_count == 0) {
				//正常->正常
				if (log.result != "-")
					continue;

				//正常->タイムアウト
				timeout_count++;
				peri.first = log.date;
				continue;
			}
			//タイムアウト 連続回数はN回未満
			else if (timeout_count < N) {
				//タイムアウト->タイムアウト
				if (log.result == "-") {
					timeout_count++;
					continue;
				}

				//タイムアウト->正常
				//N回未満なので数えない
				peri.first.reset();
				timeout_count = 0;
				continue;
			}
			//タイムアウト 連続回数はN回以上
			else {
				//タイムアウト->タイムアウト
				if (log.result == "-") {
					timeout_count++;
					continue;
				}

				//タイムアウト->正常
				peri.second = log.date;
				result[adr_str].push_back(peri);
				timeout_count = 0;
				continue;
			}
		}

		//N回以上連続タイムアウト中でログが終わった場合
		if (timeout_count >= N) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}
	}
	return result;
}

//サーバの過負荷状態になっている期間を算出する
//m回の平均がt以上となる期間
map<string, vector<period>> calc_server_busytime(map<string, vector<log_data>>* log_map, int m, int t) {
	map<string, vector<period>> result;

	const int mt = m * t;

	for (const auto& log_pair : *log_map) {
		//サーバアドレス
		string adr_str = log_pair.first;
		//pingのログデータ配列
		const vector<log_data>* logs = &log_pair.second;

		//直近m回の合計値
		int sum = 0;
		//尺取り法でm個前を取り出すためのキュー
		queue<int> que;

		//記録がない部分は t で近似 -> 平均の計算から外す
		for (size_t i = 0; i < m-1; i++)
		{
			sum += t;
			que.push(t);
		}

		bool is_busy = false;
		period peri;
		peri.first = logs->front().date;
		//　m回の総和が mt 以上な区間を取得、プッシュする
		for (const auto& log : *logs) {
			//タイムアウトなら除外し、pingの結果を t とする
			// -> 平均の計算から外す
			int time = log.result != "-" ? stoi(log.result) : t;

			sum += time;
			que.push(time);
	
			//m個以降　足して和を比べ、m個前のものを引いて次のループへ

			//過負荷->
			if (is_busy) {
				//過負荷->過負荷
				if (sum >= mt) {
				}
				//過負荷->正常
				else {
					peri.second = log.date;
					result[adr_str].push_back(peri);
					is_busy = false;
				}
			}
			//正常->
			else {
				//正常->正常
				if (sum < mt) {
				}
				//正常->過負荷
				else {
					peri.first = log.date;
					is_busy = true;
				}
			}
			//m-1個分の和にする
			int top = que.front();
			que.pop();
			sum -= top;
		}
		//過負荷状態のままログが終わった場合
		if (is_busy) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}
	}
	return result;
}

//サブネットの故障期間を出力する
//サブネット内のサーバーすべてがN回連続でタイムアウトしている期間
map<string, vector<period>> calc_subnet_downtime(map<string, vector<log_data>>* log_map, int N) {
	map<string, vector<period>> result;

	//各サーバの故障期間を求める
	auto server_downtime = calc_server_downtime(log_map, N);
	
	//各サブネットの総サーバ数を求める
	//サブネットのサーバ集合
	map<string, set<string>> subnet_server_set;
	for (const auto& log_pair : *log_map) {
		//サーバアドレス
		string adr_str = log_pair.first;
		address adr(adr_str);
		subnet_server_set[adr.get_subnet_str()].insert(adr.get_host_str());
	}
	//サブネットに属するサーバ数
	map<string, int> subnet_server_count;
	for (const auto& subnet_pair : subnet_server_set) {
		string adr_subnet = subnet_pair.first;
		subnet_server_count[adr_subnet] = subnet_pair.second.size();
	}

	//各サブネットの故障期間
	map<string, vector<vector<period>>> subnet_log_map;
	//サブネットごとに整理する
	for (const auto& log_pair : server_downtime) {
		//サーバアドレス
		string adr_str = log_pair.first;
		address adr(adr_str);
		subnet_log_map[adr.get_subnet_str()].push_back(log_pair.second);
	}

	//各サブネットで全サーバが故障中の期間を求める
	for (const auto& log_pair : subnet_log_map) {
		//ネットワークアドレス
		string adr_str = log_pair.first;
		//サブネットに属するサーバの故障期間配列
		vector<vector<period>> server_periods = log_pair.second;
		vector<int> server_i(server_periods.size(),0);

		//一つでも故障しないサーバがあった場合
		if (server_periods.size() < subnet_server_count[adr_str]) {
			continue;
		}

		//mapと累積和で和が全数に等しい区間を求める
		map<ll, int> cumulative;
		for (auto& periods : server_periods) {
			for (auto& per : periods) {
				cumulative[per.first.get_date_ll()] += 1;
				if (per.second.is_set())
					cumulative[per.second.get_date_ll()] -= 1;
			}
		}
		
		int sum = 0;
		bool timeout = false;
		period peri;
		for (auto& time_num : cumulative) {
			sum += time_num.second;

			//正常
			if (!timeout) {
				//正常->正常
				if (sum != server_periods.size()) {
					continue;
				}
				//正常->タイムアウト
				timeout = true;
				peri.first.set(time_num.first);
				continue;

			}
			//タイムアウト
			if (timeout) {
				//タイムアウト->タイムアウト
				if (sum == server_periods.size()) {
					continue;
				}

				//タイムアウト->正常
				peri.second.set(time_num.first);
				result[adr_str].push_back(peri);
				timeout = false;
				continue;
			}
		}
		//タイムアウト中のままログが終わった場合
		if (timeout) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}

	}

	return result;
}