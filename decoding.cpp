#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct minheapnode
{
	unsigned freq;
	char data;
	minheapnode* left;
	minheapnode* right;
	minheapnode(char data, int freq) {
		this->left = NULL;
		this->right = NULL;
		this->data = data;
		this->freq = freq;
	}

};
struct compare {
	bool operator()(minheapnode* a, minheapnode* b) {
		return a->freq > b->freq;
	}
};

unordered_map<char, int> build_frequency_table(FILE* input) {
	unordered_map<char, int> map;
	char tmp;
	while (true) {
		tmp = fgetc(input);
		if (tmp == EOF) {
			cout << "frequency map build successfully!";
			break;
		}
		if (map.find(tmp) != map.end()) {
			map[tmp] += 1;
		}
		else {
			map[tmp] = 1;
		}
	}
	return map;
}


priority_queue<minheapnode*, vector<minheapnode*>, compare> build_huffman_heap(unordered_map<char, int> map) {
	struct minheapnode* left, * right, * top;
	priority_queue<minheapnode*, vector<minheapnode*>, compare> minheap;
	unordered_map<char, int>::iterator itr;
	for (itr = map.begin(); itr != map.end();itr++) {
		char key = itr->first;
		int val = itr->second;
		minheapnode* node = new minheapnode(key, val);
		minheap.push(node);
		//cout << "pushed node with key " << node->data << endl;
		//cout << "pushed node with val/frequency " << node->freq << endl;
	}
	while (minheap.size() != 1) {
		minheapnode* node1 = minheap.top();
		minheap.pop();
		minheapnode* node2 = minheap.top();
		minheap.pop();
		minheapnode* new_node = new minheapnode('#', node1->freq + node2->freq);
		new_node->left = node1;
		new_node->right = node2;
		minheap.push(new_node);
	}
	return minheap;

	
}

void print_huffman_tree(minheapnode*root,string str) {
	if (!root) {
		return;
	}
	if (root->data != '#') {
		cout << " the string " <<" "<< root->data << " with frequency " << root->freq << " has huffman code " << str << endl;
	}
	print_huffman_tree(root->left, str + "0");
	print_huffman_tree(root->right, str + '1');
}

unordered_map<char, string> build_encoding_map(minheapnode* root, string str, unordered_map<char, string> encoding_map) {
	if (!root) {
		return encoding_map;
	}
	if (root->data != '#') {
		encoding_map[root->data] = str;
	}
	encoding_map = build_encoding_map(root->left, str + "0",encoding_map);
	encoding_map = build_encoding_map(root->right, str + "1",encoding_map);
	return encoding_map;
}


string compress_huffman_tree(string str,minheapnode* root) {
	string left = "";
	string right = "";
	string current = "";
	if (!root) {
		return "";
	}
	left = compress_huffman_tree(str, root->left);
	right = compress_huffman_tree(str, root->right);
	if (root->data != '#') {
		current = "1";
		current += root->data;
	}
	else {
		current += "0";
	}
	return str + left + right + current;

}

int get_header_length(int len, minheapnode* root) {
	if (!root) {
		return 0;
	}
	int left, right, current;
	left = get_header_length(0, root->left);
	right = get_header_length(0, root->right);
	if (root->data != '#') {
		current = 1;
	}
	else {
		current = 0;
	}
	return left + right + current;
}

void read_header(FILE* fr,FILE*fw) {
	return;
}

string int_to_binary(int num) {
	string str = "00000000";
	int idx = 0;
	while (num > 0) {
		if (num % 2 != 0) {
			cout << idx;
			str[idx] = '1';
		}
		idx++;
		num = num / 2;
	}
	return str;


}
unsigned char binary_to_char(string str) {
	int tmp = 0;
	for (int i = 0; i < 8;i++) {
		if (str[i] == '1') {
			tmp += pow(2, i);
		}
	}
	unsigned char ans = char(tmp);
	return ans;
}

void write_header(FILE* fw,string str) {
	string tmp = "00000000";
	int idx = 0;
	unsigned char buff;
	int ascii_value;
	string bin;
	for (int i = 0;i < str.size();i++) {
		if (str[i] == '0') {
			tmp[idx] = '0';
			idx+=1;
		}
		else if (str[i] == '1') {
			tmp[idx] = '1';
			idx += 1;
		}
		else {
			ascii_value = int(str[i]);
			bin = int_to_binary(ascii_value);
			for (int j = 0; j < tmp.size();j++) {
				tmp[idx] = bin[j];
				idx+=1;
				if (idx == 8) {
					idx = 0;
					buff = binary_to_char(tmp);
					fwrite(&buff, sizeof(unsigned char), 1, fw);
				}
			}

		}
		if (idx == 8) {
			idx = 0;
			buff = binary_to_char(tmp);
			fwrite(&buff, sizeof(unsigned char), 1, fw);
		}

	}
	if (idx != 0) {
		for (int pos = idx;pos < tmp.size();pos++) {
			tmp[pos] = '0';
		}
		buff = binary_to_char(tmp);
		fwrite(&buff, sizeof(unsigned char), 1, fw);
	}
	return;
}



void encoding(FILE* fr,FILE*fw, unordered_map<char, string>map) {
	char str;
	int idx = 0;
	string tmp = "00000000";
	unsigned char buff;
	string huff_code;
	while (1) {
		str = fgetc(fr);
		if (str == EOF) {
			if (idx != 0) {
				for (int i = idx; i < 8; i++) {
					tmp[i] = 0;
				}
				buff = binary_to_char(tmp);
				fwrite(&buff, sizeof(unsigned char), 1, fw);
			}
			break;
		}
		huff_code = map[str];
		cout << "now str is " << str << endl;
		cout << "now huff_code is " << huff_code << endl;
		for (int i = 0;i < huff_code.size();i++) {
			tmp[idx] = huff_code[i];
			idx += 1;
			if (idx == 8) {
				idx = 0;
				buff = binary_to_char(tmp);
				fwrite(&buff, sizeof(unsigned char), 1, fw);
				cout << "write successfully";
				tmp = "00000000";
			}
		}
		
	}
	cout << "file compressed successfully" << endl;

}
priority_queue<minheapnode*, vector<minheapnode*>, compare> rebuild_huffman_heap(FILE* fr, FILE* fw) {
	struct minheapnode* left, * right, * top;
	priority_queue<minheapnode*, vector<minheapnode*>, compare> minheap;

}
void decoding(FILE* fr, FILE* fw) {

	return;
}
int main() {
	// 文件中第一个Unsigned int 是文件的长度 占4个bytes 第二个也是unsigned int 是header的长度
	const char* file_name = "c:\\users\\yaozl\\onedrive\\桌面\\dat 500s\\test.txt";
	FILE* input = fopen(file_name, "rb");
	if (input == NULL) {
		cout << "File did not open successfully, please check " << endl;
		return -1;
	}
	else {
		cout << "File opened successfully!" << endl;
	}
	fseek(input, 0L, SEEK_END);
	unsigned int file_len = ftell(input);
	cout << "the input file has total " << file_len << " bytes" << endl;
	if (fseek(input, 0, SEEK_SET) != 0) {
		cout << "failed to rewind the pointer for input file" << endl;
	}
	unordered_map<char, int> frequency_table = build_frequency_table(input);
	priority_queue<minheapnode*, vector<minheapnode*>, compare> huffman_heap = build_huffman_heap(frequency_table);
	unordered_map<char, string> encoding_map;
	encoding_map = build_encoding_map(huffman_heap.top(), "", encoding_map);
	//unordered_map<char, string>::iterator itr3;
	//for (itr3 = encoding_map.begin();itr3 != encoding_map.end();itr3++) {
	//	cout << "the character is   " << itr3->first << " the huffman code is   " << itr3->second << endl;
	//}
	if (fseek(input, 0, SEEK_SET) != 0) {
		cout << "failed to rewind the pointer for input file" << endl;
	}
	string compressed_tree = compress_huffman_tree("", huffman_heap.top());
	compressed_tree += '0';
	const char* output_file = "c:\\users\\yaozl\\onedrive\\桌面\\dat 500s\\test_encode.txt";
	FILE* output = fopen(output_file, "wb");
	fwrite(&file_len, sizeof(unsigned int), 1, output);
	unsigned int header_len = get_header_length(0, huffman_heap.top());
	header_len = header_len * 2 + 8 * header_len;
	cout << "-----" << endl;
	cout << header_len;
	if (header_len % 8 != 0) {
		header_len = header_len / 8 + 1;
	}
	else {
		header_len = header_len / 8;
	}
	cout << "the header has total " << header_len << " bytes" << endl;
	fwrite(&header_len, sizeof(unsigned int), 1, output);
	write_header(output,compressed_tree);
	encoding(input, output, encoding_map);
	fclose(input);
	fclose(output);
	return 0;
}