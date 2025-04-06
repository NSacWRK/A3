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

//You may include other original headers as you see fit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"

int main(int argc, char *argv[]) {
    int dbInitialized = 0;
    int choice;
    char filename[100];
    char memberName[50];
    char value[100];
    int tableId;

    while (1) {
        printf("\n====== Picnic Table Database Dashboard ======\n");
        printf("1. Import Database\n");
        printf("2. Export Database\n");
        printf("3. Count Entries\n");
        printf("4. Sort By\n");
        printf("5. Edit Entry\n");
        printf("6. Report (By Ward or Neighbourhood)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        if (choice != 1 && !dbInitialized) {
            printf("Please import the database first before using this option.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter CSV filename to import: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                importDB(filename);
                dbInitialized = 1;
                break;

            case 2:
                printf("Enter filename to export to: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                exportDB(filename);
                break;

            case 3:
                printf("Enter member name to count (e.g., ward, tableId, streetAvenue): ");
                fgets(memberName, sizeof(memberName), stdin);
                memberName[strcspn(memberName, "\n")] = 0;

                printf("Enter value to count: ");
                fgets(value, sizeof(value), stdin);
                value[strcspn(value, "\n")] = 0;

                printf("Found %d entries with %s = %s\n", countEntries(memberName, value), memberName, value);
                break;

            case 4:
                printf("Enter member name to sort by (e.g., ward, tableId, streetAvenue): ");
                fgets(memberName, sizeof(memberName), stdin);
                memberName[strcspn(memberName, "\n")] = 0;

                sortByMember(memberName);
                break;

            case 5:
                printf("Enter tableId to edit: ");
                scanf("%d", &tableId);
                getchar();

                printf("Enter member name to edit: ");
                fgets(memberName, sizeof(memberName), stdin);
                memberName[strcspn(memberName, "\n")] = 0;

                printf("Enter new value: ");
                fgets(value, sizeof(value), stdin);
                value[strcspn(value, "\n")] = 0;

                editTableEntry(tableId, memberName, value);
                break;

            case 6:
                printf("Report by (1 = Ward, 2 = Neighbourhood): ");
                int reportType;
                scanf("%d", &reportType);
                getchar();

                if (reportType == 1)
                    reportByWard();
                else if (reportType == 2)
                    reportByNeighbourhood();
                else
                    printf("Invalid report type.\n");
                break;

            case 7:
                printf("Exiting. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
};