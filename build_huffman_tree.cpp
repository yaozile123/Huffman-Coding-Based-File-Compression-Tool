//#include <iostream>
//#include <cmath>
//#include<vector>
//#include <unordered_map>
//#include <string>
//#include<bits/stdc++.h>
//#include <fstream>
//#include <string>
//#define _CRT_SECURE_NO_WARNINGS
//using namespace std;
//
//unordered_map<char, string> huffman_map;
//unordered_map<string, char> encode_map;
//int file_len = 0;
//
//struct minheapnode
//{
//	unsigned freq;
//	char data;
//	minheapnode* left;
//	minheapnode* right;
//	minheapnode(char data, int freq) {
//		this->left = NULL;
//		this->right = NULL;
//		this->data = data;
//		this->freq = freq;
//	}
//
//};
//struct compare {
//	bool operator()(minheapnode* a, minheapnode* b) {
//		return a->freq > b->freq;
//	}
//};
//
//priority_queue<minheapnode*, vector<minheapnode*>, compare> build_heap(unordered_map<char, int> map) {
//	struct minheapnode* left, * right, * top;
//	priority_queue<minheapnode*, vector<minheapnode*>, compare> minheap;
//	unordered_map<char, int>::iterator itr;
//	for (itr = map.begin(); itr != map.end();itr++) {
//		char key = itr->first;
//		int val = itr->second;
//		minheapnode* node = new minheapnode(key, val);
//		minheap.push(node);
//		cout << "pushed node with key " << node->data << endl;
//		cout << "pushed node with val/frequency " << node->freq << endl;
//	}
//	while (minheap.size() != 1) {
//		minheapnode* node1 = minheap.top();
//		minheap.pop();
//		minheapnode* node2 = minheap.top();
//		minheap.pop();
//		minheapnode* new_node = new minheapnode('#', node1->freq + node2->freq);
//		new_node->left = node1;
//		new_node->right = node2;
//		cout << "debug2 pushed a new node to min heap from node1 and node 2 " << node1->data<< " "<<node2->data << endl;
//		cout << "node 1 frequency is " << node1->freq << " " << "node 2 frequency is " << node2->freq << endl;
//		minheap.push(new_node);
//
//
//	}
//	return minheap;
//
//	
//}
//
//unordered_map<char, int> get_frequency_dict(string sentence) {
//	unordered_map<char, int>map;
//	for (int i = 0; i < sentence.size();i++) {
//		char tmp;
//		tmp = sentence[i];
//		if (map.find(tmp) != map.end()) {
//			map[tmp] = map[tmp] + 1;
//		}
//		else {
//			map[tmp] = 1;
//		}
//	}
//	return map;
//}
//
//void print_huffman_tree(minheapnode*root,string str) {
//	if (!root) {
//		return;
//	}
//	if (root->data != '#') {
//		cout << " the string " <<" "<< root->data << " with frequency " << root->freq << " has huffman code " << str << endl;
//	}
//	print_huffman_tree(root->left, str + "0");
//	print_huffman_tree(root->right, str + '1');
//}
//
//string to8(string s) {
//	// 将st的长度补成8的倍数
//	int size = s.length();
//	int mod = 8 - (size % 8);
//	string bu = "";
//	for (int i = 0; i < mod; i++)
//		bu += "0";
//	s += bu;
//	return s;
//}
//
//int get_binary(string s) {
//	int binary = 0;
//	for (int i = 0;i < s.size();i++) {
//		if (s[i] == '1') {
//			binary += pow(2,i);
//		}
//	}
//	return binary;
//}
//
//string setStringtoASCII(string str)
//{
//	// To store size of s
//	int N = int(str.size());
//
//	// If given string is not a
//	// valid string
//	if (N % 8 != 0) {
//		return "Not Possible!";
//	}
//
//	// To store final answer
//	string res = "";
//
//	// Loop to iterate through string
//	int decimal_value = get_binary(str);
//
//	res += char(decimal_value);
//
//	// Return Answer
//	return res;
//}
//
//char setDecimaltoASCII(int decimal_value)
//{
//	char res;
//	res = char(decimal_value);
//
//	// Return Answer
//	return res;
//}
//
//string decimal_to_binary(int num) {
//	string str = "00000000";
//	int idx = 0;
//	while (num > 0) {
//		if (num % 2 == 0) {
//			str[idx] = '0';
//		}
//		else { str[idx] = '1';
//		}
//		num = num / 2;
//		idx++;
//		
//	}
//	return str;
//
//}
//
//unordered_map<char,int> open_file(const char *file_name) {
//	unordered_map<char, int> map;
//	FILE *fp = NULL;
//	cout << " now start to open the file" << endl;
//	fp = fopen(file_name, "rb");
//	if (fp == NULL) {
//		cout << "File did not open successfully, please check " << endl;
//		return map;
//	}
//	else {
//		cout << "File opened successfully! " << endl;
//	}
//	char str;
//	while (1) {
//		str = fgetc(fp);
//		if (str == EOF) {
//			break;
//		}
//		if (map.find(str) != map.end()) {
//			map[str] = map[str] + 1;
//		}
//		else {
//			map[str] = 1;
//		}
//	}
//	cout << "hash map for word frequency build successfully" << endl;
//	fclose(fp);
//	return map;
//}
//
//void build_huffman_dict(minheapnode* root, string str) {
//	if (!root) {
//		return;
//	}
//	if (root->data != '#') {
//		huffman_map.insert({root->data,str});
//		encode_map[str] = root->data;
//		//cout << " the string " << " " << root->data << " with frequency " << root->freq << " has huffman code " << str << endl;
//	}
//	build_huffman_dict(root->left, str + "0");
//	build_huffman_dict(root->right, str + "1");
//	return;
//}
//
//const char* Encode(const char* file_name, unordered_map<char, string> map) {
//	FILE* fp = NULL;
//	const char* output_file;
//	ofstream fw;
//	char str;
//	int binary_tmp;
//	string buff;
//	cout << " now start to open the file" << endl;
//	fp = fopen(file_name, "rb");
//	if (fp == NULL) {
//		cout << "File did not open successfully, please check " << endl;
//		return;
//	}
//	else {
//		cout << "File opened successfully! " << endl;
//	}
//	output_file = file_name + '.txt';
//	fw.open(output_file);
//	
//	string tmp = "00000000";
//	int idx = 0;
//	while (1) {
//		str = fgetc(fp);
//		if (str == EOF) {
//			if (idx == 0) {
//				;
//			}
//			else {
//				for (int i = idx;i < tmp.size();i++) {
//					tmp[i] = '0';
//				}
//				cout << tmp;
//				binary_tmp = get_binary(tmp);
//				fw << char(binary_tmp);
//				file_len += 1;
//				
//			}
//			
//			break;
//		}
//		file_len += 1;
//		buff = map[str];
//		
//		for (int i = 0;i < buff.size();i++) {
//			tmp[idx] = buff[i];
//			idx++;
//			if (idx == 8) {
//				idx = 0;
//				//cout << "now convert to binary, the tmp is " << tmp;
//				binary_tmp = get_binary(tmp);
//				tmp = "00000000";
//				cout << " the binary is " << binary_tmp;
//				cout << " the ascii is " << char(binary_tmp);
//				fw << char(binary_tmp);
//			}
//
//		}
//		//cout << "now str is " << str << endl;
//		//cout << "now huffman_code is " << map[str] << endl;
//		//
//	}
//	cout << "compressed file successfully" << endl;
//	fw.close();
//	fclose(fp);
//	return output_file;
//}
//
//void Decode(const char* file_name, unordered_map<string, char> map) {
//	FILE* fp = NULL;
//	const char* file_name;
//	ofstream fw;
//	int val;
//	string str;
//	string cur_code;
//	char tmp;
//	cout << " now start to open the file" << endl;
//	fp = fopen(file_name, "rb");
//	if (fp == NULL) {
//		cout << "File did not open successfully, please check " << endl;
//		return;
//	}
//	else {
//		cout << "File opened successfully! the length of file is " <<file_len<< endl;
//	}
//	fw.open("C:\\Users\\yaozl\\OneDrive\\桌面\\DAT 500S\\test_string_encode.txt");
//	int idx = 0;
//	cur_code = "";
//	while (1) {
//		tmp = fgetc(fp);
//		if (tmp == EOF) {
//			break;
//		}
//		cout << "now tmp is " << tmp << endl;
//		val = int(tmp);
//		if (val < 0) {
//			val = val + 256;
//		}
//		cout << "now ascii val is " << val << endl;
//		str = decimal_to_binary(val);
//		cout << "now binary val is " << str << endl;
//		for (int i = 0; i < str.size();i++) {
//			if (file_len == 0) {
//				break;
//			}
//			cur_code += str[i];
//			cout << "now cur code is " << cur_code << endl;
//			if (map.find(cur_code) != map.end()) {
//				cout << "find it" << endl;
//				file_len -= 1;
//				cout << file_len << endl;
//				fw << map[cur_code];
//				cur_code = "";
//			}
//			
//		}
//		
//
//	}
//	cout << "decompressed file successfully" << endl;
//	fw.close();
//	fclose(fp);
//	return;
//}
//	
//
//
//
//
//int main() {
//	const char* file_name;
//	file_name = "c:\\users\\yaozl\\onedrive\\桌面\\dat 500s\\test.txt";
//	unordered_map<char, int>map = open_file(file_name);
//	unordered_map<char, int>::iterator itr;
//	for (itr = map.begin();itr != map.end();itr++) {
//		cout << "the key is  " << itr->first << " the value/frequency is " << itr->second << endl;
//	}
//	priority_queue<minheapnode*, vector<minheapnode*>, compare> minheap;
//	minheap = build_heap(map);
//	build_huffman_dict(minheap.top(), "");
//	unordered_map<char, string>::iterator itr2;
//	unordered_map<string, char>::iterator itr3;
//	for (itr2 = huffman_map.begin();itr2 != huffman_map.end();itr2++) {
//		cout << "the key is  " << itr2->first << " the huffman code of the key is  " << itr2->second << endl;
//	}
//	for (itr3 = encode_map.begin();itr3 != encode_map.end();itr3++) {
//		cout << "the huffman code  is  " << itr3->first << " the character is   " << itr3->second << endl;
//	}
//	//cout << "started to compress file" << endl;
//	Encode(file_name, huffman_map);
//	Decode(encode_map);
//	return 0;
//	
//}