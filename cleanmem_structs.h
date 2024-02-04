#ifndef CLEANMEM_STRUCTS_H
#define CLEANMEM_STRUCTS_H

#include <stdbool.h> // For compatibility with versions before C17



struct heap_region_t{
  bool region_accessed;
  unsigned int region_size;
  unsigned int region_typeid;

  // Linking the heap regions in a chain so that we don't get lost
  struct heap_region_t* prev_region;
  struct heap_region_t* next_region;

  void* region;
};

struct heap_management_instance_t {
  unsigned int total_region_count;
  struct heap_region_t* heap_regions;
};

#endif