/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: <TODO: Aksh Chand, Forbes Feild, Vickram Gill, Naval Sachar>
 * Lab instructor: <TODO: Dhara Wagh>
 * Lecture instructor: <TODO: Dhara Wagh>
 */


//nav will atempt this 
//first header files and then complete the .c file 
#ifndef DB_IMPL_H
#define DB_IMPL_H

#include "DB.h"

// Table Type Lookup Entry

typedef struct {
    int id;
    char type[100];
} TableTypeEntry;

// Surface Material Lookup Entry
typedef struct {
    int id;
    char material[100];
} SurfaceMaterialEntry;

// Structural Material Lookup Entry
typedef struct {
    int id;
    char material[100];
} StructuralMaterialEntry;

// Neighbourhood Lookup Entry
typedef struct {
    int id;
    char name[100];
} NeighbourhoodEntry;

// Picnic Table Record (Main Data Table)
typedef struct {
    int tableId;
    int siteId;
    int tableTypeId;
    int surfaceMaterialId;
    int structuralMaterialId;
    char streetAvenue[100];
    int neighbhdId;
    char ward[50];
    char latitude[50];
    char longitude[50];
} PicnicTableEntry;

// Picnic Table Data Table
typedef struct {
    PicnicTableEntry *picnicT_entries;
    int picnicT_ElementCount;
    int picnicT_CapacitySize;
} PicnicTable;

// The Complete Database
typedef struct {
    TableTypeEntry *tableTypes;
    int tableTypeCount;
    int tableTypeCapacity;

    SurfaceMaterialEntry *surfaceMaterials;
    int surfaceMaterialCount;
    int surfaceMaterialCapacity;

    StructuralMaterialEntry *structuralMaterials;
    int structuralMaterialCount;
    int structuralMaterialCapacity;

    NeighbourhoodEntry *neighbourhoods;
    int neighbourhoodCount;
    int neighbourhoodCapacity;

    PicnicTable *picnicTableTable;
} DataBase;

// Global DB Variable
//extern DataBase *Db;


void importDB(char *filename);
void exportDB(char *filename);

// Helper Lookup/Add Prototypes
int lookupOrAddTableType(const char *type);
int lookupOrAddSurfaceMaterial(const char *mat);
int lookupOrAddStructuralMaterial(const char *mat);
void lookupOrAddNeighbourhood(int id, const char *name);

// Reverse Lookup (for export)
const char* getTableTypeById(int id);
const char* getSurfaceMaterialById(int id);
const char* getStructuralMaterialById(int id);
const char* getNeighbourhoodNameById(int id);

#endif // DB_IMPL_H