# libcleanmem
## API Documentation

This library provides a lightweight, manual-tracking garbage collection system for C programs, centered around "protected" heap regions and access tracking.

### Structures

```c
struct heap_management_instance_t {
  unsigned int total_region_count;
  struct heap_region_t* heap_regions;
};
```
* **total_region_count**: The number of active memory regions currently tracked by this instance.
* **heap_regions**: A pointer to the head of the doubly-linked list of tracked regions.

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
* **region_accessed**: A "dirty" flag. Set to `true` when accessed; used by the autofree logic to determine if the region is still in use.
* **region_size**: The size of the allocated buffer in bytes.
* **region_typeid**: User-defined identifier for the data type stored in the region.
* **region**: The actual pointer to the raw memory allocated on the heap.

---

### Heap Management Methods

```c
void init_heap_management(struct heap_management_instance_t* instance);
```
Initializes a new heap management instance. Sets the region count to zero and nullifies the list head. Must be called before any allocations are performed.

```c
void destroy_heap_management(struct heap_management_instance_t* instance);
```
Iterates through all tracked regions, manually frees the associated memory, and destroys the instance. Use this for cleanup at the end of the program lifecycle.

```c
struct heap_region_t* heap_prot_malloc(struct heap_management_instance_t* instance, unsigned int bytes, unsigned int typeid);
```
Allocates a new protected heap region of `bytes` size. Automatically registers the region with the provided management instance. Returns a pointer to the wrapper structure or `NULL` if allocation fails.

```c
void heap_management_add_region(struct heap_management_instance_t* instance, struct heap_region_t* region);
```
Internal logic used to append a new `heap_region_t` to the management instance's linked list. It includes safety checks for circular loops.

```c
void heap_management_autofree_unaccessed_regions(struct heap_management_instance_t* instance);
```
The core "Garbage Collection" hook. It scans all tracked regions:
1. If `region_accessed` is `false`, the region is freed.
2. If `region_accessed` is `true`, it is reset to `false` for the next cycle.

---

### Heap Methods

```c
void* region_prot_heap_access(struct heap_region_t* heap);
```
The primary way to retrieve the raw data pointer. Calling this automatically sets the `region_accessed` flag to `true`, shielding it from the next `autofree` cycle.

```c
unsigned int region_query_heap_typeid(struct heap_region_t* heap);
```
Returns the `typeid` associated with the region. Useful for runtime type checking when handling generic heap regions.

```c
void region_manually_free_region(struct heap_management_instance_t* instance, struct heap_region_t* heap);
```
Immediately frees a specific region and unlinks it from the management instance. Correctly updates the instance's head pointer if the first node is removed.

---

### API Documentation Status

Updated May 2026. Complete for now. Library is now rarely maintained/still WIP.
