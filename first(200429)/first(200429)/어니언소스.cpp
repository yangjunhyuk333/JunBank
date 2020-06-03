#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_LEN 20

//typedef struct {
//	int accId;
//	int balance;
//	char cusName[20];
//}Account;

class Account {
public:
	int length; //cusName의 길이를 받아오는 변수

private:
	int accID;
	int balance;
	int Resident_registration_number;
	char* cusName;

public:
	Account(int accID, int balance, int Resident_registration_number, char* cusName)
	{
		this->accID = accID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	~Account() {
		cout << "객체가 삭제됩니다." << endl;

		delete[] cusName;
	}

	void Deposit(int balance) {
		this->balance += balance;
	}

	bool CheckAccount(int accountId) {
		return this->accID == accountId;
	}

	bool Withdraw(int balance) {
		if (this->balance < balance) {
			return false;
		}

		this->balance -= balance;
		return true;
	}

	void PrintAccount() {
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << endl;
	}

	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}

	void Print_Account_Information() {
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << endl;
	}

};

Account* account[100];
int Member_Number = 0;

void creatAccount() {
	int accountId;
	int accountBalance;
	char accountName[20];
	int Resident_registration_number;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID:  ";
	cin >> accountId;
	cout << "이  름: ";
	cin >> accountName;
	cout << "입금액: ";
	cin >> accountBalance;
	//최소 입금 금액 확인
	if (accountBalance < 10) {
		cout << "최소 입금 금액은 10원입니다." << endl;
		cout << "입금액: ";
		cin >> accountBalance;
	}

	cout << "주민등록번호: ";
	cin >> Resident_registration_number;

	account[Member_Number] = new Account(accountId, accountBalance,
		Resident_registration_number, accountName);

	Member_Number++;

	cout << endl;
}

void deposit() {
	int depositInput = 0;
	int checkAccId;

	cout << "[입금]" << endl;
	cout << "ID: ";
	cin >> checkAccId;
	for (int i = 0; i < Member_Number; i++) {
		if (account[i]->CheckAccount(checkAccId)) {
			cout << "입금액: ";
			cin >> depositInput;
			cout << endl;
			account[i]->Deposit(depositInput);
		}
		else {
			cout << "유효하지 않은 ID 입니다." << endl;
			return;
		}
	}

}

void withdraw() {
	int withdrawAmount = 0;
	int checkAccId;

	cout << "[출금]" << endl;
	cout << "ID: ";
	cin >> checkAccId;
	for (int i = 0; i < Member_Number; i++) {
		if (account[i]->CheckAccount(checkAccId)) {
			cout << "얼마를 출금하시겠습니까?" << endl;
			cin >> withdrawAmount;
			cout << endl;
			account[i]->Withdraw(withdrawAmount);
		}
		else {
			cout << "유효하지 않은 ID 입니다." << endl;
			return;
		}
	}

}

void Printaccount() {
	for (int i = 0; i < Member_Number; i++) {
		cout << endl;
		account[i]->PrintAccount();
	}
}

int main() {
	while (1) {
		int input = 0;

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
			Printaccount();
			break;
		case 5:
			cout << "프로그램 종료" << endl;
			for (int i = 0; i < Member_Number; i++) delete account[i];
			return 0;
		default:
			printf("6부터는 적으면 안돼! 바로 종료!!");
		}
	}
}