#include <iostream>
#include <iomanip>	// cout.width(), cout << fixed, cout.precision()�� ���� ���� �߰�.
#include <cstring>	//calgap �Լ����� strcmp ����� �����Ƿ� �߰�.
using namespace std;

struct Subject {
	char subname[30];
	int hakjum;
	char grade[10];  // ���� ���.. ex) a+, a0..
	float gpa; // ���� ���� -> ���� ��� X ���� ����
};

struct Student {
	char stdname[30];
	int hakbun;
	Subject sub[3]; // �� �л��� ��� ���� 3��
	float avegpa;	// ������ ��� ���� -> ������ ���� ���� �� �� �ѵ� 3���� ������
};

void PrintMenu();		//�޴� ����
void inputstdinf();		// �л��� ���� ����
void PrintAllData(const Student* pSt); // �Է¹��� ��ü �л��� ���� ������ �� �л��� ��� ���� ���� ������ ���
void CalcGPA(Subject& Sub); //�л��� ���� ���� ��޿� ���� ������ ����ϴ� �Լ�
float CalcAveGPA(Subject* Sub);	//�л��� ������ ��������� ����ϴ� �Լ�
void PrintOneData(const Student& rSt);	//����ϰ��� �ϴ� ���� �л� 1���� ������ ����ϴ� �Լ�
Student* StdSearch(Student* pSt, int StudentNum);	//ã���� �ϴ� �л��� �ִ��� Ȯ���� �ִ� �Լ�, ã���� �ϴ� �л��� ���� �ÿ� �� ��ġ�� �ּ� ���� ����


struct Student Person[2];


int main()
{
	int choice;
	Student* SearchStd;
	while (1)
	{
		PrintMenu();
		cout << "���ϴ� ����� �Է��Ͻÿ� : ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			inputstdinf();
			break;
		case 2:
			PrintAllData(Person);	//const Student* pSt�� ���·�, �̴� 
			break;
		case 3:
			SearchStd = StdSearch(Person, 2);
			PrintOneData(*SearchStd);
			break;
		case 4:
			cout << "���α׷��� �����մϴ�." << endl;
			return 0;
		}
	}

	return 0;
}

void PrintMenu()
{
	cout << "====== �޴� ======" << endl;
	cout << "1. �л� ���� �Է�" << endl;
	cout << "2. ��ü �л� ���� ����" << endl;
	cout << "3. �л� �̸� �˻�" << endl;
	cout << "4. ���α׷� ����\n" << endl;
}

void inputstdinf()
{
	for (int a = 0; a < 2; a++)
	{
		cout << a + 1 << "��° �л� �̸��� �й��� �Է��Ͻÿ�." << endl;
		cout << "�̸� : "; cin >> Person[a].stdname;
		cout << "�й� : "; cin >> Person[a].hakbun;
		cout << endl;
		cout << "\n";
		cout << "������ ���� 3���� �� �������, ��������, �������� �Է��Ͻÿ�. " << endl;
		for (int b = 0; b < 3; b++)
		{
			cout << "������� : "; cin >> Person[a].sub[b].subname;
			cout << "���������� : "; cin >> Person[a].sub[b].hakjum;
			cout << "������(A+ ~ F) : "; cin >> Person[a].sub[b].grade;
			cout << endl;
			CalcGPA(Person[a].sub[b]);	//a��° �л��� b��° ������ ������ �ԷµǸ�, �� ���� �ش��ϴ� GPA�� ���.
		}
		Person[a].avegpa = CalcAveGPA(Person[a].sub);	//������ for���� ������ a��° �л��� ������ ������ �� �Է��� �Ǿ��� ������, �� �Է��� ���� ��������� ����� ������ ��������� ����.
	}
}


void PrintAllData(const Student* pSt)	//const�� �پ��� ������, ���� ������ �̷�� �� �� ����.
{

	cout.width(10);
	cout << "��ü �л� ���� ����" << endl;
	cout << "============================================================" << endl;
	for (int c = 0; c < 2; c++)
	{
		cout << "�̸� : " << Person[c].stdname << "  " << "�й� : " << Person[c].hakbun << endl;
		cout << "============================================================" << endl;
		cout.width(55);
		cout << "�����  ��������  ������  ��������" << endl;
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
		cout << "������� : ";
		cout << fixed;
		cout.precision(2);		//�Ҽ��� 2�ڸ��� ���
		cout << Person[c].avegpa << endl;	//�������� / �����(3��)
		cout << "============================================================" << endl;
	}
}

void CalcGPA(Subject& Sub)	//���޵� ����ü�� Sub�� ������ �ο���
{

	for (int d = 0; d < 2; d++)
	{
		for (int e = 0; e < 3; e++)
		{

			if (!strcmp(Sub.grade, "A+"))	//�� �Լ� ������ ����ü�� �����ϱ� ���ؼ��� Sub. �Ͱ��� �������� ����
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
				cout << "������ �߸� �Է��Ͽ����ϴ�. " << endl;
		}
	}
}

float CalcAveGPA(Subject* Sub)	//�Ű������� Subject�� �ּҸ� �ް� �ִ�.
{
	float sum = 0.0;
	for (int i = 0; i < 3; i++)
		sum += Sub[i].gpa;
	return sum / 3.0;	//��ȯ���� float�̹Ƿ�, sum/3.0�� ���� �����Ѵ�.
}

void PrintOneData(const Student& rSt)	//const�� ����Ǿ��� ������ �� �Լ������� �� ���� �Ұ�
{
	cout << "�̸� : " << rSt.stdname << " �й� : " << rSt.hakbun << endl;
	cout << "============================================================" << endl;
	cout.width(55);
	cout << "�����  ��������  ������  ��������" << endl;
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
	cout << "������� : ";
	cout << fixed;
	cout.precision(2);		//�Ҽ��� 2�ڸ��� ���
	cout << rSt.avegpa << endl;

}

Student* StdSearch(Student* pSt, int StudentNum)	//�л��� �̸��� ���ϱ� ���ؼ�, ����ü Person�� �ּҸ� �޾Ұ�, �л����� 2���̹Ƿ� 2�� ���� ����
{
	char hakname[30];	//�˻��ϰ��� �� �̸��� ������ char�� �迭
	cout << "�˻� �� �л��� �̸��� �Է��Ͻÿ� : "; cin >> hakname;
	for (int a = 0; a < StudentNum; a++)	//�л� ���� �θ��̹Ƿ�, Student ����ü �迭�� ���̰� 2�̴�. �׷��� ���̸� 2�� �����ؼ� 2�� �ݺ�.
	{
		if (!strcmp((pSt + a)->stdname, hakname))	//���� pSt�迭�� [a]��°(�̴� Person[a]�� ���� ��)�� �л��̸��� hakname�� ���ٸ�
			return (pSt + a);	//pst+a�� ��ȯ�ض� ->�̴� Student ����ü�� �ּ��̴�. �� �Լ��� ��ȯ���� Student* �̱� ������ �ּҸ� ��ȯ�ؾ��Ѵ�.
	}
}