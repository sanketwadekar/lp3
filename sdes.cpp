#include<iostream>
using namespace std;

int* p8(int* number){
	int positions[8] = {5, 2, 6, 3, 7, 4, 9, 8};
	int* result = new int[8];
	for(int i = 0; i < 8; i++){
		result[i] = number[positions[i]];
	}
	return result;
}

int* p10(int number[]){
	int positions[10] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};
	int* result = new int[10];
	for(int i = 0; i < 10; i++){
		cout<<"Substituting "<<number[positions[i]] <<" at "<<i<<endl;
		result[i] = number[positions[i]];
	}
	return result;
}

void leftshift(int* key, int start){
	int temp = key[start];
	for(int i = start; i < start + 4; i++){
		key[i] = key[i + 1];
	}
	key[start + 4] = temp;
}

void printData(int* arr, int len){
	for(int i = 0; i < len; i++){
		cout<<arr[i];
	}
	cout<<endl;
}

void ip(int* pt){
	int pos[8] = {1, 5, 2, 0, 3, 7, 4, 6};
	int temp[8];
	for(int i =0; i < 8; i++){
		temp[i] = pt[i];
	}
	for(int i =0; i < 8; i++){
		pt[i] = temp[pos[i]];
	}
}

int* ep(int* pt){
	int pos[8] = {3, 0, 1, 2, 1, 2, 3, 0};
	int temp[4];
	int* expandedText = new int[8];
	for(int i =0; i < 4; i++){
		temp[i] = pt[i  + 4];
	}
	for(int i =0; i < 8; i++){
		expandedText[i] = temp[pos[i]];
	}
	return expandedText;
}


void xorkey(int* pt, int* k){
	for(int i = 0; i < 8; i++){
		pt[i] = pt[i] ^ k[i];
	}
}


void s0(int* pt, int* op){
	int box[4][4] = {{1, 0, 3, 2},
	{3, 2, 1, 0},
	{0, 2, 1, 3},
	{3, 1, 3, 2}};
	int b1 = pt[0], b2 = pt[1], b3 = pt[2], b4 = pt[3];
	int col = 2*b2 + b3;
	int row = 2*b1 + b4;
	int newSub = box[row][col];
	op[1] = newSub%2;
	op[0] = (newSub/2)%2;
}

void s1(int* pt, int* op){
	int box[4][4] = {{0, 1, 2, 3},
		{2, 0, 1, 3},
		{3, 0, 1, 0},
		{2, 1, 0, 3}};
	int b1 = pt[4], b2 = pt[5], b3 = pt[6], b4 = pt[7];
	int col = 2*b2 + b3;
	int row = 2*b1 + b4;
	int newSub = box[row][col];
	op[3] = newSub%2;
	op[2] = (newSub/2)%2;
}

void p4(int* op){
	int pos[4] = {1, 3, 2, 0};
	int temp[4] = {op[0], op[1], op[2], op[3]};
	for(int i = 0; i < 4; i++){
		op[i] = temp[pos[i]];
	}
}

void xorlpt(int* pt, int* op){
	for(int i = 0; i < 4; i++){
		pt[i] = op[i] ^ pt[i];
	}
}

void sw(int* pt){
	for(int i = 0; i < 4; i++){
		int temp = pt[i];
		pt[i] = pt[i + 4];
		pt[i + 4] = temp;
	}
}

void fk(int* pt, int* k){
	int* expandedtext = ep(pt);
	cout<<"\nExpanded Text = ";
	printData(expandedtext, 8);
	xorkey(expandedtext, k);
	cout<<"\nEXOR with key = ";
	printData(expandedtext, 8);
	int* op = new int[4];
	s0(expandedtext, op);
	s1(expandedtext, op);
	cout<<"\n After s0 and s1 = ";
	printData(op, 4);
	p4(op);
	cout<<"\n After p4 = ";
	printData(op, 4);
	xorlpt(pt, op);
	cout<<"\n After xor with lpt = ";
	printData(pt, 4);
}

void inversep(int* pt){
	int pos[8] = {3, 0, 2, 4, 6, 1, 7, 5};
	int temp[8];
	for(int i =0; i < 8; i++){
		temp[i] = pt[i];
	}
	for(int i =0; i < 8; i++){
		pt[i] = temp[pos[i]];
	}
}

int main(){
	int key[10], plaintext[8], ciphertext[8];
	for(int i = 0; i < 10; i++){
		cin>>key[i];
	}

	// KEY GENERATION
	int* p10result = p10(key);
	cout<<"After p10: ";
	printData(p10result, 10);
	leftshift(p10result, 0);
	leftshift(p10result, 5);
	cout<<"\nAfter left shift: ";
	printData(p10result, 10);
	int* k1 = p8(p10result);
	cout<<"\nKey1 = ";
	printData(k1, 8);
	leftshift(p10result, 0);
	leftshift(p10result, 0);
	leftshift(p10result, 5);
	leftshift(p10result, 5);
	cout<<"\nKey2 = ";
	int* k2 = p8(p10result);
	printData(k2, 8);

	cout<<"Enter plain text (8 bit) : ";
	for(int i = 0; i < 8; i++){
		cin>>plaintext[i];
	}

	// ENCRYPTION
	ip(plaintext);
	cout<<"\n\nENCRYPTION\n\nAfter Initial Permutation, ";
	printData(plaintext, 8);
	// Round 1
	fk(plaintext, k1);
	cout<<"\nAfter Round 1, ";
	printData(plaintext, 8);
	sw(plaintext);
	cout<<"\nAfter sw : ";
	printData(plaintext, 8);
	//Round 2
	fk(plaintext, k2);
	cout<<"\nAfter two rounds, ciphertext = ";
	printData(plaintext, 8);
	inversep(plaintext);
	cout<<"\nAfter inverse permutation, ciphertext = ";
	printData(plaintext, 8);



	//DECRYPTION
	ip(plaintext);
	cout<<"\n\nDECRYPTION\n\nAfter Initial Permutation, ";
	printData(plaintext, 8);
	fk(plaintext, k2);
	cout<<"\nAfter Round 1, ";
	printData(plaintext, 8);
	sw(plaintext);
	cout<<"\nAfter sw : ";
	printData(plaintext, 8);
	fk(plaintext, k1);
	cout<<"\nAfter Round 2, ";
	printData(plaintext, 8);
	inversep(plaintext);
	cout<<"\nAfter inverse permutation, plaintext = ";
	printData(plaintext, 8);
	return 0;
}