#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//�f�[�^��ǂݍ��݁A�e�T�[�o�̘A����N��^�C���A�E�g�ɂȂ������Ԃ��o�͂���
//N�͑������Ŏw�肷��
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: ./exam2.exe [N]\nexample: ./exam2.exe 3\n";
		return 0;
	}
	
	int N = stoi(string(argv[1]));
	//int N = 2;
	int num;
	cin >> num;

	auto in = input(num);
	auto data = convert(in);

	//�A�h���X�̕�������L�[�Ƃ��ă��O�f�[�^��z��ŕۊǂ���
	map<string, vector<log_data>> log_map;

	for (const auto& log : data) {
		log_map[log.adr.get_str()].push_back(log);
	}

	//N��A���Ń^�C���A�E�g�ɂȂ������Ԃ����߂�
	auto server_downtimes = calc_server_downtime(&log_map, N);

	//�̏���Ԃ��o��
	output_server_downtime(&server_downtimes);

	return 0;
}
