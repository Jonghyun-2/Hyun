/*
#include <iostream>
#include <filesystem>
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	vector<cv::String> medical_img_files;  // 파일명
	cv::String medical_img_file;		//파일 하나하나 
	cv::String ex_extension;			//확장자만 제외
	cv::String extension;				//확장자
	cv::String fileName;				//확장자, 경로 제외 순수 '파일이름'
	cv::String newfileName;				//변경후 파일 이름
	cv::String pathName;				//파일이름 제외한 직전 경로
	int fileLen;						//파일경로 총길이
	int extensionPos;					//확장자명제외 길이
	int filenamePosEnd;					
	int filenamePos;					//처음으로 \\이 나오는 곳의 길이(파일명 전 길이)
	cv::glob("D:\\Dental_Screening_dataset\\labeling_data\\unlabeled_data\\*.tif",medical_img_files);
	
	for (int i = 0; i < medical_img_files.size(); i++) {
		medical_img_file = medical_img_files[i];
		extensionPos = medical_img_file.find_last_of(".");
		filenamePos = medical_img_file.find_last_of("\\");
		fileLen = medical_img_file.length();
		filenamePosEnd = extensionPos - filenamePos-1;
		
		ex_extension = medical_img_file.substr(0,extensionPos);
		extension = medical_img_file.substr(extensionPos, fileLen);
		pathName = medical_img_file.substr(0, filenamePos+1);
		fileName = medical_img_file.substr(filenamePos+1, filenamePosEnd);
		cout << pathName << endl;

		if (filenamePosEnd == 12) {
			newfileName = medical_img_file;
		}
		else if (filenamePosEnd == 11) {
			newfileName = pathName + "\\0" + fileName +extension;
		}
		else if (filenamePosEnd == 10) {
			newfileName = pathName + "\\00" + fileName + extension;
		}
		else if (filenamePosEnd == 9) {
			newfileName = pathName + "\\000" + fileName + extension;
		}
		else if (filenamePosEnd == 8) {
			newfileName = pathName + "\\0000" + fileName + extension;
		}
		else if (filenamePosEnd == 7) {
			newfileName = pathName + "\\00000" + fileName + extension;
		}
		else if (filenamePosEnd == 6) {
			newfileName = pathName + "\\000000" + fileName + extension;
		}
		else if (filenamePosEnd == 5) {
			newfileName = pathName + "\\0000000" + fileName + extension;
		}
		//cout << medical_img_file << endl;
		//cout << newfileName << endl;
		rename(medical_img_file.c_str(), newfileName.c_str());
		medical_img_files[i] = newfileName;
	}
	for (int i = 0; i < medical_img_files.size(); i++) {
		cout << medical_img_files[i] << endl;
	}
	return 0;
}
*/