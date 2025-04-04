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
void importDB(char *filename){
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
}

// This Function takes the name of a .csv file as paramter and creates a .csv file containing the information of the Database
// (exported .csv file must be exactly the same as the original .csv file from which the Database was created)
void exportDB(char *filename){
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
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
}

// Edit Table Entry Functions 
// this function takes a tableID, the name of a member of the picnicTable entry and a value for that member as 
//paramters. Fnds the entry which that tableID and changes its memberName value to newValue
void editTableEntry(int tableID, char *memberName, char *value){
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
}

// this function produces a listing of picnic tables grouped by neighbourhoods in ascending alphabetical order
void reportByNeighbourhood(){
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
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
        printf("************************************************\n")

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

                printf("%d     %s     %s     %s     %s     %d     %s     %s     %s", picTE.siteId, tableT, surfaceMat, structuralMat, picTE.streetAvenue, picTE.neighbhdId, neighbourhoodName, picTE.latitude, picTE.longitude);

            }
        }
    }
    return; 
}

// This function will free the DB 
void freeDB(){
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
}

int main() {
    return 0;
}
