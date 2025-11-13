#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;
    int choice;
    long position;
    size_t result;

    // Try opening file in read/write mode, create if not exists
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);

                if (emp.empId <= 0) {
                    printf("Invalid Employee ID.\n");
                    break;
                }

                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);

                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                position = (emp.empId - 1) * sizeof(struct Employee);
                fseek(filePtr, position, SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);

                printf("Employee details added successfully.\n");
                break;
            }

            case 2: {
                printf("Enter Employee ID to display: ");
                scanf("%d", &emp.empId);

                if (emp.empId <= 0) {
                    printf("Invalid Employee ID.\n");
                    break;
                }

                position = (emp.empId - 1) * sizeof(struct Employee);
                fseek(filePtr, position, SEEK_SET);
                result = fread(&emp, sizeof(struct Employee), 1, filePtr);

                if (result != 1) {
                    printf("No record found for Employee ID %d.\n", emp.empId);
                } else {
                    printf("\nEmployee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                }
                break;
            }

            case 3: {
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp.empId);

                if (emp.empId <= 0) {
                    printf("Invalid Employee ID.\n");
                    break;
                }

                position = (emp.empId - 1) * sizeof(struct Employee);
                fseek(filePtr, position, SEEK_SET);
                result = fread(&emp, sizeof(struct Employee), 1, filePtr);

                if (result != 1) {
                    printf("No record found for Employee ID %d.\n", emp.empId);
                    break;
                }

                printf("Enter New Employee Name: ");
                scanf("%s", emp.empName);

                printf("Enter New Employee Salary: ");
                scanf("%f", &emp.empSalary);

                fseek(filePtr, position, SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);

                printf("Employee details updated successfully.\n");
                break;
            }

            case 4:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    fclose(filePtr);
    return 0;
}

