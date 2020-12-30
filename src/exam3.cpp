#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//�f�[�^��ǂݍ��݁A�e�T�[�o�̘A����N��^�C���A�E�g�ɂȂ������Ԃ��o�͂���
//N�͑������Ŏw�肷��
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

	//�A�h���X�̕�������L�[�Ƃ��ă��O�f�[�^��z��ŕۊǂ���
	map<string, vector<log_data>> log_map;

	for (const auto& log : data) {
		log_map[log.adr.get_str()].push_back(log);
	}

	//m��̕��ς�t�ȏ�̉ߕ��׊��Ԃ����߂�
	auto server_busytimes = calc_server_busytime(&log_map, m, t);

	//�̏���Ԃ��o��
	output_server_downtime(&server_busytimes);

	return 0;
}
