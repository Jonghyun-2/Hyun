#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	string fileNameCsv;
	string csv_path = "test.csv";
	string test = "123456";
	size_t firstParsingPos;
	size_t secondParsingPos;
	string ex_first_element;
	string first_element;
	string second_element;
	//파일 전체 삭제

	string in_line;
	fstream in(csv_path,ios::in | ios::out);
	while (in) {
		getline(in, fileNameCsv);
		firstParsingPos = fileNameCsv.find_first_of(",");
		first_element =fileNameCsv.substr(0, firstParsingPos);
		ex_first_element = fileNameCsv.substr(firstParsingPos+1);
		//cout << fileNameCsv << endl;
		//cout << first_element << endl;
		//cout << ex_first_element << endl;
		secondParsingPos = ex_first_element.find_first_of(",");
		second_element = fileNameCsv.substr(firstParsingPos+1, secondParsingPos);
		
		if (second_element == "2") {
			cout << fileNameCsv;
			in << endl;
		}
		
	}

	in.close();

	return 0;
}