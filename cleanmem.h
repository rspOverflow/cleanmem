/*
 * Copyright (C) 2025 rspOverflow (nanoHeap)
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CLEANMEM_H
#define CLEANMEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "cleanmem_structs.h"


void init_heap_management(struct heap_management_instance_t* instance);
void destroy_heap_management(struct heap_management_instance_t* instance);

struct heap_region_t* heap_prot_malloc(struct heap_management_instance_t* instance, unsigned int bytes, unsigned int typeid);
void heap_management_add_region(struct heap_management_instance_t* instance, struct heap_region_t* region);
void heap_management_autofree_unaccessed_regions(struct heap_management_instance_t* instance);

void* region_prot_heap_access(struct heap_region_t* heap);
unsigned int region_query_heap_typeid(struct heap_region_t* heap);
void region_manually_free_region(struct heap_region_t* heap);

#endif  // CLEANMEM_H
