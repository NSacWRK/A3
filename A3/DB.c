/* DB.c
 *
 * This file contains the implementation of core functions for managing a picnic table database system.
 * It includes functionality for importing/exporting data from CSV files, counting and editing entries based on various attributes,
 * sorting, generating reports grouped by neighborhoods or wards, and properly freeing memory used by the database.
 * All database interactions rely on lookup tables
 *
 * Author: <TODO: Aksh Chand, Forbes Fields, Vickram Gill, Naval Sachar>
 * Lab instructor: <TODO: Dhara Wagh>
 * Lecture instructor: <TODO: Dhara Wagh>
 */

 #include "DB.h"       /* Import the public database header. */
 #include "DB_impl.h"  /* Import the private database header */
 
 // This function will take the name of a .csv file as parameter and creates and populates the Database
 // with the correpsonding data set information
 void importDB(char *filename){
     //nav works in this 
     return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
 }
 
 // This Function takes the name of a .csv file as paramter and creates a .csv file containing the information of the Database
 // (exported .csv file must be exactly the same as the original .csv file from which the Database was created)
 void exportDB(char *filename){
     //nav works on this 
     return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
 }
 
 // Count Entries (Currently Empty Function)
 // This function takes the name of a member of the picniTable entry and a value for that member as paramter and returns 
 // the number of entries in the picnicTable which have that value in the memberName
 
 /*The function must be implemented for:
  *   1- Table Type
  *   2- Surface Material
  *   3- Structural Material
  *   4 - Neghborhood ID
  *   4- Neighborhood Name
  *   5- Ward
  */
 int countEntries(char *memberName, char * value){
     //return 0; // Return for now - as we're creating empty functions (will be worked on later) for MS1
     int i,j,nbhdID,entryCount;
     entryCount = 0;
 
     if(Db == NULL || Db->picnicTableTable == NULL){
         printf("Error - No Database Available, or No Elements Within PicnicTable Available");
         return 0;
     }
 
     for (i = 0; i < Db->picnicTableTable->picnicT_ElementCount; i++){
         PicnicTableEntry picTEntry;
         picTEntry = Db->picnicTableTable->picnicT_entries[i];
 
         // #1 Table Type (UNDER TABLE STRUCT - (Look at CMPT_201_Database_Description PDF - Table Relationships))
         if(strcmp(memberName, "Table Type") == 0){
             for(j=0; j < Db->tableTypeTable->tableT_ElementCount; j++){
                 if(Db->tableTypeTable->tableT_entries[j].code == picTEntry.tableTypeId && strcmp(Db->tableTypeTable->tableT_entries[j].value, value) == 0){
                     entryCount++;
                 }
                 
             }
         }
         // #2) Surface Material (UNDER TABLE STRUCT -(Look at CMPT_201_Database_Description PDF - Table Relationships))
         else if (strcmp(memberName, "Surface Material") == 0){
             for(j=0; j < Db->surfaceMaterialTable->tableT_ElementCount; j++){
                 if(Db->surfaceMaterialTable->tableT_entries[j].code == picTEntry.surfaceMaterialId && strcmp(Db->surfaceMaterialTable->tableT_entries[j].value, value) == 0){
                     entryCount++;
                 }
             }
         }
         // #3) Structural Material (UNDER TABLE STRUCT - (Look at CMPT_201_Database_Description PDF - Table Relationships))
         else if (strcmp(memberName, "Structural Material") == 0){
             for(j=0; j < Db->structuralMaterialTable->tableT_ElementCount; j++){
                 if(Db->structuralMaterialTable->tableT_entries[j].code == picTEntry.structuralMaterialId && strcmp(Db->structuralMaterialTable->tableT_entries[j].value, value) == 0){
                     entryCount++;
                 }
             }
         }
 
         // # 4) Neighbourhood ID (Look at CMPT_201_Database_Description PDF - Table Relationships)
         else if (strcmp(memberName, "Neighbourhood Id") == 0){
             nbhdID = atoi(value);
             if(picTEntry.neighbhdId == nbhdID){
                 entryCount++;
             }
         }
 
         // #5) Neighbourhood Name (NEIGHBOURHOOD STRUCT - (Look at CMPT_201_Database_Description PDF - Table Relationships))
         else if (strcmp(memberName, "Neighbourhood Name") == 0){
             for(j=0; j < Db->neighborhoodTable->neighbourhoodT_ElementCount; j++){
                 if(Db->neighborhoodTable->neighbourhoodT_entries[j].code == picTEntry.neighbhdId && strcmp(Db->neighborhoodTable->neighbourhoodT_entries[j].value, value) == 0){
                     entryCount++;
                 }
             }
         }
 
         // #6) Ward (Within PicnicTable / picTEntry directly)
         else if (strcmp(memberName, "Ward") == 0){
             if(strcmp(picTEntry.ward, value) == 0){
                 entryCount++;
             }
         }
     }
     return entryCount;
 }
 
 // SortByMember Function
 // Tis function takes the name of a member of the picnicTable entry as an argument and sorts the table in ascending order
 // f the entry values of that member 
 void sortByMember(char *memberName){
     //this one nav will do 
     return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
 }
 
 // Edit Table Entry Functions 
 // this function takes a tableID, the name of a member of the picnicTable entry and a value for that member as 
 //paramters. Fnds the entry which that tableID and changes its memberName value to newValue
 void editTableEntry(int tableID, char *memberName, char *value){
     int i, j;
     int found = 0;
     int newValueCode = -1;
     
     // Check if database is initialized
     if(Db == NULL || Db->picnicTableTable == NULL){
         printf("Error - No Database Available, or No Elements Within PicnicTable Available\n");
         return;
     }
     
     // Find the picnic table entry with the given tableID
     PicnicTableEntry *targetEntry = NULL;
     for(i = 0; i < Db->picnicTableTable->picnicT_ElementCount; i++){
         if(Db->picnicTableTable->picnicT_entries[i].tableId == tableID){
             targetEntry = &(Db->picnicTableTable->picnicT_entries[i]);
             found = 1;
             break;
         }
     }
     
     // If no entry with the given tableID is found, return
     if(!found){
         printf("Error - No picnic table entry found with tableID %d\n", tableID);
         return;
     }
     
     // Determine which member to modify based on memberName
     if(strcmp(memberName, "Table Type") == 0){
         // Check if the value already exists in the tableTypeTable
         for(j = 0; j < Db->tableTypeTable->tableT_ElementCount; j++){
             if(strcmp(Db->tableTypeTable->tableT_entries[j].value, value) == 0){
                 newValueCode = Db->tableTypeTable->tableT_entries[j].code;
                 break;
             }
         }
         
         // If the value doesn't exist, add it to the tableTypeTable
         if(newValueCode == -1){
             // Check if we need to resize the table
             if(Db->tableTypeTable->tableT_ElementCount >= Db->tableTypeTable->tableT_CapacitySize){
                 // Resize logic would go here, but for simplicity, we'll just print an error
                 printf("Error - Table Type table is full, cannot add new value\n");
                 return;
             }
             
             // Add the new value to the table
             int newIndex = Db->tableTypeTable->tableT_ElementCount;
             // Generate a new code (for simplicity, use the next available number)
             newValueCode = Db->tableTypeTable->tableT_entries[newIndex-1].code + 1;
             
             Db->tableTypeTable->tableT_entries[newIndex].code = newValueCode;
             Db->tableTypeTable->tableT_entries[newIndex].value = strdup(value);
             Db->tableTypeTable->tableT_ElementCount++;
         }
         
         // Update the picnic table entry with the new value's code
         targetEntry->tableTypeId = newValueCode;
     }
     else if(strcmp(memberName, "Surface Material") == 0){
         // Check if the value already exists in the surfaceMaterialTable
         for(j = 0; j < Db->surfaceMaterialTable->tableT_ElementCount; j++){
             if(strcmp(Db->surfaceMaterialTable->tableT_entries[j].value, value) == 0){
                 newValueCode = Db->surfaceMaterialTable->tableT_entries[j].code;
                 break;
             }
         }
         
         // If the value doesn't exist, add it to the surfaceMaterialTable
         if(newValueCode == -1){
             // Check if we need to resize the table
             if(Db->surfaceMaterialTable->tableT_ElementCount >= Db->surfaceMaterialTable->tableT_CapacitySize){
                 // Resize logic would go here, but for simplicity, we'll just print an error
                 printf("Error - Surface Material table is full, cannot add new value\n");
                 return;
             }
             
             // Add the new value to the table
             int newIndex = Db->surfaceMaterialTable->tableT_ElementCount;
             // Generate a new code (for simplicity, use the next available number)
             newValueCode = Db->surfaceMaterialTable->tableT_entries[newIndex-1].code + 1;
             
             Db->surfaceMaterialTable->tableT_entries[newIndex].code = newValueCode;
             Db->surfaceMaterialTable->tableT_entries[newIndex].value = strdup(value);
             Db->surfaceMaterialTable->tableT_ElementCount++;
         }
         
         // Update the picnic table entry with the new value's code
         targetEntry->surfaceMaterialId = newValueCode;
     }
     else if(strcmp(memberName, "Structural Material") == 0){
         // Check if the value already exists in the structuralMaterialTable
         for(j = 0; j < Db->structuralMaterialTable->tableT_ElementCount; j++){
             if(strcmp(Db->structuralMaterialTable->tableT_entries[j].value, value) == 0){
                 newValueCode = Db->structuralMaterialTable->tableT_entries[j].code;
                 break;
             }
         }
         
         // If the value doesn't exist, add it to the structuralMaterialTable
         if(newValueCode == -1){
             // Check if we need to resize the table
             if(Db->structuralMaterialTable->tableT_ElementCount >= Db->structuralMaterialTable->tableT_CapacitySize){
                 // Resize logic would go here, but for simplicity, we'll just print an error
                 printf("Error - Structural Material table is full, cannot add new value\n");
                 return;
             }
             
             // Add the new value to the table
             int newIndex = Db->structuralMaterialTable->tableT_ElementCount;
             // Generate a new code (for simplicity, use the next available number)
             newValueCode = Db->structuralMaterialTable->tableT_entries[newIndex-1].code + 1;
             
             Db->structuralMaterialTable->tableT_entries[newIndex].code = newValueCode;
             Db->structuralMaterialTable->tableT_entries[newIndex].value = strdup(value);
             Db->structuralMaterialTable->tableT_ElementCount++;
         }
         
         // Update the picnic table entry with the new value's code
         targetEntry->structuralMaterialId = newValueCode;
     }
     else {
         printf("Error - Cannot modify member '%s'. Only 'Table Type', 'Surface Material', and 'Structural Material' can be modified.\n", memberName);
     }
 }
 
 // this function produces a listing of picnic tables grouped by neighbourhoods in ascending alphabetical order
 
 // Similarly to ReportByWard - the same format and approach was used (as they're quite similar in functionality - just one sorts according to 
 // ward and the other according to Neighbourhood - will still using the Lookup Table (using the NeighbourhoodId - neighID - to access the certain 
 // elements))
     // Resources Used for Help:
     // - https://stackoverflow.com/questions/40033310/sorting-a-list-of-strings-in-alphabetical-order-c
     // - https://www.w3schools.com/dsa/dsa_algo_bubblesort.php
     
 
 void reportByNeighbourhood(){
     int i, j, k;
     char *neighArray[64];
     char *currentNeighbourName, *tmpNeigh;
     int neighAddedCounter, currentNeighbourID;
     int picnicTCount, diffNeighCount, tableTEC, surfaceMEC, structuralEC, neighEC;
     //currentNeighbourName = NULL;
 
     picnicTCount = Db->picnicTableTable->picnicT_ElementCount;
     diffNeighCount = 0; // distinct / different wards
 
     if(Db == NULL || Db->picnicTableTable == NULL){
         printf("Error - No Database Available, or No Elements Within PicnicTable Available");
         return 0;
     }
 
     for(i=0; i < picnicTCount; i++){
         currentNeighbourID = Db->picnicTableTable->picnicT_entries[i].neighbhdId;
         currentNeighbourName = NULL;
         //neighElementC = Db->neighborhoodTable->neighnourhoodT_ElementCount;
         //neighEntries = Db->neighborhoodTable->neighbourhoodT_entries;
         //neighAddedCounter = 0;
 
          for(j=0; j < Db->neighborhoodTable->neighbourhoodT_ElementCount; j++){
             if(Db->neighborhoodTable->neighbourhoodT_entries[j].code == currentNeighbourID){
                 currentNeighbourName = Db->neighborhoodTable->neighbourhoodT_entries[j].value;
                 break;
             }
          }
 
          if(currentNeighbourName == NULL)
             continue;
         
         neighAddedCounter = 0;
         for(k=0; k < diffNeighCount; k++){
             if(strcmp(neighArray[k], currentNeighbourName) == 0){
                 neighAddedCounter = 1;
                  break;
                 }
             }
 
         if(neighAddedCounter == 0){
             neighArray[diffNeighCount++] = currentNeighbourName;
         }
     }
 
     for(i=0; i < diffNeighCount; i++){
         for(j=0; j < diffNeighCount; j++){
             if(strcmp(neighArray[i], neighArray[j]) < 0){
                 tmpNeigh = neighArray[i];
                 neighArray[i] = neighArray[j];
                 neighArray[j] = tmpNeigh;
 
             }
         }
     }
 
     for(i=0; i < diffNeighCount; i++){
         printf("\n%s\n", neighArray[i]);
         printf("************************************************\n");
 
         for(j=0; j < picnicTCount; j++){
             PicnicTableEntry picTE;
             picTE = Db->picnicTableTable->picnicT_entries[j];
             char *currentEntryNeighName;
             currentEntryNeighName = NULL;
 
             for(k=0; k < Db->neighborhoodTable->neighbourhoodT_ElementCount; k++){
                 if(Db->neighborhoodTable->neighbourhoodT_entries[k].code == picTE.neighbhdId){
                     currentEntryNeighName = Db->neighborhoodTable->neighbourhoodT_entries[k].value;
                     break;
                 }
             }
             if (currentEntryNeighName == NULL)
                 continue;
 
             if(strcmp(currentEntryNeighName, neighArray[i]) == 0){
                 // Since these are integer values, PicnicTable doesnt store full names like "Wood" - 
                 // It Uses codes / ID's that are associated with certain values that link to the lookup tables (TableType, SurfaceMat, StructMat, Neigh...)
                 // Called Foreign Keys - ID"s that refer to entries in lookup Tables
 
                 char *tableT; // Lookup Table (Watch Video Once Again To Provide Explaination)
                 char *surfaceMat;// // Lookup Table (Watch Video Once Again To Provide Explaination)
                 char *structuralMat; //Lookup Table (Watch Video Once Again To Provide Explaination)
                 //char *neighbourhoodName; // Lookup Table (Watch Video Once Again To Provide Explaination)
 
                 // Element Counts for 'For Loop' - just for clairty/visability sake
                 tableTEC = Db->tableTypeTable->tableT_ElementCount;
                 surfaceMEC = Db->surfaceMaterialTable->tableT_ElementCount;
                 structuralEC = Db->structuralMaterialTable->tableT_ElementCount;
                 //neighEC = Db->neighborhoodTable->neighbourhoodT_ElementCount;
 
                 for (k=0; k < tableTEC; k++){
                     if(Db->tableTypeTable->tableT_entries[k].code == picTE.tableTypeId){
                         tableT = Db->tableTypeTable->tableT_entries[k].value;
                         break;
                     }
                 }
 
                 for(k=0; k < surfaceMEC; k++){
                     if(Db->surfaceMaterialTable->tableT_entries[k].code == picTE.surfaceMaterialId){
                         surfaceMat= Db->surfaceMaterialTable->tableT_entries[k].value;
                         break;
                     }
                 }
 
                 for(k=0; k < structuralEC; k++){
                     if(Db->structuralMaterialTable->tableT_entries[k].code == picTE.structuralMaterialId){
                         structuralMat = Db->structuralMaterialTable->tableT_entries[k].value;
                         break;
                     }
                 }
 
                 /*for(k=0; k < neighEC; k++){
                     if(Db->neighborhoodTable->neighbourhoodT_entries[k].code == picTE.neighbhdId){
                         neighbourhoodName = Db->neighborhoodTable->neighbourhoodT_entries[k].value;
                         break;
                     }
                 }*/
 
                 printf("%d     %s     %s     %s     %s     %d     %s     %s     %s\n", picTE.siteId, tableT, surfaceMat, structuralMat, picTE.streetAvenue, picTE.neighbhdId, currentEntryNeighName, picTE.latitude, picTE.longitude);
 
             }
         }
     }
     return; 
 }
 
 // this function produces a listing of picnic tables grouped by wards in ascending order
 
 // Resources Used for Help:
     // - https://stackoverflow.com/questions/40033310/sorting-a-list-of-strings-in-alphabetical-order-c
     // - https://www.w3schools.com/dsa/dsa_algo_bubblesort.php
     
 void reportByWard(){
     int i, j, k;
     char *wardArray[64];
     char *currentWard, *tmpWard;
     int wardAddedCounter;
     int picnicTCount, diffWardCount, tableTEC, surfaceMEC, structuralEC, neighEC;
 
     picnicTCount = Db->picnicTableTable->picnicT_ElementCount;
     diffWardCount = 0; // distinct / different wards
 
     if(Db == NULL || Db->picnicTableTable == NULL){
         printf("Error - No Database Available, or No Elements Within PicnicTable Available");
         return 0;
     }
 
     for(i=0; i < picnicTCount; i++){
          currentWard = Db->picnicTableTable->picnicT_entries[i].ward;
          wardAddedCounter = 0; //already seen this ward (alreadyadded)
 
          for(j=0; j < diffWardCount; j++){
             if(strcmp(wardArray[j], currentWard) == 0){
                 wardAddedCounter = 1;
                 break;
             }
          }
 
          if(wardAddedCounter == 0){
             wardArray[diffWardCount++] = currentWard;
          }
 
     }
 
     for(i=0; i < diffWardCount; i++){
         for(j=0; j < diffWardCount; j++){
             if(strcmp(wardArray[i], wardArray[j]) < 0){
                 tmpWard = wardArray[i];
                 wardArray[i] = wardArray[j];
                 wardArray[j] = tmpWard;
 
             }
         }
     }
 
     for(i=0; i < diffWardCount; i++){
         printf("\n%s\n", wardArray[i]);
         printf("************************************************\n");
 
         for(j=0; j < picnicTCount; j++){
             PicnicTableEntry picTE;
             picTE = Db->picnicTableTable->picnicT_entries[j];
 
             if(strcmp(picTE.ward, wardArray[i]) == 0){
                 // Since these are integer values, PicnicTable doesnt store full names like "Wood" - 
                 // It Uses codes / ID's that are associated with certain values that link to the lookup tables (TableType, SurfaceMat, StructMat, Neigh...)
                 // Called Foreign Keys - ID"s that refer to entries in lookup Tables
 
                 char *tableT; // Lookup Table (Watch Video Once Again To Provide Explaination)
                 char *surfaceMat;// // Lookup Table (Watch Video Once Again To Provide Explaination)
                 char *structuralMat; //Lookup Table (Watch Video Once Again To Provide Explaination)
                 char *neighbourhoodName; // Lookup Table (Watch Video Once Again To Provide Explaination)
 
                 // Element Counts for 'For Loop' - just for clairty/visability sake
                 tableTEC = Db->tableTypeTable->tableT_ElementCount;
                 surfaceMEC = Db->surfaceMaterialTable->tableT_ElementCount;
                 structuralEC = Db->structuralMaterialTable->tableT_ElementCount;
                 neighEC = Db->neighborhoodTable->neighbourhoodT_ElementCount;
 
                 for (k=0; k < tableTEC; k++){
                     if(Db->tableTypeTable->tableT_entries[k].code == picTE.tableTypeId){
                         tableT = Db->tableTypeTable->tableT_entries[k].value;
                         break;
                     }
                 }
 
                 for(k=0; k < surfaceMEC; k++){
                     if(Db->surfaceMaterialTable->tableT_entries[k].code == picTE.surfaceMaterialId){
                         surfaceMat= Db->surfaceMaterialTable->tableT_entries[k].value;
                         break;
                     }
                 }
 
                 for(k=0; k < structuralEC; k++){
                     if(Db->structuralMaterialTable->tableT_entries[k].code == picTE.structuralMaterialId){
                         structuralMat = Db->structuralMaterialTable->tableT_entries[k].value;
                         break;
                     }
                 }
 
                 for(k=0; k < neighEC; k++){
                     if(Db->neighborhoodTable->neighbourhoodT_entries[k].code == picTE.neighbhdId){
                         neighbourhoodName = Db->neighborhoodTable->neighbourhoodT_entries[k].value;
                         break;
                     }
                 }
 
                 printf("%d     %s     %s     %s     %s     %d     %s     %s     %s\n", picTE.siteId, tableT, surfaceMat, structuralMat, picTE.streetAvenue, picTE.neighbhdId, neighbourhoodName, picTE.latitude, picTE.longitude);
 
             }
         }
     }
     return; 
 }
 
 //This function will free the database
 void freeDB(){
     int i;
     
     //check if database is initialized
     if(Db == NULL){
         return;
     }
     
     //free the tableTypeTable
     if(Db->tableTypeTable != NULL){
         //free each entry's value (which is dynamically allocated)
         for(i = 0; i < Db->tableTypeTable->tableT_ElementCount; i++){
             if(Db->tableTypeTable->tableT_entries[i].value != NULL){
                 free(Db->tableTypeTable->tableT_entries[i].value);
             }
         }
         //free the entries array
         if(Db->tableTypeTable->tableT_entries != NULL){
             free(Db->tableTypeTable->tableT_entries);
         }
         //free the table itself
         free(Db->tableTypeTable);
     }
     
     //free the surfaceMaterialTable
     if(Db->surfaceMaterialTable != NULL){
         //free each entry's value
         for(i = 0; i < Db->surfaceMaterialTable->tableT_ElementCount; i++){
             if(Db->surfaceMaterialTable->tableT_entries[i].value != NULL){
                 free(Db->surfaceMaterialTable->tableT_entries[i].value);
             }
         }
         //free the entries array
         if(Db->surfaceMaterialTable->tableT_entries != NULL){
             free(Db->surfaceMaterialTable->tableT_entries);
         }
         //free the table itself
         free(Db->surfaceMaterialTable);
     }
     
     //free the structuralMaterialTable
     if(Db->structuralMaterialTable != NULL){
         //Free each entry's value
         for(i = 0; i < Db->structuralMaterialTable->tableT_ElementCount; i++){
             if(Db->structuralMaterialTable->tableT_entries[i].value != NULL){
                 free(Db->structuralMaterialTable->tableT_entries[i].value);
             }
         }
         //free the entries array
         if(Db->structuralMaterialTable->tableT_entries != NULL){
             free(Db->structuralMaterialTable->tableT_entries);
         }
         //free the table itself
         free(Db->structuralMaterialTable);
     }
     
     //free the neighborhoodTable
     if(Db->neighborhoodTable != NULL){
         //free each entry's value
         for(i = 0; i < Db->neighborhoodTable->neighbourhoodT_ElementCount; i++){
             if(Db->neighborhoodTable->neighbourhoodT_entries[i].value != NULL){
                 free(Db->neighborhoodTable->neighbourhoodT_entries[i].value);
             }
         }
         //free the entries array
         if(Db->neighborhoodTable->neighbourhoodT_entries != NULL){
             free(Db->neighborhoodTable->neighbourhoodT_entries);
         }
         //free the table itself
         free(Db->neighborhoodTable);
     }
     
     //free the picnicTableTable
     if(Db->picnicTableTable != NULL){
         //free each entry's dynamically allocated fields
         for(i = 0; i < Db->picnicTableTable->picnicT_ElementCount; i++){
             if(Db->picnicTableTable->picnicT_entries[i].streetAvenue != NULL){
                 free(Db->picnicTableTable->picnicT_entries[i].streetAvenue);
             }
             if(Db->picnicTableTable->picnicT_entries[i].ward != NULL){
                 free(Db->picnicTableTable->picnicT_entries[i].ward);
             }
             if(Db->picnicTableTable->picnicT_entries[i].latitude != NULL){
                 free(Db->picnicTableTable->picnicT_entries[i].latitude);
             }
             if(Db->picnicTableTable->picnicT_entries[i].longitude != NULL){
                 free(Db->picnicTableTable->picnicT_entries[i].longitude);
             }
         }
         //free the entries array
         if(Db->picnicTableTable->picnicT_entries != NULL){
             free(Db->picnicTableTable->picnicT_entries);
         }
         //free the table itself
         free(Db->picnicTableTable);
     }
     
     //finally, free the database structure itself
     free(Db);
     Db = NULL; //set to NULL to prevent use after free
 }
 
 int main() {
     return 0;
 }
 