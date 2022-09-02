#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#define MAX_FILES 100

using namespace std;

chrono::system_clock::time_point start;

void loadMatrixFile(int **&M, string filename, int &R, int &C){
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
			M = new int*[R];
			for(int i = 0; i < R; i++){
				M[i] = new int[C];
				for(int j = 0; j < C; j++){
					M[i][j] = 0; //initializing Matrix
				}
			}
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

void matMult(int **M1, int **M2, int fileCounter, int R, int n, int C, int R0, int Rf, int C0, int Cf){
	int counter = 1, sum, auxC;
	ofstream file;
	string filename = "resources/process/P" + to_string(fileCounter) + ".txt";
	file.open(filename);
	if (file.is_open()) {
		file << R << " " << C << endl;
		if(Rf != R0){ 
            auxC = Cf;
            Cf = C; 
        }  
		for(int i = R0; i < Rf; i++){
			for(int j = C0; j < Cf; j++){
				sum = 0;
				for(int k = 0; k < n; k++){
					sum += M1[i][k]*M2[k][j];					
				}
				file << "C" << i << j << " " << sum << endl;
			}
			if(R0 != Rf){
                C0 = 0;
                if((Rf - R0) == counter){
                    Cf = auxC;
                }
                counter++;
            }
		}
		chrono::system_clock::time_point end = chrono::system_clock::now();
		file << chrono::duration_cast<chrono::nanoseconds> (end- start).count() << "ns" << "\n";
	}
}

void openProcess(int** M1, int** M2, int R1, int n, int C2, int P){
	int num_files = ceil(((double)(R1*C2))/P);
	string filename;
	pid_t process[num_files];

	int C0, Cf, R0, Rf;
	for(int i = 0; i < num_files; i++){
		R0 = P*i/R1 ;
		C0 = P*i % R1;
		Rf = P*(i+1)/R1;
		Cf = P*(i+1)%R1;
		process[i] = fork();
		if(process[i] == 0){
			start = std::chrono::system_clock::now();
			matMult(M1, M2, i, R1, n, C2, R0, Rf, C0, Cf);
			exit(0);
		}
		else{
			wait(NULL);
		}
	}
}

bool isNumber(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
	return true;
}

int main(int argc, char **argv){
    if(argc != 4){ // check arguments
		cout << "USAGE: ./procMat <fileM1> <fileM2> <N>" << endl;
		return 1;
	}

	if(!isNumber(argv[3])){
		cout << "ERROR: Invalid number" << endl;
		exit(-1);
	}

    int P;
    string filename1, filename2;
	stringstream s;

	s << argv[1] << " " << argv[2] << " " << argv[3];
	s >> filename1 >> filename2 >> P;


	int **M1;
	int R1, C1;
	loadMatrixFile(M1, filename1, R1, C1);

	int **M2;
	int R2, C2;
	loadMatrixFile(M2, filename2, R2, C2);

	if (C1 != R2){ //check if multiplication is possible
		cout << "ERROR: Invalid matrix" << endl;
		return 0;
	}
	int n = R2;
	openProcess(M1, M2, R1, n, C2, P);

	return 0;

}