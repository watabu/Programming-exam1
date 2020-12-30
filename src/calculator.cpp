#include "calculator.hpp"

//�T�[�o�̌̏���Ԃ��Z�o����
//�^�C���A�E�g���̒P���Ȋ���
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map) {
	map<string, vector<period>> result;

	for (const auto& log_pair : *log_map) {
		//�T�[�o�A�h���X
		string adr_str = log_pair.first;
		//ping�̃��O�f�[�^�z��
		const vector<log_data>* logs = &log_pair.second;

		bool timeout = false;
		period peri;
		//�@�^�C���A�E�g�������玟�̐ڑ��܂ł��擾�A�̏���Ԃ��v�b�V������
		for (const auto& log : *logs) {
			//����
			if (!timeout) {
				//����->����
				if (log.result != "-")
					continue;

				//����->�^�C���A�E�g
				timeout = true;
				peri.first = log.date;
				continue;
			}

			//�^�C���A�E�g
			if (timeout) {
				//�^�C���A�E�g->�^�C���A�E�g
				if (log.result == "-") {
					continue;
				}

				//�^�C���A�E�g->����
				peri.second = log.date;
				result[adr_str].push_back(peri);
				timeout = false;
				continue;
			}
		}

		//�^�C���A�E�g���̂܂܃��O���I������ꍇ
		if (timeout) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}
	}

	return result;
}

//�T�[�o�̌̏���Ԃ��Z�o����
//N��A���Ń^�C���A�E�g��������
map<string, vector<period>> calc_server_downtime(map<string, vector<log_data>>* log_map, int N) {
	map<string, vector<period>> result;

	for (const auto& log_pair : *log_map) {
		//�T�[�o�A�h���X
		string adr_str = log_pair.first;
		//ping�̃��O�f�[�^�z��
		const vector<log_data>* logs = &log_pair.second;

		//�A���Ń^�C���A�E�g�ɂȂ��Ă����
		int timeout_count = 0;
		period peri;
		//�@�^�C���A�E�g�������玟�̐ڑ��܂ł��擾�A�̏���Ԃ��v�b�V������
		for (const auto& log : *logs) {
			//����
			if (timeout_count == 0) {
				//����->����
				if (log.result != "-")
					continue;

				//����->�^�C���A�E�g
				timeout_count++;
				peri.first = log.date;
				continue;
			}
			//�^�C���A�E�g �A���񐔂�N�񖢖�
			else if (timeout_count < N) {
				//�^�C���A�E�g->�^�C���A�E�g
				if (log.result == "-") {
					timeout_count++;
					continue;
				}

				//�^�C���A�E�g->����
				//N�񖢖��Ȃ̂Ő����Ȃ�
				peri.first.reset();
				timeout_count = 0;
				continue;
			}
			//�^�C���A�E�g �A���񐔂�N��ȏ�
			else {
				//�^�C���A�E�g->�^�C���A�E�g
				if (log.result == "-") {
					timeout_count++;
					continue;
				}

				//�^�C���A�E�g->����
				peri.second = log.date;
				result[adr_str].push_back(peri);
				timeout_count = 0;
				continue;
			}
		}

		//N��ȏ�A���^�C���A�E�g���Ń��O���I������ꍇ
		if (timeout_count >= N) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}
	}
	return result;
}

//�T�[�o�̉ߕ��׏�ԂɂȂ��Ă�����Ԃ��Z�o����
//m��̕��ς�t�ȏ�ƂȂ����
map<string, vector<period>> calc_server_busytime(map<string, vector<log_data>>* log_map, int m, int t) {
	map<string, vector<period>> result;

	const int mt = m * t;

	for (const auto& log_pair : *log_map) {
		//�T�[�o�A�h���X
		string adr_str = log_pair.first;
		//ping�̃��O�f�[�^�z��
		const vector<log_data>* logs = &log_pair.second;

		//����m��̍��v�l
		int sum = 0;
		//�ڎ��@��m�O�����o�����߂̃L���[
		queue<int> que;

		//�L�^���Ȃ������� t �ŋߎ� -> ���ς̌v�Z����O��
		for (size_t i = 0; i < m-1; i++)
		{
			sum += t;
			que.push(t);
		}

		bool is_busy = false;
		period peri;
		peri.first = logs->front().date;
		//�@m��̑��a�� mt �ȏ�ȋ�Ԃ��擾�A�v�b�V������
		for (const auto& log : *logs) {
			//�^�C���A�E�g�Ȃ珜�O���Aping�̌��ʂ� t �Ƃ���
			// -> ���ς̌v�Z����O��
			int time = log.result != "-" ? stoi(log.result) : t;

			sum += time;
			que.push(time);
	
			//m�ȍ~�@�����Ęa���ׁAm�O�̂��̂������Ď��̃��[�v��

			//�ߕ���->
			if (is_busy) {
				//�ߕ���->�ߕ���
				if (sum >= mt) {
				}
				//�ߕ���->����
				else {
					peri.second = log.date;
					result[adr_str].push_back(peri);
					is_busy = false;
				}
			}
			//����->
			else {
				//����->����
				if (sum < mt) {
				}
				//����->�ߕ���
				else {
					peri.first = log.date;
					is_busy = true;
				}
			}
			//m-1���̘a�ɂ���
			int top = que.front();
			que.pop();
			sum -= top;
		}
		//�ߕ��׏�Ԃ̂܂܃��O���I������ꍇ
		if (is_busy) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}
	}
	return result;
}

//�T�u�l�b�g�̌̏���Ԃ��o�͂���
//�T�u�l�b�g���̃T�[�o�[���ׂĂ�N��A���Ń^�C���A�E�g���Ă������
map<string, vector<period>> calc_subnet_downtime(map<string, vector<log_data>>* log_map, int N) {
	map<string, vector<period>> result;

	//�e�T�[�o�̌̏���Ԃ����߂�
	auto server_downtime = calc_server_downtime(log_map, N);
	
	//�e�T�u�l�b�g�̑��T�[�o�������߂�
	//�T�u�l�b�g�̃T�[�o�W��
	map<string, set<string>> subnet_server_set;
	for (const auto& log_pair : *log_map) {
		//�T�[�o�A�h���X
		string adr_str = log_pair.first;
		address adr(adr_str);
		subnet_server_set[adr.get_subnet_str()].insert(adr.get_host_str());
	}
	//�T�u�l�b�g�ɑ�����T�[�o��
	map<string, int> subnet_server_count;
	for (const auto& subnet_pair : subnet_server_set) {
		string adr_subnet = subnet_pair.first;
		subnet_server_count[adr_subnet] = subnet_pair.second.size();
	}

	//�e�T�u�l�b�g�̌̏����
	map<string, vector<vector<period>>> subnet_log_map;
	//�T�u�l�b�g���Ƃɐ�������
	for (const auto& log_pair : server_downtime) {
		//�T�[�o�A�h���X
		string adr_str = log_pair.first;
		address adr(adr_str);
		subnet_log_map[adr.get_subnet_str()].push_back(log_pair.second);
	}

	//�e�T�u�l�b�g�őS�T�[�o���̏ᒆ�̊��Ԃ����߂�
	for (const auto& log_pair : subnet_log_map) {
		//�l�b�g���[�N�A�h���X
		string adr_str = log_pair.first;
		//�T�u�l�b�g�ɑ�����T�[�o�̌̏���Ԕz��
		vector<vector<period>> server_periods = log_pair.second;
		vector<int> server_i(server_periods.size(),0);

		//��ł��̏Ⴕ�Ȃ��T�[�o���������ꍇ
		if (server_periods.size() < subnet_server_count[adr_str]) {
			continue;
		}

		//map�ƗݐϘa�Řa���S���ɓ�������Ԃ����߂�
		map<ll, int> cumulative;
		for (auto& periods : server_periods) {
			for (auto& per : periods) {
				cumulative[per.first.get_date_ll()] += 1;
				if (per.second.is_set())
					cumulative[per.second.get_date_ll()] -= 1;
			}
		}
		
		int sum = 0;
		bool timeout = false;
		period peri;
		for (auto& time_num : cumulative) {
			sum += time_num.second;

			//����
			if (!timeout) {
				//����->����
				if (sum != server_periods.size()) {
					continue;
				}
				//����->�^�C���A�E�g
				timeout = true;
				peri.first.set(time_num.first);
				continue;

			}
			//�^�C���A�E�g
			if (timeout) {
				//�^�C���A�E�g->�^�C���A�E�g
				if (sum == server_periods.size()) {
					continue;
				}

				//�^�C���A�E�g->����
				peri.second.set(time_num.first);
				result[adr_str].push_back(peri);
				timeout = false;
				continue;
			}
		}
		//�^�C���A�E�g���̂܂܃��O���I������ꍇ
		if (timeout) {
			peri.second.reset();
			result[adr_str].push_back(peri);
		}

	}

	return result;
}