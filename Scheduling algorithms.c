/*
Name: Bassit Ilahi

Panther ID: 6328318

Description: This program reads a file that contains the number of processes with burst time and arrival time. The user can elect to 
utilize FCFS or SJF scheduling algorithm from the command line. The program will then read this file and calculate the average turn 
around time and waiting time for each process and produce an output with the times along with the order of execution of each processes. 

Certification: I, Bassit Ilahi, certify that the submitted documents belongs to me and is the work of no other individual or sources. 
I certify that this work is my own and was not plagiarized or replicated by any means. 
I affirm that this work does not fall into the category of plagiarism as per abiding to FIU's guidelines and policies relating to plagiarism.
*/


//imported libraries 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//definition of struct with processes to be used which includes all the times needed defined as integers 
struct Process {
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
};


/*this function will be used to calculate the fcfs (first come first served) wait time and turn around time 
for each process. The input parameter n is the number of processes whihc will be read from the file and 
also the fileProcesses parameter is of type process which was a struct defined above to include all necessary 
variables. Additionally, there are two for loops which will  be used. These loops will calculate waiting timwe
and turn around time using the processes struct from input*/
void fcfs(struct Process *fileProcesses, int n) {
    int i;
    fileProcesses[0].waitingTime = 0;

    for (i = 1; i < n; i++) {
        fileProcesses[i].waitingTime = fileProcesses[i - 1].waitingTime + fileProcesses[i - 1].burstTime;
    }

    for (i = 0; i < n; i++) {
        fileProcesses[i].turnaroundTime = fileProcesses[i].waitingTime + fileProcesses[i].burstTime;
    }
}


/*this function will be used to calculate the sjf (shortest job first) wait timw and turn around time for each 
process. This function takes 2 input, n for the number of processes and fileProcesses for the struct of type 
process. This function will create two temporary struct of type process to compare the values. The values for
each temp process will be compared and the shortest time will be updated. Additionally, this function will be 
called recursively, to increase efficiency, with the newly updated process and n*/
void sjf(struct Process *fileProcesses, int n) {
    int i, j;
    struct Process temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (fileProcesses[i].burstTime > fileProcesses[j].burstTime) {
                temp = fileProcesses[i];
                fileProcesses[i] = fileProcesses[j];
                fileProcesses[j] = temp;
            }
        }
    }

    fcfs(fileProcesses, n); //recursive call
}


/*this function is used to calculate the average turn around time for each process. The function takes 2 input, n being the 
number of processes and fileProcesses being the struct process data type defined above. This function will take each turn around
time for each process stored in the struct and add them then dividing by n since n is number of processes. After the 
calculation, this value is returned as a float*/
float averageTurnaroundTime(struct Process *fileProcesses, int n) {
    int i;
    float totalTurnaroundTime = 0;

    for (i = 0; i < n; i++) {
        totalTurnaroundTime += fileProcesses[i].turnaroundTime;
    }

    return totalTurnaroundTime / n;
}


/*this function is used to calculate the average waiting time for each process. The function takes 2 input, n being the 
number of processes and fileProcesses being the struct process data type defined above. This function will take each waiting 
time for each process stored in the struct and add them then dividing by n since n is number of processes. After the 
calculation, this value is returned as a float*/
float averageWaitingTime(struct Process *fileProcesses, int n) {
    int i;
    float totalWaitingTime = 0;

    for (i = 0; i < n; i++) {
        totalWaitingTime += fileProcesses[i].waitingTime;
    }

    return totalWaitingTime / n;
}


/*this function is used to print the order of each process based on execution. The function takes the same fileProcess 
and also n being the number of processes. A for loop is utilized to iterate n times since n is the number of processes.
Furthermore, the if statement is used to print the arrow between the processes and not at the beginning or end of printing*/
void executionOrder(struct Process *fileProcesses, int n) {
    int i;
    printf("Order of execution: ");
    for (i = 0; i < n; i++) {
        printf("P%d", i + 1);
        if (i != n - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}


//main method where driver code is executed 
int main(int argc, char *argv[]) {
	
	//uses argc to read the command line for proper command. Also prints an error message with correct usage if comman is entered incorrectly 
    if (argc != 3) {
        printf("Usage: ./bassitilahi <filename> <algorithm>\n");
        return 1;
    }
	
	//uses argv to open the file listed in the command line
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

	//fscanf statement will write the value from the file into the integer variable n defined below for further processing 
    int n;
    fscanf(file, "%d", &n);

	//dynamically assign a memory block for the fileProcesses struct. The size of the memory block will have a relation to 
	//n (the number of processes)
    struct Process *fileProcesses = malloc(n * sizeof(struct Process));

	//uses a for loop to read the file that was opened. Reads the values and assignts them to the burst time and arrival time for the 
	//struct process that was created above 
    int i;
    for (i = 0; i < n; i++) {
        fscanf(file, "%d %d", &(fileProcesses[i].burstTime), &(fileProcesses[i].arrivalTime));
    }

	//closes file after reading so as to avoid loss or corruption of data 
    fclose(file);
	
	/*reads the command line 2nd argument using argv and comparing it to verify which scheduling algorithm to use. If the argument is 
	FCFS, the fcfs function is called with input being the fileProcess with the data read from the file and n being the number of processes 
	read from the file also. Additionally, if the argument is SJF, the sfj function is called with input being the fileProcess with the data 
	read from the file and n being the number of processes read from the file. Also, an error messsage is displayed with the available 
	scheduling algorithm if an invalid entry is made*/
    if (strcmp(argv[2], "FCFS") == 0) {
        fcfs(fileProcesses, n);
        printf("Selected Scheduling Algorithm: FCFS\n");
    } else if (strcmp(argv[2], "SJF") == 0) {
        sjf(fileProcesses, n);
        printf("Selected Scheduling Algorithm: SJF\n");
    } else {
        printf("Invalid scheduling algorithm. Available options: FCFS, SJF\n");
        return 1;
    }

	//call to the execution order function to print the order of execution of process. The input used is the fileProcess which contains 
	//the data read from the file and n is the number of processes read from the file also
    executionOrder(fileProcesses, n);
	
	/*as per instructions, the average waiting time and average turn around time is displayed. These values are obtained by calling the 
	averageWaitingTime and averageTurnAroundTime functions defined above with inputs being the fileProcesses struct that contains the arrival time 
	and burst time from the file read from the command line. Furthermore, n is the number of processes and this was obtained from the file read also.*/
    printf("Average Waiting Time: %.2f\n", averageWaitingTime(fileProcesses, n));
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime(fileProcesses, n));

	//free the struc process created above to release the memory block that was assigned dynamically 
    free(fileProcesses);

    return 0;
	
}//end main 