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
    float A[m_A][n_A];
    for (int i=0; i<m_A; ++i){
        for (int j=0; j<n_A; ++j){
            cin >> element;
            float number = std::stof(element);
            A[i][j] = number;
        }
    }
    
    cin >> str;
    int m_B = std::stoi(str);
    cin >> str;
    int n_B = std::stoi(str);
    float B[m_B][n_B];
    for (int i=0; i<m_B; ++i){
        for (int j=0; j<n_B; ++j){
            cin >> element;
            float number = std::stof(element);
            B[i][j] = number;
        }
    }
    
    cin >> str;
    int m_pi = std::stoi(str);
    cin >> str;
    int n_pi = std::stoi(str);
    float PI[m_pi][n_pi];
    for (int i=0; i<m_pi; ++i){
        for (int j=0; j<n_pi; ++j){
            cin >> element;
            float number = std::stof(element);
            PI[i][j] = number;
        }
    }
    
    cin >> str;
    int T = std::stoi(str);
    int state[T];
    for (int i=0; i<T; ++i){
        cin >> state[i];
    }
    
    /*=================================================================//
     //=================================================================//
     //=================================================================*/
    
    float Prob[n_B];
    float Prob_temp[n_B];
    // Compute on each state
    for (int state_num=0; state_num<T; ++state_num){
        if (state_num==0){
            float temp = 0;
            for (int i=0; i<m_B; ++i){
                Prob_temp[i] = PI[0][i];
            }
        }
        else{
            for (int j=0; j<n_A; ++j){
                float temp = 0;
                for (int i=0; i<m_A; ++i){
                    temp = temp + Prob[i]*A[i][j];
                }
                Prob_temp[j] = temp;
            }
        }
        for (int i=0; i<m_B; ++i){
            Prob[i] = Prob_temp[i]*B[i][state[state_num]];
        }
    }
    
    float ans;
    for (int i=0; i<m_B; ++i){
        ans = ans + Prob[i];
    }
    cout<< ans << endl;
    
    return 0;
}
