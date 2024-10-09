#include <iostream>
#include <vector>

using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int rows;
    int cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(rows, vector<int>(cols));
    }

    static Matrix createMatrix(const vector<vector<int>>& input) {
        Matrix matrix(input.size(), input[0].size());
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                matrix.data[i][j] = input[i][j];
            }
        }
        return matrix;
    }

    void setValue(int r, int c, int value) {
        if (r < rows && c < cols) {
            data[r][c] = value;
        }
    }

    int getValue(int r, int c) const {
        return (r < rows && c < cols) ? data[r][c] : 0;
    }

    Matrix transpose() const {
        Matrix transposed(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transposed.setValue(j, i, data[i][j]);
            }
        }
        return transposed;
    }

    void display() const {
        for (const auto& row : data) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }


    void input() {
        cout << "Enter the elements of the matrix:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "Element [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }
};

int main() {
    int rows, cols;

    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    Matrix matrix(rows, cols);

    matrix.input();

    cout << "Original Matrix:" << endl;
    matrix.display();

    Matrix transposed = matrix.transpose();

    cout << "Transposed Matrix:" << endl;
    transposed.display();

    return 0;
}
