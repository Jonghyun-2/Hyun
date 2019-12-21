#include <iostream>
#include <experimental/filesystem>
#include <string>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;
namespace fs = std::experimental::filesystem;

void glob_img_paths(fs::path glob_path);
vector<fs::path> paths_frontal;
vector<fs::path> paths_frontal_smile;
vector<fs::path> paths_profile;
vector<fs::path> input_paths_patient;
const array<string, 5> extensions{ ".bmp", ".png", ".jpg", ".tif", ".tiff" };
vector<fs::path> img_paths;

int main() {
	fs::path input_path_root("");
	input_path_root = fs::path("D:/De_id_sample_data/fullTestSet");
	glob_img_paths(input_path_root);
	for (int i = 0; i < img_paths.size(); i++) {
		Mat img = imread(img_paths[i].string());
		resize(img, img, Size(518, 345));
		imwrite(img_paths[i].string(), img);
		cout << img_paths[i].string() << endl;
		cout << i << " : changed" << endl;
	}
	
	return 0;
}


void glob_img_paths(fs::path glob_path) {
	//vector<fs::path> img_paths;
	string ext("");

	// Reset
	paths_frontal.clear();
	paths_frontal_smile.clear();
	paths_profile.clear();

	// Get patient directories.
	for (const fs::directory_entry e : fs::directory_iterator(glob_path)) {
		// If the entry is a directory:
		if (fs::is_directory(e.status())) {
			input_paths_patient.push_back(e.path());
		}
	}
	sort(input_paths_patient.begin(), input_paths_patient.end());

	// Get files in each patient directory.
	for (const fs::path input_path_patient : input_paths_patient) {
		for (const fs::directory_entry e : fs::directory_iterator(input_path_patient)) {
			// Convert a extension to lower case.
			ext = string(e.path().extension().string());
			for_each(ext.begin(), ext.end(), [](char & ch) {
				ch = tolower(ch);
			});

			// If the entry has specific extensions:
			if (find(extensions.begin(), extensions.end(), ext) != extensions.end()) {
				img_paths.push_back(e.path());
			}
		}
		sort(img_paths.begin(), img_paths.end());

		// DEBUG:
		//cout << input_path_patient.filename() << endl;
		//for (const fs::path img_file : img_paths) {
		//	cout << '\t' << img_file.filename() << endl;
		//}

		// Add first 3 image paths.
		try {
			// Frontal face image
			paths_frontal.push_back(img_paths.at(0));
			// Frontal smile face image
			paths_frontal_smile.push_back(img_paths.at(1));
			// Profile face image
			paths_profile.push_back(img_paths.at(2));
		}
		catch (const std::out_of_range& err) {
			//cerr << err.what() << endl;
		}

		// Reset
		//img_paths.clear();
	}
}