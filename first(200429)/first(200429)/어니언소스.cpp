#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_LEN 20
#define MAX_MEMBER 100

//������ ���� ����
//typedef struct {
//	int accId;
//	int balance;
//	char cusName[20];
//}Account;

//���� Ŭ����(���� ����)
class Account {

protected:
	int accID; //���� ��ȣ
	int balance; //���� �ܾ�
	int Resident_registration_number; //�ֹε�Ϲ�ȣ
	char* cusName; //�̸�

public:

	//������ ���̵�, �ݾ�, �ֹε�Ϲ�ȣ, �̸�
	Account(int inputAccID, int balance, int Resident_registration_number, char* cusName)
	{
		this->accID = inputAccID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	//���� ���� ����(�����ε�)
	Account(int inputAccID, int Resident_registration_number, char* cusName) : accID(inputAccID){
		this->balance = 0;
		this->accID = inputAccID;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	//�Ҹ���
	~Account() {
		cout << "��ü�� �����˴ϴ�." << endl; //�Ҹ��ڰ� ȣ���� �Ǹ� �ش� ������ ���

		delete[] cusName;
	}

	//���� ������
	Account(const Account& copy_user)
		: accID(copy_user.accID), Resident_registration_number(copy_user.Resident_registration_number)
	{
		cout << "���� ������ ȣ��" << endl;
		this->balance = copy_user.balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, copy_user.cusName);
	}

	//��� ����� ��� ���� �޼ҵ�
	char *getAccountMember(){
		return cusName;
	}

	//��� ID ����� ��� ���� �޼ҵ�
	int getAccountId() const {
		return accID;
	}

	//��� �ֹε�Ϲ�ȣ�� ��� ���� �޼ҵ�
	int getResident_registration() const {
		return Resident_registration_number;
	}

	//�Ա�
	virtual void Deposit(int balance) {
		int calInterest = interest(this->balance + balance);;
		this->balance += balance + calInterest;
		cout << "������: ";
		cout << calInterest << endl;
		cout << endl;
	}

	//������ ����ؼ� ��ȯ�ϴ� �޼ҵ�(������: 1%)
	virtual int interest(int balance) {
		return ((int) balance * 0.01);
	}

	//���� Ȯ��(���¸� Ȯ���ؼ� boolean ���� �����ִ� �޼ҵ�),
	bool CheckAccount(int accountId) const {
		return this->accID == accountId; //����ڰ� �Է��� ���°� �ִ��� Ȯ��
	} 

	//���
	bool Withdraw(int balance) {
		if (this->balance < balance) { 
			return false; 
		}

		this->balance -= balance;
		return true;
	}

	//���� ��ü ���
	virtual void PrintAccount() const {
		cout << endl;
		cout << "���� ����: ����" << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹε�Ϲ�ȣ: " << Resident_registration_number << endl;
		cout << endl;
	}

	//�ֹε�Ϲ�ȣ Ȯ��
	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}

};

//���� ���� Ŭ���� (Account Ŭ���� ���)
class DepositAccount : public Account {
private:
	int balance;

public:

	//���ݰ��� ����
	DepositAccount(Account& copy_member, int inputAccID) 
		: Account(inputAccID, copy_member.getResident_registration(), copy_member.getAccountMember())
	{
		balance = 0;
	}

	~DepositAccount(){

	}

	
	//�Ա�(����)
	virtual void Deposit(int balance) {
		int calInterest = interest(this->balance + balance);
		this->balance += balance + calInterest;
		cout << "������: ";
		cout << calInterest << endl;
		cout << endl;
	}

	//������ ����ؼ� ��ȯ�ϴ� �޼ҵ�(������: 2%)
	virtual int interest(int balance) {
		return ((int)balance * 0.02);
	}

	virtual void PrintAccount() const{
		cout << endl;
		cout << "���� ����: ����" << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹε�Ϲ�ȣ: " << Resident_registration_number << endl;
		cout << endl;
	}

};

//���� ���� Ŭ����
class AccountManager {

public:

	//��ü ����
	Account* account[MAX_MEMBER]; //���� ����
	int Member_Number = 0; //��� ���� ī��Ʈ

	//� ���¿��� �۾��� �� �� �����ϴ� �Լ�
	int CheckAccountType() {
		int selectType;

		cout << "� ���¿��� �۾��Ͻðڽ��ϱ�?\n1. ���� ���� \n2. ���� ����" << endl;
		cin >> selectType;

		switch (selectType)
		{
		case 1:
			return 1;
			break;

		case 2:
			return 2;
			break;

		default:
			cout << "���ڸ� �߸� �Է��ϼ̽��ϴ�." << endl;
			cout << endl;
			CheckAccountType();
		}
	}

	//���� ���θ� Ȯ�� �ϴ� �Լ�
	bool CheckAccount() {
		if (Member_Number == 0) {
			cout << "���� ��ϵ� ���°� �����ϴ�." << endl;
			return false;
		}
		return true;
	}
	
	//ID�ߺ��Ǵ� �� Ȯ�� �ϴ� �Լ�
	bool CheckAccId(int accID) {
		for (int checkAccId_idx = 0; checkAccId_idx < Member_Number; checkAccId_idx++) {
			if (account[checkAccId_idx]->CheckAccount(accID)) {
				return true;
			}
		}
		return false;	
	}

	//�ߺ��Ǵ� Id �ε����� �����ϴ� �Լ�
	int CheckAccId_idx(int accID) {
		for (int checkAccId_idx = 0; checkAccId_idx <= Member_Number; checkAccId_idx++) {
			if (accID == account[checkAccId_idx]->getAccountId()) {
				return checkAccId_idx;
			}
		}
		return 0;
	}
	
	//�ֹε�Ϲ�ȣ �ߺ� Ȯ��
	bool CheckResidentNumber(int residentNumber) {
		for (int checkAccResident_idx = 0; checkAccResident_idx < Member_Number; checkAccResident_idx++) {
			if (residentNumber == account[checkAccResident_idx]->getResident_registration()) {
				return true;
			}
			return false;
		}
	}

	//���� ����
	void CreateAccount() {
		cout << endl;
		cout << "[���°���]" << endl;

		int checkType = CheckAccountType();

		if (checkType == 1) {
			CreateOrdinaryAccount();
		}
		else if (checkType == 2){
			CreateDepositAccount();
		}
		else {
			cout << endl;
			cout << "�߸� �����ϼ̽��ϴ�." << endl;
			cout << endl;
			CreateAccount();
			cout << endl;
		}
	}

	//������� ����
	void CreateOrdinaryAccount() {
		//���� ����
		int inputId; //ID �Է�
		int inputResidentNumber; //�ֹε�Ϲ�ȣ �Է�
		int amountBalance; //�Աݾ� �Է�
		char* inputCusName = new char[MAX_LEN]; //�̸� �Է�
		
		//����
		cout << endl;
		cout << "���� ID: ";
		cin >> inputId;

		//�ߺ� �˻�(ID)
		while (1) {
			if (Member_Number > 0 && CheckAccId(inputId) == true) {
				cout << endl;
				cout << "���°� �ߺ� �˴ϴ�. �ٽ� �Է����ּ���." << endl;
				cout << "���� ID: ";
				cin >> inputId;
				cout << endl;
				continue;
			}
			else {
				break;
			}
		}

		//�̸� �Է�
		cout << "�̸�: ";
		cin >> inputCusName;

		//�Աݾ� �Է�
		cout << "�Աݾ�: ";
		cin >> amountBalance;
		
		//�ּ� �Աݾ�
		while (1) {
			if (amountBalance < 10) {
				cout << "���°��� �� �ּ� �Աݾ��� 10�� �̻��Դϴ�." << endl;
				cout << "�Աݾ�: ";
				cin >> amountBalance;
				continue;
			}
			else { 
				break; 
			}
		}

		//�ֹε�Ϲ�ȣ �Է�
		cout << "�ֹε�Ϲ�ȣ: ";
		cin >> inputResidentNumber;
		cout << endl;

		//�ߺ� �˻�(�ֹε�Ϲ�ȣ)
		while (1) {
			if (CheckResidentNumber(inputResidentNumber) == true) {
				cout << "�ֹε�Ϲ�ȣ�� �ߺ� �˴ϴ�. �ٽ� �Է����ּ���." << endl;
				cout << "�ֹε�Ϲ�ȣ: ";
				cin >> inputResidentNumber;
				continue;
			}
			else {
				break;
			}
		}
		

		//������ ȣ��(���� ����)
		account[Member_Number] = new Account(inputId, amountBalance, inputResidentNumber, inputCusName);
		Member_Number++;

	}

	//���ݰ��� ����
	void CreateDepositAccount() {
		//���� ����
		int inputOrdinaryId = 0; //���� ID �Է�
		int ordinaryId_idx = 0; //���� ID �ε��� �޾ƿ���
		int inputId = 0; //ID �Է�
		int amountBalance = 0; //�Աݾ� �Է�
		bool checkParam;

		//���� ���� �Է�
		cout << endl;
		cout << "���� ����: ";
		cin >> inputOrdinaryId;

		while (1) {
			//ID�˻�
			checkParam = CheckAccId(inputOrdinaryId);

			//���� ���� �˻�(�˻�)
			if (checkParam != true) { //�������� ������ �ٽ� �Է�
				cout << endl;
				cout << "���� ���°� �������� �ʽ��ϴ�." << endl;
				cout << "���� ����: ";
				cin >> inputOrdinaryId;
				cout << endl;
				continue;
			}
			else {
				//���� ���� �ε��� ����
				ordinaryId_idx = CheckAccId_idx(inputOrdinaryId);
				break;
			}
		}

		//����ID �Է�
		cout << "����ID: ";
		cin >> inputId;

		//���� ��ȣ �ߺ� �˻�
		while (1) {
			if (CheckAccId(inputId) == true) { //�ߺ� �Ǹ� �ٽ� �Է�
				cout << endl;
				cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
				cout << "����ID: ";
				cin >> inputId;
				cout << endl;
				continue;
			}
			else {
				break;
			}
		}
		
		//���� ���� ����
		account[Member_Number] = new DepositAccount(*account[ordinaryId_idx], inputId);

		//��� ���� ����
		Member_Number++;

	}

	//���� �Ա�
	void Deposit() {
		int inputId; //ID�Է�
		int amountBalance; //�Ա��� �ݾ�
		int selectId_idx; //ID �ε���
		bool checkParam; //check�� ���� ����

		//����� ������ ���� �޴��� ���ư�
		if (Member_Number < 1) {
			cout << endl;
			cout << "����� �����Ƿ� ������ �� �����ϴ�." << endl;
			cout << endl;
			return;
		}

		//�Ա� �� ���� ID(���� ��ȣ) �Է�
		cout << endl;
		cout << "[�Ա�]" << endl;
		cout << "ID: ";
		cin >> inputId;

		//�Է��� ID�� �ִ��� ���� �˻�
		while (1) {
			
			selectId_idx = CheckAccId_idx(inputId);

			checkParam = CheckAccId(inputId);

			if (checkParam != true) { //���ٸ� �ٽ� �Է�
				cout << "�ش��ϴ� ID�� �����ϴ�." << endl;
				cout << "ID: ";
				cin >> inputId;
				cout << endl;
				continue;
			}
			else {
				break;
			}
		}

		//�Աݾ� �Է�
		cout << "�Աݾ�: ";
		cin >> amountBalance;

		//�Ա�
		account[selectId_idx]->Deposit(amountBalance);

	}

	//���� ���
	void Withdraw() {
		int inputId; //ID�Է�
		int amountBalance; //�Ա��� �ݾ�
		int selectId_idx; //ID �ε���
		bool checkParam; //check�� ���� ����

		//����� ������ ���� �޴��� ���ư�
		if (Member_Number < 1) {
			cout << endl;
			cout << "����� �����Ƿ� ������ �� �����ϴ�." << endl;
			cout << endl;
			return;
		}

		//����� �� ID �Է�
		cout << endl;
		cout << "[���]" << endl;
		cout << "ID: ";
		cin >> inputId;

		//�ش�Ǵ� ID�� �ִ��� ���� �˻�
		while (1) {
			selectId_idx = CheckAccId_idx(inputId);
			checkParam = CheckAccId(inputId);

			if (checkParam != true) { //���ٸ� �ٽ� �Է�
				cout << endl;
				cout << "�ش��ϴ� ID�� �����ϴ�.";
				cout << "ID: ";
				cin >> inputId;
				continue;
			}
			else {
				break;
			}
		}

		//��ݾ� �Է�
		cout << "��ݾ�: ";
		cin >> amountBalance;
		cout << endl;

		//���
		account[selectId_idx]->Withdraw(amountBalance);
	}

	//���� ���
	void Printaccount() const{
		for (int printIdx = 0; printIdx < Member_Number; printIdx++) {
			cout << endl;
			account[printIdx]->PrintAccount();
		}

		//����� �ִ��� ���� �˻�
		if (Member_Number < 1) {
			cout << endl;
			cout << "����� �����Ƿ� ������ �� �����ϴ�." << endl;
			cout << endl;
			return;
		}
	}
};

//AccountManager ��ü ����
AccountManager accountManager;

//���� �Լ�
int main() {
	while (1) {
		int input = 0;

		cout << "-----Menu-----\n1. ���°���\n2. �Ա�\n3. ���\n4. �������� ��ü ���\n5. ���α׷� ����\n\n����: ";
		cin >> input;

		switch (input) {
		case 1:
			accountManager.CreateAccount();

			break;

		case 2:
			accountManager.Deposit();
			
			break;

		case 3:
			accountManager.Withdraw();
			
			break;

		case 4:
			accountManager.Printaccount();
			
			break;

		case 5:
			cout << "���α׷� ����" << endl;
			for (int i = 0; i < accountManager.Member_Number; i++) {
				delete accountManager.account[i];
			}
			return 0;
		default:
			printf("6���ʹ� ������ �ȵ�! �ٷ� ����!!");
			exit(1);
		}
	}
}