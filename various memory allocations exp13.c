#include <stdio.h>

// Function for Best Fit algorithm
void bestfit(int mp[], int p[], int m, int n) {
    int i;
    int j = 0;

    for (i = 0; i < n && j < m; i++) {
        if (mp[i] >= p[j]) {
            printf("\nProcess %d (%d KB) fits in partition %d (%d KB)", j + 1, p[j], i + 1, mp[i]);
            mp[i] = mp[i] - p[j];
            j++;
            i = -1; // restart checking from beginning
        }
    }

    for (i = j; i < m; i++) {
        printf("\nProcess %d (%d KB) must wait for memory", i + 1, p[i]);
    }
}

// Function for ascending sort
void sort(int a[], int n) {
    int i, j, t;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i] < a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Function for descending sort
void rsort(int a[], int n) {
    int i, j, t;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// First Fit
void firstfit(int mp[], int p[], int m, int n) {
    int i, j;

    for (j = 0; j < m; j++) {
        for (i = 0; i < n; i++) {
            if (mp[i] >= p[j]) {
                printf("\nProcess %d (%d KB) fits in partition %d (%d KB)", j + 1, p[j], i + 1, mp[i]);
                mp[i] -= p[j];
                break;
            }
        }
        if (i == n) {
            printf("\nProcess %d (%d KB) must wait for memory", j + 1, p[j]);
        }
    }
}

// Worst Fit
void worstfit(int mp[], int p[], int m, int n) {
    int temp[20];
    int i;

    for (i = 0; i < n; i++) {
        temp[i] = mp[i];
    }

    rsort(temp, n);
    bestfit(temp, p, m, n);
}

// Main function
int main() {
    int m;
    int n;
    int mp[20];
    int p[20];
    int ch;
    int i;

    printf("Number of memory partitions: ");
    scanf("%d", &n);

    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter the memory partitions (KB):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }

    printf("Enter the process sizes (KB):\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            firstfit(mp, p, m, n);
            break;
        case 2:
            sort(mp, n);
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice");
            break;
    }

    return 0;
}

