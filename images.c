//Authors: Kellen Strinden and Peter Hippert
//Date Due: 5/7/2024
//File Name: finalProject.c
//Purpose: CS 135 Final Project

#include <stdio.h>

#define MAX_RESOLUTION 500
#define DEFAULT_FILE "default.txt"
#define FILE_NAME_MAX 50

int mainMenu();
int editMenu();
int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, int resultArray[][maxRes]);
void newImage(FILE* fp, int size);
void displayImage(int imageX, int imageY, int maxRes, int imgArray[][maxRes],int cropCondition);
void cropCurrentImage();
void dimCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes], int imgEdited[][maxRes]);
void brightenCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes], int imgEdited[][maxRes]);
void rotateCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes], int imgEdited[][maxRes]);
void saveImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]);

int main(){
	//Variable Declaration
	int userChoice, editChoice, lengthX, lengthY, imgProcessTest, imageData[MAX_RESOLUTION][MAX_RESOLUTION], imageEdited[MAX_RESOLUTION][MAX_RESOLUTION];
	FILE* currentImage = fopen(DEFAULT_FILE, "r");
	
	//Default Image Verification and Processing
	if(currentImage == NULL){
		printf("Could not open default image file. Exiting Program.");
		return 0;
	}
	
	imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageData);
	fclose(currentImage);
	
	//Main Program Handling
	printf("--------------------------------------------------\n");
	printf("Welcome!\n");
	printf("--------------------------------------------------\n");
	
	do{
		userChoice = mainMenu();
		
		switch(userChoice){
			case 1:
				//Load New Image
				newImage(currentImage, FILE_NAME_MAX);
				imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageData);
				fclose(currentImage);
				
				//Checks load status of the image. If loading fails, the default file is loaded
				if(imgProcessTest == 1){
					printf("Image Loading Error. Loading Default File\n");
					printf("--------------------------------------------------\n");
					currentImage = fopen(DEFAULT_FILE, "r");
					imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageData);
					fclose(currentImage);
				}
				break;
			case 2:
				//Display Current Image
				printf("Displaying Current Image.\n\n");
				displayImage(lengthX, lengthY, MAX_RESOLUTION, imageData, 0);
				break;
			case 3:
				//Edit Current Image
				editChoice = editMenu();
				
				//Determines function based on choice from editMenu()
				switch(editChoice){
					case 1:
						//Crop Current Image
						cropCurrentImage(lengthX, lengthY, MAX_RESOLUTION, imageData, imageEdited);
						break;
					case 2:
						//Dim Current Image
						printf("Dimming Current Image...\n\n");
						dimCurrentImage(lengthX, lengthY, MAX_RESOLUTION, imageData, imageEdited);
						displayImage(lengthX, lengthY, MAX_RESOLUTION, imageEdited, 0);
						saveImage(lengthX, lengthY, MAX_RESOLUTION, imageEdited);
						break;
					case 3:
						//Brighten Current Image
						printf("Brightening Current Image...\n\n");
						brightenCurrentImage(lengthX, lengthY, MAX_RESOLUTION, imageData, imageEdited);
						displayImage(lengthX, lengthY, MAX_RESOLUTION, imageEdited, 0);
						saveImage(lengthX, lengthY, MAX_RESOLUTION, imageEdited);
						break;
					case 4:
						//Rotate Current Image
						rotateCurrentImage(lengthX, lengthY, MAX_RESOLUTION, imageData, imageEdited);
						displayImage(lengthY, lengthX, MAX_RESOLUTION, imageEdited, 0);
						saveImage(lengthY, lengthX, MAX_RESOLUTION, imageEdited);
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
	
	//Prompts user to choose a menu option
	printf("Please select an option:\n");
	printf("  1: Load Current Image\n");
	printf("  2: Display Current Image\n");
	printf("  3: Edit Image\n");
	printf("  4: Exit\n");
	
	printf("Choice: ");
	scanf("%d", &choice);
	printf("--------------------------------------------------\n");
	
	//Returns the integer value of the user's choice for menu logic
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

int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, int resultArray[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col, result;
	char tempArray[maxRes][maxRes];
	
	//Resets the image arrays to null state
	for(row = 0; row < maxRes; row++){
		for(col = 0; col < maxRes; col++){
			resultArray[row][col] = '\0';
		}
	}
	
	//Scans through the current file to get raw image data
	for(row = 0; row < maxRes; row++){
		fgets(tempArray[row], (maxRes + 1), filePtr);
	}
	
	//Calculates the image length and width
	for(row = 0; (tempArray[row][0] != '\0')&&(tempArray[row][0] != '\n'); row++){}
	*imageY = row;
	
	for(col = 0; (tempArray[0][col] != '\0')&&(tempArray[0][col] != '\n'); col++){}
	*imageX = col;
	
	//Processes the image into the desired format
	for(row = 0; row < *imageY; row++){
		for(col = 0; col < *imageX; col++){
		      	switch(tempArray[row][col]){
			        case '0':
			        	resultArray[row][col] = 0;
			        	break;
			        case '1':
			        	resultArray[row][col] = 1;
			        	break;
			        case '2':
					resultArray[row][col] = 2;
					break;
			        case '3':
					resultArray[row][col] = 3;
					break;
			        case '4':
					resultArray[row][col] = 4;
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
	
	//Prompts user to enter a file name
	printf("Enter file name (i.e. example.txt): ");
	scanf("%s", fileName);
	
	//Attempts to open the user-provided file and verifies it
	fp = fopen(fileName, "r");
	
	printf("\n");
	if (fp == NULL){
		printf("Invalid File. Opening Default File.\n");
		printf("--------------------------------------------------\n");
		fp = fopen(DEFAULT_FILE, "r");
	}else if(fp != NULL){
		printf("File Loaded Successfully.\n");
		printf("--------------------------------------------------\n");
	}
}

void displayImage(int imageX, int imageY, int maxRes, int imgArray[][maxRes],int cropCondition){
	//Written by Peter Hippert
	
	//Check to see if display is within crop function. Special Formatting needed if yes
	if (cropCondition==1) {
		//Displays image for the cropCurrentImage function
		for (int rowInd = 0;rowInd < imageY; rowInd++){
			if (rowInd==imageY-1){
				printf("%d",imageY);
			}else if (rowInd>0&&rowInd<imageY){
				printf(" ");
			}
			
			for (int colInd= 0;colInd < imageX; colInd++){
				switch(imgArray[rowInd][colInd]){
					case 0:
						printf("  ");
						break;
					case 1:
						printf(". ");
						break;
					case 2:
						printf("o ");
						break;
					case 3:
						printf("O ");
						break;
					case 4:
						printf("0 ");
						break;
					default:
						break;
				}
			}

			printf("\n");
		}
	}else{
		//Displays the current image for all other use cases
		for (int rowInd = 0;rowInd < imageY; rowInd++){
			for (int colInd= 0;colInd < imageX; colInd++){
				switch(imgArray[rowInd][colInd]){
					case 0:
						printf("  ");
						break;
					case 1:
						printf(". ");
						break;
					case 2:
						printf("o ");
						break;
					case 3:
						printf("O ");
						break;
					case 4:
						printf("0 ");
						break;
					default:
						break;
				}
			}

			printf("\n");
		}
	}
	printf("\n--------------------------------------------------\n");
}

void cropCurrentImage(int row,int column,int maxRes,int ogArray[][maxRes],int newArray[][maxRes]){
	//Written by Peter Hippert
	
	int minCol,maxCol,minRow,maxRow;
	int rowCount=0,colCount=0;
	
	//Shows the column number of the left and right boundaries
	printf(" 1");
	for (int i = 0; i<((row-2)*2)+1;i++){
		printf(" ");
	}
	printf("%d\n",row);
	
	//Shows the row number of the top and bottom boundaries and displays the unedited image
	printf("1");
	displayImage(row, column, MAX_RESOLUTION, ogArray, 1);
	
	//Prompts user for cropping choices
	printf("The image you want to crop is %d x %d.\n", row, column);
	printf("The row and column values start in the upper lefthand corner.\n\n");
	printf("Which column do you want to be the new left side? ");
	scanf("%d",&minCol);
	printf("\nWhich column do you want to be the new right side? ");
	scanf("%d",&maxCol);
	printf("\nWhich row do you want to be the new top? ");
	scanf("%d",&minRow);
	printf("\nWhich row do you want to be the new bottom? ");
	scanf("%d",&maxRow);
	
	//Fills the cropped image array with cropped image values
	for (int i = minRow-1;i<maxRow;i++){
		colCount = 0;
		for (int j = minCol-1;j<maxCol;j++){
			newArray[rowCount][colCount] = ogArray[i][j]; 
			colCount++;
		}
		rowCount++;
	}
	
	//Displays cropped image to user and prompts them to save the image
	printf("\nCropped Image:\n\n");
	displayImage(rowCount,colCount,MAX_RESOLUTION,newArray,0);
	saveImage(rowCount,colCount,maxRes,newArray);
}

void dimCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes], int imgEdited[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col;

  	for(row = 0; row < lengthY; row++){
    		for(col = 0; col < lengthX; col++){
      			//Reduces the integer value of every array element by one
      			imgEdited[row][col] = imgArray[row][col] - 1;

			//Checks the new integer values and sets them to the minimum value if it is exceeded
      			if(imgEdited[row][col] < 0){
        			imgEdited[row][col] = 0;
      			}
    		}
  	}
}

void brightenCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes], int imgEdited[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col;

  	for(row = 0; row < lengthY; row++){
    		for(col = 0; col < lengthX; col++){
      			//Increases the integer value of every array element by one
      			imgEdited[row][col] = imgArray[row][col] + 1;

			//Checks the new integer values and sets them to the maximum value if it is exceeded
      			if(imgEdited[row][col] > 4){
        			imgEdited[row][col] = 4;
      			}
    		}
  	}
}

void rotateCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes], int imgEdited[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col;
	
	//Fills the edited image array with the rotated values of the original array
	for(col = 0; col < lengthX; col++){
		for(row = 0; row < lengthY; row++){
			imgEdited[col][row] = imgArray[lengthY - 1 - row][col];
		}
	}
}

void saveImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]){
	//Written by Kellen Strinden
	
	char fileName[FILE_NAME_MAX], saveChoice;
	int row, col;
	
	//Prompts the user to save the image
	printf("Would you like to save the edited image (Y/N): ");
	scanf(" %c", &saveChoice);
	
	//Determines whether or not to save the image based on user input
	switch(saveChoice){
		case 'Y':
		case 'y':
			printf("Enter the save file name: ");
			scanf("%s", fileName);
			
			FILE* saveFile = fopen(fileName, "w");
			
			for(row = 0; row < lengthY; row++){
				for(col = 0; col < lengthX; col++){
					fprintf(saveFile, "%d", imgArray[row][col]);
				}
				fprintf(saveFile, "\n");
			}
			fclose(saveFile);
			break;
		default:
			break;
	}
	
	printf("--------------------------------------------------\n");
}
