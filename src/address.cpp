#include "address.hpp"

const int ADDRESS_LEN = 32;

address::address() {
	const string init = "0.0.0.0/16";
	set(init);
}
address::address(string init) {
	set(init);
}
address::address(ul adr, ul prefix) {
	set(adr, prefix);
}

address::address(bitset32 adr, ul prefix) {
	set(adr, prefix);
}

void address::set(string origin) {
	this->origin = origin;

	//0~3番目はアドレス、4番目がプレフィクス長
	auto result = split(origin, "./");
	//不正な値が与えられた場合
	if (result.size() != 5) {
		cout << "error: invalid value\n";
		return;
	}

	int tmp_adr = 0;
	for (size_t i = 0; i < 4; i++)
	{
		tmp_adr *= 256;
		tmp_adr += stoi(result[i]);
	}
	bits = tmp_adr;
	prefix_length = stoi(result[4]);
}

void address::set(ul adr, ul prefix) {
	bits = adr;
	prefix_length = prefix;
	origin = address2str(adr, prefix);
}

void address::set(bitset32 adr, ul prefix) {
	bits = adr;
	prefix_length = prefix;
	origin = address2str(adr, prefix);
}

string address::get_str() const{
	return origin;
}

bitset32 address::get_address() {
	return bits;
}

//
ul address::get_prefix() {
	return prefix_length;
}

//ネットワーク部のアドレスを取得
bitset32 address::get_subnet_address() {
	bitset32 all = bits;
	bitset32 network = all >> (ADDRESS_LEN - prefix_length) << (ADDRESS_LEN - prefix_length);
	return network;
}

//ホスト部のアドレスを取得
bitset32 address::get_host_address() {
	bitset32 all = bits;
	bitset32 host = all << prefix_length >> prefix_length;
	return host;
}

string address::get_subnet_str() {
	return address2str(get_subnet_address(), prefix_length);
}

string address::get_host_str() {
	return address2str(get_host_address(), prefix_length);
}

//アドレスを簡易的に出力する
void address::test_show() {
	cout << "ori: " << get_str() << endl;
	cout << "net: " << get_subnet_str() << endl;
	cout << "hst: " << get_host_str() << endl;
	cout << "prf: " << get_prefix() << endl;
}



//分解されたアドレスを表示用の文字列に変換する
string address::address2str(bitset32 adr, ul prefix) {
	string result = "";

	bitset32 adr_tmp = 0;
	for (size_t i = 0; i < ADDRESS_LEN; i++)
	{
		adr_tmp[ADDRESS_LEN - 1 - i] = adr[i];
	}

	for (size_t i = 0; i < 4; i++)
	{
		int value = 0;
		for (size_t j = 0; j < 8; j++)
		{
			int index = i * 8 + j;
			value *= 2;
			value += adr_tmp[index];
		}

		result += to_string(value);

		if (i != 3)
			result.push_back('.');
	}
	result.push_back('/');
	result += to_string(prefix);
	return result;
}