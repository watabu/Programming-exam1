#include "utilities.hpp"

//��������w�肳�ꂽ�����ŕ�������
vector<string> split(string origin, string separator) {
	vector<string> result;

	string tmp;
	for (auto c : origin) {
		//�Z�p���[�^�[�̏ꍇ
		if (separator.find(c) != string::npos) {
			result.push_back(tmp);
			tmp = "";
			continue;
		}

		tmp.push_back(c);
	}
	result.push_back(tmp);
	return result;
}


seg_tree::seg_tree(int n_) {
	int m = 1;
	init = make_pair(1e18,0);
	while (m < n_) {
		m *= 2;
	}
	n = m;
	//�t�̐�n, �}�̐� n - 1
	data = vector<pair<ll, int>>(2 * n - 1, init);
}

void seg_tree::update(int i, int x) {
	int j = n - 1 + i;
	data[j].first = x;
	data[j].second = i;
	while (j > 0) {
		j = (j - 1) / 2;
		data[j] = min(data[j * 2 + 1], data[j * 2 + 2]);
	}
}

pair<ll, int> seg_tree::query(int a, int b) {
	return query_sub(a, b, 0, 0, n);
}

pair<ll, int> seg_tree::top() {
	return query(0, n);
}


//k: ���݌��Ă���m�[�h�̈ʒu�A [l, r): data[k]������킵�Ă�����
pair<ll, int> seg_tree::query_sub(int a, int b, int k, int l, int r) {
	if (r <= a || b <= l) {//�͈͊O
		return init;
	}
	else if (a <= l && r <= b) {//�͈͓��Ȃ̂Ŏ��g�̒l��Ԃ�
		return data[k];
	}
	else {//�ꕔ��Ԃ����Ƃ�
		pair<ll, int> vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
		pair<ll, int> vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);

		return min(vl, vr);
	}
}