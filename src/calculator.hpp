#pragma once
#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "utilities.hpp"
#include <queue>
#include <set>

//�T�[�o�̌̏���Ԃ��Z�o����
//�^�C���A�E�g���̒P���Ȋ���
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map);

//�T�[�o�̌̏���Ԃ��Z�o����
//N��A���Ń^�C���A�E�g��������
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map, int N);

//�T�[�o�̉ߕ��׏�ԂɂȂ��Ă�����Ԃ��Z�o����
//m��̕��ς�t�ȏ�ƂȂ����
map<string, vector<period>> calc_server_busytime(map<string, vector<log_data>>* log_map, int m, int t);

//�T�u�l�b�g�̌̏���Ԃ��o�͂���
//�T�u�l�b�g���̃T�[�o�[���ׂĂ�N��A���Ń^�C���A�E�g���Ă������
map<string, vector<period>> calc_subnet_downtime(map<string, vector<log_data>>* log_map, int N);
