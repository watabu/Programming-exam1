#include "utilities.hpp"

//文字列を指定された文字で分割する
vector<string> split(string origin, string separator) {
	vector<string> result;

	string tmp;
	for (auto c : origin) {
		//セパレーターの場合
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
	//葉の数n, 枝の数 n - 1
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


//k: 現在見ているノードの位置、 [l, r): data[k]があらわしている区間
pair<ll, int> seg_tree::query_sub(int a, int b, int k, int l, int r) {
	if (r <= a || b <= l) {//範囲外
		return init;
	}
	else if (a <= l && r <= b) {//範囲内なので自身の値を返す
		return data[k];
	}
	else {//一部区間が被るとき
		pair<ll, int> vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
		pair<ll, int> vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);

		return min(vl, vr);
	}
}