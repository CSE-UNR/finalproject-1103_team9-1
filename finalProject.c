//Authors: Kellen Strinden and Peter Hippert
//Date Due: 5/7/2024
//Purpose: CS 135 Final Project

#include <stdio.h>

#define MAX_RESOLUTION 100
#define DEFAULT_FILE "default.txt" //Added a default file

int mainMenu();
int editMenu();
//Add new image function here
int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, char imgArray[][maxRes], char resultArray[][maxRes]);

int main(){
	//Variable Declaration
	int userChoice, editChoice, lengthX, lengthY, imgProcessTest;
	char imageRaw[MAX_RESOLUTION][MAX_RESOLUTION], imageProcessed[MAX_RESOLUTION][MAX_RESOLUTION];
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
				
				imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageRaw, imageProcessed);
				if(imgProcessTest == 1){
					//Load default image in the case of processing error
				}
				break;
			case 2:
				//Display Current Image
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
	int row, col, result;
	
	//Resets the image arrays to null state
	for(row = 0; row < maxRes; row++){
		for(col = 0; col < maxRes; col++){
			imgArray[col][row] = '\0';
			resultArray[col][row] = '\0';
		}
	}
	
	//Scans through the current file to get raw image data
	for(row = 0; row < maxRes; row++){
		fgets(imgArray[row], (maxRes + 1), filePtr);
	}
	
	//Calculates the image length and width
	for(row = 0; (imgArray[row][0] != '\0')&&(imgArray[row][0] != '\n'); row++){}
	*imageY = row;
	
	for(col = 0; (imgArray[0][col] != '\0')&&(imgArray[0][col] != '\n'); col++){}
	*imageX = col;
	
	//Processes the image into the desired format
	for(row = 0; row < *imageY; row++){
		for(col = 0; col < *imageX; col++){
			switch(imgArray[col][row]){
				case '0':
					resultArray[row][col] = ' ';
					break;
				case '1':
					resultArray[row][col] = '.';
					break;
				case '2':
					resultArray[row][col] = 'o';
					break;
				case '3':
					resultArray[row][col] = 'O';
					break;
				case '4':
					resultArray[row][col] = '0';
					break;
				default:
					printf("Error Reading from file. Loading Default Image.");
					return 1;
					break;
			}
		}
	}
	
	return 0;
}








