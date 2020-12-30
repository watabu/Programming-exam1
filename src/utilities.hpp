#pragma once
#include "header.hpp"
//ファイル分けするほどでもない細かい機能

vector<string> split(string origin, string separator);

//セグ木　完全二分木ベース
//区間X排他的論理和
class seg_tree {
	//葉の数
	int n;
	//実際のデータ
	vector<pair<ll, int> > data;
	//初期値
	pair<ll, int> init;
public:
	seg_tree(int n_);

	void update(int i, int x);
	pair<ll, int> query(int a, int b);
	pair<ll, int> top();

private:

	//k: 現在見ているノードの位置、 [l, r): data[k]があらわしている区間
	pair<ll, int> query_sub(int a, int b, int k, int l, int r);
};