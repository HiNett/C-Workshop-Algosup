/*
 * Create a program that help AlgoWork Company to create a list of employees.
 * The program should be able to:
 * - Add new employee
 * - Remove employee
 * - Update employee
 * - Search employee
 * - Print all employees
 *
 * The contact are made of:
 * - Name
 * - Phone
 * - Email
 * - Address
 * - Age
 * - Role
 *
 * The program should be able to save the data in a file and load it when the program starts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_EMAIL 50
#define MAX_ADDRESS 100
#define MAX_ROLE 50
#define MAX_EMPLOYEES 100

typedef struct {
    char id[10];
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    char address[MAX_ADDRESS];
    int age;
    char role[MAX_ROLE];
} Employee;

typedef struct {
    Employee employees[MAX_EMPLOYEES];
    int count;
} EmployeeList;

void trimNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void readStringWithSpaces(char *output, int maxLen) {
    fgets(output, maxLen, stdin);
    trimNewline(output);
}

int generateEmployeeId(EmployeeList *list) {
    int newId = 1;
    if (list->count > 0) {
        sscanf(list->employees[list->count - 1].id, "%d", &newId);
        newId++;
    }
    return newId;
}

void printEmployee(Employee employee) {
    printf("ID : %s\n", employee.id);
    printf("Name: %s\n", employee.name);
    printf("Phone: %s\n", employee.phone);
    printf("Email: %s\n", employee.email);
    printf("Address: %s\n", employee.address);
    printf("Age: %d\n", employee.age);
    printf("Role: %s\n", employee.role);
}

void printEmployeeList(EmployeeList employeeList) {
    for (int i = 0; i < employeeList.count; ++i) {
        printf("Employee %d:\n", i + 1);
        printEmployee(employeeList.employees[i]);
    }
}

void addEmployee(EmployeeList *employeeList, Employee employee) {
    employeeList->employees[employeeList->count] = employee;
    employeeList->count++;
}

void removeEmployee(EmployeeList *employeeList, int index) {
    for (int i = index; i < employeeList->count - 1; ++i) {
        employeeList->employees[i] = employeeList->employees[i + 1];
    }
    employeeList->count--;
}

void updateEmployee(EmployeeList *employeeList, int index, Employee employee) {
    employeeList->employees[index] = employee;
}

int searchEmployee(EmployeeList employeeList, char *data) {
    for (int i = 0; i < employeeList.count; ++i) {
        if (strcmp(employeeList.employees[i].name, data) == 0 ||
            strcmp(employeeList.employees[i].id, data) == 0 ||
            strcmp(employeeList.employees[i].phone, data) == 0 ||
            strcmp(employeeList.employees[i].email, data) == 0 ||
            strcmp(employeeList.employees[i].address, data) == 0 ||
            employeeList.employees[i].age == atoi(data) ||
            strcmp(employeeList.employees[i].role, data) == 0) {
            return i;
        }
    }
    return -1;
}

void saveEmployeeList(EmployeeList employeeList) {
    FILE *file = fopen("../employees.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < employeeList.count; ++i) {
        fprintf(file, "%s\n", employeeList.employees[i].id);
        fprintf(file, "%s\n", employeeList.employees[i].name);
        fprintf(file, "%s\n", employeeList.employees[i].phone);
        fprintf(file, "%s\n", employeeList.employees[i].email);
        fprintf(file, "%s\n", employeeList.employees[i].address);
        fprintf(file, "%d\n", employeeList.employees[i].age);
        fprintf(file, "%s\n", employeeList.employees[i].role);
    }

    fclose(file);
}

EmployeeList loadEmployeeList() {
    EmployeeList employeeList;
    employeeList.count = 0;

    FILE *file = fopen("../employees.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char id[10];
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    char address[MAX_ADDRESS];
    int age;
    char role[MAX_ROLE];

    while (fscanf(file, "%s\n", name) != EOF) {
        strcpy(employeeList.employees[employeeList.count].name, name);
        fscanf(file, "%s\n", phone);
        strcpy(employeeList.employees[employeeList.count].phone, phone);
        fscanf(file, "%s\n", email);
        strcpy(employeeList.employees[employeeList.count].email, email);
        fscanf(file, "%s\n", address);
        strcpy(employeeList.employees[employeeList.count].address, address);
        fscanf(file, "%d\n", &age);
        employeeList.employees[employeeList.count].age = age;
        fscanf(file, "%s\n", role);
        strcpy(employeeList.employees[employeeList.count].role, role);

        employeeList.count++;
    }

    fclose(file);

    return employeeList;
}

int main() {
    EmployeeList employeeList = loadEmployeeList();

    while (true) {
        #ifdef _WIN32
                system("cls");
        #else
                system(“clear”);
        #endif
        printf(" _____ _____ _____ _____ _____\n");
        printf("|   __|   __|  _  |_   _|   __|\n");
        printf("|   __|__   |     | | | |__   |\n");
        printf("|_____|_____|__|__| |_| |_____|\n\n\n\n");
        printf("\n\t **** Welcome to Contact Management System ****");
        printf("\n\n\n\t\t\tMAIN MENU");
        printf("\n\t\t=====================");
        printf("\n\t\t[1] Add a new Employee");
        printf("\n\t\t[2] Remove an employee");
        printf("\n\t\t[3] Edit an employee");
        printf("\n\t\t[4] Search an employee");
        printf("\n\t\t[5] Print all employees");
        printf("\n\t\t[6] Exit");
        printf("\n\t\t=================\n\t\t");

        int choice;
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 1) {
            Employee employee;
            int newId = generateEmployeeId(&employeeList);
            snprintf(employee.id, sizeof(employee.id), "%d", newId);

            #ifdef _WIN32
                        system("cls");
            #else
                        system(“clear”);
            #endif
            printf("\n\n\n\t\t\tEmployee Creation");
            printf("\n\t\t=====================");
            printf("\n\t\tEnter name: ");
            readStringWithSpaces(employee.name, MAX_NAME);
            printf("\n\t\tEnter phone: ");
            readStringWithSpaces(employee.phone, MAX_PHONE);
            printf("\n\t\tEnter email: ");
            readStringWithSpaces(employee.email, MAX_EMAIL);
            printf("\n\t\tEnter address: ");
            readStringWithSpaces(employee.address, MAX_ADDRESS);
            printf("\n\t\tEnter age: ");
            scanf("%d", &employee.age);
            getchar();
            printf("\n\t\tEnter role: ");
            readStringWithSpaces(employee.role, MAX_ROLE);
            printf("\n\t\t=====================");

            addEmployee(&employeeList, employee);
        } else if (choice == 2) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system(“clear”);
            #endif
            printf("\n\n\n\t\t\tEmployee Deletion");
            printf("\n\t\t=====================");
            printf("\n\t\tEnter any user information (Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);
            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("\n\t\tEmployee not found!\n");
            } else {
                removeEmployee(&employeeList, index);
            }
        } else if (choice == 3) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system(“clear”);
            #endif
            printf("\n\n\n\t\t\tEmployee Edition");
            printf("\n\t\t=====================");
            printf("Enter any user information (Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);

            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("Employee not found!\n");
            } else {
                #ifdef _WIN32
                                system("cls");
                #else
                                system(“clear”);
                #endif
                Employee employee;
                printf("\n\n\n\t\t\tEdit Employee");
                printf("\n\t\t=====================");
                printf("\n\t\tEnter name: ");
                readStringWithSpaces(employee.name, MAX_NAME);
                printf("\n\t\tEnter phone: ");
                readStringWithSpaces(employee.phone, MAX_PHONE);
                printf("\n\t\tEnter email: ");
                readStringWithSpaces(employee.email, MAX_EMAIL);
                printf("\n\t\tEnter address: ");
                readStringWithSpaces(employee.address, MAX_ADDRESS);
                printf("\n\t\tEnter age: ");
                scanf("%d", &employee.age);
                getchar();
                printf("\n\t\tEnter role: ");
                readStringWithSpaces(employee.role, MAX_ROLE);
                printf("\n\t\t=====================");

                updateEmployee(&employeeList, index, employee);
            }
        } else if (choice == 4) {
            #ifdef _WIN32
                        system("cls");
            #else
                        system(“clear”);
            #endif
            printf("\n\n\n\t\t\tEmployee Search");
            printf("\n\t\t===============================\n");
            printf("\t\tEnter any user information \n\t\t(Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);

            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("Employee not found!\n");
            } else {
                printEmployee(employeeList.employees[index]);
            }
        } else if (choice == 5) {
            printEmployeeList(employeeList);
        } else if (choice == 6) {
            saveEmployeeList(employeeList);
            break;
        }
    }
}

// Path: main.c
