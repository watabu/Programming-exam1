#pragma once
#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "utilities.hpp"
//���͏����ƃf�[�^�̍\����

typedef pair<date_time, date_time> period;

//���͂ɋ߂����f�[�^
struct log_raw_data
{
	string date;
	string address;
	string result;
};

//�Ǝ��N���X�ŕ\�����ꂽ�f�[�^
struct log_data
{
	date_time date;
	address adr;
	string result;
};

bool operator<(const log_data& right, const log_data& left);

vector<log_raw_data> input(int num);

vector<log_data> convert(vector<log_raw_data> raw_data);
