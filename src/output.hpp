#pragma once
#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
//�o�͏���

//�T�[�o�̌̏���Ԃ��o�͂���
void output_server_downtime(map<string, vector<period>>* period_map);

//�T�[�o�̉ߕ��׏�ԂɂȂ��Ă�����Ԃ��o�͂���
void output_server_busytime(map<string, vector<period>>* period_map);

//�l�b�g���[�N�̌̏���Ԃ��o�͂���
void output_network_downtime(map<string, vector<period>>* period_map);

void output_period(period per);
void output_period_separated(period per);
