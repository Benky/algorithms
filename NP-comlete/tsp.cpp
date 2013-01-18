#include <iostream>
#include <fstream>
#include <cmath>

#define MASK_WITH_ONE_BIT(k) (1 << (k))
#define SET_OR_MASK(S, k) ((S) ^ MASK_WITH_ONE_BIT(k))

#define CREATEARRAY_2D(TYPE,NAME,XSIZE,YSIZE) TYPE **NAME = new TYPE*[(XSIZE)]; for (int _i = 0; _i < (XSIZE); _i++) NAME[_i] = new TYPE[(YSIZE)];

using namespace std;

int cityCount;

float step2Compute(int s, int i, float** M, float** d) {
    float result = INFINITY;
    for (int j = 0; j< cityCount;j++){
        if ((MASK_WITH_ONE_BIT(j) & s) != 0) {
            result = min(result, d[i][j] + M[j][SET_OR_MASK(s, j)]);
        }
    }
    return result;
}

/**
 * Computes result of given TSP problem
 **/
float get_result(float **d, float** M) {
    float res = INFINITY;
    int allSet = MASK_WITH_ONE_BIT(cityCount) - 2;
    
    for (int k = 1; k < cityCount; k++){
        res = min(res, d[0][k] + M[k][SET_OR_MASK(allSet,k)]);
    }
    
    return res;
}

int main() {
    ifstream myfile ("samples/tsp");
    
    myfile >> cityCount;
    
    CREATEARRAY_2D(float, d, cityCount, cityCount);
    CREATEARRAY_2D(float, M, cityCount, MASK_WITH_ONE_BIT(cityCount));
    
    //load distance matrix from file
    for(int i = 0; i < cityCount; i++) {
        for(int j = 0; j < cityCount; j++) {
            myfile >> d[i][j];
        }
    }
    
    myfile.close();
    
    //step1 - initialize result matrix
    for (int i = 1; i < cityCount; i++){
        M[i][0] = d[i][0];
    }
    
    //step2
    for (int s = 2; s < MASK_WITH_ONE_BIT(cityCount) - 1; s = s + 2){
        for (int i = 1 ; i < cityCount; i++) {
            if (MASK_WITH_ONE_BIT(i) != s) {
                M[i][s] = step2Compute(s, i, M, d);
            }
        }
    }

    cout << get_result(d, M) << endl;
    return 0;
}
