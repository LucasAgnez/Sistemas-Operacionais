#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<chrono>
#include<iomanip>
#include<vector>

#define MAX_FILES 20

using namespace std;

void loadMatrixFile(vector<vector<int>>&M, string filename, int &R, int &C){
	ifstream file;
	string line;
	string discard;
	int count;
	filename = "resources/basic_matrixes/" +filename + ".txt";
	file.open(filename); //load file into M
	if (!file) {
		cerr << "Couldn't open file " << filename << endl;
		exit(-1);
	}
	count = 0;
	while(getline(file, line)){
		if (line.size() == 0) {
			continue;
		}
		if(line.find("p")!= string::npos){
			stringstream stream(line);
			stream >> discard;  //discard dimensions index and load them into R and C
			stream >> R;
			stream >> C;
			vector<vector<int>> M1(R, vector<int>(C));
			M = M1;
			continue;
		}
		if(line.find("d")!= string::npos){
			stringstream stream(line);
			stream >> discard;
			for(int i = 0; i < C; i++) {   
				stream >> M[count][i]; //loading into M1
			}
			count++;
		}
	}
	file.close();
}

vector<vector<int>> multMat(vector<vector<int>> M1, vector<vector<int>> M2, int R1, int C1, int R2, int C2){

	vector<vector<int>> M3(R1, vector<int>(C2));
	
	for (int i = 0; i < R1; i++){ //perform multiplication
		for (int j = 0; j < C2; j++){
			int sum = 0;
			for (int k = 0; k < R2; k++){
				sum += M1[i][k]*M2[k][j];
			}
			M3[i][j] = sum;
		}
	}
	return M3;
}

void printMatrixFile(vector<vector<int>> M, int R, int C, int time){
	int fileCounter = 1; // counter for the name of the file
	string filename;
	int count = 1;
	while(count < MAX_FILES){ // max number of files
		fstream file;
		filename = "resources/sequential/S" + to_string(fileCounter) + ".txt";
		fileCounter++;	
		file.open(filename);
	  	if (!file){ // create and print M3 onto the file
			file.open(filename,  fstream::in | fstream::out | fstream::trunc);
			file << R << " " << C << endl;
			for(int i = 0; i < R; i++){
				for(int j = 0; j < C; j++){
					file  << "C" << i << j << " " <<  M[i][j] << endl;
				}
			}
			file << fixed << time << setprecision(9); 
			file << "ns";
			file.close();
			break;
		}
	}
}


int main(int argc, char **argv){
	if(argc != 3){ // check arguments
		cerr << "USAGE: ./seqMat <fileM1> <fileM2>" << endl;
		return 1;
	}

	string filename1, filename2;
	stringstream s;

	s << argv[1] << " " << argv[2];
	s >> filename1 >> filename2;
	
	vector<vector<int>> M1;
	int R1, C1;
	loadMatrixFile(M1, filename1, R1, C1);

	vector<vector<int>> M2;
	int R2, C2;
	loadMatrixFile(M2, filename2, R2, C2);

	if (C1 != R2){ //check if multiplication is possible
		cout << "ERROR: Invalid matrix" << endl;
		return 1;
	}

	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);

	vector<vector<int>> M3 = multMat(M1, M2, R1, C1, R2, C2); // load the multiplication into M3

	auto end = chrono::high_resolution_clock::now();
	
	int time = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); // measure duration
	
	printMatrixFile(M3, R1, C2, time);

	return 0;
}