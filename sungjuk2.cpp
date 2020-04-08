#include <iostream>
#include <iomanip>	// cout.width(), cout << fixed, cout.precision()를 쓰기 위해 추가.
#include <cstring>	//calgap 함수에서 strcmp 사용이 있으므로 추가.
using namespace std;

struct Subject {
	char subname[30];
	int hakjum;
	char grade[10];  // 과목 등급.. ex) a+, a0..
	float gpa; // 과목 평점 -> 과목 등급 X 과목 학점
};

struct Student {
	char stdname[30];
	int hakbun;
	Subject sub[3]; // 이 학생이 듣는 과목 3개
	float avegpa;	// 교과목 평균 평점 -> 각각의 과목 평점 다 더 한뒤 3으로 나누기
};

void PrintMenu();		//메뉴 선택
void inputstdinf();		// 학생에 대한 정보
void PrintAllData(const Student* pSt); // 입력받은 전체 학생에 대한 정보와 그 학생이 듣는 과목에 대한 정보를 출력
void CalcGPA(Subject& Sub); //학생이 받은 과목 등급에 따라서 평점을 계산하는 함수
float CalcAveGPA(Subject* Sub);	//학생의 교과목 평균평점을 계산하는 함수
void PrintOneData(const Student& rSt);	//출력하고자 하는 개인 학생 1명의 정보를 출력하는 함수
Student* StdSearch(Student* pSt, int StudentNum);	//찾고자 하는 학생이 있는지 확인해 주는 함수, 찾고자 하는 학생이 있을 시에 그 위치의 주소 값을 리턴


struct Student Person[2];


int main()
{
	int choice;
	Student* SearchStd;
	while (1)
	{
		PrintMenu();
		cout << "원하는 기능을 입력하시오 : ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			inputstdinf();
			break;
		case 2:
			PrintAllData(Person);	//const Student* pSt의 형태로, 이는 
			break;
		case 3:
			SearchStd = StdSearch(Person, 2);
			PrintOneData(*SearchStd);
			break;
		case 4:
			cout << "프로그램을 종료합니다." << endl;
			return 0;
		}
	}

	return 0;
}

void PrintMenu()
{
	cout << "====== 메뉴 ======" << endl;
	cout << "1. 학생 성적 입력" << endl;
	cout << "2. 전체 학생 성적 보기" << endl;
	cout << "3. 학생 이름 검색" << endl;
	cout << "4. 프로그램 종료\n" << endl;
}

void inputstdinf()
{
	for (int a = 0; a < 2; a++)
	{
		cout << a + 1 << "번째 학생 이름과 학번을 입력하시오." << endl;
		cout << "이름 : "; cin >> Person[a].stdname;
		cout << "학번 : "; cin >> Person[a].hakbun;
		cout << endl;
		cout << "\n";
		cout << "수강한 과목 3개와 각 교과목명, 과목학점, 과목등급을 입력하시오. " << endl;
		for (int b = 0; b < 3; b++)
		{
			cout << "교과목명 : "; cin >> Person[a].sub[b].subname;
			cout << "과목학점수 : "; cin >> Person[a].sub[b].hakjum;
			cout << "과목등급(A+ ~ F) : "; cin >> Person[a].sub[b].grade;
			cout << endl;
			CalcGPA(Person[a].sub[b]);	//a번째 학생의 b번째 과목의 정보가 입력되면, 그 과목에 해당하는 GPA를 계산.
		}
		Person[a].avegpa = CalcAveGPA(Person[a].sub);	//안쪽의 for문이 끝나면 a번째 학생의 과목의 정보는 다 입력이 되었기 때문에, 그 입력을 토대로 평균평점을 계산해 교과목 평균평점에 저장.
	}
}


void PrintAllData(const Student* pSt)	//const가 붙었기 때문에, 값의 수정은 이루어 질 수 없다.
{

	cout.width(10);
	cout << "전체 학생 성적 보기" << endl;
	cout << "============================================================" << endl;
	for (int c = 0; c < 2; c++)
	{
		cout << "이름 : " << Person[c].stdname << "  " << "학번 : " << Person[c].hakbun << endl;
		cout << "============================================================" << endl;
		cout.width(55);
		cout << "과목명  과목학점  과목등급  과목평점" << endl;
		cout << "============================================================" << endl;
		for (int e = 0; e < 3; e++)
		{
			cout.width(25);
			cout << Person[c].sub[e].subname << "\t" << Person[c].sub[e].hakjum << "\t" << Person[c].sub[e].grade << "\t";
			cout << fixed;
			cout.precision(2);
			cout << Person[c].sub[e].gpa << endl;
		}
		cout << "============================================================" << endl;
		cout.width(50);
		cout << "평균평점 : ";
		cout << fixed;
		cout.precision(2);		//소숫점 2자리수 출력
		cout << Person[c].avegpa << endl;	//과목평점 / 과목수(3개)
		cout << "============================================================" << endl;
	}
}

void CalcGPA(Subject& Sub)	//전달된 구조체에 Sub란 별명을 부여함
{

	for (int d = 0; d < 2; d++)
	{
		for (int e = 0; e < 3; e++)
		{

			if (!strcmp(Sub.grade, "A+"))	//이 함수 내에서 구조체에 접근하기 위해서는 Sub. 와같은 형식으로 접근
				Sub.gpa = 4.5 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "A0"))
				Sub.gpa = 4.0 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "B+"))
				Sub.gpa = 3.5 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "B0"))
				Sub.gpa = 3.0 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "C+"))
				Sub.gpa = 2.5 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "C0"))
				Sub.gpa = 2.0 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "D+"))
				Sub.gpa = 1.5 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "D0"))
				Sub.gpa = 1.0 * (float)(Sub.hakjum);
			else if (!strcmp(Sub.grade, "F"))
				Sub.gpa = 0.0;
			else
				cout << "성적을 잘못 입력하였습니다. " << endl;
		}
	}
}

float CalcAveGPA(Subject* Sub)	//매개변수로 Subject의 주소를 받고 있다.
{
	float sum = 0.0;
	for (int i = 0; i < 3; i++)
		sum += Sub[i].gpa;
	return sum / 3.0;	//반환형이 float이므로, sum/3.0의 값을 리턴한다.
}

void PrintOneData(const Student& rSt)	//const가 선언되었기 때문에 이 함수내에서 값 수정 불가
{
	cout << "이름 : " << rSt.stdname << " 학번 : " << rSt.hakbun << endl;
	cout << "============================================================" << endl;
	cout.width(55);
	cout << "과목명  과목학점  과목등급  과목평점" << endl;
	cout << "============================================================" << endl;
	for (int e = 0; e < 3; e++)
	{
		cout.width(25);
		cout << rSt.sub[e].subname << "\t" << rSt.sub[e].hakjum << "\t" << rSt.sub[e].grade << "\t";
		cout << fixed;
		cout.precision(2);
		cout << rSt.sub[e].gpa << endl;
	};
	cout << "============================================================" << endl;
	cout.width(50);
	cout << "평균평점 : ";
	cout << fixed;
	cout.precision(2);		//소숫점 2자리수 출력
	cout << rSt.avegpa << endl;

}

Student* StdSearch(Student* pSt, int StudentNum)	//학생의 이름을 비교하기 위해서, 구조체 Person의 주소를 받았고, 학생수가 2명이므로 2를 전달 받음
{
	char hakname[30];	//검색하고자 할 이름을 저장할 char형 배열
	cout << "검색 할 학생의 이름을 입력하시오 : "; cin >> hakname;
	for (int a = 0; a < StudentNum; a++)	//학생 수가 두명이므로, Student 구조체 배열은 길이가 2이다. 그래서 길이를 2로 설정해서 2번 반복.
	{
		if (!strcmp((pSt + a)->stdname, hakname))	//만약 pSt배열의 [a]번째(이는 Person[a]와 같은 뜻)의 학생이름이 hakname과 같다면
			return (pSt + a);	//pst+a를 반환해라 ->이는 Student 구조체의 주소이다. 이 함수의 반환형이 Student* 이기 때문에 주소를 반환해야한다.
	}
}