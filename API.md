# libcleanmem
## API Documentation


### Structures

```c
struct heap_management_instance_t {
  unsigned int total_region_count;
  struct heap_region_t* heap_regions;
};
```

```c
struct heap_region_t {
  bool region_accessed;
  unsigned int region_size;
  unsigned int region_typeid;

  struct heap_region_t* prev_region;
  struct heap_region_t* next_region;

  void* region;
};
```


### Heap Management Methods

```c
void init_heap_management(struct heap_management_instance_t* instance);
```

```c
void destroy_heap_management(struct heap_management_instance_t* instance);
```

```c
void struct heap_region_t* heap_prot_malloc(struct heap_management_instance_t* instance, unsigned int bytes, unsigned int typeid);
```

```c
void heap_management_add_region(struct heap_management_instance_t* instance, struct heap_region_t* region);
```

```c
void heap_management_autofree_unaccessed_regions(struct heap_management_instance_t* instance);
```


### Heap Methods

```c
void* region_prot_heap_access(struct heap_region_t* heap);
```

```c
unsigned int region_query_heap_typeid(struct heap_region_t* heap);
```

```c
void region_manually_free_region(struct heap_region_t* heap);
```


### API Documentation Status

Incomplete as of the 31st of December 2024. Requires more detailed descriptions.
