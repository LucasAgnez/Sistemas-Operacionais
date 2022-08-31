#include<bits/stdc++.h>

using namespace std;

int** multMat(int** M1, int** M2, int R1, int C1, int R2, int C2){
	if (C1 != R2){ //check if multiplication is possible
		cout << "ERROR: Invalid matrix" << endl;
		return NULL;
	}
	int** M3 = new int*[R1];
	for(int i = 0; i < R1; i++){ // create new matrix
		M3[i] = new int[C2];
		for(int j = 0; j < C2; j++){
			M3[i][j] = 0;
		}
	}
	
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

int main(int argc, char **argv){
	if(argc != 3){ // check arguments
		cout << "USAGE: ./seqMat <fileM1> <fileM2>" << endl;
		return 1;
	}
	string filename1, filename2;
	stringstream s;
	ifstream file;
	string line;
	string discard;
	int R1, C1, R2, C2;
	int **M1, **M2;
	int count;
	s << argv[1] << " " << argv[2];
	s >> filename1 >> filename2;
	filename1 = "resources/basic_matrixes/" +filename1 + ".txt";
	filename2 = "resources/basic_matrixes/" +filename2 + ".txt";
	file.open(filename1); //load first file into M1
	if (!file) {
		cerr << "Couldn't open file " << filename1 << endl;
		exit(-1);
	}
	count = 0;
	while(getline(file, line)){
		if (line.size() == 0) {
			continue;
		}
		if(line.find("p")!= string::npos){
			stringstream stream(line);
			stream >> discard;  //discard dimensions index and load them into R1 and C1
			stream >> R1;
			stream >> C1;
			M1 = new int*[R1];
			for(int i = 0; i < R1; i++){
				M1[i] = new int[C1];
				for(int j = 0; j < C1; j++){
					M1[i][j] = 0; //initializing M1
				}
			}
			continue;
		}
		if(line.find("d")!= string::npos){
			stringstream stream(line);
			stream >> discard;
			for(int i = 0; i < C1; i++) {   
				stream >> M1[count][i]; //loading into M1
			}
			count++;
		}
	}
	file.close();
	file.open(filename2);  //load the second file into M2
	if (!file) {
		cerr << "Couldn't open file " << filename2 << endl;
		exit(-1); 
	}

	count = 0;
	while(getline(file, line)){
		if (line.size() == 0) {
			continue; //skip empty lines
		}
		if(line.find("p")!= string::npos){
			stringstream stream(line);
			stream >> discard; //discard dimensions index and load them into R2 and C2
			stream >> R2;
			stream >> C2;
			M2 = new int*[R2];
			for(int i = 0; i < R2; i++){
				M2[i] = new int[C2];
				for(int j = 0; j < C2; j++){
					M2[i][j] = 0; //initializing M2				
				}
			}
			continue;
		}
		if(line.find("d")!= string::npos){
			stringstream stream(line);
			stream >> discard;
			for(int i = 0; i < C2; i++) {   
				stream >> M2[count][i]; //loading into M2
			}
			count++;
		}
	}
	file.close();
	auto begin = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);

	int **M3 = multMat(M1, M2, R1, C1, R2, C2); // load the multiplication into M3
	if(M3==NULL){
		exit(-1); // check for error
	}
	auto end = chrono::high_resolution_clock::now();
	int time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	int fileCounter = 1; // counter for the name of the file
	string filename;
	while(count < 10){ // max number of files
		fstream file;
		filename = "resources/sequential/S" + to_string(fileCounter) + ".txt";
		fileCounter++;	
		file.open(filename);
      	if (!file){ // create and print M3 onto the file
			file.open(filename,  fstream::in | fstream::out | fstream::trunc);
			file << R1 << " " << C2 << endl;
			for(int i = 0; i < R1; i++){
				for(int j = 0; j < C2; j++){
					file  << "C" << i << j << " " <<  M3[i][j] << endl;
				}
			}
    		file << fixed << time << setprecision(9); 
			file << "ns";
			file.close();
			break;
    	}
	}
	
	return 0;
}