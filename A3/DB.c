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
        else if (strcmp(memberName, "Neighbourhood ID") == 0){
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
void reportByWard(){
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
}

// This function will free the DB 
void freeDB(){
    return; // Return for now - as we're creating empty functions (will be worked on later) for MS1
}

int main() {
    return 0;
}
