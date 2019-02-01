#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define NODES 1000000
#define INFECTED 1
#define HEALTHY 0

int main(void)
{
srand(time(NULL));                                  // Randomize the time
FILE *FilePointer = fopen("Result.csv", "w");       // Make a file, to write results on it
float B = 1;                                        // Randomness variable
for (B = 1; B<=10; B++){
    int TotalInfected=1;                            // Num of infected 
    int network[NODES]={HEALTHY};                   // All network nodes are healthy
    network[rand() % 1000000] = INFECTED;           // One  network node is infected (radomly)
    int j = 1;                                      // Variable used on the "while" loop
    int time = 0;
    int random;
    float rnd;
    printf("\n\nRadomness B = %0.1f\n", B/10);
    int NITT = 0;                                   // Number of infected this time
    
    while (TotalInfected < NODES && TotalInfected > 0){
        for (int i = 1; i<=j; i++){
            random = rand() % 1000001;              // Choose a random network
            rnd = (float) rand() / (float) RAND_MAX;// Choose a random number
            if ( rnd  <=  B/10){                    // If the random number is less than B (where 0.1 < B < 1)
                if (network[random] == HEALTHY){    // then, if the random network is healthy
                    network[random] = INFECTED;     // then make it infected
                    TotalInfected++;                // also add 1 to the Number of infected Networks
                    NITT++;                         // also add 1 to the Number of infected Networks this time                    
                }
            }
        }
        j = TotalInfected;
        time++;
        printf("Time: %d \nNum of Infected: %d \n", time, TotalInfected);
        fprintf(FilePointer, "%d; %d; %d; \n", time, TotalInfected, NITT);
        NITT = 1;                                   // re initialize Number of infected Networks this time
    }
}
fclose(FilePointer);
return 0;
}
