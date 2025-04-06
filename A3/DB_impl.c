/*
 * DB_impl.c
 *
 * This file contains the implementation of internal helper functions used by the database module.
 * These functions handle operations on internal data structures such as the lookup tables
 * for Table Type, Surface Material, Structural Material, and Neighbourhood Name.
 * 
 * Specifically, this file implements:
 *  - lookupOrAddTableType
 *  - lookupOrAddSurfaceMaterial
 *  - lookupOrAddStructuralMaterial
 *  - lookupOrAddNeighbourhood
 *  - getTableTypeById
 *  - getSurfaceMaterialById
 *  - getStructuralMaterialById
 *  - getNeighbourhoodNameById
 *
 * These functions are declared in DB_impl.h and used by DB.c during import/export and query operations.
 * They are not part of the public interface and are not exposed to the dashboard or other modules.
 *
 * Author: Aksh Chand, Forbes Feild, Vickram Gill, Naval Sachar
 * Lab Instructor: Dhara Wagh
 * Lecture Instructor: Dhara Wagh
 */

/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Aksh Chand, Forbes Feild, Vickram Gill, Naval Sachar>
 * Lab instructor: <TODO:Dhara Wagh>
 * Lecture instructor: <TODO: Dhara Wagh>
 */

//#include "DB.h"      /* Import the public database header. */

//nav will also do this 
//here I will figure out what to do 
//call what ever is in the header file and provide the code for that 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB_impl.h"

DataBase *Db = NULL;

// Reusable helper for reallocating any lookup table
#define RESIZE_IF_NEEDED(array, count, capacity, type) \
    if ((count) == (capacity)) { \
        (capacity) *= 2; \
        (array) = realloc((array), sizeof(type) * (capacity)); \
    }

// -------------- LOOKUP + ADD FUNCTIONS -----------------

int lookupOrAddTableType(const char *type) {
    for (int i = 0; i < Db->tableTypeTable->count; i++) {
        if (strcmp(Db->tableTypeTable->entries[i].type, type) == 0)
            return Db->tableTypeTable->entries[i].id;
    }

    RESIZE_IF_NEEDED(Db->tableTypeTable->entries, Db->tableTypeTable->count, Db->tableTypeTable->capacity, TableTypeEntry);

    int newId = Db->tableTypeTable->count + 1;
    Db->tableTypeTable->entries[Db->tableTypeTable->count].id = newId;
    strncpy(Db->tableTypeTable->entries[Db->tableTypeTable->count].type, type, sizeof(Db->tableTypeTable->entries[0].type));
    Db->tableTypeTable->count++;

    return newId;
}

int lookupOrAddSurfaceMaterial(const char *material) {
    for (int i = 0; i < Db->surfaceMaterialTable->count; i++) {
        if (strcmp(Db->surfaceMaterialTable->entries[i].material, material) == 0)
            return Db->surfaceMaterialTable->entries[i].id;
    }

    RESIZE_IF_NEEDED(Db->surfaceMaterialTable->entries, Db->surfaceMaterialTable->count, Db->surfaceMaterialTable->capacity, SurfaceMaterialEntry);

    int newId = Db->surfaceMaterialTable->count + 1;
    Db->surfaceMaterialTable->entries[Db->surfaceMaterialTable->count].id = newId;
    strncpy(Db->surfaceMaterialTable->entries[Db->surfaceMaterialTable->count].material, material, sizeof(Db->surfaceMaterialTable->entries[0].material));
    Db->surfaceMaterialTable->count++;

    return newId;
}

int lookupOrAddStructuralMaterial(const char *material) {
    for (int i = 0; i < Db->structuralMaterialTable->count; i++) {
        if (strcmp(Db->structuralMaterialTable->entries[i].material, material) == 0)
            return Db->structuralMaterialTable->entries[i].id;
    }

    RESIZE_IF_NEEDED(Db->structuralMaterialTable->entries, Db->structuralMaterialTable->count, Db->structuralMaterialTable->capacity, StructuralMaterialEntry);

    int newId = Db->structuralMaterialTable->count + 1;
    Db->structuralMaterialTable->entries[Db->structuralMaterialTable->count].id = newId;
    strncpy(Db->structuralMaterialTable->entries[Db->structuralMaterialTable->count].material, material, sizeof(Db->structuralMaterialTable->entries[0].material));
    Db->structuralMaterialTable->count++;

    return newId;
}

void lookupOrAddNeighbourhood(int id, const char *name) {
    for (int i = 0; i < Db->neighborhoodTable->count; i++) {
        if (Db->neighborhoodTable->entries[i].id == id)
            return;
    }

    RESIZE_IF_NEEDED(Db->neighborhoodTable->entries, Db->neighborhoodTable->count, Db->neighborhoodTable->capacity, NeighbourhoodEntry);

    Db->neighborhoodTable->entries[Db->neighborhoodTable->count].id = id;
    strncpy(Db->neighborhoodTable->entries[Db->neighborhoodTable->count].name, name, sizeof(Db->neighborhoodTable->entries[0].name));
    Db->neighborhoodTable->count++;
}

// -------------- REVERSE LOOKUP (ID → STRING) -----------------

const char* getTableTypeById(int id) {
    for (int i = 0; i < Db->tableTypeTable->count; i++) {
        if (Db->tableTypeTable->entries[i].id == id)
            return Db->tableTypeTable->entries[i].type;
    }
    return "Unknown";
}

const char* getSurfaceMaterialById(int id) {
    for (int i = 0; i < Db->surfaceMaterialTable->count; i++) {
        if (Db->surfaceMaterialTable->entries[i].id == id)
            return Db->surfaceMaterialTable->entries[i].material;
    }
    return "Unknown";
}

const char* getStructuralMaterialById(int id) {
    for (int i = 0; i < Db->structuralMaterialTable->count; i++) {
        if (Db->structuralMaterialTable->entries[i].id == id)
            return Db->structuralMaterialTable->entries[i].material;
    }
    return "Unknown";
}

const char* getNeighbourhoodNameById(int id) {
    for (int i = 0; i < Db->neighborhoodTable->count; i++) {
        if (Db->neighborhoodTable->entries[i].id == id)
            return Db->neighborhoodTable->entries[i].name;
    }
    return "Unknown";
}


//extra notes for this file: 
/*
 * NOTE: Things to keep in mind for these helper functions:
 *
 * - Make sure all lookup tables (tableTypes, surfaceMaterials, etc.) are
 *   initialized with malloc and set to a starting capacity in importDB().
 *
 * - Each table keeps track of:
 *     - the array itself,
 *     - how many entries it currently has (count),
 *     - how much space it has total (capacity).
 *
 * - The RESIZE_IF_NEEDED macro automatically doubles the size of a table
 *   if it runs out of space.
 *
 * - The getXById() functions are used to convert IDs back to text (for export).
 *
 * - We use strcmp() to compare strings, and strncpy() to copy them safely.
 */