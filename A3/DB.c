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
 *   5- Neighborhood Name
 *   6- Ward
 */
int countEntries(char *memberName, char * value){

    int count = 0;

    for (int i = 0; i < Db->picnicTableTable->picnicT_ElementCount; i++) {
        PicnicTableEntry entry = Db->picnicTableTable->picnicT_entries[i];

        if (strcmp(memberName, "ward") == 0 && strcmp(entry.ward, value) == 0)
            count++;
        else if (strcmp(memberName, "tableId") == 0 && entry.tableId == atoi(value))
            count++;
        else if (strcmp(memberName, "siteId") == 0 && entry.siteId == atoi(value))
            count++;
        else if (strcmp(memberName, "streetAvenue") == 0 && strcmp(entry.streetAvenue, value) == 0)
            count++;
        else if (strcmp(memberName, "neighbhdId") == 0 && entry.neighbhdId == atoi(value))
            count++;
        else if (strcmp(memberName, "latitude") == 0 && strcmp(entry.latitude, value) == 0)
            count++;
        else if (strcmp(memberName, "longitude") == 0 && strcmp(entry.longitude, value) == 0)
            count++;
    }

    return count;
}


    //return 0; // Return for now - as we're creating empty functions (will be worked on later) for MS1
    int i,j,nbhdID,entryCount; // Initalize i, j, nbhdID, entryCount (int) - that will be used later on in/for the for loops tec
    entryCount = 0; // initalize the entryCount to 0 - this variable will keep track of how many matched entries we've found - which we currently intialized at 0
    // as initally there are zero matched entries 

    // Error Check - this will simply make sure that our picnicTableTable and/or Db are NULL - which is it is - will return NULL 
    // as we cant count entries using the Tables and Db that are empty / NULL

    if(Db == NULL || Db->picnicTableTable == NULL){
        printf("Error - No Database Available, or No Elements Within PicnicTable Available");
        return 0;
    }

    // Fo rloop that will iterate throguh each entry within the picnicTableTable 
    for (i = 0; i < Db->picnicTableTable->picnicT_ElementCount; i++){
        PicnicTableEntry picTEntry; // We first initalize a variable (calling the struct PicnicTableEntry) - which will give us access to the feilds for each picnicTable Table entry 
        // but in this case we want to get the current picnic table entry which we are checking
        picTEntry = Db->picnicTableTable->picnicT_entries[i]; // set the entry variable for the picnic Table current entry position/index we're at

        // #1 Table Type (UNDER TABLE STRUCT / LOOKUP - (Look at CMPT_201_Database_Description PDF - Table Relationships))
        if(strcmp(memberName, "Table Type") == 0){ // Using the strcmp function, this will check to see if we're searching/checking for the member "Table Type"
            // For loop that will iterate through all the entries in the Table Type lookup Table 
            for(j=0; j < Db->tableTypeTable->tableT_ElementCount; j++){
                // If statement that will check to see if the code in the lookup macthes the picnic table's tapeTypeId and the and the value matches for the 
                // the value that we're looking for - if this is VALID and MATCHes - we increment the entryCount by 1 
                if(Db->tableTypeTable->tableT_entries[j].code == picTEntry.tableTypeId && strcmp(Db->tableTypeTable->tableT_entries[j].value, value) == 0){
                    entryCount++; // Increment count
                }
                
            }
        }
        // The same implementation goes for the rest of the members we're searching
        // #2) Surface Material (UNDER TABLE STRUCT / LOOKUP -(Look at CMPT_201_Database_Description PDF - Table Relationships))
        else if (strcmp(memberName, "Surface Material") == 0){ // Using the strcmp function, this will check to see if we're searching/checking for the member "Surface Material"
            for(j=0; j < Db->surfaceMaterialTable->tableT_ElementCount; j++){  // For loop that will iterate through all the entries in the Table Type lookup Table
                 // If statement that will check to see if the code in the lookup macthes the picnic table's tapeTypeId and the and the value matches for the 
                // the value that we're looking for - if this is VALID and MATCHes - we increment the entryCount by 1
                if(Db->surfaceMaterialTable->tableT_entries[j].code == picTEntry.surfaceMaterialId && strcmp(Db->surfaceMaterialTable->tableT_entries[j].value, value) == 0){
                    entryCount++; // Increment count 
                }
            }
        }
        // #3) Structural Material (UNDER TABLE STRUCT / LOOKUP- (Look at CMPT_201_Database_Description PDF - Table Relationships))
        else if (strcmp(memberName, "Structural Material") == 0){  // Using the strcmp function, this will check to see if we're searching/checking for the member "Structural Material"
            for(j=0; j < Db->structuralMaterialTable->tableT_ElementCount; j++){ // For loop that will iterate through all the entries in the Table Type lookup Table
                // If statement that will check to see if the code in the lookup macthes the picnic table's tapeTypeId and the and the value matches for the 
                // the value that we're looking for - if this is VALID and MATCHes - we increment the entryCount by 1
                if(Db->structuralMaterialTable->tableT_entries[j].code == picTEntry.structuralMaterialId && strcmp(Db->structuralMaterialTable->tableT_entries[j].value, value) == 0){
                    entryCount++;
                }
            }
        }

        // # 4) Neighbourhood ID (Look at CMPT_201_Database_Description PDF - Table Relationships)
        else if (strcmp(memberName, "Neighbourhood Id") == 0){ // Using the strcmp function, this will check to see if we're searching/checking for the member "Neighbourhood ID"
            // COnvert the value we're looking/searching for in this given memberName - but since value is a char, and in out struct neigh. ID is an Int
            // We would have to use the atoi function 0 which will convert the char/string into an integer to allow us to search for that given value (integer) in this memberName
            nbhdID = atoi(value); 
            if(picTEntry.neighbhdId == nbhdID){ // Comparing the integer and compare it / seee if it matches the picnic entry's neighbourhood ID (neighbhdId)
                entryCount++;// if it matches, increment the counter
            }
        }

        // #5) Neighbourhood Name (NEIGHBOURHOOD STRUCT - (Look at CMPT_201_Database_Description PDF - Table Relationships))
        else if (strcmp(memberName, "Neighbourhood Name") == 0){ // Using the strcmp function, this will check to see if we're searching/checking for the member "Neighbourhood Name"
            for(j=0; j < Db->neighborhoodTable->neighbourhoodT_ElementCount; j++){
                // If statement that will check to see if the neighbhdId and the code from the neighbourhood LookupTable match AND if the values also match accordingly, we
                // increment the counter 
                if(Db->neighborhoodTable->neighbourhoodT_entries[j].code == picTEntry.neighbhdId && strcmp(Db->neighborhoodTable->neighbourhoodT_entries[j].value, value) == 0){
                    entryCount++; // Increment the counter 
                }
            }
        }

        // #6) Ward (Within PicnicTable / picTEntry directly)
        else if (strcmp(memberName, "Ward") == 0){ // Using the strcmp function, this will check to see if we're searching/checking for the member "Ward"
            if(strcmp(picTEntry.ward, value) == 0){ // If statements to check if the values match, if they match increment the counter
                entryCount++;
            }
        }
    }
    return entryCount; // return the final result 
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

    int i, j, picnicTElementC; // Initalize the variables i , j , picnicTElementC (ints) => i and j will both be used for loops, picnicTElementC is used to count the number of picnic table entries
    int newValueInsertIndex; // initalize the variable newValueInsertIndex (int)
    
    // Error Check - this will simply make sure that our picnicTableTable and/or Db are NULL - which is it is - will return NULL 
    // as we cant count entries using the Tables and Db that are empty / NULL

    if(Db == NULL || Db->picnicTableTable == NULL){
        printf("Error - No Database Available, or No Elements Within PicnicTable Available");
        return 0;
     }

     picnicTElementC = Db->picnicTableTable->picnicT_ElementCount; // This will get and store the total number of entries/element count in the picnicTable Table
     // This for loop will iterate through each of the entries in the table
     for(i=0; i < picnicTElementC; i++){
        // First If Statement that will check to see if the current entry's tableId matches the tableId passed in the paramter / the one we want to edit/update
        if(Db->picnicTableTable->picnicT_entries[i].tableId == tableID){
            // Second if statement that will check to see if the member name (passed in the paramater) is Surface Material - which is the 
            //member that we want to update 
            if(strcmp(memberName, "Surface Material") == 0){
                // Nested for Loop that will check to see and will iterate through the surface material lookup table and see if the value exists
                for(j=0; j < Db->surfaceMaterialTable->tableT_ElementCount; j++){
                    // If statement that IF there exists a value, we set the surfaceMaterialId in the picnic entry to the code of the macthed value 
                    if(strcmp(Db->surfaceMaterialTable->tableT_entries[j].value, value) == 0){
                        Db->picnicTableTable->picnicT_entries[i].surfaceMaterialId = Db->surfaceMaterialTable->tableT_entries[j].code;
                        return; // return 
                    }
                }
                // Otherwise as stated in Db.h " If the new value is not found in the existing tables, this value must be added to the  corresponding table."
                // which is what we'll be doing here 
                newValueInsertIndex = Db->surfaceMaterialTable->tableT_ElementCount; // First - Calaculate the Index where we want to insert/update or where the new value will go
                Db->surfaceMaterialTable->tableT_entries[newValueInsertIndex].code = newValueInsertIndex; // Second - we will set a new code (foreign key or ID) - using the index 
                Db->surfaceMaterialTable->tableT_entries[newValueInsertIndex].value = malloc(strlen(value) + 1); // Third - we will dynamically allocate memory for the newly addded value, and then copy the value
                strcpy(Db->surfaceMaterialTable->tableT_entries[newValueInsertIndex].value, value); // Copy the new value
                Db->picnicTableTable->picnicT_entries[i].surfaceMaterialId = newValueInsertIndex; // Fourth - We will assign the new ID to the picnic entry and increase the element count (as we've added a new value - increasing the count)
                Db->surfaceMaterialTable->tableT_ElementCount++; // Increase Element Count
                return;
            }

            // Similarly to the surface Material, this will do the same but for Structural Material
            // else if statement that will check to see if the member name (passed in the paramater) is Structural Material - which is the 
            // member that we want to update 
            else if(strcmp(memberName, "Structural Material") == 0){
                //for Loop that will check to see and will iterate through the surface material lookup table and see if the value exists
                for(j=0; j < Db->structuralMaterialTable->tableT_ElementCount; j++){
                    // If statement that IF there exists a value, we set the structuralMaterialId in the picnic entry to the code of the macthed value 
                    if (strcmp(Db->structuralMaterialTable->tableT_entries[j].value, value) == 0){
                        Db->picnicTableTable->picnicT_entries[i].structuralMaterialId = Db->structuralMaterialTable->tableT_entries[j].code;
                        return; // return
                    }
                }
                // Otherwise as stated in Db.h " If the new value is not found in the existing tables, this value must be added to the  corresponding table."
                // which is what we'll be doing here 
                newValueInsertIndex = Db->structuralMaterialTable->tableT_ElementCount;// First - Calaculate the Index where we want to insert/update or where the new value will go
                Db->structuralMaterialTable->tableT_entries[newValueInsertIndex].code = newValueInsertIndex; // Second - we will set a new code (foreign key or ID) - using the index 
                Db->structuralMaterialTable->tableT_entries[newValueInsertIndex].value = malloc(strlen(value) + 1); // Third - we will dynamically allocate memory for the newly addded value, and then copy the value
                strcpy(Db->structuralMaterialTable->tableT_entries[newValueInsertIndex].value, value); // Copy the new value
                Db->picnicTableTable->picnicT_entries[i].structuralMaterialId = newValueInsertIndex; // Fourth - We will assign the new ID to the picnic entry and increase the element count (as we've added a new value - increasing the count)
                Db->structuralMaterialTable->tableT_ElementCount++; // Increase Element Count
                return;
            }

            // Similarly to the structural Material, this will do the same but for Table Type
            // else if statement that will check to see if the member name (passed in the paramater) is Structural Material - which is the 
            // member that we want to update 

            else if(strcmp(memberName, "Table Type") == 0){
                //for Loop that will check to see and will iterate through the surface material lookup table and see if the value exists
                for(j=0; j < Db->tableTypeTable->tableT_ElementCount; j++){
                    // If statement that IF there exists a value, we set the tableTypeId in the picnic entry to the code of the macthed value 
                    if (strcmp(Db->tableTypeTable->tableT_entries[j].value, value) == 0){
                        Db->picnicTableTable->picnicT_entries[i].tableTypeId = Db->tableTypeTable->tableT_entries[j].code;
                        return; // return
                    }
                }
                // Otherwise as stated in Db.h " If the new value is not found in the existing tables, this value must be added to the  corresponding table."
                // which is what we'll be doing here 
                newValueInsertIndex = Db->tableTypeTable->tableT_ElementCount; // First - Calaculate the Index where we want to insert/update or where the new value will go
                Db->tableTypeTable->tableT_entries[newValueInsertIndex].code = newValueInsertIndex; // Second - we will set a new code (foreign key or ID) - using the index 
                Db->tableTypeTable->tableT_entries[newValueInsertIndex].value = malloc(strlen(value) + 1); // Third - we will dynamically allocate memory for the newly addded value, and then copy the value
                strcpy(Db->tableTypeTable->tableT_entries[newValueInsertIndex].value, value); // Copy the new value
                Db->picnicTableTable->picnicT_entries[i].tableTypeId = newValueInsertIndex;// Fourth - We will assign the new ID to the picnic entry and increase the element count (as we've added a new value - increasing the count)
                Db->tableTypeTable->tableT_ElementCount++; // Increase Element Count
                return;
            }
            // Else - return an Error Message indicating that Chosen Member Name is not Valid
            else{
                printf("Error - Member Name Chosen Not Valid.\n");
                return;
            }
        }
     }
     // If there is no matching table ID - we will throw and return an error message as well
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
    int i, j, k; // Initalize variables i, j, k (ints) - which will be used in our Loops (mainly nested for loops)
    char *neighArray[64]; // initalize a string/char array that is storeed as a pointer called neighArray - which stores up to 64 strings/chars
    char *currentNeighbourName, *tmpNeigh; // Initalize variable currentNeighbourName, tmpNeigh, which are chars and pointers 
    // currentNeighourName will store the name of current neighbourhood name while we're iterating in our for loops 
    // tmpNeigh - will be used whenever we're rearranging for alphabetically sort the names (used for swapping)
    int neighAddedCounter, currentNeighbourID;
    int picnicTCount, diffNeighCount, tableTEC, surfaceMEC, structuralEC, neighEC;

    // Initalize al the int vars listed above ^, where neighAddedCounter will check to see if the neighbourhood is whithint he Array,
    // currentNeighbourID will store the ID of the current picnic tables neighbourhood. picnicTCount is the total numeber of entries and 
    // diffneighCount is how many different neighbourhoods we've found.

    //tableTEC, surfaceMEC, structuralEC, neighEC, are variables that will store their respectd element count (just used for simpliciyt and visual sake later on)
    
    picnicTCount = Db->picnicTableTable->picnicT_ElementCount; // Store the number of picnic tables 
    diffNeighCount = 0; // distinct / different wards (set to 0)

    // Error Check - this will simply make sure that our picnicTableTable and/or Db are NULL - which is it is - will return NULL 
    // as we cant count entries using the Tables and Db that are empty / NULL

    if(Db == NULL || Db->picnicTableTable == NULL){
        printf("Error - No Database Available, or No Elements Within PicnicTable Available");
        return 0;
    }
    // For loop that will iterate through all the picnic tbales and will get the current neighbhd's ID's at that given index position in the iteration
    for(i=0; i < picnicTCount; i++){
        currentNeighbourID = Db->picnicTableTable->picnicT_entries[i].neighbhdId;
        currentNeighbourName = NULL;

        // For loop that will iterate, and lookup the neighbourhood name from the neighbourhood look up table using the code
         for(j=0; j < Db->neighborhoodTable->neighbourhoodT_ElementCount; j++){
            // If statement that checks to see that if theres a match (equal each other) - ID and the currrentNeighbourID
            if(Db->neighborhoodTable->neighbourhoodT_entries[j].code == currentNeighbourID){
                currentNeighbourName = Db->neighborhoodTable->neighbourhoodT_entries[j].value; // Set the neighborhood name from the associated value
                break;
            }
         }
         // If statement that checks to see if there was no name / entry found (IS NULL) - skip or continue
         if(currentNeighbourName == NULL)
            continue;
        

        neighAddedCounter = 0; // THis is a counter, that is set to 0, but while we're iterating through the neighbourrds and find if neighbouhrood name is already in our neighArray, we set the Flag to 0 
        for(k=0; k < diffNeighCount; k++){ // for loop that will check to see if the name is already in the neighArray
            if(strcmp(neighArray[k], currentNeighbourName) == 0){ // if the Names Match
                neighAddedCounter = 1; // Set the flag / counter to 1 indicating that it already exist's within teh neighArray
                 break;
                }
            }

        // if the Name does not exist within the array, add it to the array 
        if(neighAddedCounter == 0){
            neighArray[diffNeighCount++] = currentNeighbourName;
        }
    }
    // This nested for loop, will help rearrange / sort the Neighbourhoods alphabteically
    for(i=0; i < diffNeighCount; i++){
        for(j=0; j < diffNeighCount; j++){
            if(strcmp(neighArray[i], neighArray[j]) < 0){
                tmpNeigh = neighArray[i];
                neighArray[i] = neighArray[j];
                neighArray[j] = tmpNeigh;

            }
        }
    }
    // For loop that will iterate through the neighArray (holds all the neighbourhoods) and print thm 
    for(i=0; i < diffNeighCount; i++){
        printf("\n%s\n", neighArray[i]);
        printf("************************************************\n");

        // For loop that will iterate and go through eahc picnic table, and match it with the current neighbourhood
        for(j=0; j < picnicTCount; j++){
            PicnicTableEntry picTE;
            picTE = Db->picnicTableTable->picnicT_entries[j];
            char *currentEntryNeighName;
            currentEntryNeighName = NULL;
            // This for loop will try to look up the neighbourhood name for the current picnic table entry that we're on
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

                // For loop that will find the name for the table type 
                // this will check to see if the lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to tableT
                for (k=0; k < tableTEC; k++){
                    if(Db->tableTypeTable->tableT_entries[k].code == picTE.tableTypeId){
                        tableT = Db->tableTypeTable->tableT_entries[k].value;
                        break;
                    }
                }

                // Same logic is implemented for surface material
                // For loop that will find the name for the Surface Material 
                // this will check to see if the surface material lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to surfaceMat
                for(k=0; k < surfaceMEC; k++){
                    if(Db->surfaceMaterialTable->tableT_entries[k].code == picTE.surfaceMaterialId){
                        surfaceMat= Db->surfaceMaterialTable->tableT_entries[k].value;
                        break;
                    }
                }

                // Same logic is implemented for structural material
                // For loop that will find the name for the Surface Material 
                // this will check to see if the structural material lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to structuralMat

                for(k=0; k < structuralEC; k++){
                    if(Db->structuralMaterialTable->tableT_entries[k].code == picTE.structuralMaterialId){
                        structuralMat = Db->structuralMaterialTable->tableT_entries[k].value;
                        break;
                    }
                }

                // Print out the results - according to how its mentioned its suppose to look like the example PDF (similar to reportbyWard - except ordered for neighbourhood Alphebrtcially)
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
    int i, j, k; // Initalize variables i, j, k (ints) - which will be used in our Loops (mainly nested for loops)
    char *wardArray[64]; // initalize a string/char array that is storeed as a pointer called neighArray - which stores up to 64 strings/chars
    char *currentWard, *tmpWard; // Initalize variable currentNeighbourName, tmpNeigh, which are chars and pointers 
    int wardAddedCounter;
    int picnicTCount, diffWardCount, tableTEC, surfaceMEC, structuralEC, neighEC;
    // picnicTCount is the total numeber of entries
    // diffWardCount is how many different wards we've found.
    // wardAddedCounter will check to see if the ward is whithin the Array,
    //tableTEC, surfaceMEC, structuralEC, neighEC, are variables that will store their respectd element count (just used for simplicity and visual sake later on in our loops)

    // All very similar to the previous function reportByNieghbourhood ^

    picnicTCount = Db->picnicTableTable->picnicT_ElementCount; // Store the number of picnic tables 
    diffWardCount = 0; // distinct / different wards

    // Error Check - this will simply make sure that our picnicTableTable and/or Db are NULL - which is it is - will return NULL 
    // as we cant count entries using the Tables and Db that are empty / NULL
    if(Db == NULL || Db->picnicTableTable == NULL){
        printf("Error - No Database Available, or No Elements Within PicnicTable Available");
        return 0;
    }

    // For loop that will iterate through all of the picnicTable entries - and will extract the ward for each table entry
     // Very similar to reportByWard
    for(i=0; i < picnicTCount; i++){
         currentWard = Db->picnicTableTable->picnicT_entries[i].ward;
         wardAddedCounter = 0; //already seen this ward (alreadyadded)
    
         // similarly to reportByNeighbourhood - this will just check to see if the current Ward in our iteration already exists in the wardArray
         for(j=0; j < diffWardCount; j++){
            if(strcmp(wardArray[j], currentWard) == 0){ // if the Names match (currentWard we're on in our iteration and ward in the Array at that given iteration)
                wardAddedCounter = 1; // set the counter / flag to 1 indicating that this alreayd exists in the array
                break;
            }
         }
         // if the Ward does not exist within the array, add it to the array 
         if(wardAddedCounter == 0){
            wardArray[diffWardCount++] = currentWard;
         }

    }
    // This nested for loop, will help rearrange / sort the wards in order
    for(i=0; i < diffWardCount; i++){
        for(j=0; j < diffWardCount; j++){
            if(strcmp(wardArray[i], wardArray[j]) < 0){
                tmpWard = wardArray[i];
                wardArray[i] = wardArray[j];
                wardArray[j] = tmpWard;

            }
        }
    }
    // For loop, that will help in printing and formatting our output, that should be similar to the one given in the reportByWard in the example PDF
    for(i=0; i < diffWardCount; i++){
        printf("\n%s\n", wardArray[i]); // This will print out each Unqiue Ward as the Header (Ward 1, Ward 2, Ward 3, etc...., or how many of the wards there are but in ORDER)
        printf("************************************************\n");
        // For loop that will iterate through each and every picnic table entry
        // and will store the given entry (at the index position) in the variable picTE
        for(j=0; j < picnicTCount; j++){
            PicnicTableEntry picTE;
            picTE = Db->picnicTableTable->picnicT_entries[j];

            // This will whcekc to see if the entry belongs to the current ward being printed 
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
                neighEC = Db->neighborhoodTable->neighbourhoodT_ElementCount

                // Similiary to the reportByNeighbourhood, this will do the same where:
                // For loop that will find the ward for the table type 
                // this will check to see if the lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to tableT
                for (k=0; k < tableTEC; k++){
                    if(Db->tableTypeTable->tableT_entries[k].code == picTE.tableTypeId){
                        tableT = Db->tableTypeTable->tableT_entries[k].value;
                        break;
                    }
                }

                // Same logic is implemented for surface material
                // For loop that will find the name for the Surface Material 
                // this will check to see if the surface material lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to surfaceMat
                for(k=0; k < surfaceMEC; k++){
                    if(Db->surfaceMaterialTable->tableT_entries[k].code == picTE.surfaceMaterialId){
                        surfaceMat= Db->surfaceMaterialTable->tableT_entries[k].value;
                        break;
                    }
                }

                // Same logic is implemented for surface material
                // For loop that will find the name for the Surface Material 
                // this will check to see if the surface material lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to structuralMat
                for(k=0; k < structuralEC; k++){
                    if(Db->structuralMaterialTable->tableT_entries[k].code == picTE.structuralMaterialId){
                        structuralMat = Db->structuralMaterialTable->tableT_entries[k].value;
                        break;
                    }
                }
                // Same logic is implemented for surface material
                // For loop that will find the name for the Surface Material 
                // this will check to see if the surface material lookup entry's ID (code) matches the one from the PicnicTable entry, it it does it assigns the 
                // mathcing/corresponding/respcted name to neighbourhood Name
                for(k=0; k < neighEC; k++){
                    if(Db->neighborhoodTable->neighbourhoodT_entries[k].code == picTE.neighbhdId){
                        neighbourhoodName = Db->neighborhoodTable->neighbourhoodT_entries[k].value;
                        break;
                    }
                }
                // Print out the results - according to how its mentioned its suppose to look like the example PDF (similar to reportbyNeighboourhood - except ordered for ward - Reported by Ward)
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
