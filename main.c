#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int fd = open("/dev/random",O_RDONLY);
	int sizeOfArray = 10;
	char * fileName = "mynumbersfile";
	
	if (fd < 0){
		printf("Could not open /dev/random\n");
	}
	else{
		printf("Successfully opened /dev/random\n");
	}

	int * numbersArray = calloc(sizeOfArray, sizeof(int));
	int bytesRead = read(fd, numbersArray, sizeOfArray * sizeof(int));

	if(bytesRead < 0){
		printf("Error reading from /dev/random\n");
	}
	else{
		printf("Successfully read %d bytes (%d integers) from /dev/random\n", sizeOfArray * sizeof(int), sizeOfArray);
	}
	close(fd);

	printf("~~~Printing the random numbers~~~\n");
	for (int i = 0; i < sizeOfArray; i++){
		printf("%d\n", numbersArray[i]);
	}

	fd = open(fileName, O_RDWR | O_CREAT, 111111111);
	if(fd < 0){
		printf("Error opening %s\n", fileName);
	}
	else{
		printf("Successfully opened %s\n", fileName);
	}
	printf("~~~Writing to %s~~~\n", fileName);
	bytesRead = write(fd, numbersArray, sizeOfArray * sizeof(int));
	if(bytesRead < 0){
		printf("Error writing to %s\n", fileName);
	}
	else{
		printf("Successfully wrote %d bytes (%d integers) to %s\n", sizeOfArray * sizeof(int), sizeOfArray, fileName);
	}
	close(fd);

	fd = open(fileName,O_RDWR);
	if(fd < 0){
		printf("Error opening %s\n", fileName);
	}
	else{
		printf("Successfully opened %s\n", fileName);
	}

	printf("~~~Reading from %s~~~\n", fileName);
	bytesRead = read(fd, numbersArray, sizeOfArray * sizeof(int));
	if(bytesRead < 0){
		printf("Error reading file\n");
	}
	else{
		printf("Successfully read %d bytes (%d integers) from %s\n", sizeOfArray * sizeof(int), sizeOfArray, fileName);
	}
	printf("~~~Printing the random numbers~~~\n");
	for (int i = 0; i < sizeOfArray; i++){
		printf("%d\n", numbersArray[i]);
	}
	close(fd);
	return 0;
}