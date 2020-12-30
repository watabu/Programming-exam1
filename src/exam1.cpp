#include "header.hpp"
#include "address.hpp"
#include "date_time.hpp"
#include "input.hpp"
#include "calculator.hpp"
#include "output.hpp"


//�f�[�^��ǂݍ��݁A�e�T�[�o�̒P���ȃ^�C���A�E�g���Ԃ��o�͂���
int main() {
	int num;
	cin >> num;

	auto in = input(num);
	auto data = convert(in);

	//�A�h���X�̕�������L�[�Ƃ��ă��O�f�[�^��z��ŕۊǂ���
	map<string, vector<log_data>> log_map;

	for (const auto& log : data) {
		log_map[log.adr.get_str()].push_back(log);
	}

	auto server_downtimes = calc_server_downtime(&log_map);

	//�̏���Ԃ��o��
	output_server_downtime(&server_downtimes);

	return 0;
}
