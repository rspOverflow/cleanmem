/*
 * Copyright (C) 2025 rspOverflow (nanoHeap)
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdlib.h>

#include "cleanmem.h"
#include "cleanmem_structs.h"


void* region_prot_heap_access(struct heap_region_t* heap) {
  if (heap) {
    heap->region_accessed = true;
    return heap->region;
  }

  return NULL;
}

unsigned int region_query_heap_typeid(struct heap_region_t* heap) {
  return heap ? heap->region_typeid : 0;
}

void region_manually_free_region(struct heap_management_instance_t* instance, struct heap_region_t* heap) {
  if (!heap || !instance) return;

  // Update head pointer if freeing the first node
  if (instance->heap_regions == heap) {
    instance->heap_regions = heap->next_region;
  }

  // Unlink from neighbors
  if (heap->next_region) {
    heap->next_region->prev_region = heap->prev_region;
  }

  if (heap->prev_region) {
    heap->prev_region->next_region = heap->next_region;
  }

  free(heap->region);
  free(heap);

  if (instance->total_region_count > 0) {
    instance->total_region_count--;
  }
}
