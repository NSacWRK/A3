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

#include "DB.h"      /* Import the public database header. */

//nav will also do this 
//here I will figure out what to do 
//call what ever is in the header file and provide the code for that 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB_impl.h"

DataBase *Db;

// Reusable helper for reallocating any lookup table
#define RESIZE_IF_NEEDED(array, count, capacity, type) \
    if ((count) == (capacity)) { \
        (capacity) *= 2; \
        (array) = realloc((array), sizeof(type) * (capacity)); \
    }

// -------------- LOOKUP + ADD FUNCTIONS -----------------

int lookupOrAddTableType(const char *type) {
    for (int i = 0; i < Db->tableTypeCount; i++) {
        if (strcmp(Db->tableTypes[i].type, type) == 0)
            return Db->tableTypes[i].id;
    }

    RESIZE_IF_NEEDED(Db->tableTypes, Db->tableTypeCount, Db->tableTypeCapacity, TableTypeEntry);

    int newId = Db->tableTypeCount + 1;
    Db->tableTypes[Db->tableTypeCount].id = newId;
    strncpy(Db->tableTypes[Db->tableTypeCount].type, type, sizeof(Db->tableTypes[0].type));
    Db->tableTypeCount++;

    return newId;
}

int lookupOrAddSurfaceMaterial(const char *material) {
    for (int i = 0; i < Db->surfaceMaterialCount; i++) {
        if (strcmp(Db->surfaceMaterials[i].material, material) == 0)
            return Db->surfaceMaterials[i].id;
    }

    RESIZE_IF_NEEDED(Db->surfaceMaterials, Db->surfaceMaterialCount, Db->surfaceMaterialCapacity, SurfaceMaterialEntry);

    int newId = Db->surfaceMaterialCount + 1;
    Db->surfaceMaterials[Db->surfaceMaterialCount].id = newId;
    strncpy(Db->surfaceMaterials[Db->surfaceMaterialCount].material, material, sizeof(Db->surfaceMaterials[0].material));
    Db->surfaceMaterialCount++;

    return newId;
}

int lookupOrAddStructuralMaterial(const char *material) {
    for (int i = 0; i < Db->structuralMaterialCount; i++) {
        if (strcmp(Db->structuralMaterials[i].material, material) == 0)
            return Db->structuralMaterials[i].id;
    }

    RESIZE_IF_NEEDED(Db->structuralMaterials, Db->structuralMaterialCount, Db->structuralMaterialCapacity, StructuralMaterialEntry);

    int newId = Db->structuralMaterialCount + 1;
    Db->structuralMaterials[Db->structuralMaterialCount].id = newId;
    strncpy(Db->structuralMaterials[Db->structuralMaterialCount].material, material, sizeof(Db->structuralMaterials[0].material));
    Db->structuralMaterialCount++;

    return newId;
}

void lookupOrAddNeighbourhood(int id, const char *name) {
    for (int i = 0; i < Db->neighbourhoodCount; i++) {
        if (Db->neighbourhoods[i].id == id)
            return; // already exists
    }

    RESIZE_IF_NEEDED(Db->neighbourhoods, Db->neighbourhoodCount, Db->neighbourhoodCapacity, NeighbourhoodEntry);

    Db->neighbourhoods[Db->neighbourhoodCount].id = id;
    strncpy(Db->neighbourhoods[Db->neighbourhoodCount].name, name, sizeof(Db->neighbourhoods[0].name));
    Db->neighbourhoodCount++;
}

// -------------- REVERSE LOOKUP (ID → STRING) -----------------

const char* getTableTypeById(int id) {
    for (int i = 0; i < Db->tableTypeCount; i++) {
        if (Db->tableTypes[i].id == id)
            return Db->tableTypes[i].type;
    }
    return "Unknown";
}

const char* getSurfaceMaterialById(int id) {
    for (int i = 0; i < Db->surfaceMaterialCount; i++) {
        if (Db->surfaceMaterials[i].id == id)
            return Db->surfaceMaterials[i].material;
    }
    return "Unknown";
}

const char* getStructuralMaterialById(int id) {
    for (int i = 0; i < Db->structuralMaterialCount; i++) {
        if (Db->structuralMaterials[i].id == id)
            return Db->structuralMaterials[i].material;
    }
    return "Unknown";
}

const char* getNeighbourhoodNameById(int id) {
    for (int i = 0; i < Db->neighbourhoodCount; i++) {
        if (Db->neighbourhoods[i].id == id)
            return Db->neighbourhoods[i].name;
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