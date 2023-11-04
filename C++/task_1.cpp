#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;


int getRandomInt(int a, int b) {
    return rand()%(b-a+1);
}


vector<vector<int>> createMatrix(int rows, int columns) {
    // Функиця для генерации матриц
    srand(time(NULL));

    vector<vector<int>> matrix(rows, vector<int>(columns, 0)); // Инициализируем матрицу нулями

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

    int lenRows = sizeof(matrix); // Определяем количество строк в матрице

    for (int i=0; i<lenRows-1; i++) {
        int lenColumns = sizeof(matrix[i]); // Определяем количество столбцов

        for (int j=0; j<lenColumns-1; j++) {
            int index = matrix[i][j];

            lenElem = to_string(index).length();

            if (lenElem > maxLenElem) {  // Ищем наибольшее количество символов в числе для красивого вывода
                maxLenElem = lenElem;
            }
        };
    };

    for (int i=0; i<lenRows-1; i++) {
        int lenColumns = sizeof(matrix[i]);

        for (int j=0; j<lenColumns-1; j++) {
            int index = matrix[i][j];

            int difference = maxLenElem - to_string(index).length();  // Находим число для нужного количества пробелов
            coutString = string(difference, ' ') + to_string(index) + ' ' + '|' + ' ';

            cout << coutString; // Выводим каждый столбец строки
        };

        int lenOneElem = maxLenElem; // Определяем количество символов в одном столбце строки

        // По необходимости указываем визуально главную диагональ
        if (showMainDiagonal){
            cout << endl << string((lenOneElem+3)*i, ' ') << string(lenOneElem, '^') << endl;
        } else {
            cout << endl << endl;
        }
    };
}


int main() {
    int rang = 11; // Порядок матрицы

    vector<vector<int>> squareMatrix = createMatrix(rang, rang); // Генерируем матрицу размера rang x rang
    vector<vector<int>> coutMatrix(rang, vector<int>(rang, 0)); // Определяем итоговую матрицу

    cout << "Main Matrix" << endl;
    printMatrix(squareMatrix);  // Выводим исходную матрицу с указанием главной диагонали

    for (int i=0; i<rang; i++) {
      int mainIndex = squareMatrix[i][i]; // Получаем элемент на главной диагонали

      for (int j=0; j<rang; j++) {
        int index = squareMatrix[i][j];

        if (index > mainIndex) {  // Если элемент больше элемента на главной диагонали в этой строке,
            coutMatrix[i][j] = 1; // Он равен единице
        } else {
            coutMatrix[i][j] = 0; // Иначе - нулю
        }
      };
    };

    cout << endl;

    cout << "Cout Matrix" << endl;
    printMatrix(coutMatrix, false); // Выводим итоговую матрицу

    return 0;
}
