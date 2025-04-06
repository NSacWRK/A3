/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Aksh Chand, Forbes Feild, Vickram Gill, Naval Sachar>
 * Lab instructor: <TODO: Dhara Wagh>
 * Lecture instructor: <TODO: Dhara Wagh>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"

// defined max lengths for consistency
#define FILENAME_MAX 256
#define INPUT_MAX 100
#define MEMBER_NAME_MAX 50

// retrieve input from user 
void getInput(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

int main(int argc, char *argv[]) {
    int dbInitialized = 0;
    int choice;
    char filename[FILENAME_MAX];
    char memberName[MEMBER_NAME_MAX];
    char value[INPUT_MAX];
    int tableId;

    while (1) {
        printf("\n====== Picnic Table Database Dashboard ======\n");
        printf("1. Import Database\n");
        printf("2. Export Database\n");
        printf("3. Count Entries\n");
        printf("4. Sort Tables\n");
        printf("5. Edit Table Entry\n");
        printf("6. Generate Reports\n");
        printf("7. Exit\n");
        
        printf("Enter your choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        if (choice != 1 && !dbInitialized) {
            printf("Please import the database first (Option 1).\n");
            continue;
        }

        switch (choice) {
            case 1:
                getInput("Enter CSV filename to import: ", filename, sizeof(filename));
                if (strlen(filename) == 0) {
                    printf("Filename cannot be empty.\n");
                    break;
                }
                importDB(filename);
                dbInitialized = 1;
                break;

            case 2:
                getInput("Enter filename to export to: ", filename, sizeof(filename));
                exportDB(filename);
                break;

            case 3:
                getInput("Enter member name to count: ", memberName, sizeof(memberName));
                getInput("Enter value to count: ", value, sizeof(value));
                printf("Found %d entries with %s = %s\n", 
                      countEntries(memberName, value), memberName, value);
                break;

            case 4:
                getInput("Enter member name to sort by: ", memberName, sizeof(memberName));
                sortByMember(memberName);
                break;

            case 5:
                printf("Enter tableId to edit: ");
                if (scanf("%d", &tableId) != 1) {
                    printf("Invalid table ID.\n");
                    while (getchar() != '\n');
                    break;
                }
                getchar();
                getInput("Enter member name to edit: ", memberName, sizeof(memberName));
                getInput("Enter new value: ", value, sizeof(value));
                editTableEntry(tableId, memberName, value);
                break;

            case 6:
                printf("\n== Report Options ==\n");
                printf("1. By Ward\n2. By Neighbourhood\n3. Back\n");
                printf("Enter report type: ");
                int reportType;
                if (scanf("%d", &reportType) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                getchar();
                switch (reportType) {
                    case 1: reportByWard(); break;
                    case 2: reportByNeighbourhood(); break;
                    default: printf("Returning to main menu.\n");
                }
                break;

            case 7:
                if (dbInitialized) freeDB();
                printf("Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter 1-7.\n");
        }
    }
    return 0;
}