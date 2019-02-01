#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NODES 500
typedef struct sensor{
	int flag;
	int radius;
	float energy;
}Sensor;

int getRandomCoordinate(int coordinate, int radius, int coordinateMax);

int main(void)
{
    srand(time(NULL));                                    // Randomize the time
    int time = 0;    
    float B = 1;                                          // Randomness variable
    int radius=1;
    char radiusChar[6];                                   // Just a variable to contain characters
    for (radius=1; radius<=10; radius++){
        sprintf(radiusChar, "%d", radius);                // Convert int to char  
        strcat(radiusChar, ".csv");                       // radiusChar + ".csv" = 1.csv, 2.csv, ...
        FILE *FilePointer = fopen(radiusChar, "w");       // Make a file, to write results on it
        Sensor sensors[NODES][NODES]={0,-1,-1};
        sensors[rand()%NODES][rand()%NODES].flag = 1;
        int currentSensorX = rand()%NODES;
        int randomSensorX = -1;
        int currentSensorY = rand()%NODES;
        int updatedSensor = 1;
        int randomSensorY = -1;

        while(updatedSensor<NODES*NODES){
            do{
                randomSensorX=getRandomCoordinate(currentSensorX, radius, NODES);
                randomSensorY=getRandomCoordinate(currentSensorY, radius, NODES);
                
                }while(randomSensorX==currentSensorX);
                currentSensorY = randomSensorY;
                currentSensorX = randomSensorX;
                if(!sensors[currentSensorX][currentSensorY].flag){
                    updatedSensor+=1;
                    sensors[currentSensorX][currentSensorY].flag = 1;
                }
                time++;
                fprintf(FilePointer, "%d;\n", updatedSensor); //How many sensors got the message? 
            }
        updatedSensor = 1;
        fclose(FilePointer);
    }

        return 0;
    }

int getRandomCoordinate(int coordinate, int radius, int coordinateMax){     //one value for one coordination. x or y. 
    int min = (coordinate-radius)<0?0:coordinate-radius;                    //if <0 then 
    int max = (coordinate+radius)>coordinateMax?coordinateMax:coordinate+radius;
    return  min + rand()%((max-min)+1);
    
}