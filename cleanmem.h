#ifndef CLEANMEM_H
#define CLEANMEM_H

#include "cleanmem_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



void init_heap_management(struct heap_management_instance_t* instance);
void destroy_heap_management(struct heap_management_instance_t* instance);

struct heap_region_t* heap_prot_malloc(struct heap_management_instance_t* instance, unsigned int bytes, unsigned int typeid);
void heap_management_add_region(struct heap_management_instance_t* instance, struct heap_region_t* region);
void heap_management_autofree_unaccessed_regions(struct heap_management_instance_t* instance);

void* region_prot_heap_access(struct heap_region_t* heap);
unsigned int region_query_heap_typeid(struct heap_region_t* heap);
void region_manually_free_region(struct heap_region_t* heap);

#endif