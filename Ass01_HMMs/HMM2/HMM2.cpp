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
    
    float delta[m_A];
    float delta_idx[m_A];
    float max_prob[m_A][T-1];
    int state_seq[m_A][T-1];
    
    // Compute on state_num = 0
    for (int i=0; i<m_A; ++i){
        delta[i] = PI[0][i]*B[i][state[0]];
    }
    // Compute on each state
    float tempo;
    for (int state_num=1; state_num<T; ++state_num){
        // calculate probs in each state (ex.A,B,H,S)
        for (int j=0; j<n_A; ++j){
            float temp_prob = -1;
            int temp_state = m_A+1; //m_A+1 is not in the state number
            for (int i=0; i<m_A; ++i){
                // Get Maximum prob
                tempo = delta[i]*A[i][j]*B[j][state[state_num]];
                if (temp_prob < tempo){
                    temp_prob = tempo;
                    max_prob[j][state_num-1] = tempo;
                    state_seq[j][state_num-1] = i; // Get the argmax state
                }
            }
        }
        for (int i=0; i<m_A; ++i){
            delta[i] = max_prob[i][state_num-1];
        }
    }
    
    // Answer BOX
    int ans[T];
    
    // Get the final state
    int temp_state = m_A+1;
    float temp_prob = 0.0;
    for(int i=0; i<m_A; ++i) {
        if(max_prob[i][T-2] > temp_prob){
            temp_prob = max_prob[i][T-2];
            temp_state = i;
        }
    }
    ans[T-1] = temp_state;
    
    // Get each state from next state
    for (int state_num=T-2; state_num>-1; --state_num){
        float temp_prob = 0.0;
        int next_state = ans[state_num+1];
        int temp_state = state_seq[next_state][state_num];
        ans[state_num] = temp_state;
    }
    
    for (int i=0; i<T; ++i){
        cout << ans[i] << " ";
    }
    cout << endl;
    
    return 0;
}
