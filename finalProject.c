//Authors: Kellen Strinden and Peter Hippert
//Date Due: 5/7/2024
//Purpose: CS 135 Final Project

#include <stdio.h>

#define MAX_RESOLUTION 100
#define DEFAULT_FILE "default.txt" //Added a default file
#define FILE_NAME "file.txt" //Added file for testing loadImage function

int mainMenu();
int editMenu();
int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, char imgArray[][maxRes], char resultArray[][maxRes]);
void newImage(FILE* fp, int size);
void displayImage(FILE* filePtr, int* imageX, int* imageY, int maxRes, char imgArray[][maxRes], char resultArray[][maxRes]);

int main(){
	//Variable Declaration
	int userChoice, editChoice, lengthX, lengthY, imgProcessTest;
	char imageData[MAX_RESOLUTION][MAX_RESOLUTION];
	FILE* currentImage = fopen(DEFAULT_FILE, "r");
	
	//Default Image Verification and Processing
	if(currentImage == NULL){
		printf("Could not open default image file. Exiting Program.");
		return 0;
	}
	
	imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageRaw, imageProcessed);
	
	//Main Program Handling
	printf("--------------------------------------------------\n");
	printf("Welcome!\n");
	printf("--------------------------------------------------\n");
	
	do{
		userChoice = mainMenu();
		
		switch(userChoice){
			case 1:
				//Load New Image
				newImage(currentImage,MAX_RESOLUTION);
				imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageData);
				if(imgProcessTest == 1){
					//Load default image in the case of processing error
				}
				break;
			case 2:
				//Display Current Image
				displayImage(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageRaw, imageProcessed);
				break;
			case 3:
				//Edit Current Image
				editChoice = editMenu();
				
				switch(editChoice){
					case 1:
						//Crop Current Image
						break;
					case 2:
						//Dim Current Image
						break;
					case 3:
						//Brighten Current Image
						break;
					case 4:
						//Rotate Current Image
						break;
					case 5:
						//Exit To Main Menu
						break;
					default:
						//Invalid Choice Handling
						printf("Invalid Choice. Returning to Main Menu.\n");
						printf("--------------------------------------------------\n");
						break;
				}
				
				break;
			case 4:
				//Exit Program
				printf("Goodbye!\n");
				printf("--------------------------------------------------\n");
				break;
			default:
				//Invalid Choice Handling
				printf("Invalid Choice. Please Try Again.\n");
				printf("--------------------------------------------------\n");
				break;
		}
	}while(userChoice != 4);
	
	return 0;
}

int mainMenu(){
	//Written by Peter Hippert
	int choice;
	printf("Please select an option:\n");
	printf("  1: Load Current Image\n");
	printf("  2: Display Current Image\n");
	printf("  3: Edit Image\n");
	printf("  4: Exit\n");
	printf("Choice: ");
	scanf("%d", &choice);
	printf("--------------------------------------------------\n");
	return choice;
}

int editMenu(){
	//Written by Kellen Strinden
	
	int result;
	
	//Prompts user to choose an editing option
	printf("Please select an option from the following:\n");
	printf("  1: Crop Current Image\n");
	printf("  2: Dim Current Image\n");
	printf("  3: Brighten Current Image\n");
	printf("  4: Rotate Current Image\n");
	printf("  5: Return to Main Menu\n");
	
	printf("Choice: ");
	scanf("%d", &result);
	printf("--------------------------------------------------\n");
	
	//Returns the integer value of the user's choice for menu logic
	return result;
}

int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, char imgArray[][maxRes], char resultArray[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col, result;
	char tempArray[maxRes][maxRes];
	
	//Resets the image arrays to null state
	for(row = 0; row < maxRes; row++){
		for(col = 0; col < maxRes; col++){
			resultArray[col][row] = '\0';
		}
	}
	
	//Scans through the current file to get raw image data
	for(row = 0; row < maxRes; row++){
		fgets(tempArray[row], (maxRes + 1), filePtr);
	}
	
	//Calculates the image length and width
	for(row = 0; (imgArray[row][0] != '\0')&&(imgArray[row][0] != '\n'); row++){}
	*imageY = row;
	
	for(col = 0; (imgArray[0][col] != '\0')&&(imgArray[0][col] != '\n'); col++){}
	*imageX = col;
	
	//Processes the image into the desired format
	for(row = 0; row < *lengthY; row++){
		for(col = 0; col < *lengthX; col++){
		      	switch(imgArray[row][col]){
			        case '0':
			          resArray[row][col] = 0;
			          break;
			        case '1':
			          resArray[row][col] = 1;
			          break;
			        case '2':
			          resArray[row][col] = 2;
			          break;
			        case '3':
			          resArray[row][col] = 3;
			          break;
			        case '4':
			          resArray[row][col] = 4;
			          break;
			        default:
			          //Returns a fail state for the function
			          return 1;
			          break;
			}
		}
	}
	
	return 0;
}

void newImage(FILE* fp, int size){
	//Written by Peter Hippert
	
	char fileName[size];
	//printf("Enter file name:\n");
	//scanf("%s",fileName);
	//printf("%s\n",fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL){
		printf("Invalid File\n");
		fp = fopen(DEFAULT_FILE, "r");
		return;
	}
}

void displayImage(FILE* filePtr, int* imageX, int* imageY, int maxRes, char imgArray[][maxRes], char resultArray[][maxRes]){
	//Written by Peter Hippert

	//Currently disfunctional due to imgProcess changes. Edited version needs to convert integer data to printed character for ease of file saving
	
	imgProcess(filePtr,imageX,imageY,maxRes,imgArray,resultArray);
	for (int rowInd = 0;rowInd < *imageX; rowInd++){
		for (int colInd= 0;colInd < *imageY; colInd++){
			printf("%c ",resultArray[rowInd][colInd]);
		}

		printf("\n");
	}
}

