#include <bits/stdc++.h>
#include <iostream>

using namespace std;

string ltrim(const string &);

string rtrim(const string &);

vector<string> split(const string &);

bool isSolutionExists = true;
string errorMessage;

vector<double> solveByGauss(int n, vector<vector<double>> matrix) {
    vector<double> solution(n, 0.0);
    for (int i = 0; i < n; ++i) {
        int maximalRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(matrix[k][i]) > abs(matrix[maximalRow][i]))
                maximalRow = k;
        }
        if (matrix[maximalRow][i] == 0) {
            isSolutionExists = false;
            errorMessage = "The system has no roots of equations or has an infinite set of them.";
            return solution;
        }
        swap(matrix[i], matrix[maximalRow]);
        for (int k = i + 1; k < n; ++k) {
            double coefficient = matrix[k][i] / matrix[i][i];
            for (int j = i; j <= n; ++j) {
                matrix[k][j] -= coefficient * matrix[i][j];
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        solution[i] = matrix[i][n];
        for (int j = i + 1; j < n; ++j) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }
    for (int i = 0; i < n; ++i) {
        double residual = 0.0;
        for (int j = 0; j < n; ++j) {
            residual += matrix[i][j] * solution[j];
        }
        solution.push_back(matrix[i][n] - residual);
    }
    return solution;
}

int main() {
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    int matrix_rows = n;
    int matrix_columns = n + 1;

    vector<vector<double>> matrix(matrix_rows);

    for (int i = 0; i < matrix_rows; i++) {
        matrix[i].resize(matrix_columns);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < matrix_columns; j++) {
            double matrix_row_item = stod(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    vector<double> result = solveByGauss(n, matrix);

    if (isSolutionExists) {
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];

            if (i != result.size() - 1) {
                cout << "\n";
            }
        }
    } else {
        cout << errorMessage;
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(' ', start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
