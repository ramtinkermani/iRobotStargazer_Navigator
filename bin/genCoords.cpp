#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;
int main(){
	string line;
	char* lineChars = new char[line.size()+1];
	ifstream kimFile;
	char* kimCoordsChars;
	int kimCoordsArr[100];
	int k=0;
	kimFile.open("kimCoords.txt", ios::in);
	if(kimFile.is_open()){
			getline (kimFile, line);
			cout << "\nCoords: " << line << endl;
			int i=0, j=0;
			char temp[10];
			while(line[i] != '\0'){
				if(line[i] != ','){
					temp[j] = line[i];
					j++;
				}
				else{
					temp[j] = '\0';
					kimCoordsArr[k]=atoi(temp);
					j=0; k++;
				}
				//cout << line[i] << endl;
			i++;
			}

		kimFile.close();
	}
	else
		cout <<"\n\nCouldn't open File!\n\n";
	int i;

	ofstream parthFile;
	parthFile.open("coordinates.txt");

	for(i=0; i<k; i++){
		cout << "coord " << i << "= " << kimCoordsArr[i] << endl;
		switch(kimCoordsArr[i]){
			case 1: parthFile << "0.137 3.641" << endl; break;
			case 2: parthFile << "1.102 1.644" << endl; break;
			case 3: parthFile << "0.608 0.257" << endl; break;
			case 4: parthFile << "1.348 3.759" << endl; break;
			case 5: parthFile << "0.238 2.174" << endl; break;

			case 6: parthFile << "0.750 3.300" << endl; break;
			case 7: parthFile << "0.697 2.92" << endl; break;
			case 8: parthFile << "2.207 3.336" << endl; break;
			case 9: parthFile << "2.160 2.961" << endl; break;
			case 10: parthFile << "1.821 3.306" << endl; break;

			case 11: parthFile << "1.623 2.95" << endl; break;
			case 12: parthFile << "-0.154 1.0297" << endl; break;
			case 13: parthFile << "-0.256 0.659" << endl; break;
			case 14: parthFile << "-0.604 1.111" << endl; break;
			case 15: parthFile << "-0.620 0.677" << endl; break;

			case 16: parthFile << "2.163 0.910" << endl; break;
			case 17: parthFile << "2.064 0.660" << endl; break;
			case 18: parthFile << "1.803 1.129" << endl; break;
			case 19: parthFile << "1.677 0.65" << endl; break;
			case 20: parthFile << "0.214 3.245" << endl; break;

			case 21: parthFile << "-0.468 3.300" << endl; break;
			case 22: parthFile << "-0.204 2.744" << endl; break;
			case 23: parthFile << "-0.174 2.044" << endl; break;
			case 24: parthFile << "1.32 3.38" << endl; break;
			case 25: parthFile << "0.526 0.678" << endl; break;
			case 26: parthFile << "1.102 1.236" << endl; break;
			default: break;
		}
	}
	parthFile.close();
	return 0;
}
