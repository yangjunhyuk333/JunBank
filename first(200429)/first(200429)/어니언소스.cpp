#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_LEN 20
#define MAX_MEMBER 100

//과거의 나의 행적
//typedef struct {
//	int accId;
//	int balance;
//	char cusName[20];
//}Account;

//계좌 클래스(보통 계좌)
class Account {

protected:
	int accID; //계좌 번호
	int balance; //계좌 잔액
	int Resident_registration_number; //주민등록번호
	char* cusName; //이름

public:

	//생성자 아이디, 금액, 주민등록번호, 이름
	Account(int inputAccID, int balance, int Resident_registration_number, char* cusName)
	{
		this->accID = inputAccID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	//예금 계좌 생성(오버로딩)
	Account(int inputAccID, int Resident_registration_number, char* cusName) : accID(inputAccID){
		this->balance = 0;
		this->accID = inputAccID;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	//소멸자
	~Account() {
		cout << "객체가 삭제됩니다." << endl; //소멸자가 호출이 되면 해당 내용을 출력

		delete[] cusName;
	}

	//복사 생성자
	Account(const Account& copy_user)
		: accID(copy_user.accID), Resident_registration_number(copy_user.Resident_registration_number)
	{
		cout << "복사 생성자 호출" << endl;
		this->balance = copy_user.balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, copy_user.cusName);
	}

	//멤버 목록을 얻기 위한 메소드
	char *getAccountMember(){
		return cusName;
	}

	//멤버 ID 목록을 얻기 위한 메소드
	int getAccountId() const {
		return accID;
	}

	//멤버 주민등록번호를 얻기 위한 메소드
	int getResident_registration() const {
		return Resident_registration_number;
	}

	//입금
	virtual void Deposit(int balance) {
		int calInterest = interest(this->balance + balance);;
		this->balance += balance + calInterest;
		cout << "이자율: ";
		cout << calInterest << endl;
		cout << endl;
	}

	//이자율 계산해서 반환하는 메소드(이자율: 1%)
	virtual int interest(int balance) {
		return ((int) balance * 0.01);
	}

	//계좌 확인(계좌를 확인해서 boolean 값을 보내주는 메소드),
	bool CheckAccount(int accountId) const {
		return this->accID == accountId; //사용자가 입력한 계좌가 있는지 확인
	} 

	//출금
	bool Withdraw(int balance) {
		if (this->balance < balance) { 
			return false; 
		}

		this->balance -= balance;
		return true;
	}

	//계좌 전체 출력
	virtual void PrintAccount() const {
		cout << endl;
		cout << "계좌 종류: 보통" << endl;
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민등록번호: " << Resident_registration_number << endl;
		cout << endl;
	}

	//주민등록번호 확인
	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}

};

//예금 계좌 클래스 (Account 클래스 상속)
class DepositAccount : public Account {
private:
	int balance;

public:

	//예금계좌 생성
	DepositAccount(Account& copy_member, int inputAccID) 
		: Account(inputAccID, copy_member.getResident_registration(), copy_member.getAccountMember())
	{
		balance = 0;
	}

	~DepositAccount(){

	}

	
	//입금(예금)
	virtual void Deposit(int balance) {
		int calInterest = interest(this->balance + balance);
		this->balance += balance + calInterest;
		cout << "이자율: ";
		cout << calInterest << endl;
		cout << endl;
	}

	//이자율 계산해서 반환하는 메소드(이자율: 2%)
	virtual int interest(int balance) {
		return ((int)balance * 0.02);
	}

	virtual void PrintAccount() const{
		cout << endl;
		cout << "계좌 종류: 예금" << endl;
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민등록번호: " << Resident_registration_number << endl;
		cout << endl;
	}

};

//계좌 관리 클래스
class AccountManager {

public:

	//객체 생성
	Account* account[MAX_MEMBER]; //보통 계좌
	int Member_Number = 0; //멤버 개수 카운트

	//어떤 계좌에서 작업을 할 지 선택하는 함수
	int CheckAccountType() {
		int selectType;

		cout << "어떤 계좌에서 작업하시겠습니까?\n1. 보통 계좌 \n2. 예금 계좌" << endl;
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
			cout << "숫자를 잘못 입력하셨습니다." << endl;
			cout << endl;
			CheckAccountType();
		}
	}

	//계좌 여부를 확인 하는 함수
	bool CheckAccount() {
		if (Member_Number == 0) {
			cout << "현재 등록된 계좌가 없습니다." << endl;
			return false;
		}
		return true;
	}
	
	//ID중복되는 지 확인 하는 함수
	bool CheckAccId(int accID) {
		for (int checkAccId_idx = 0; checkAccId_idx < Member_Number; checkAccId_idx++) {
			if (account[checkAccId_idx]->CheckAccount(accID)) {
				return true;
			}
		}
		return false;	
	}

	//중복되는 Id 인덱스를 리턴하는 함수
	int CheckAccId_idx(int accID) {
		for (int checkAccId_idx = 0; checkAccId_idx <= Member_Number; checkAccId_idx++) {
			if (accID == account[checkAccId_idx]->getAccountId()) {
				return checkAccId_idx;
			}
		}
		return 0;
	}
	
	//주민등록번호 중복 확인
	bool CheckResidentNumber(int residentNumber) {
		for (int checkAccResident_idx = 0; checkAccResident_idx < Member_Number; checkAccResident_idx++) {
			if (residentNumber == account[checkAccResident_idx]->getResident_registration()) {
				return true;
			}
			return false;
		}
	}

	//계좌 생성
	void CreateAccount() {
		cout << endl;
		cout << "[계좌개설]" << endl;

		int checkType = CheckAccountType();

		if (checkType == 1) {
			CreateOrdinaryAccount();
		}
		else if (checkType == 2){
			CreateDepositAccount();
		}
		else {
			cout << endl;
			cout << "잘못 선택하셨습니다." << endl;
			cout << endl;
			CreateAccount();
			cout << endl;
		}
	}

	//보통계좌 생성
	void CreateOrdinaryAccount() {
		//변수 선언
		int inputId; //ID 입력
		int inputResidentNumber; //주민등록번호 입력
		int amountBalance; //입금액 입력
		char* inputCusName = new char[MAX_LEN]; //이름 입력
		
		//시작
		cout << endl;
		cout << "계좌 ID: ";
		cin >> inputId;

		//중복 검사(ID)
		while (1) {
			if (Member_Number > 0 && CheckAccId(inputId) == true) {
				cout << endl;
				cout << "계좌가 중복 됩니다. 다시 입력해주세요." << endl;
				cout << "계좌 ID: ";
				cin >> inputId;
				cout << endl;
				continue;
			}
			else {
				break;
			}
		}

		//이름 입력
		cout << "이름: ";
		cin >> inputCusName;

		//입금액 입력
		cout << "입금액: ";
		cin >> amountBalance;
		
		//최소 입금액
		while (1) {
			if (amountBalance < 10) {
				cout << "계좌개설 시 최소 입금액은 10원 이상입니다." << endl;
				cout << "입금액: ";
				cin >> amountBalance;
				continue;
			}
			else { 
				break; 
			}
		}

		//주민등록번호 입력
		cout << "주민등록번호: ";
		cin >> inputResidentNumber;
		cout << endl;

		//중복 검사(주민등록번호)
		while (1) {
			if (CheckResidentNumber(inputResidentNumber) == true) {
				cout << "주민등록번호가 중복 됩니다. 다시 입력해주세요." << endl;
				cout << "주민등록번호: ";
				cin >> inputResidentNumber;
				continue;
			}
			else {
				break;
			}
		}
		

		//생성자 호출(보통 계좌)
		account[Member_Number] = new Account(inputId, amountBalance, inputResidentNumber, inputCusName);
		Member_Number++;

	}

	//예금계좌 생성
	void CreateDepositAccount() {
		//변수 선언
		int inputOrdinaryId = 0; //원본 ID 입력
		int ordinaryId_idx = 0; //원본 ID 인덱스 받아오기
		int inputId = 0; //ID 입력
		int amountBalance = 0; //입금액 입력
		bool checkParam;

		//원본 계좌 입력
		cout << endl;
		cout << "원본 계좌: ";
		cin >> inputOrdinaryId;

		while (1) {
			//ID검사
			checkParam = CheckAccId(inputOrdinaryId);

			//원본 계좌 검색(검사)
			if (checkParam != true) { //존재하지 않으면 다시 입력
				cout << endl;
				cout << "원본 계좌가 존재하지 않습니다." << endl;
				cout << "원본 계좌: ";
				cin >> inputOrdinaryId;
				cout << endl;
				continue;
			}
			else {
				//원본 계좌 인덱스 저장
				ordinaryId_idx = CheckAccId_idx(inputOrdinaryId);
				break;
			}
		}

		//계좌ID 입력
		cout << "계좌ID: ";
		cin >> inputId;

		//계좌 번호 중복 검사
		while (1) {
			if (CheckAccId(inputId) == true) { //중복 되면 다시 입력
				cout << endl;
				cout << "계좌번호가 중복됩니다." << endl;
				cout << "계좌ID: ";
				cin >> inputId;
				cout << endl;
				continue;
			}
			else {
				break;
			}
		}
		
		//예금 계좌 생성
		account[Member_Number] = new DepositAccount(*account[ordinaryId_idx], inputId);

		//멤버 개수 증가
		Member_Number++;

	}

	//계좌 입금
	void Deposit() {
		int inputId; //ID입력
		int amountBalance; //입금할 금액
		int selectId_idx; //ID 인덱스
		bool checkParam; //check를 위한 변수

		//멤버가 없을때 메인 메뉴로 돌아감
		if (Member_Number < 1) {
			cout << endl;
			cout << "멤버가 없으므로 실행할 수 없습니다." << endl;
			cout << endl;
			return;
		}

		//입금 할 계정 ID(계좌 번호) 입력
		cout << endl;
		cout << "[입금]" << endl;
		cout << "ID: ";
		cin >> inputId;

		//입력한 ID가 있는지 여부 검사
		while (1) {
			
			selectId_idx = CheckAccId_idx(inputId);

			checkParam = CheckAccId(inputId);

			if (checkParam != true) { //없다면 다시 입력
				cout << "해당하는 ID가 없습니다." << endl;
				cout << "ID: ";
				cin >> inputId;
				cout << endl;
				continue;
			}
			else {
				break;
			}
		}

		//입금액 입력
		cout << "입금액: ";
		cin >> amountBalance;

		//입금
		account[selectId_idx]->Deposit(amountBalance);

	}

	//계좌 출금
	void Withdraw() {
		int inputId; //ID입력
		int amountBalance; //입금할 금액
		int selectId_idx; //ID 인덱스
		bool checkParam; //check를 위한 변수

		//멤버가 없을때 메인 메뉴로 돌아감
		if (Member_Number < 1) {
			cout << endl;
			cout << "멤버가 없으므로 실행할 수 없습니다." << endl;
			cout << endl;
			return;
		}

		//출금을 할 ID 입력
		cout << endl;
		cout << "[출금]" << endl;
		cout << "ID: ";
		cin >> inputId;

		//해당되는 ID가 있는지 여부 검사
		while (1) {
			selectId_idx = CheckAccId_idx(inputId);
			checkParam = CheckAccId(inputId);

			if (checkParam != true) { //없다면 다시 입력
				cout << endl;
				cout << "해당하는 ID가 없습니다.";
				cout << "ID: ";
				cin >> inputId;
				continue;
			}
			else {
				break;
			}
		}

		//출금액 입력
		cout << "출금액: ";
		cin >> amountBalance;
		cout << endl;

		//출금
		account[selectId_idx]->Withdraw(amountBalance);
	}

	//계좌 출력
	void Printaccount() const{
		for (int printIdx = 0; printIdx < Member_Number; printIdx++) {
			cout << endl;
			account[printIdx]->PrintAccount();
		}

		//멤버가 있는지 여부 검사
		if (Member_Number < 1) {
			cout << endl;
			cout << "멤버가 없으므로 실행할 수 없습니다." << endl;
			cout << endl;
			return;
		}
	}
};

//AccountManager 객체 생성
AccountManager accountManager;

//메인 함수
int main() {
	while (1) {
		int input = 0;

		cout << "-----Menu-----\n1. 계좌개설\n2. 입금\n3. 출금\n4. 계좌정보 전체 출력\n5. 프로그램 종료\n\n선택: ";
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
			cout << "프로그램 종료" << endl;
			for (int i = 0; i < accountManager.Member_Number; i++) {
				delete accountManager.account[i];
			}
			return 0;
		default:
			printf("6부터는 적으면 안돼! 바로 종료!!");
			exit(1);
		}
	}
}