#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../DB.h"
//#include "DB.c"

int main(){

    int countEntryTest;

    printf("*****************************\n");
    printf("Testing ImportDB Function\n");
    importDB("PicnicTableSmall.csv");

    printf("*****************************");
    printf("\nTesting countEntries Function\n");
    countEntryTest = countEntries("Surface Material", "Wood");
    printf("Total Count of Entries for Wood: %d\n", countEntryTest);

    printf("*****************************");
    printf("\nTesting sortByMember Function\n");
    sortByMember("latitude");

    printf("*****************************");
    printf("\nTesting editTableEntry Function\n");
    editTableEntry(3, "Surface Material", "Metal");

    printf("*****************************");
    printf("\nTesting reportbyNeighbourhood Function\n");
    reportByNeighbourhood();

    printf("*****************************");
    printf("\nTesting reportByWard Function\n");
    reportByWard();

    printf("*****************************");
    printf("\nTesting exportDB Function\n");
    exportDB("exportDB_test_PicnicTableSmall.csv");

    printf("*****************************\n");
    printf("\nFree All Database Memory\n");
    freeDB();
    return 0;

}