#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]){
    string element;
    string str;
    
    cin >> str;
    int m_A = std::stoi(str);
    cin >> str;
    int n_A = std::stoi(str);
    float Amat[m_A][n_A];
    for (int i=0; i<m_A; ++i){
        for (int j=0; j<n_A; ++j){
            cin >> element;
            float number = std::stof(element);
            Amat[i][j] = number;
        }
    }
    
    cin >> str;
    int m_B = std::stoi(str);
    cin >> str;
    int n_B = std::stoi(str);
    float Bmat[m_B][n_B];
    for (int i=0; i<m_B; ++i){
        for (int j=0; j<n_B; ++j){
            cin >> element;
            float number = std::stof(element);
            Bmat[i][j] = number;
        }
    }
    
    cin >> str;
    int m_pi = std::stoi(str);
    cin >> str;
    int n_pi = std::stoi(str);
    float PImat[m_pi][n_pi];
    for (int i=0; i<m_pi; ++i){
        for (int j=0; j<n_pi; ++j){
            cin >> element;
            float number = std::stof(element);
            PImat[i][j] = number;
        }
    }
    
    float pi_A[m_pi][n_pi];
    float pi_A_B[m_pi][n_B];
    
    cout << "1 " << n_B << " ";
    
    for (int row = 0; row < m_pi; row++) {
        for (int col = 0; col < n_A; col++) {
            // Multiply the row of A by the column of B to get the row, column of product.
            pi_A[row][col] = 0;
            for (int inner = 0; inner < m_A; inner++) {
                pi_A[row][col] += PImat[row][inner] * Amat[inner][col];
            }
        }
    }
    for (int row = 0; row < m_pi; row++) {
        for (int col = 0; col < n_B; col++) {
            // Multiply the row of A by the column of B to get the row, column of product.
            pi_A_B[row][col] = 0;
            for (int inner = 0; inner < m_B; inner++) {
                pi_A_B[row][col] += pi_A[row][inner] * Bmat[inner][col];
            }
            cout << pi_A_B[row][col] << " ";
        }
        cout << endl;
    }
    
    
    return 0;
}
