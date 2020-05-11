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

	cout << "[계좌개설]" << endl;
	cout << "계좌ID:  ";
	cin >> account -> accId;
	cout << "이  름: ";
	cin >> account -> cusName;
	cout << "입금액: ";
	cin >> account -> balance;
}

void deposit() {
	printf("입금");
}

void withdraw() {
	printf("출금");
}

void accountPrint() {
	printf("고객 전체 출력");
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