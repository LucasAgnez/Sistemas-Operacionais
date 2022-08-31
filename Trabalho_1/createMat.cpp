#include<bits/stdc++.h>

using namespace std;

void createRandMatrix(int **M, int R, int C){
	srand( (unsigned)time(NULL) );
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			M[i][j] = rand() % 1000; //initializing M1 with random values
		}
	}
}

void printMatrixFile(int **M, int R, int C){
	int count = 1;
	string filename;
	while(count < 5){
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



int main(int argc, char **argv){
	if(argc != 5){ //check arguments
		cout << "USAGE: ./createMat <RowsM1> <ColsM1> <RowsM2> <ColsM2>" << endl;
		return 1;
	}
	int RowsM1, RowsM2, ColsM1, ColsM2;
	stringstream s;
	s << argv[1] << " " << argv[2] << " " << argv[3] << " "  << argv[4];
	s >> RowsM1 >> ColsM1 >> RowsM2 >> ColsM2; //load arguments

	int** M1 = new int*[RowsM1];
	for(int i = 0; i < RowsM1; i++){
		M1[i] = new int[ColsM1];
	}
	createRandMatrix(M1, RowsM1, ColsM1);
	printMatrixFile(M1, RowsM1, ColsM1);

	int** M2 = new int*[RowsM2];
	for(int i = 0; i < RowsM2; i++){
		M2[i] = new int[ColsM2];
	}
	createRandMatrix(M2, RowsM2, ColsM2);
	printMatrixFile(M2, RowsM2, ColsM2);
	
	
	return 0;
}