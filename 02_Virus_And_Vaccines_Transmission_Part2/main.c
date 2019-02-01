typedef struct NODESTRUCT{
    int state;
    int healingTime;
} Node;

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define NODES 1000000
#define HEALTHY  0
#define INFECTED 1
#define IMMUNED  2

int main(void)
{
    srand(time(NULL));                                  // Randomize the time
    FILE *FilePointer = fopen("Result2.csv", "w");      // Make a file, to write results on it
    float B = 1;                                        // Randomness variable
    
    for (B = 1; B<=10; B++){
        Node network[NODES];
        for (int i = 0; i<NODES; i++){                   // Initialize 
            network[i].state = HEALTHY;                  // All network nodes are healthy and have healing time=5
            network[i].healingTime = 5;
        }
        network[rand() % NODES].state = INFECTED;        // One  network node is infected (radomly)
        int TotalInfected=1;                             // Num of Total infected 
        int TotalImmunded=0;                             // Num of immuned
        int j = 1;                                       // Variable used on the "while" loop
        int time = 0;
        int random;
        float rnd;
        printf("\n\nRadomness B = %0.1f\n", B/10);
        int NITT = 0;                                    // Number of infected this time
        
        while (TotalInfected < NODES && TotalInfected > 0){
            
            for (int i = 1; i<=j; i++){
             random = rand() % 1000;                         // Choose a random network
                    rnd = (float) rand() / (float) RAND_MAX; // Choose a random number
                    if ( rnd  <=  B/10){                     // If the random number is less than B (where 0.1 < B < 1)
                        if (network[random].state == HEALTHY){   // then, if the random network is healthy
                            network[random].state = INFECTED;    // then make it infected
                            TotalInfected++;                     // also add 1 to the Number of infected Networks
                            NITT++;                              // also add 1 to the Number of infected Networks this time
                        }
                    }
            }
  
            for (int node=0; node <= NODES; node++){
                if (network[node].state == INFECTED){
                    network[node].healingTime--;
                    if(network[node].healingTime==0 ){
                        network[node].state=IMMUNED;
                        TotalImmunded++;
                        TotalInfected--;
                    }
                }
            }
            
            j = TotalInfected;
            time++;
            printf("Time: %d \nInfected: %d Immuned: %d\n", time, TotalInfected, TotalImmunded);
            fprintf(FilePointer, "%f; %d; %d;\n", B, TotalInfected, TotalImmunded); //Time NumOfInf NumOfThisTime
           // if (time > 10000){printf("ERROR!"); exit(1);} //error
            NITT = 1;                                       // re initialize Number of infected Networks this time
        }
    }

    fclose(FilePointer);
    
    return 0;
}

