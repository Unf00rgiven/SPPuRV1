#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;

// помоћне функције
static bool loadStudents(string fileName);
static void printStudentNames();
static void printStudentIndexNums();
static void printStudentNamesAndIndexNums();
static void addStudent();
static void makeIndexToNameMap();
static void printIndexToNameMap();
static void printDesiredIndex(int x);
static void makeNameToIndexMap();
static void printDesiredName(string name);
static void printSpecial();
static void replace();

// глобалне променљиве
static list<string> studentNames;
static vector<int> studentIndexNums;
static map<int, string> studentIndexToNameMap;
static map<string, int> studentNameToIndexMap;


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Niste uneli potrebne argumente za pokretanje programa!" << endl;
		cout << "Argumenti komandne linije treba da budu:" << endl;
		cout << "1. apsolutna ili relativna putanja do datoteke: \"baza_studenata.txt\"" << endl;
		cout << "2. ime studenta" << endl;
		cout << "3. prezime studenta" << endl;
		exit(-1);
	}

	bool retVal;

	retVal = loadStudents(argv[1]);

	if (retVal == false)
	{
		cout << "Greska prilikom ucitavanja ulazne datoteke!\n" << endl;
		exit(-1);
	}

	printStudentNames();
	printStudentIndexNums();

	printStudentNamesAndIndexNums();

	addStudent();

	printStudentNamesAndIndexNums();

	makeIndexToNameMap();
	printIndexToNameMap();

	int x;
	cout << "Unesite broj indeksa: ";
	cin >> x;

	printDesiredIndex(x);

	makeNameToIndexMap();

	string name;
	string surname;
	// TODO: име и презиме студента преузети из прослеђених аргумената командне линије
	name = argv[2];
	surname = argv[3];

	string fullName;
	// TODO: формирај од имена и презимена један знаковни низ

	fullName = name + " " + surname;

	printDesiredName(fullName);

	// Додатни
	printSpecial();

	replace();

	cout << endl << endl;

	return 0;
}


bool loadStudents(string fileName)
{
	// учитава датотеку "baza_studenata.txt"

	ifstream inputFile(fileName);

	if (inputFile.is_open() == false)
	{
		cout << endl << "GRESKA! Pogresno ime datoteke" << endl << endl;
		return false;
	}

	string ime;
	string prezime;
	int brojIndeksa;
	string punoIme;

	do
	{
		inputFile >> ime;
		inputFile >> prezime;
		inputFile >> brojIndeksa;

		// место за код
		// TODO: направите од имена и презимена један знаковни низ: надаље "име" се односи на име и презиме
		punoIme = ime + " " + prezime;
		// TODO: попуните studentNames са именима, а studentIndexNums са бројевима индекса
		studentNames.push_back(punoIme);
		studentIndexNums.push_back(brojIndeksa);

	} while (inputFile.eof() == false);

	inputFile.close();

	return true;
}


void printStudentNames()
{
	// TODO: имплементирати
	list<string>::iterator studentNamesIt;
	cout << "-------------------- printStudentNames ---------------------------" << endl;
	for (studentNamesIt = studentNames.begin(); studentNamesIt != (--studentNames.end()) ; studentNamesIt++)
	{
		cout << *studentNamesIt << endl;
	}
	cout <<  endl << endl << endl;
}


void printStudentIndexNums()
{
	// штампа на екран студентске индексе али у обрнутом редоследу
	// TODO: имплементирати
	vector<int>::reverse_iterator studentIndexIt;
	cout << "-------------------- printStudentIndexNums ---------------------------" << endl;
	for (studentIndexIt = (++studentIndexNums.rbegin()); studentIndexIt != studentIndexNums.rend(); studentIndexIt++)
	{
		cout << *studentIndexIt << endl;
	}
	cout << endl << endl << endl;

}


void printStudentNamesAndIndexNums()
{
	// штампа на екран име студента праћено бројем индекса
	// користити информације у studentNames и studentIndexNums
	// TODO: имплементирати
	list<string>::iterator studentNamesIt;
	vector<int>::iterator studentIndexIt=studentIndexNums.begin();
	cout << "-------------------- printStudentNamesAndIndexNums ---------------------------"<<endl;
	for (studentNamesIt = studentNames.begin(); studentNamesIt != (--studentNames.end()); studentNamesIt++)
	{
		cout << *studentNamesIt << " " << *studentIndexIt << endl;
		studentIndexIt++;
	}
	cout << endl << endl << endl;

}


void addStudent()
{
	string studentsName = "Marko Kraljevic";
	int studentsIndexNum = 54321;

	// TODO: додати студента Краљевића Марка тачно иза Малог Радојице (12345)

	list<string>::iterator studentNamesIt = studentNames.begin();
	vector<int>::iterator studentIndexIt = studentIndexNums.begin();
	
	for (; studentIndexIt != studentIndexNums.end(); studentIndexIt++) 
	{
		if ((*studentIndexIt) == 12345) 
		{
			break;
		}
		studentNamesIt++;
	}

	studentNames.insert(++studentNamesIt, studentsName);
	studentIndexNums.insert(++studentIndexIt, studentsIndexNum);

}


void makeIndexToNameMap()
{
	// TODO: направити мапу пресликавања бројева индекса на имена
	list<string>::iterator studentNamesIt = studentNames.begin();
	vector<int>::iterator studentIndexIt;

	for (studentIndexIt = studentIndexNums.begin(); studentIndexIt != studentIndexNums.end(); studentIndexIt++) 
	{
		studentIndexToNameMap[*studentIndexIt] = *studentNamesIt;
		studentNamesIt++;
	}
}


void printIndexToNameMap()
{
	// TODO: одшампати на екран садржај IndexToName мапе
	cout << "------------------printIndexToNameMap--------------------" << endl;
	map<int, string>::iterator studentIndexToNameMapIt;

	for (studentIndexToNameMapIt = studentIndexToNameMap.begin(); studentIndexToNameMapIt != studentIndexToNameMap.end(); studentIndexToNameMapIt++)
	{
		cout << studentIndexToNameMapIt->first << " " << studentIndexToNameMapIt->second << endl;
	}
	cout << endl << endl << endl;
}


void printDesiredIndex(int x)
{
	// TODO: наћи име студента у мапи на основу броја индекса, и одшампати име на екран
	// претпоставити да је број индекса увек валидан
	map<int, string>::iterator studentIndexToNameMapIt;
	studentIndexToNameMapIt=studentIndexToNameMap.find(x);

	if (studentIndexToNameMapIt == studentIndexToNameMap.end()) 
	{
		cout << "Ne postoji takav student" << endl;
	}
	else cout << "Student sa ovim brojem indexa je:" << studentIndexToNameMapIt->second << endl;
	cout << endl << endl << endl;
}


void makeNameToIndexMap()
{
	// TODO: направити мапу пресликавања имена на бројеве индекса
	list<string>::iterator studentNamesIt = studentNames.begin();
	vector<int>::iterator studentIndexIt;

	for (studentIndexIt = studentIndexNums.begin(); studentIndexIt != studentIndexNums.end(); studentIndexIt++) 
	{
		studentNameToIndexMap[*studentNamesIt] = *studentIndexIt;
		studentNamesIt++;
	}
}


void printDesiredName(string name)
{
	// TODO: наћи индекс студента на основу имена, и одшампати индекс на екран
	// претпоставити да је могућ унос невалидног имена
	map<string, int>::iterator studentNameToIndexMapIt;
	studentNameToIndexMapIt = studentNameToIndexMap.find(name);

		if (studentNameToIndexMapIt == studentNameToIndexMap.end()) 
		{
			cout << "Ne postoji takav student" << endl;
		}
		else cout << "Broj indexa studenta " << name << " je:" << studentNameToIndexMapIt->second << endl;
		cout << endl << endl << endl;
}


void printSpecial()
{
	// TODO: коришћењем итератора проћи кроз целу мапу studentIndexToNameMap
	// и исписати на екран парове индекс и име_презиме студената, за све студенте
	// осим последњег. За последњег студента исписати само име и презиме.
	cout << "--------------------------printSpecial---------------------------" << endl;

	map<int, string>::iterator studentIndexToNameMapIt;

	for (studentIndexToNameMapIt = studentIndexToNameMap.begin(); studentIndexToNameMapIt != studentIndexToNameMap.end(); studentIndexToNameMapIt++) 
	{
		if (studentIndexToNameMapIt == (--studentIndexToNameMap.end())) {
			cout << studentIndexToNameMapIt->second << endl;
		}
		else
			cout << studentIndexToNameMapIt->first << " " << studentIndexToNameMapIt->second << endl;
	}

	cout << endl << endl << endl;
	
}


void replace()
{
	// TODO: коришћењем метода знаковног низа у задатој реченици заменити зарезе размацима
	string str = "Sve,zareze,izmedju,reci,zameniti,razmacima";

	cout << endl << "Recenica koju treba prepraviti je:";
	cout << endl << str << endl;

	// TODO: имплементирати замену
	string::iterator stringIt;

	for (stringIt = str.begin(); stringIt != str.end(); stringIt++)
	{
		if (*stringIt == ',')
		{
			*stringIt = ' ';
		}
	}

	cout << endl << "Ispravljena recenica:";
	cout << endl << str << endl;
}
