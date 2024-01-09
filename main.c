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
        printf("1. Add new employee\n");
        printf("2. Remove employee\n");
        printf("3. Update employee\n");
        printf("4. Search employee\n");
        printf("5. Print all employees\n");
        printf("6. Exit\n");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            Employee employee;
            printf("Enter name: ");
            scanf("%s", employee.name);
            printf("Enter phone: ");
            scanf("%s", employee.phone);
            printf("Enter email: ");
            scanf("%s", employee.email);
            printf("Enter address: ");
            scanf("%s", employee.address);
            printf("Enter age: ");
            scanf("%d", &employee.age);
            printf("Enter role: ");
            scanf("%s", employee.role);

            addEmployee(&employeeList, employee);
        } else if (choice == 2) {
                printf("Enter any user information (Role, Phone number, etc.) : ");
                char data[MAX_ADDRESS];
                scanf("%s", data);
                int index = searchEmployee(employeeList, data);
                if (index == -1) {
                    printf("Employee not found!\n");
                } else {
                    removeEmployee(&employeeList, index);
                }
        } else if (choice == 3) {
            printf("Enter any user information (Role, Phone number, etc.) : ");
            char data[MAX_ADDRESS];
            scanf("%s", data);

            int index = searchEmployee(employeeList, data);
            if (index == -1) {
                printf("Employee not found!\n");
            } else {
                Employee employee;
                printf("Enter name: ");
                scanf("%s", employee.name);
                printf("Enter phone: ");
                scanf("%s", employee.phone);
                printf("Enter email: ");
                scanf("%s", employee.email);
                printf("Enter address: ");
                scanf("%s", employee.address);
                printf("Enter age: ");
                scanf("%d", &employee.age);
                printf("Enter role: ");
                scanf("%s", employee.role);

                updateEmployee(&employeeList, index, employee);
            }
        } else if (choice == 4) {
            printf("Enter any user information (Role, Phone number, etc.) : ");
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
