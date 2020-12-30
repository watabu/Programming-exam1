#include "output.hpp"

//�T�[�o�̌̏���Ԃ��o�͂���
void output_server_downtime(map<string, vector<period>>* period_map) {
	//�̏���Ԃ�����Ȃ�
	if (period_map->empty()) {
		cout << "zero-downtime \n";
		return;
	}

	for (auto& item : *period_map) {
		//�T�[�o�̃A�h���X
		string server_adr = item.first;
		//�̏���Ԃ̔z��
		vector<period>* periods = &item.second;

		cout << server_adr << endl;
		
		for (auto& period : *periods) {
			//output_period(period);
			output_period_separated(period);
		}
	}
}

//�T�[�o�̉ߕ��׏�ԂɂȂ��Ă�����Ԃ��o�͂���
void output_server_busytime(map<string, vector<period>>* period_map) {

}

//�T�[�o�̌̏���Ԃ��o�͂���
void output_network_downtime(map<string, vector<period>>* period_map) {

}

void output_period(period per) {
	if (per.second.is_set()) {
		cout << per.first.get_date_str() << " ~ " << per.second.get_date_str() << endl;
	}
	else {
		cout << per.first.get_date_str() << " ~ " << "now" << endl;
	}
}

void output_period_separated(period per) {
	if (per.second.is_set()) {
		cout << per.first.get_date_str_separated() << " ~ " << per.second.get_date_str_separated() << endl;
	}
	else {
		cout << per.first.get_date_str_separated() << " ~ " << "now" << endl;
	}
}