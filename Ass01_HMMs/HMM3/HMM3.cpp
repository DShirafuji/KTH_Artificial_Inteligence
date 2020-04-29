#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <limits>
#include <string>
#include <float.h>
#include <math.h>
using namespace std;

int main(int argc, char * argv[]){
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
    
    
    float alpha[m_A][T];
    float beta[m_A][T];
    float di_gamma[m_A][n_A][T-1];
    float gamma_t[m_A][T];
    float c[T];
    
    /*======================================
     ============== Start Loop ==============
     ======================================*/
    float logProb = 0;
    float oldLogProb = (-1)*(FLT_MAX);
    float P_O_ramda = 0.0;
    float Prior_P_O_ramda = (-1)*(FLT_MAX);
    int loop = 0;
    while (true){
        //============ Compute alpha ============//
        //Compute the alpha[i][0]
        c[0] = 0.0;
        for (int i=0; i<m_A; ++i){
            alpha[i][0] = PI[0][i]*B[i][state[0]];
            c[0] = c[0] + alpha[i][0];
        }
        //Scale the alpha[i][0]
        c[0] = 1/c[0];
        for (int i=0; i<m_A; ++i){
            alpha[i][0] = c[0]*alpha[i][0];
        }
        //Compute all alpha
        for (int t=1; t<T; ++t){
            c[t] = 0.0;
            for (int i=0; i<m_A; ++i){
                alpha[i][t] = 0.0;
                for (int j=0; j<m_A; ++j){
                    alpha[i][t] = alpha[i][t] + alpha[j][t-1]*A[j][i];
                }
                alpha[i][t] = alpha[i][t]*B[i][state[t]];
                c[t] = c[t] + alpha[i][t];
            }
            //Scale the all alpha
            c[t] = 1/c[t];
            for (int i=0; i<m_A; ++i){
                alpha[i][t] = c[t]*alpha[i][t];
            }
        }
        
        //============ Compute beta ============//
        // beta(T-1) = 1 * c(T−1)
        for (int i=0; i<m_A; ++i){
            beta[i][T-1] = 1*c[T-1];
        }
        for (int t=T-2; t>-1; --t){
            for (int i=0; i<m_A; ++i){
                beta[i][t] = 0.0;
                for (int j=0; j<m_A; ++j){
                    beta[i][t] = beta[i][t] + beta[j][t+1]*A[i][j]*B[j][state[t+1]];
                }
                //scale beta
                beta[i][t] = c[t]*beta[i][t];
            }
        }
        
        //============ Compute di-gamma and gamma ============//
        for (int t=0; t<T-1; ++t){
            for (int i=0; i<m_A; ++i){
                gamma_t[i][t] = 0.0;
                for (int j=0; j<m_A; ++j){
                    di_gamma[i][j][t] = alpha[i][t]*A[i][j]*B[j][state[t+1]]*beta[j][t+1];
                    gamma_t[i][t] = gamma_t[i][t] + di_gamma[i][j][t];
                }
            }
        }
        //Special Case for gamma
        for (int i=0; i<m_A; ++i){
            gamma_t[i][T-1] = alpha[i][T-1];
        }
        //============ Re-Estimate Matrix A, B, and PI ============//
        for (int i=0; i<n_pi; ++i){
            PI[0][i] = gamma_t[i][0];
        }
        
        float denom;
        float number_;
        for (int i=0; i<m_A; ++i){
            denom = 0;
            for (int t=0; t<T-1; ++t){
                denom = denom + gamma_t[i][t];
            }
            for (int j=0; j<m_A; ++j){
                number_ = 0;
                for (int t=0; t<T-1; ++t){
                    number_ = number_ + di_gamma[i][j][t];
                }
                A[i][j] = number_/denom;
            }
        }
        
        for (int i=0; i<m_B; ++i){
            denom = 0;
            for (int t=0; t<T; ++t){
                denom = denom + gamma_t[i][t];
            }
            for (int j=0; j<n_B; ++j){
                number_ = 0;
                for (int t=0; t<T; ++t){
                    if (state[t] == j){
                        number_ = number_ + gamma_t[i][t];
                    }
                }
                B[i][j] = number_/denom;
            }
        }
        
        
        //============ Compute log[P(O|ramda)] ============//
        logProb = 0;
        for (int i=0; i<T; ++i){
            logProb = logProb + log(c[i]);
        }
        logProb = (-1)*logProb;
        if (logProb > oldLogProb){
            oldLogProb = logProb;
            continue;
        }
        else{
            break;
        }
    }
    
    //======================== Output ========================//
    cout << m_A << " " << n_A << " ";
    for (int i=0; i<m_A; ++i){
        for (int j=0; j<n_A; ++j){
            cout << A[i][j] << " ";
        }
    }
    cout << endl;
    cout << m_B << " " << n_B << " ";
    for (int i=0; i<m_B; ++i){
        for (int j=0; j<n_B; ++j){
            cout << B[i][j] << " ";
        }
    }
    cout << endl;
    
    return 0;
}
