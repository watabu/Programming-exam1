#pragma once
#include "header.hpp"
#include "utilities.hpp"

typedef bitset<32> bitset32;
extern const int ADDRESS_LEN;

/// <summary>
/// �A�h���X�������N���X
/// �z�X�g�����̂ݎ擾�Ȃǂ��ȒP�ɍs����
/// </summary>
class address {
private:
	string origin;
	bitset32 bits;
	ul prefix_length;
public:
	address();
	address(string init);
	address(ul adr, ul prefix);
	address(bitset32 adr, ul prefix);

	void set(string origin);
	void set(ul adr, ul prefix);
	void set(bitset32 adr, ul prefix);

	string get_str() const;
	
	bitset32 get_address();
	ul get_prefix();
	bitset32 get_subnet_address();
	bitset32 get_host_address();

	string get_subnet_str();
	string get_host_str();

	void test_show();

private:
	string address2str(bitset32 adr, ul prefix);
};
