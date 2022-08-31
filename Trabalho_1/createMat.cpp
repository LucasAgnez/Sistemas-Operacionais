#include<bits/stdc++.h>

using namespace std;

int main(int argc, char **argv){
	if(argc != 5){ //check arguments
		cout << "USAGE: ./createMat <RowsM1> <ColsM1> <RowsM2> <ColsM2>" << endl;
		return 1;
	}
	srand( (unsigned)time(NULL) );
	int RowsM1, RowsM2, ColsM1, ColsM2;
	stringstream s;
	s << argv[1] << " " << argv[2] << " " << argv[3] << " "  << argv[4];
	s >> RowsM1 >> ColsM1 >> RowsM2 >> ColsM2; //load arguments

	int** M1 = new int*[RowsM1];
	for(int i = 0; i < RowsM1; i++){
		M1[i] = new int[ColsM1];
		for(int j = 0; j < ColsM1; j++){
			M1[i][j] = rand() % 1000; //initializing M1 with random values
		}
	}

	int** M2 = new int*[RowsM2];
	for(int i = 0; i < RowsM2; i++){
		M2[i] = new int[ColsM2];
		for(int j = 0; j < ColsM2; j++){
			M2[i][j] = rand() % 1000; //initializing M2 with random values
		}
	}
 
	int count = 1;
	string filename;
	while(count < 5){
		fstream file;
		filename = "resources/basic_matrixes/M" + to_string(count) + ".txt"; //add filepath and extension
		count++;	
		file.open(filename);
      	if (!file){ 
			file.open(filename, fstream::out);
			file << "p " << RowsM1 << " " << ColsM1 << endl;
			for(int i = 0; i < RowsM1; i++){
				file << "d ";
				for(int j = 0; j < ColsM1; j++){
					file  << M1[i][j] << " ";	//loading M1 into a file
				}
				file << endl;
			}
			file.close();
			break;
    	}
	}
	count = 1;
	while(count < 5){
		fstream file;
		filename = "resources/basic_matrixes/M" + to_string(count) + ".txt"; //add filepath and extension
		count++;	
		file.open(filename);
      	if (!file){ 
			file.open(filename,  fstream::out);
			file << "p " << RowsM2 << " " << ColsM2 << endl;
			for(int i = 0; i < RowsM2; i++){
				file << "d ";
				for(int j = 0; j < ColsM2; j++){
					file  << M2[i][j] << " ";	//loading M2 into a file
				}
				file << endl;
			}
			file.close();
			break;
    	}
	}
	return 0;
}