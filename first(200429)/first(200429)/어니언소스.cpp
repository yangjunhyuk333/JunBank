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

	cout << "[계좌개설]" << endl;
	cout << "계좌ID:  ";
	cin >> User.accId;
	cout << "이  름: ";
	cin >> User.cusName;
	cout << "입금액: ";
	cin >> User.balance;

	account[Member_Number] = User;

	Member_Number++;
}

void deposit() {
	int depositInput;
	int checkAccId;

	cout << "[입금]" << endl;
	cout << "ID: ";
	cin >> checkAccId;
	cout << "입금액: ";
	cin >> depositInput;

	for (int i = 0; i < Member_Number; i++) {
		if (account[i].accId == checkAccId) {
			account[i].balance += depositInput;
		}
		else {
			cout << "유효하지 않은 ID 입니다." << endl;
		}
	}
	cout << endl;
}

void withdraw() {
	int withdrawAmount;
	int checkAccId;

	cout << "[출금]" << endl;
	cout << "ID: " << endl;
	cin >> checkAccId;
	cout << "얼마를 출금하시겠습니까?" << endl;
	cin >> withdrawAmount;

	for (int i = 0; i < Member_Number; i++) {
		if (account[i].accId == checkAccId) {
			account[i].balance -= withdrawAmount;
		}
		else {
			cout << "유효하지 않은 ID 입니다." << endl;
		}
	}
	cout << endl;
}

void accountPrint() {
	for (int i = 0; i < Member_Number; i++) {
		cout << "계좌ID: " << account[i].accId << endl;
		cout << "이  름: " << account[i].cusName << endl;
		cout << "잔  액: " << account[i].balance << endl;
	}
}

int main() {
	while (1) {
		int input = 0;
		Account* member = new Account;

		cout << "-----Menu-----\n1. 계좌개설\n2. 입금\n3. 출금\n4. 계좌정보 전체 출력\n5. 프로그램 종료\n선택: ";
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
			cout << "프로그램 종료" << endl;
			delete[] member;
			return 0;
		default:
			printf("6부터는 적으면 안돼! 바로 종료!!");
		}
	}
}