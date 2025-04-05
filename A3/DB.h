/* DB.h
 * 
 * Public interface to the specification for your database implementation
 *
 * Please do not modify any code in this file!  We will be testing your code
 * under the assumption that the public interface matches this interface.
 *
 * Author: <TODO: Aksh Chand, Forbes Feild, Vickram Gill, Naval Sachar>
 * Lab instructor: <TODO: Dhara Wagh>
 * Lecture instructor: <TODO: Dhara Wagh>
 */

 #ifndef DB_H
 #define DB_H
 
 /*
  * DECLARE AND TYPEDEF HERE THE STRUCTS Table, NeighbourhoodTable, AND PicnicTable
  * WHICH WILL BE FIELDS IN THE STRUCT DataBase BELOW. YOU MAY DECLARE ADDITIONAL
  * STRUCTS AS NEEDED.
  */
 
  // Similar to Lab Assignment #2 (Setting up Struct(s) for Hashtable and Hashtable entries)
  typedef struct{
     int code; 
     char *value;
  } TableCVEntry;
 
 // Similar to Lab Assignment #2 (Setting up Struct(s) for Hashtable and Hashtable entries)
  typedef struct{
     TableCVEntry *tableT_entries;
     int tableT_CapacitySize;
     int tableT_ElementCount;
  } Table;
 
 // Similar to Lab Assignment #2 (Setting up Struct(s) for Hashtable and Hashtable entries)
  typedef struct{
     int code; 
     char *value;
  } NeighbourhoodCodeValTableEntry;
 
 // Similar to Lab Assignment #2 (Setting up Struct(s) for Hashtable and Hashtable entries)
  typedef struct{
     NeighbourhoodCodeValTableEntry *neighbourhoodT_entries;
     int neighbourhoodT_CapacitySize;
     int neighbourhoodT_ElementCount;
  } NeighbourhoodTable;
 
  // Similar to Lab Assignment #2 (Setting up Struct(s) for Hashtable and Hashtable entries)
  typedef struct{
     int tableId;
     int siteId;
     int tableTypeId;
     int surfaceMaterialId;
     int structuralMaterialId;
     char *streetAvenue;
     int neighbhdId;
     char *ward;
     char *latitude;
     char *longitude;
  } PicnicTableEntry;
 
  // Similar to Lab Assignment #2 (Setting up Struct(s) for Hashtable and Hashtable entries)
  typedef struct{
     PicnicTableEntry *picnicT_entries;
     int picnicT_CapacitySize;
     int picnicT_ElementCount;
  } PicnicTable;
 
 /*
  * The INIT_SIZE is only relevant if you are using arrays for your data structures. 
  * If you are using linked lists you will not need it
  */
 #define INIT_SIZE 5  
 
 
 /*
  * You may change the internal details of the struct below,
  * only keep it typedef'ed to DataBase
  */
 typedef struct {
     // You can add anything you see fit here
     Table *tableTypeTable;
     Table *surfaceMaterialTable;
     Table *structuralMaterialTable;
     NeighbourhoodTable *neighborhoodTable;
     PicnicTable *picnicTableTable;
 } DataBase;
 
 /* Declare a global DataBase variable*/
 /* That should be the only global variable declared*/
 /* DB.c should have the definition of this variable*/
 extern DataBase *Db;
 
 // *********************
 // Ask if we should implement importDB and exportDB in the header file (mentions not to make any changes here)
 //void importDB(char *filename);
 
 //void exportDB(char *filename);
 
 /*
  * Take the name of a member of the picnicTable entry and a value for that member 
  * as parameters and return the number of entries in the picnicTable which have 
  * that value for the memberName.
  * 
  * This is to be implemented for the following members:
  *  1- Table Type
  *  2- Surface Material
  *  3- Structural Material
  *  4- Neighborhood ID
  *  5- Neighborhood Name
  *  6- Ward
  */
 
 
 int countEntries(char *memberName, char * value);
 
 /*
  * Take the name of a member of the picnicTable entry as an argument 
  * and sort the table in ascending order of the entry values of that member. 
  * The function must be implemented for:
  *   1- Table Type
  *   2- Surface Material
  *   3- Structural Material
  *   4- Neighborhood Name
  *   5- Ward
  */
 void sortByMember(char *memberName);
 
 /*
  * Take a tableID, the name of a member of the picnicTable entry and a value for that 
  * member as parameters, and find the entry which has that tableID and 
  * change its memberName value to newValue. 
  * Members that can be modified:
  *  1- Table Type
  *  2- Surface Material
  *  3- Structural Material 
  * If the new value is not found in the existing tables, this value must be added to the 
  * corresponding table.
  */
 void editTableEntry(int tableID, char *memberName, char *value);
 
 /*
  * print a listing of picnic tables grouped by neigbourhoods in ascending 
  * alphabetical order.
  */
 void reportByNeighbourhood();
 
 /*
  * print a listing of picnic tables grouped by wards in ascending order.
  */
 void reportByWard();
 
 /*
  * Frees all dynamic memory associated with each table upon exit. 
  */
 void freeDB();
 
 
 #endif
 