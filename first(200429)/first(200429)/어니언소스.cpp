#include <iostream>
#include <stdio.h>
using namespace std;

typedef struct {
	int accId;
	int balance;
	char cusName[20];
}Account;

void creatAccount() {
	Account* account = new Account[100];

	cout << "[���°���]" << endl;
	cout << "����ID:  ";
	cin >> account -> accId;
	cout << "��  ��: ";
	cin >> account -> cusName;
	cout << "�Աݾ�: ";
	cin >> account -> balance;
}

void deposit() {
	printf("�Ա�");
}

void withdraw() {
	printf("���");
}

void accountPrint() {
	printf("�� ��ü ���");
}

int main() {
	while (1) {
		int input = 0;
		Account* member = new Account;

		cout << "-----Menu-----\n1. ���°���\n2. �Ա�\n3. ���\n4. �������� ��ü ���\n5. ���α׷� ����\n����: ";
		cin >> input;

		switch (input) {
		case 1:
			creatAccount();
			break;
		case 2:
			deposit();
			break;
		case 3:
			withdraw();
			break;
		case 4:
			accountPrint();
			break;
		case 5:
			cout << "���α׷� ����" << endl;
			delete[] member;
			return 0;
		default:
			printf("6���ʹ� ������ �ȵ�! �ٷ� ����!!");
		}
	}
}