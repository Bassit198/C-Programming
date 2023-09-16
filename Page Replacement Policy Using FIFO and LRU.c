/*
Name: Bassit Ilahi

Panther ID: 6328318

Description: This program implements 2 algorithms, FIFO and LRU, for page replacement policy. The program is intended to read and process a 
file with page numbers along with a designaated memory size specified by the user. This file and memory size is stated in the command line 
by the user. After running the algorithms, the program will output the number of page faults and the final state of memory as per instructions.

Certification: I, Bassit Ilahi, certify that the submitted documents belongs to me and is the work of no other individual or sources. 
I certify that this work is my own and was not plagiarized or replicated by any means. 
I affirm that this work does not fall into the category of plagiarism as per abiding to FIU's guidelines and policies relating to plagiarism.

Reference: Some skeleton code was provided by the instructor. The provided code was meant as a guide to follow as per intructions. Aside from 
the provided code, the remaining code and implementation was done by myself with no third party help. Additionally, I used the link below as a 
reference for further understanding of the two algorithms: https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/
*/

//imported libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//variables to be used 
int mem_size = 0;
int* memory;
int* page_refs;
int* age; 
int page_faults = 0;

// Get page references from a file and store them in an array
int get_refs(char* file_name, int mem_size) {
	int num_refs = 0, page_ref, length;
	FILE *file;

	// Open the file for reading
	file = fopen(file_name, "r");
	if (file == NULL) {
		printf("Failed to open the file.\n");
		exit(1);
	}

	// Move file pointer to the end of the file
	fseek(file, 0, SEEK_END);

	// Get the position of the file pointer, which is the length of the file
	length = ftell(file);

	// Move file pointer back to the beginning of the file
	fseek(file, 0, SEEK_SET);

	// Allocate memory for page references array
	page_refs = (int*) malloc((length) * sizeof(int));

	// Initialize page references array to -1
	for (int i = 0; i < length; ++i) {
		page_refs[i] = -1;
	}

	// Read page references from the file
	while (fscanf(file, "%d", &page_ref) == 1) {
		page_refs[num_refs++] = page_ref;
	}

	// Close the file
	fclose(file);
	return num_refs;
	}
	

//first in first out algorithm: used to determine the number of page faults replacement policy based on FIFO. 
//This method will accept 2 input parameters, file_name and mem_size attained from the command line
void fifo(char* file_name, int mem_size) {
	
	//additional variables to be used for FIFO algorithm 
    int num_refs = get_refs(file_name, mem_size);
    int fifoPage_faults = 0;
    int oldest = 0;
	
	//allocate memory dynamically to the memory variable 
	memory = (int*) malloc( mem_size * sizeof(int));
	
	//this for loop will verify if the page reference is already in memory, if it is, algorithm will move to next
    for (int i = 0; i < num_refs; ++i) {
        bool exist = false;
        for (int j = 0; j < mem_size; ++j) {
            if (memory[j] == page_refs[i]) {
                exist = true;
                break;
            }
        }

		//updates the page fault counter if the page reference does not exist 
        if (!exist) {
            memory[oldest] = page_refs[i];
            oldest = (oldest + 1) % mem_size;
            ++fifoPage_faults;
        }
    }
	
	//prints the results of the FIFO algoritm and the final memory state as per instructions 
    printf("FIFO: %d page faults\n", fifoPage_faults);
    printf("Final state of memory: ");
	
	//for loop used to print the value of each memory state for LRU 
    for (int i = 0; i < mem_size; ++i){
        printf("%d ", memory[i]);
	}
    printf("\n");
	
}//end fifo method


//least recnetly used algorithm: used to determine the number of page faults replacement policy based on LRU. 
//This method accepts 2 input parameters, file_name and mem_size attained from the command line
void lru(char* file_name, int mem_size) {
	
	//allocate memory dynamically to memory and age variable 
    memory = (int*)malloc(mem_size * sizeof(int));
    age = (int*)malloc(mem_size * sizeof(int));
	
	//additional vairable to count page references for LRU algorithm
	int num_refs = get_refs(file_name, mem_size);

	//initialization of memory memory and age (how recent) variables 
    for (int i = 0; i < mem_size; ++i) {
        memory[i] = -1;
        age[i] = -1;
    }

	//this outer for loop will process each page reference 
    for (int i = 0; i < num_refs; ++i) {
        int page_ref = page_refs[i];
        bool exist = false;

		//this inner for loop will cverify if the page reference is already in memory and if not, 
		//it will update the age (recency)
        for (int j = 0; j < mem_size; ++j) {
            if (memory[j] == page_ref) {
                exist = true;
                age[j] = i;
                break;
            }
        }

		//checks if the page exisits and if it does not, update page index counter 
        if (!exist) {
            int page_index = 0;
            for (int j = 1; j < mem_size; ++j) {
                if (age[j] < age[page_index]) {
                    page_index = j;
                }
            }
			
			//replace the LRU page reference 
            memory[page_index] = page_ref;
            age[page_index] = i;
            page_faults++;
        }
    }

	//prints the results of the LRU algoritm and the final memory state as per instructions 
    printf("LRU: %d page faults\n", page_faults);
    printf("Final state of memory: ");
	
	//for loop used to print the value of each memory state for LRU 
    for (int i = 0; i < mem_size; ++i) {
        printf("%d ", memory[i]);
    }
    printf("\n");

}//end LRU method



//main method where driver code is executed 
int main(int argc, char *argv[]) {
	
	//checks if the command line has atleast 3 arguments (program name, filename and memory size), if 
	//not, prints an error message of what is required 
	if (argc != 3) {
	printf("Usage: %s pagereffile memorysize\n", argv[0]);
	return 1;
	}
	
	// Get file name and memory size from command line arguments
	char* file_name = argv[1];
	mem_size = atoi(argv[2]);
	
	// Check if memory size is within the valid range, if not, prints an error message 
	if (mem_size < 1 || mem_size > 10) {
		printf("Error: memory size must be between 1 and 10\n");
		return 1;
	}
	
	// Call page replacement functions
	fifo(file_name, mem_size);
	lru(file_name, mem_size);

	// Free dynamically allocated memory for page references
	free(page_refs);
	free(memory);
	free(age);

	return 0;
}//end main method
