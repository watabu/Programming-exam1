#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//�f�[�^��ǂݍ��݁A
//N�͑������Ŏw�肷��
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: ./exam4.exe [N]\nexample: ./exam4.exe 3\n";
		return 0;
	}

	int N = stoi(string(argv[1]));
	//int N = 1;

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
	auto subnet_downtimes = calc_subnet_downtime(&log_map, N);

	//�̏���Ԃ��o��
	output_server_downtime(&subnet_downtimes);

	return 0;
}
