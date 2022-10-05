#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;
typedef unsigned long long ull;
//program that reads 8 files and prints the greater execution time...

ull greater_time = 0;

void readFiles( int num_files ){
	ifstream file;
	string line, filename;

	for( int i = 0; i < num_files; i++ ){
		filename = "resources/process/P" + to_string(i) + ".txt";
		//filename = "resources/process/P0.txt";
		file.open(filename);
		if( ! file ){
			cerr << "Couldn't open file. P" << to_string(i) << endl;
			return;
		}

		while( file >> ws && getline( file, line ) ){
			continue;
		}

		size_t pos = line.find("ms");
		line.erase( pos, string::npos );
		//cout << line << endl;
		ull aux;
		aux = stoull( line );

		if ( aux > greater_time ){
			greater_time = aux;
		}
		file.close();

	}
	cout << greater_time << endl;

}

int main(int argc, char** argv){
	readFiles( atoi( argv[1] ) );
	return 0;
}