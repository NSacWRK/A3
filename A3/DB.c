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
int countEntries(char *memberName, char * value){
    return 0; // Return for now - as we're creating empty functions (will be worked on later) for MS1
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
