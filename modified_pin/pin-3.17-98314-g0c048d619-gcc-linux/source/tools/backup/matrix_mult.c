#include <stdio.h>

void multiplyMatrices(int first[][3],
                      int second[][3],
                      int result[][3],
                      int r1, int c1, int r2, int c2) {

// Initializing elements of matrix mult to 0.
   int i,j,k; 
   for (int i = 0; i < r1; ++i) {
          for (int j = 0; j < c2; ++j) {
                   result[i][j] = 0;
                         }
                            }

                               // Multiplying first and second matrices and storing it in result
                                  for (int i = 0; i < r1; ++i) {
                                        for (int j = 0; j < c2; ++j) {
                                                 for (int k = 0; k < c1; ++k) {
                                                             result[i][j] += first[i][k] * second[k][j];
                                                                      }
                                                                            }
                                                                               }
                                                                               }

int main() {
   int first[3][3], second[3][3], result[3][3];
   int i,o;
   
   srand(time(NULL));
   for(o = 0; o<3; o++)
       for(i = 0; i<3; i++){
           first[o][i] = rand() % 10;
	   second[o][i] = rand() % 10;
   }
   multiplyMatrices(first, second, result, 3,3,3,3);
   return 0;
}
