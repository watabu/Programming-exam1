#pragma once
#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
//出力処理

//サーバの故障期間を出力する
void output_server_downtime(map<string, vector<period>>* period_map);

//サーバの過負荷状態になっている期間を出力する
void output_server_busytime(map<string, vector<period>>* period_map);

//ネットワークの故障期間を出力する
void output_network_downtime(map<string, vector<period>>* period_map);

void output_period(period per);
void output_period_separated(period per);
