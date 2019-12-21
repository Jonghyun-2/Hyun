#include "mainHeader.h"
#include <string>

int main() {
	
	string path_str = "./imgs";
	string astric = "\\*";
	string folpath;
	//string smile = "P";
	folpath = path_str + astric;
	vector<cv::String>folders; 
	vector<cv::String> smile_path;
	glob(folpath,folders,true);
	
	for (int i = 0; i < folders.size(); i++) {
		cout << folders[i] << endl ;// folders[i].length() << endl;
		cv::String except_expand = folders[i].substr(0, folders[i].length()-4 ) ;
		cout << except_expand.find_last_of("P") << endl;
		cout << "except_expand.length() : "<< except_expand.length() << endl;   //24
		if (except_expand[except_expand.length() - 1] == 'P') {
			smile_path.push_back(folders[i]);
		}
		cout << folders[i].substr(folders[i].length() - 4, folders[i].length()) << endl;   //.JPG

	}
	for (int i = 0; i < smile_path.size(); i++) {
		cout << "path" << smile_path[i] << endl;
	}
	
	

}

//#include <iostream>
//
//using namespace std;
//
//int main() {
//	string a = "hi hello";
//
//	if (a.find("sub") == string::npos) {
//		cout << a.find("sub") << endl;
//	}
//	return 0;
//}