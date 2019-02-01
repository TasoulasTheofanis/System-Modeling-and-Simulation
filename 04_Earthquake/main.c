#include <stdio.h>
#include <stdlib.h>

#define Fcrit 0.4
#define Fout 0.01

int main(void)
{
    float plate[10][10];
    float helper_plate[10][10] = {0};
    float earthquake[10][10] ={0};
    int time = 0;
    int isShaking = 0;
    int i;
    int j;
    int magnitude=0;
    FILE *FilePointer = fopen("Result.csv", "w");  // Make a file, to write results on it
     
    for (i=0; i<=9; i++) {
    	for (j=0; j<=9; j++){
    		plate[i][j]=((float)rand()/(float)RAND_MAX)*Fcrit;
    	}
    }

    while (time<=10000){
    	isShaking=0;                   // No shaking
    	for(i=0;i<=9;i++){             // Check if any plate is shaking
    		for(j=0;j<=9;j++){
    			if(plate[i][j]>=Fcrit){// If the plate reaches Fcrit
    				isShaking=1;       // there is at least a shaking plate
    				break;
    			}
    		}
    		if (isShaking){
    			break;
    		}
    	}
    	for(i=0;i<=9;i++){
    		for(j=0;j<=9;j++){
    			if(!isShaking){
    				plate[i][j]+=Fout;
    			}
    			else if(plate[i][j]>=Fcrit){ // Adjust the neighbor plates
    				if(i==0){                // 1st line
    					helper_plate[i+1][j] += 0.25 * plate[i][j];
    				}
    				else if(i==9){           // 10th line
    					helper_plate[i-1][j] += 0.25 * plate[i][j];
    				}
    				else{                   // Any other line
    					helper_plate[i+1][j] += 0.25 * plate[i][j];
    					helper_plate[i-1][j] += 0.25 * plate[i][j];
    				}
    				if(j==0){
    					helper_plate[i][j+1] += 0.25 * plate[i][j];
    				}
    				else if(j==9){
    					helper_plate[i][j-1] += 0.25 * plate[i][j];
    				}
    				else{
    					helper_plate[i][j+1] += 0.25 * plate[i][j];
    					helper_plate[i][j-1] += 0.25 * plate[i][j];
    				}
    				plate[i][j]=0;         // The plate lost its power
    				earthquake[i][j]=1;    // An earthquake began
    			}
    		}
    	}
    	if(isShaking){
    		for(i=0;i<=9;i++){
    			for(j=0;j<=9;j++){
    				plate[i][j]+=helper_plate[i][j];
    				helper_plate[i][j]=0;
    			}
    		}
    	}
    	if(!isShaking){
    		magnitude=0;
    		for(i=0;i<=9;i++){
    			for(j=0;j<=9;j++){
    				if(earthquake[i][j]==1){
    					magnitude+=1;
    				}
    				earthquake[i][j]=0;   // An earthquake ended
    			}
    		}
    		fprintf(FilePointer, "%d;\n", magnitude);
    		time++;
    	}
    }
    fclose(FilePointer);
    return 0;
}