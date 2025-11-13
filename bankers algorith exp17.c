#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES] = {3, 3, 2}; // Available resources
int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[MAX_PROCESSES][MAX_RESOURCES];

int is_safe();
int request_resources(int process_num, int request[]);

void calculate_need() {
    int i;
    int j;
    for (i = 0; i < MAX_PROCESSES; i++) {
        for (j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int request_resources(int process_num, int request[]) {
    int i;

    // Check if request can be granted
    for (i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process_num][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return 0;
        }
        if (request[i] > available[i]) {
            printf("Error: Resources not available right now.\n");
            return 0;
        }
    }

    // Try to allocate temporarily
    for (i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_num][i] += request[i];
        need[process_num][i] -= request[i];
    }

    // Check if system is in safe state
    if (is_safe()) {
        return 1; // Safe to grant
    } else {
        // Rollback allocation
        for (i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_num][i] -= request[i];
            need[process_num][i] += request[i];
        }
        return 0; // Not safe
    }
}

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int i;
    int j;
    int k;
    int count;
    int found;

    // Initialize work = available
    for (i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Initialize all processes as unfinished
    for (i = 0; i < MAX_PROCESSES; i++) {
        finish[i] = 0;
    }

    count = 0;
    while (count < MAX_PROCESSES) {
        found = 0;
        for (i = 0; i < MAX_PROCESSES; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == MAX_RESOURCES) {
                    for (k = 0; k < MAX_RESOURCES; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if (found == 0) {
            return 0; // Not a safe state
        }
    }

    return 1; // Safe state
}

int main() {
    int process_num;
    int request[MAX_RESOURCES];
    int i;

    calculate_need();

    printf("Enter process number (0 to 4): ");
    scanf("%d", &process_num);

    if (process_num < 0 || process_num >= MAX_PROCESSES) {
        printf("Invalid process number.\n");
        return 1;
    }

    printf("Enter resource request (e.g., 0 1 0): ");
    for (i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }

    if (request_resources(process_num, request)) {
        printf("Request granted. System is in a safe state.\n");
    } else {
        printf("Request denied. System would enter an unsafe state.\n");
    }

    return 0;
}

