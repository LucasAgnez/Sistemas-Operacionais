#include<bits/stdc++.h>

#define MAXFILES 10

using namespace std;

void createRandMatrix(int **&M, int R, int C){
	srand( (unsigned)time(NULL) );
	M = new int*[R];
	for(int i = 0; i < R; i++){
		M[i] = new int[C];
		for(int j = 0; j < C; j++){
			M[i][j] = rand() % 1000; //initializing M1 with random values
		}
	}
}
void printMatrixFile(int **M, int R, int C){
	int count = 1;
	string filename;
	while(count < MAXFILES){
		fstream file;
		filename = "resources/basic_matrixes/M" + to_string(count) + ".txt"; //add filepath and extension
		count++;	
		file.open(filename);
	  	if (!file){ 
			file.open(filename, fstream::out);
			file << "p " << R << " " << C << endl;
			for(int i = 0; i < R; i++){
				file << "d ";
				for(int j = 0; j < C; j++){
					file  << M[i][j] << " ";	//loading M1 into a file
				}
				file << endl;
			}
			file.close();
			break;
		}
	}
}

bool isNumber(string str) {
	for (int i = 0; i < str.length(); i++)
	if (!isdigit(str[i]))
		return false;
	return true;
}

int main(int argc, char **argv){
	if(argc != 5){ //check arguments
		cerr << "USAGE: ./createMat <RowsM1> <ColsM1> <RowsM2> <ColsM2>" << endl;
		return 1;
	}

	if(!isNumber(argv[1]) || !isNumber(argv[2]) || !isNumber(argv[3]) || !isNumber(argv[4])){
		cerr << "ERROR: Invalid number" << endl;
		exit(-1);
	}

	int RowsM1, RowsM2, ColsM1, ColsM2;
	stringstream s;
	s << argv[1] << " " << argv[2] << " " << argv[3] << " "  << argv[4];
	s >> RowsM1 >> ColsM1 >> RowsM2 >> ColsM2; //load arguments

	int** M1;
	createRandMatrix(M1, RowsM1, ColsM1);

	printMatrixFile(M1, RowsM1, ColsM1);

	int** M2;
	createRandMatrix(M2, RowsM2, ColsM2);
	
	printMatrixFile(M2, RowsM2, ColsM2);
	
	return 0;
}