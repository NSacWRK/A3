/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Aksh Chand, Forbes Feild, Vickram Gill, Naval Sachar>
 * Lab instructor: <TODO: Dhara Wagh>
 * Lecture instructor: <TODO: Dhara Wagh>
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

// This function will take the name of a .csv file as parameter and creates and populates the Database
// with the correpsonding data set information

// Help/Information Used as Guide to complete ImportDB was taken from countingCovid.c (From Assignment #1) - Similairty from that into this function as we also parse through a file (with Headers) etc
// Also help from source code for File I/O from Lecture Slides 
void importDB(char *filename){
    char fileLine[512];

    // Used as a counter, that will determine if the current line that we're on while parsing through data is the Header Line that
    // displays the content for each column such as Table, Surface Material, Structural Material, Longitude, Latitude, etc...
    int firstFileLine = 1;

    FILE *fp = fopen(filename, "r"); 
    if(fp == NULL){
        printf("error opening File!\n");
        return;
    }

    // Dynamically allocate memory for our Database corresponding data set information - Used for the PicnicTable Data Table
    // Where it will show tableTypeTable (id, Type), surfaceMaterialTable (id, surfaceMaterial), structuralMaterialTable(id, struct Material)
    // neighbourhoodTable (Neigh. ID, Neigh Name) - ALL OF LOOKUP TABLES then PicnicTable which holds all of the info stated in the Example PDF provided showing the outputs 
    Db = malloc(sizeof(DataBase));
    Db->picnicTableTable = malloc(sizeof(PicnicTable)); // Allocating the memory for the Data Table
    Db->picnicTableTable->picnicT_entries = malloc(sizeof(PicnicTableEntry) * INIT_SIZE); // Allocating memory for each entry in the Picnic Table
    Db->picnicTableTable->picnicT_ElementCount = 0; // Initialize the current Element Count to 0
    Db->picnicTableTable->picnicT_CapacitySize = INIT_SIZE; // Since we're using Arrays

    while (fgets(fileLine, sizeof(fileLine), fp)){
        if(firstFileLine){
            firstFileLine = 0;
            continue;
        }

        // Calculating if the Table Resizing Is Needed (very similar to Hashtable Implementation from Assignment #2)
        // Then reallocating the memory from the previous sized Table into the newly resized table
        int capacityPT = Db->picnicTableTable->picnicT_CapacitySize;
        if (Db->picnicTableTable->picnicT_ElementCount == capacityPT){
            int newCapacityPT = capacityPT * 2;
            Db->picnicTableTable->picnicT_entries = realloc(
                Db->picnicTableTable->picnicT_entries, sizeof(PicnicTableEntry) * newCapacityPT);
            Db->picnicTableTable->picnicT_CapacitySize = newCapacityPT;
        }

        // Begin parsing the current line and mapping to struct
        char *token = strtok(fileLine, ",\n");
        if(token == NULL) continue;

        PicnicTableEntry newEntry;

        newEntry.siteId = atoi(token); // Id

        token = strtok(NULL, ",\n"); // Table Type
        newEntry.tableTypeId = lookupOrAddTableType(token);

        token = strtok(NULL, ",\n"); // Surface Material
        newEntry.surfaceMaterialId = lookupOrAddSurfaceMaterial(token);

        token = strtok(NULL, ",\n"); // Structural Material
        newEntry.structuralMaterialId = lookupOrAddStructuralMaterial(token);

        token = strtok(NULL, ",\n"); // Street/Avenue
        strncpy(newEntry.streetAvenue, token, sizeof(newEntry.streetAvenue));

        token = strtok(NULL, ",\n"); // Neighbourhood Id
        newEntry.neighbhdId = atoi(token);

        token = strtok(NULL, ",\n"); // Neighbourhood Name
        lookupOrAddNeighbourhood(newEntry.neighbhdId, token); // Store only in lookup

        token = strtok(NULL, ",\n"); // Ward
        strncpy(newEntry.ward, token, sizeof(newEntry.ward));

        token = strtok(NULL, ",\n"); // Latitude
        strncpy(newEntry.latitude, token, sizeof(newEntry.latitude));

        token = strtok(NULL, ",\n"); // Longitude
        strncpy(newEntry.longitude, token, sizeof(newEntry.longitude));

        // Assign unique tableId and store in database
        newEntry.tableId = Db->picnicTableTable->picnicT_ElementCount + 1;

        // Add the new entry to the array
        Db->picnicTableTable->picnicT_entries[Db->picnicTableTable->picnicT_ElementCount++] = newEntry;
    }

    fclose(fp);
    printf("Database import complete. %d entries loaded.\n", Db->picnicTableTable->picnicT_ElementCount);
}
    //nav works in this 
    //return; // Return for now - as we're creating empty functions (will be worked on later) for MS1


// This Function takes the name of a .csv file as paramter and creates a .csv file containing the information of the Database
// (exported .csv file must be exactly the same as the original .csv file from which the Database was created)
void exportDB(char *filename){
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Error opening file for writing!\n");
        return;
    }

    // Write header
    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude\n");

    for(int i = 0; i < Db->picnicTableTable->picnicT_ElementCount; i++){
        PicnicTableEntry entry = Db->picnicTableTable->picnicT_entries[i];

        // Write each line using lookup functions to get the original strings
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%s,%s,%s,%s\n",
            entry.siteId,
            getTableTypeById(entry.tableTypeId),
            getSurfaceMaterialById(entry.surfaceMaterialId),
            getStructuralMaterialById(entry.structuralMaterialId),
            entry.streetAvenue,
            entry.neighbhdId,
            getNeighbourhoodNameById(entry.neighbhdId),
            entry.ward,
            entry.latitude,
            entry.longitude
        );
    }

    fclose(fp);
    printf("Database export complete. File saved as: %s\n", filename);
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
    int count = Db->picnicTableTable->picnicT_ElementCount;

    for(int i = 0; i < count - 1; i++){
        for(int j = i + 1; j < count; j++){
            PicnicTableEntry *a = &Db->picnicTableTable->picnicT_entries[i];
            PicnicTableEntry *b = &Db->picnicTableTable->picnicT_entries[j];

            int cmp = 0;

            // Numeric fields
            if(strcmp(memberName, "tableId") == 0)
                cmp = a->tableId > b->tableId;
            else if(strcmp(memberName, "siteId") == 0)
                cmp = a->siteId > b->siteId;
            else if(strcmp(memberName, "neighbhdId") == 0)
                cmp = a->neighbhdId > b->neighbhdId;

            // Text fields
            else if(strcmp(memberName, "streetAvenue") == 0)
                cmp = strcmp(a->streetAvenue, b->streetAvenue) > 0;
            else if(strcmp(memberName, "ward") == 0)
                cmp = strcmp(a->ward, b->ward) > 0;
            else if(strcmp(memberName, "latitude") == 0)
                cmp = strcmp(a->latitude, b->latitude) > 0;
            else if(strcmp(memberName, "longitude") == 0)
                cmp = strcmp(a->longitude, b->longitude) > 0;

            if(cmp){
                // Swap entries
                PicnicTableEntry temp = *a;
                *a = *b;
                *b = temp;
            }
        }
    }

    printf("Sorting complete by '%s'.\n", memberName);
}
    

// Edit Table Entry Functions 
// this function takes a tableID, the name of a member of the picnicTable entry and a value for that member as 
//paramters. Fnds the entry which that tableID and changes its memberName value to newValue
//* Members that can be modified:
 //*  1- Table Type
 //*  2- Surface Material
 //*  3- Structural Material 
 //* If the new value is not found in the existing tables, this value must be added to the 
 //* corresponding table.
 
void editTableEntry(int tableID, char *memberName, char *value){

    int i, j, picnicTElementC;
    int newValueInsertIndex;
    
    if(Db == NULL || Db->picnicTableTable == NULL){
        printf("Error - No Database Available, or No Elements Within PicnicTable Available");
        return 0;
     }

     picnicTElementC = Db->picnicTableTable->picnicT_ElementCount;
     for(i=0; i < picnicTElementC; i++){
        if(Db->picnicTableTable->picnicT_entries[i].tableId == tableID){
            if(strcmp(memberName, "Surface Material") == 0){
                for(j=0; j < Db->surfaceMaterialTable->tableT_ElementCount; j++){
                    if(strcmp(Db->surfaceMaterialTable->tableT_entries[j].value, value) == 0){
                        Db->picnicTableTable->picnicT_entries[i].surfaceMaterialId = Db->surfaceMaterialTable->tableT_entries[j].code;
                        return;
                    }
                }
                newValueInsertIndex = Db->surfaceMaterialTable->tableT_ElementCount;
                Db->surfaceMaterialTable->tableT_entries[newValueInsertIndex].code = newValueInsertIndex;
                Db->surfaceMaterialTable->tableT_entries[newValueInsertIndex].value = malloc(strlen(value) + 1);
                strcpy(Db->surfaceMaterialTable->tableT_entries[newValueInsertIndex].value, value);
                Db->picnicTableTable->picnicT_entries[i].surfaceMaterialId = newValueInsertIndex;
                Db->surfaceMaterialTable->tableT_ElementCount++;
                return;
            }

            else if(strcmp(memberName, "Structural Material") == 0){
                for(j=0; j < Db->structuralMaterialTable->tableT_ElementCount; j++){
                    if (strcmp(Db->structuralMaterialTable->tableT_entries[j].value, value) == 0){
                        Db->picnicTableTable->picnicT_entries[i].structuralMaterialId = Db->structuralMaterialTable->tableT_entries[j].code;
                        return;
                    }
                }
                newValueInsertIndex = Db->structuralMaterialTable->tableT_ElementCount;
                Db->structuralMaterialTable->tableT_entries[newValueInsertIndex].code = newValueInsertIndex;
                Db->structuralMaterialTable->tableT_entries[newValueInsertIndex].value = malloc(strlen(value) + 1);
                strcpy(Db->structuralMaterialTable->tableT_entries[newValueInsertIndex].value, value);
                Db->picnicTableTable->picnicT_entries[i].structuralMaterialId = newValueInsertIndex;
                Db->structuralMaterialTable->tableT_ElementCount++;
                return;
            }

            else if(strcmp(memberName, "Table Type") == 0){
                for(j=0; j < Db->tableTypeTable->tableT_ElementCount; j++){
                    if (strcmp(Db->tableTypeTable->tableT_entries[j].value, value) == 0){
                        Db->picnicTableTable->picnicT_entries[i].tableTypeId = Db->tableTypeTable->tableT_entries[j].code;
                        return;
                    }
                }
                newValueInsertIndex = Db->tableTypeTable->tableT_ElementCount;
                Db->tableTypeTable->tableT_entries[newValueInsertIndex].code = newValueInsertIndex;
                Db->tableTypeTable->tableT_entries[newValueInsertIndex].value = malloc(strlen(value) + 1);
                strcpy(Db->tableTypeTable->tableT_entries[newValueInsertIndex].value, value);
                Db->picnicTableTable->picnicT_entries[i].tableTypeId = newValueInsertIndex;
                Db->tableTypeTable->tableT_ElementCount++;
                return;
            }

            else{
                printf("Error - Member Name Chosen Not Valid.\n");
                return;
            }
        }
     }
     printf("Error - Invalid Table ID\n");
     return;
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
    
    picnicTCount = Db->picnicTableTable->picnicT_ElementCount;
    diffNeighCount = 0; // distinct / different wards

    if(Db == NULL || Db->picnicTableTable == NULL){
        printf("Error - No Database Available, or No Elements Within PicnicTable Available");
        return 0;
    }
    for(i=0; i < picnicTCount; i++){
        currentNeighbourID = Db->picnicTableTable->picnicT_entries[i].neighbhdId;
        currentNeighbourName = NULL;
       
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

// This function will free the DB 
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
