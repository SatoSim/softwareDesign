#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<float>> read_file(string name) {
    ifstream file;
    file.open(name, ios::in);

    vector<vector<float>> content;
    vector<float> row;
    string line;

    if (file.is_open()) {
        int count = 0;
        while (getline(file, line)) {
            
            row.clear();

            stringstream ss(line);
            string num;
            while (getline(ss, num, ',')) {
                row.push_back(stoi(num));
            }
            content.push_back(row);
            count++;
        }

    } else {
        cout << "Could not open the file\n";
        return {};
    }
    file.close();
    return content;
}

float* getLabelasArray(int pos, string filename) {
    vector<vector<float>> data = read_file(filename);

    float* labelArr;
    labelArr = new float[9];  // Init array of 9 w/ zeroes
    for (int i = 0; i < 9; i++) {
        labelArr[i] = 0;
    }
    int index = data[pos][0];

    labelArr[index] = 1;
    return labelArr;
}

float* getNumasArray(int pos, string filename) {
    vector<vector<float>> data = read_file(filename);

    float* arr;
    arr = new float[784];

    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            arr[(i * 28) + j] = data[pos][(i * 28) + j];
        }
    }
    return arr;
}

float* normNumArray(float* arr) {
    for (int i = 0; i < 784; i++) {
        arr[i] = arr[i] / 255;
    }
    return arr;
}

void displayNum(int pos, string filename) {
    // float** numArr = getNumasArrayDisplay(pos, filename);
    vector<vector<float>> data = read_file(filename);
    int num_rows = 28;
    int num_cols = 28;

    float** num;
    num = new float*[num_rows];

    for (int i = 0; i < num_rows; i++) {
        num[i] = new float[num_cols];
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            num[i][j] = (data[pos][(i * 28) + j + 1]);
        }
    }

    for (int row = 0; row < 28; row++) {
        for (int col = 0; col < 28; col++) {
            if (num[row][col] != 0) {
                cout << "*";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
    cout<<endl;
}

void displayNum2(float* num) {
    // float** numArr = getNumasArrayDisplay(pos, filename);
 
    for (int row = 0; row < 28; row++) {
        for(int col = 0; col < 28; col++){
            if (num[col +(28*row)]!= 0){
                cout << "0";
            } else {
                cout << "-";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

