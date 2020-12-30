#pragma once
#include "header.hpp"
//�t�@�C����������قǂł��Ȃ��ׂ����@�\

vector<string> split(string origin, string separator);

//�Z�O�؁@���S�񕪖؃x�[�X
//���X�r���I�_���a
class seg_tree {
	//�t�̐�
	int n;
	//���ۂ̃f�[�^
	vector<pair<ll, int> > data;
	//�����l
	pair<ll, int> init;
public:
	seg_tree(int n_);

	void update(int i, int x);
	pair<ll, int> query(int a, int b);
	pair<ll, int> top();

private:

	//k: ���݌��Ă���m�[�h�̈ʒu�A [l, r): data[k]������킵�Ă�����
	pair<ll, int> query_sub(int a, int b, int k, int l, int r);
};