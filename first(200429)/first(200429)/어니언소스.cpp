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
	int length; //cusName�� ���̸� �޾ƿ��� ����

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
		cout << "��ü�� �����˴ϴ�." << endl;

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
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << endl;
	}

	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}

	void Print_Account_Information() {
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
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

	cout << "[���°���]" << endl;
	cout << "����ID:  ";
	cin >> accountId;
	cout << "��  ��: ";
	cin >> accountName;
	cout << "�Աݾ�: ";
	cin >> accountBalance;
	//�ּ� �Ա� �ݾ� Ȯ��
	if (accountBalance < 10) {
		cout << "�ּ� �Ա� �ݾ��� 10���Դϴ�." << endl;
		cout << "�Աݾ�: ";
		cin >> accountBalance;
	}

	cout << "�ֹε�Ϲ�ȣ: ";
	cin >> Resident_registration_number;

	account[Member_Number] = new Account(accountId, accountBalance,
		Resident_registration_number, accountName);

	Member_Number++;

	cout << endl;
}

void deposit() {
	int depositInput = 0;
	int checkAccId;

	cout << "[�Ա�]" << endl;
	cout << "ID: ";
	cin >> checkAccId;
	for (int i = 0; i < Member_Number; i++) {
		if (account[i]->CheckAccount(checkAccId)) {
			cout << "�Աݾ�: ";
			cin >> depositInput;
			cout << endl;
			account[i]->Deposit(depositInput);
		}
		else {
			cout << "��ȿ���� ���� ID �Դϴ�." << endl;
			return;
		}
	}

}

void withdraw() {
	int withdrawAmount = 0;
	int checkAccId;

	cout << "[���]" << endl;
	cout << "ID: ";
	cin >> checkAccId;
	for (int i = 0; i < Member_Number; i++) {
		if (account[i]->CheckAccount(checkAccId)) {
			cout << "�󸶸� ����Ͻðڽ��ϱ�?" << endl;
			cin >> withdrawAmount;
			cout << endl;
			account[i]->Withdraw(withdrawAmount);
		}
		else {
			cout << "��ȿ���� ���� ID �Դϴ�." << endl;
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
			Printaccount();
			break;
		case 5:
			cout << "���α׷� ����" << endl;
			for (int i = 0; i < Member_Number; i++) delete account[i];
			return 0;
		default:
			printf("6���ʹ� ������ �ȵ�! �ٷ� ����!!");
		}
	}
}