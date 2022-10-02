#include<iostream>
#include<chrono>
#include<vector>
#include<fstream>
#include<sstream>
#include<cmath>
#include<thread>
#include<string>
#include<cmath>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<iomanip>

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

void matMult(vector<vector<int>> M1, vector<vector<int>> M2, int fileCounter, int R, int n, int C, int R0, int C0, int Rf, int Cf){ 
    auto start = chrono::high_resolution_clock::now();
    int counter = 1, sum, auxC;    
    std::ofstream file;
    string filename = "resources/threads/T" + to_string(fileCounter) + ".txt";
	file.open(filename);
	if (file.is_open()) {
		file << R << " " << C << endl;
		if(Rf != R0){ 
            auxC = Cf;
            Cf = C;
        }
		for(int i = R0; i <= Rf; i++){
			for(int j = C0; j < Cf; j++){
				sum = 0;
				for(int k = 0; k < n; k++){
					sum += M1[i][k]*M2[k][j];					
				}
				file << "C" << i << "," << j << " " << sum << endl;
			}
			if(R0 != Rf){
                C0 = 0;
                if((Rf - R0) == counter){
                    Cf = auxC;
                }
                counter++;
            }
		} 
		auto end = chrono::high_resolution_clock::now();
		auto time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		file << fixed << time << setprecision(9);
		file << "ns";
		file.close();
    }
	pthread_exit(NULL);
}


void openThreads(vector<vector<int>> M1, vector<vector<int>> M2, int R, int n, int C, int P){
	int num_files = ceil(((double)(R*C))/P);
    std::vector<thread> threads;
	string filename;

	int C0, Cf, R0, Rf;
	for(int i = 0; i < num_files; i++){
		R0 = P*i/R;
		C0 = P*i % R;
		Rf = P*(i+1)/R;
		Cf = P*(i+1)%R;
        threads.push_back(thread(matMult, M1, M2, i, R, n, C, R0, C0, Rf, Cf));
	}

    for(auto &thread : threads){ 
        thread.join();
    }
}

bool isNumber(string str) {
	for (int i = 0; i < str.length(); i++)
	if (!isdigit(str[i]))
		return false;
	return true;
}

int main(int argc, char **argv){
    if(argc != 4){ // check arguments
		cerr << "USAGE: ./threadMat <fileM1> <fileM2> <N>" << endl;
		return 1;
	}

	if(!isNumber(argv[3])){
		cerr << "ERROR: Invalid number" << endl;
		exit(-1);
	}

    int P;
    string filename1, filename2;
	stringstream s;

	s << argv[1] << " " << argv[2] << " " << argv[3];
	s >> filename1 >> filename2 >> P;


	vector<vector<int>> M1;
	int R1, C1;
	loadMatrixFile(M1, filename1, R1, C1);

	vector<vector<int>> M2;
	int R2, C2;
	loadMatrixFile(M2, filename2, R2, C2);

	if (C1 != R2){ //check if multiplication is possible
		cout << "ERROR: Invalid matrix" << endl;
		return 0;
	}

	int n = R2;

	openThreads(M1, M2, R1, n, C2, P);

	return 0;

}
