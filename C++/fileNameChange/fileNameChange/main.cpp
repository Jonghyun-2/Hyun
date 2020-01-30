#include <iostream>
#include <string>
#include <experimental/filesystem>
//#include "opencv2/opencv.hpp"

namespace fs = std::experimental::filesystem;
using namespace std;

//const
//array<string, 5> extensions{ ".bmp", ".png", ".jpg", ".tif", ".tiff" };
vector<string> extensions{ ".bmp", ".png", ".jpg", ".tif", ".tiff" };
//Global
fs::path inputPath("");
fs::path output_path0_root("");
vector<fs::path> paths_ff;
vector<fs::path> paths_fs;
vector<fs::path> paths_fm;
vector<fs::path> paths_fl;

//Func
void changeName(fs::path path);

int main() {

	cout << "Input Path : ";
	cin >> inputPath;
	//inputPath = "C:\\Users\\mmmil\\Desktop\\DeIDTestDataSet\\aa";
	output_path0_root = fs::path(inputPath.string()+"_Original");
	cout << "Ouput Path : " << output_path0_root << endl << endl;
	if (!fs::is_directory(inputPath)) {
		cout << "[ERROR] Wrong Path \n";
		return -1;

	}

	cout << "Renaming..." << endl;
	copy(inputPath, output_path0_root, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
	
	changeName(inputPath);

	cout << "Done" << endl;
	char a;
	cin >> a;
	return 0;
}

void changeName(fs::path path) {
	// DEBUG:
	cout << "< Image Paths >" << endl << endl;
	string stem("");
	string ext("");
	string suffix("");
	string faceType("");
	string imgName("");
	
	// Reset.
	paths_ff.clear();
	paths_fs.clear();
	paths_fm.clear();
	paths_fl.clear();

	// Get patient directories.
	for (const fs::directory_entry patient_dir : fs::directory_iterator(path)) {
		// If the entry is a directory (patient directory):
		if (fs::is_directory(patient_dir.status())) {
			for (const fs::directory_entry tx_phase_dir : fs::directory_iterator(patient_dir)) {
				// If the entry is a directory (Tx phase directory):
				if (fs::is_directory(tx_phase_dir.status())) {
					// Get files in each patient directory.
					for (const fs::directory_entry e : fs::directory_iterator(tx_phase_dir)) {
						// Convert a extension to lower case.
						string newName;
						ext = string(e.path().extension().string());
						for_each(ext.begin(), ext.end(), [](char & ch) {
							ch = tolower(ch);
						});

						// If the entry has a specific extension:
						if (find(extensions.begin(), extensions.end(), ext) != extensions.end()) {
							stem = e.path().stem().string();
							//cout <<"[Before]fileName : "<< e.path()<< endl;
							int firstU = int(e.path().string().find_last_of("_"));
							suffix = e.path().string().substr(0, firstU);
							int secondU = int(suffix.find_last_of("_"));
							imgName = suffix.substr(0, secondU);
							faceType = suffix.substr(secondU + 1, firstU);
							

							// fro -> FF
							if (faceType =="fro") {
								newName = imgName + "FF.jpg";
								//cout << "[After]fileName : " << newName << endl<<endl;
								fs::rename(e.path(), newName);
							}
							// smile -> FS
							else if (faceType == "smile") {
								newName = imgName + "FS.jpg";
								//cout << "[After]fileName : " << newName << endl << endl;
								fs::rename(e.path(), newName);
								
							}
							// a45 -> FM
							else if (faceType == "a45") {
								newName = imgName + "FM.jpg";
								//cout << "[After]fileName : " << newName << endl << endl;
								fs::rename(e.path(), newName);
							}
							// lat -> FL
							else if (faceType == "lat") {
								newName = imgName + "FL.jpg";
								//cout << "[After]fileName : " << newName << endl << endl;
								fs::rename(e.path(), newName);
							}

							else {
								cout << "Pass" << endl<<endl ;
							}
						}
					}
				}
			}
		}
	}
	// DEBUG:
	cout << endl;
}