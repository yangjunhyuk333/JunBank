#include <iostream>
#include <stdio.h>
using namespace std;

typedef struct {
	int accId;
	int balance;
	char cusName[20];
}Account;

Account* account = new Account[100];
int Member_Number = 0;

void creatAccount() {
	Account User;

	cout << "[���°���]" << endl;
	cout << "����ID:  ";
	cin >> User.accId;
	cout << "��  ��: ";
	cin >> User.cusName;
	cout << "�Աݾ�: ";
	cin >> User.balance;

	account[Member_Number] = User;

	Member_Number++;
}

void deposit() {
	int depositInput;
	int checkAccId;

	cout << "[�Ա�]" << endl;
	cout << "ID: ";
	cin >> checkAccId;
	cout << "�Աݾ�: ";
	cin >> depositInput;

	for (int i = 0; i < Member_Number; i++) {
		if (account[i].accId == checkAccId) {
			account[i].balance += depositInput;
		}
		else {
			cout << "��ȿ���� ���� ID �Դϴ�." << endl;
		}
	}
	cout << endl;
}

void withdraw() {
	int withdrawAmount;
	int checkAccId;

	cout << "[���]" << endl;
	cout << "ID: " << endl;
	cin >> checkAccId;
	cout << "�󸶸� ����Ͻðڽ��ϱ�?" << endl;
	cin >> withdrawAmount;

	for (int i = 0; i < Member_Number; i++) {
		if (account[i].accId == checkAccId) {
			account[i].balance -= withdrawAmount;
		}
		else {
			cout << "��ȿ���� ���� ID �Դϴ�." << endl;
		}
	}
	cout << endl;
}

void accountPrint() {
	for (int i = 0; i < Member_Number; i++) {
		cout << "����ID: " << account[i].accId << endl;
		cout << "��  ��: " << account[i].cusName << endl;
		cout << "��  ��: " << account[i].balance << endl;
	}
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