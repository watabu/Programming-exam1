#pragma once
#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "utilities.hpp"
#include <queue>
#include <set>

//サーバの故障期間を算出する
//タイムアウト中の単純な期間
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map);

//サーバの故障期間を算出する
//N回連続でタイムアウトした期間
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map, int N);

//サーバの過負荷状態になっている期間を算出する
//m回の平均がt以上となる期間
map<string, vector<period>> calc_server_busytime(map<string, vector<log_data>>* log_map, int m, int t);

//サブネットの故障期間を出力する
//サブネット内のサーバーすべてがN回連続でタイムアウトしている期間
map<string, vector<period>> calc_subnet_downtime(map<string, vector<log_data>>* log_map, int N);
