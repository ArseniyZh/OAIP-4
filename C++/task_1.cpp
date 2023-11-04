#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;


int getRandomInt(int a, int b) {
    return rand()%(b-a+1);
}


vector<vector<int>> createMatrix(int rows, int columns) {
    // ������� ��� ��������� ������
    srand(time(NULL));

    vector<vector<int>> matrix(rows, vector<int>(columns, 0)); // �������������� ������� ������

    int max_param;
    if (rows > columns) {
        max_param = rows;
    } else {
        max_param = columns;
    }

    for (int i=0; i<rows; i++) {
      for (int j=0; j<columns; j++) {
        matrix[i][j] = getRandomInt(-max_param, max_param);
      }
    };

    return matrix;
}


void printMatrix(vector<vector<int>> matrix, bool showMainDiagonal=true) {
    int maxLenElem = 0;
    int lenElem = 0;
    string coutString;

    int lenRows = sizeof(matrix); // ���������� ���������� ����� � �������

    for (int i=0; i<lenRows-1; i++) {
        int lenColumns = sizeof(matrix[i]); // ���������� ���������� ��������

        for (int j=0; j<lenColumns-1; j++) {
            int index = matrix[i][j];

            lenElem = to_string(index).length();

            if (lenElem > maxLenElem) {  // ���� ���������� ���������� �������� � ����� ��� ��������� ������
                maxLenElem = lenElem;
            }
        };
    };

    for (int i=0; i<lenRows-1; i++) {
        int lenColumns = sizeof(matrix[i]);

        for (int j=0; j<lenColumns-1; j++) {
            int index = matrix[i][j];

            int difference = maxLenElem - to_string(index).length();  // ������� ����� ��� ������� ���������� ��������
            coutString = string(difference, ' ') + to_string(index) + ' ' + '|' + ' ';

            cout << coutString; // ������� ������ ������� ������
        };

        int lenOneElem = maxLenElem; // ���������� ���������� �������� � ����� ������� ������

        // �� ������������� ��������� ��������� ������� ���������
        if (showMainDiagonal){
            cout << endl << string((lenOneElem+3)*i, ' ') << string(lenOneElem, '^') << endl;
        } else {
            cout << endl << endl;
        }
    };
}


int main() {
    int rang = 11; // ������� �������

    vector<vector<int>> squareMatrix = createMatrix(rang, rang); // ���������� ������� ������� rang x rang
    vector<vector<int>> coutMatrix(rang, vector<int>(rang, 0)); // ���������� �������� �������

    cout << "Main Matrix" << endl;
    printMatrix(squareMatrix);  // ������� �������� ������� � ��������� ������� ���������

    for (int i=0; i<rang; i++) {
      int mainIndex = squareMatrix[i][i]; // �������� ������� �� ������� ���������

      for (int j=0; j<rang; j++) {
        int index = squareMatrix[i][j];

        if (index > mainIndex) {  // ���� ������� ������ �������� �� ������� ��������� � ���� ������,
            coutMatrix[i][j] = 1; // �� ����� �������
        } else {
            coutMatrix[i][j] = 0; // ����� - ����
        }
      };
    };

    cout << endl;

    cout << "Cout Matrix" << endl;
    printMatrix(coutMatrix, false); // ������� �������� �������

    return 0;
}
