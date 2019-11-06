// ������ ��ġ �ſ￡ ��ģ �� ó�� �¿츦 �ٲٴ� ��ȯ : �¿� ��Ī or �¿� �����̶�� ��
// ������ ���ϸ� ������ ��ó�� �ٲٴ� ��ȯ : ���� ��Ī �Ǵ� ���� ���� �̶�� ��
// �̷��� ��Ī��ȭ�� �Է� ����� ���� ũ���� ��� ������ ����
// input_img & output_img�� pixel���� 1:1�� ����

// void flip(InputArray src, OutputArray dst, int flipcode); -ok
// (input_img, output_img, int (pos(�¿�),0(����),neg(����)))


//���� �̹����� �ڸ��Ŀ�  -ok
//�ڸ� ȭ���� �ݹ��� ������ �غ��� -ok
//������ �����̽��� ������ (spacebar == 32 ) ȭ���� �Ѿ�� ���� -ok
//���� ���縦 �ؾ��ұ� ���� ���縦 �ؾ��ұ� -??

/*
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat Original_img = imread("coffee.jpg");
	Mat Left_cut_img = Original_img;
	Mat Right_cut_img = Original_img;
	Rect Left_area(0,0 , Original_img.cols / 2, Original_img.rows); //(x,y,width,height)
	Rect Rigth_area(Original_img.cols / 2, 0, Original_img.cols/2, Original_img.rows);
	Left_cut_img = Original_img(Left_area);
	Right_cut_img = Original_img(Rigth_area);
	Mat Mirror_img;

	cv::namedWindow("���� ������ �̹���", cv::WINDOW_NORMAL);

	flip(Left_cut_img, Mirror_img, 1); // img mirroring
	imshow("���� �̹���", Original_img);
	imshow("���� ������ �̹���", Mirror_img);
	 while(true) { 
		 if (waitKey() == 32) 
			 break;
	 }
	 destroyWindow("���� ������ �̹���");

	 cv::namedWindow("������ �̹���", cv::WINDOW_NORMAL);

	imshow("������ �̹���", Right_cut_img);
	while (true) {
		if (waitKey() == 32)
			break;
	}
	destroyWindow("������ �̹���");

	return 0;
}

//next ���콺�̺�Ʈ ����Ͽ� bounding box area ����, �ش� box�� (x,y,wid,hei) csv ���Ͽ� ����
*/

//glob function test
/*
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/utils/filesystem.hpp"

#define path_str "\Original_picture"
//#define base_str "\Users\Jong_Hyun\Desktop\code\paly_ground\Mirror_image"
using namespace std;

vector<cv::String> medical_img_files;
cv::Mat Showing_img;
int main() {
	//if file exist return 1
	if (cv::utils::fs::exists(path_str) == 1) {			
		//if folder exist return 1
		if (cv::utils::fs::isDirectory(path_str) == 1) {			
			cv::utils::fs::glob(path_str, "\*.jpg", medical_img_files);

			for (int i =0;i<medical_img_files.size();i++)
			{
				cout << medical_img_files[i] << endl;
				Showing_img = cv::imread(medical_img_files[i]);
				cv::imshow("img window", Showing_img);

				if (cv::waitKey() == 32)
					continue;
				cv::destroyWindow("img window");
			}
		}
		else{
		cout << "It's not folder" << endl;
		}
	}

	else {
		cout << "file not exist" << endl;   // if folder is not exist make folder�ƴ��� ������ �ҷ��ͼ� �װ� path�� �����ϸ� ���ݾ�? &  �׷� .csv���ϸ������ �ָ� �ǰٴ�
	}

	return 0;
}
*/

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/utils/filesystem.hpp"
#define path_str "Picture"
#define Save_path_str "Slicing_img\\"
#define Bounding_path_str "Bounding_img\\"
				//#define base_str "\Users\Jong_Hyun\Desktop\code\paly_ground\Mirror_image"

using namespace std;
using namespace cv;

//declear func
void load_image();
string Cutting_func(vector<cv::String> loaded_file_names);
vector<cv::String> Read_image(string file_join_path);
void bounding_box(vector<cv::String> cut_img_files, string file_join_path);
void on_mouse(int event, int x, int y, int flags, void* );

//global variable
vector<cv::String> medical_img_files; 
vector<cv::String> cut_img_files;
cv::Point L_button_down;
cv::Point L_button_up;
cv::Mat img;
cv::String cut_img_file_name;
cv::Mat ori_img;
cv::Mat check_img; //beta

//main func
int main() {
	string file_join_path;

	load_image();
	file_join_path = Cutting_func(medical_img_files);
	Read_image(file_join_path);

	return 0;
}


//Define func

//input : None  , output :None  , 
//Enter Picture folder & read pic as vector
void load_image() {
	//if file exist return 1
	if (cv::utils::fs::exists(path_str) == 1) {
		//if folder exist return 1
		if (cv::utils::fs::isDirectory(path_str) == 1) {
			cv::utils::fs::glob(path_str, "*.jpg", medical_img_files);
		}
		else {
			cout << "It's not folder" << endl;
		}
	}

	else {
		cout << "folder not exist" << endl;   // if folder is not exist make folder�ƴ��� ������ �ҷ��ͼ� �װ� path�� �����ϸ� ���ݾ�? &  �׷� .csv���ϸ������ �ָ� �ǰٴ�
	}
	//������ ������ �ȿ��ٰ� ����� ������ ���������� ����
	return ;
}



//input : vector filename(from load_image())   output : path where cutting image saved(to Read_img()) 
//�����ϳ��� �ҷ��� �ΰ��� ������ ���� �κ��� mirroring �� \\Slicing_img ������ ����
string Cutting_func(vector<cv::String> loaded_file_names) {
	cv::Mat Loaded_img;
	cv::Mat Mirror_img;
	string join_path = cv::utils::fs::join(path_str, Save_path_str);
	//cv::namedWindow("���� ������ �̹���", cv::WINDOW_NORMAL);
	for (int i = 0; i < loaded_file_names.size(); i++)
	{	
		Loaded_img = cv::imread(loaded_file_names[i]);
		cv::Rect Left_area(0, 0, Loaded_img.cols / 2, Loaded_img.rows); //(x,y,width,height)
		cv::Rect Rigth_area(Loaded_img.cols / 2, 0, Loaded_img.cols / 2, Loaded_img.rows);
		cv::Mat Left_cut_img = Loaded_img(Left_area);
		cv::Mat Right_cut_img = Loaded_img(Rigth_area);
		flip(Left_cut_img, Mirror_img, 1); // img mirroring

		int left_save_number = i * 2;
		int right_save_number = i * 2 + 1;
		char left_save_number_str[100];
		char right_save_number_str[100];

		_itoa_s(left_save_number, left_save_number_str,10); //int, str, 10����
		_itoa_s(right_save_number, right_save_number_str, 10);

		
		//Saving Image
		cv::imwrite(join_path + left_save_number_str + ".jpg", Mirror_img);
		cv::imwrite(join_path + right_save_number_str + ".jpg", Right_cut_img);
	}

	return join_path;
}


//Input : path where cutting image saved(from Cutting_func) ,  Output : cut_img_files name as vector
//read cutting img & run bounding box func
vector<cv::String> Read_image(string file_join_path) {
	cv::utils::fs::glob(file_join_path, "*.jpg", cut_img_files);
	
	/*for (int i = 0; i < cut_img_files.size(); i++) {
		cout << cut_img_files[i] << endl;  //check img name
	}*/
	bounding_box(cut_img_files,file_join_path);

	return cut_img_files;
}


//Input : file name list / path ,  Output : X
void bounding_box(vector<cv::String> cut_img_files, string file_join_path) {
	string bounding_join_path = cv::utils::fs::join(file_join_path, Bounding_path_str);
	//cut_img_files = �߸����ϰ���
	for (int i = 0; i < cut_img_files.size(); i++) {
		char save_number[100];
		cut_img_file_name = cut_img_files[i];
		_itoa_s(i, save_number, 10);
		img = cv::imread(cut_img_file_name);
		
		ori_img = img.clone();
		cv::namedWindow("Operating_window");
		cv::imshow("Operating_window", img);
		cv::setMouseCallback("Operating_window", on_mouse);

		while(true){
			if (cv::waitKey() == 32)
			{
				cv::rectangle(img, L_button_down, L_button_up, Scalar(0, 255, 255), 2);
				cv::imshow("Operating_window", ori_img);
				cout << "axis" << L_button_down << L_button_up << endl;
				cv::imwrite(file_join_path + save_number + ".jpg", img);
				break;
			}
			else if (cv::waitKey() == 65)//a , beta
			{
				cv::String check_img_file_name = cut_img_files[i - 1]; //beta
				check_img = cv::imread(check_img_file_name);//beta
				cv::imshow("Operating_window", check_img);
				break;
			}
		}
		
	}

	return;
}

//�̹� �ٿ���ڽ����� �������� �� ������ �Ѿ�� �ұ� - ���ο� ������ ���� �׾ȿ� ��������

//Input : ,  Output : 
void on_mouse(int event, int x, int y, int flags, void*) {

	switch (event) {
	case cv::MouseEventTypes::EVENT_LBUTTONDOWN:
		L_button_down = cv::Point(x, y);
		break;

	case cv::MouseEventTypes::EVENT_MOUSEMOVE:
		//img = imread(cut_img_file_name); //����   //***************************
		img = ori_img.clone();

		if (flags & cv::MouseEventFlags::EVENT_FLAG_LBUTTON) {        //!< indicates that the left mouse button is down.	
			//cv::line(img, cv::Point(0, y), cv::Point(img.cols, y), cv::Scalar(255, 255, 255), 2);
			//cv::line(img, cv::Point(x, 0), cv::Point(x, img.rows), cv::Scalar(255, 255, 255), 2);
			cv::rectangle(img, L_button_down, cv::Point(x, y), cv::Scalar(0, 0, 255), 2);
			L_button_up = Point(x, y);
			imshow("Operating_window", img);
		}

		//else {
		//	cv::line(img, cv::Point(0, y), cv::Point(img.cols, y), cv::Scalar(255, 255, 255), 2);
		//	cv::line(img, cv::Point(x, 0), cv::Point(x, img.rows), cv::Scalar(255, 255, 255), 2);
		//	cv::rectangle(img, L_button_down, L_button_up, cv::Scalar(0, 0, 255), 2);
		//	cv::imshow("Operating_window", img);
		//}
		//break;
	default:
		break;

	}

	//	cout << "saving axis" << L_button_down << L_button_up << endl;
	return;
}