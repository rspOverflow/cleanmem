/*
 * Copyright (C) 2025 rspOverflow (nanoHeap)
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdlib.h>
#include <stdint.h>

#include "cleanmem.h"
#include "cleanmem_structs.h"


void init_heap_management(struct heap_management_instance_t* instance) {
  if (instance) {
    instance->total_region_count = 0;
    instance->heap_regions = NULL;
  }
}

void destroy_heap_management(struct heap_management_instance_t* instance) {
  if (instance && instance->heap_regions) {
    struct heap_region_t* selected_region = &(instance->heap_regions[0]);

    while(selected_region) {
      struct heap_region_t* next_selected_region = selected_region->next_region;
      region_manually_free_region(selected_region);
      selected_region = next_selected_region;
    }
  }
}

struct heap_region_t* heap_prot_malloc(struct heap_management_instance_t* instance, unsigned int bytes, unsigned int typeid) {
  if (instance) {
    struct heap_region_t* new_region = malloc(sizeof(struct heap_region_t));

    if (new_region) {
      new_region->region_accessed = false;
      new_region->region_size = bytes;
      new_region->region_typeid = typeid;

      new_region->prev_region = NULL;
      new_region->next_region = NULL;
    
      new_region->region = malloc(bytes);

      heap_management_add_region(instance, new_region);
      return new_region;
    }
  }

  return NULL;
}

void heap_management_add_region(struct heap_management_instance_t* instance, struct heap_region_t* region) {
  if(instance && instance->heap_regions && region) {
    struct heap_region_t* loop_prevention_ptr = &(instance->heap_regions[0]);
    struct heap_region_t* selected_region = &(instance->heap_regions[0]);
    uint64_t iteration = 0;
    
    while(selected_region) {
      if (iteration > 0 && loop_prevention_ptr == selected_region) {
        printf("cleanmem: ERROR! Loop detected within managed heap regions!");
        destroy_heap_management(instance);
        abort();
      }
      
      if (selected_region->next_region) {
        selected_region = selected_region->next_region;
      } else {
        break;
      }

      iteration++;
    }

    selected_region->next_region = region;
    region->prev_region = selected_region;
    region->next_region = NULL; // Make sure it's null.
  }
}

void heap_management_autofree_unaccessed_regions(struct heap_management_instance_t* instance) {
  if (instance && instance->heap_regions) {
    struct heap_region_t* selected_region = &(instance->heap_regions[0]);

    while(selected_region) {
      struct heap_region_t* next_region_ptr = selected_region->next_region;
      
      if (!selected_region->region_accessed) {
        region_manually_free_region(selected_region);
      } else {
        selected_region->region_accessed = false;
      }
      
      selected_region = next_region_ptr;
    }
  }
}
