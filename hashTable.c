#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TABLE_SIZE 6

typedef struct entry {
    int key;
    int value;
    struct entry *prev;
    struct entry *next;
} entry_t;

// Hash table structure using an array of doubly linked lists.
typedef struct hash_table {
    entry_t **buckets; // Array of pointers to entry lists
    size_t capacity;   // Number of buckets
    size_t size;       // Total number of entries
} hash_table_t;

// Function to insert an entry into a bucket (inserts at head)
void insert_entry(entry_t **bucket, entry_t *entry) {
    entry->prev = NULL;
    entry->next = *bucket;
    if (*bucket != NULL) {
        (*bucket)->prev = entry;
    }
    *bucket = entry;
}

size_t hash(int key, int table_size) {
    
    int mult = (int)floor(table_size * (key * (sqrt(5) - 1) / 2)) % table_size;
    int div = mult % table_size;
    return div;
}

// Function to double the size of the hash table
void double_table(hash_table_t *ht) {
    size_t new_capacity = ht->capacity * 2;
    // Allocate new buckets; initialize them to NULL
    entry_t **new_buckets = calloc(new_capacity, sizeof(entry_t *));
    if (new_buckets == NULL) {
        fprintf(stderr, "Error: Memory allocation failed while doubling hash table.\n");
        exit(EXIT_FAILURE);
    }

    // Rehash all entries from the old table into the new table.
    for (size_t i = 0; i < ht->capacity; i++) {
        entry_t *entry = ht->buckets[i];
        while (entry != NULL) {
            entry_t *next_entry = entry->next;  // Save next pointer because we'll re-link the entry

            // Compute new index based on the new capacity
            size_t new_index = hash(entry->key, new_capacity);
            // Insert the entry at the head of the new bucket list.
            insert_entry(&new_buckets[new_index], entry);

            entry = next_entry;
        }
    }

    // Free the old buckets array.
    free(ht->buckets);
    // Update the hash table to use the new buckets and capacity.
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
}

// Function to double the size of the hash table
void half_table(hash_table_t *ht) {
    size_t new_capacity = ht->capacity / 2;
    // Allocate new buckets; initialize them to NULL
    entry_t **new_buckets = calloc(new_capacity, sizeof(entry_t *));
    if (new_buckets == NULL) {
        fprintf(stderr, "Error: Memory allocation failed while doubling hash table.\n");
        exit(EXIT_FAILURE);
    }

    // Rehash all entries from the old table into the new table.
    for (size_t i = 0; i < ht->capacity; i++) {
        entry_t *entry = ht->buckets[i];
        while (entry != NULL) {
            entry_t *next_entry = entry->next;  // Save next pointer because we'll re-link the entry

            // Compute new index based on the new capacity
            size_t new_index = hash(entry->key, new_capacity);
            // Insert the entry at the head of the new bucket list.
            insert_entry(&new_buckets[new_index], entry);

            entry = next_entry;
        }
    }

    // Free the old buckets array.
    free(ht->buckets);
    // Update the hash table to use the new buckets and capacity.
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
}

// Create a new hash table with a given initial capacity.
hash_table_t *hash_table_create(size_t capacity) {
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    if (ht == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    ht->buckets = calloc(TABLE_SIZE, sizeof(entry_t *));
    if (ht->buckets == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    ht->capacity = TABLE_SIZE;
    ht->size = 0;
    return ht;
}

// Insert a new key-value pair into the hash table.
void hash_table_insert(hash_table_t *ht, int key, int value) {
    // Create a new entry
    entry_t *new_entry = malloc(sizeof(entry_t));
    if (new_entry == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_entry->key = key;
    new_entry->value = value;
    new_entry->prev = new_entry->next = NULL;

    // Determine the index and insert the entry
    size_t index = hash(key, ht->capacity);
    insert_entry(&ht->buckets[index], new_entry);
    ht->size++;

    // If every bucket has at least one entry, double the table.
    // (Here we check if the table is "full" in the sense that no bucket is empty.
    int full = 1;
    for (size_t i = 0; i < ht->capacity; i++) {
        if (ht->buckets[i] == NULL) {
            full = 0;
            break;
        }
    }
    if (full) {
        double_table(ht);
    }
}

// Delete an entry with the specified key from the hash table.
void hash_table_delete(hash_table_t *ht, int key) {
    // Compute the bucket index using the hash function.
    size_t index = hash(key, ht->capacity);
    entry_t *entry = ht->buckets[index];

    // Traverse the bucket's linked list to find the matching entry.
    while (entry != NULL) {
        if (entry->key == key) {
            // Found the entry to delete.
            if (entry->prev != NULL) {
                // If there's a previous node, link it to the next node.
                entry->prev->next = entry->next;
            } else {
                // If no previous node, then this entry is the head.
                ht->buckets[index] = entry->next;
            }
            if (entry->next != NULL) {
                // Update the next node's previous pointer.
                entry->next->prev = entry->prev;
            }
            free(entry);
            ht->size--;

            int non_empty_buckets = 0;
            for (size_t i = 0; i < ht->capacity; i++) {
                if (ht->buckets[i] != NULL) {
                    non_empty_buckets++;
                }
            }
            if(non_empty_buckets < ht->capacity * .25) {
                half_table(ht);
            }
            return; // Exit after deletion.
        }
        entry = entry->next;
    }
    
    
    // Print a message if the key is not found.
    fprintf(stderr, "Key %d not found in hash table.\n", key);
}


void hash_table_print(hash_table_t *ht) {
    if (ht == NULL) {
        printf("Hash table is NULL.\n");
        return;
    }
    printf("Hash Table Contents:\n");
    // Iterate over each bucket.
    for (size_t i = 0; i < ht->capacity; i++) {
        printf("Bucket %zu: ", i);
        entry_t *entry = ht->buckets[i];
        if (entry == NULL) {
            printf("Empty");
        }
        // Traverse the doubly linked list in this bucket.
        while (entry != NULL) {
            printf("(key: %d, value: %d) -> ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("NULL\n");
    }
}

int main(int argc, char **argv){

    srand(time(NULL));

    hash_table_t *ht = hash_table_create(TABLE_SIZE);
    for(int i = 0; i < TABLE_SIZE; i++){
        int random = (rand() % 1000) + 1;
        hash_table_insert(ht, i, random);
    }
    printf("Hash table size: %zu\n", ht->size);
    printf("Hash table capacity: %zu\n", ht->capacity);
    printf("Hash table load factor: %.2f\n", (float)ht->size / ht->capacity);
    hash_table_print(ht);

    while (ht->size > 1) {
        // Always start from bucket 0 after a deletion.
        for (size_t i = 0; i < ht->capacity && ht->size > 1; i++) {
            // Delete entries from bucket i until it’s empty.
            while (ht->buckets[i] != NULL && ht->size > 1) {
                int key_to_delete = ht->buckets[i]->key;
                hash_table_delete(ht, key_to_delete);
            }
        }
    }

    printf("Hash table size: %zu\n", ht->size);
    printf("Hash table capacity: %zu\n", ht->capacity);
    printf("Hash table load factor: %.2f\n", (float)ht->size / ht->capacity);
    hash_table_print(ht);
    
    for(int i = 0; i < TABLE_SIZE; i++){
        int random = (rand() % 1000) + 1;
        hash_table_insert(ht, i, random);
    }

    printf("Hash table size: %zu\n", ht->size);
    printf("Hash table capacity: %zu\n", ht->capacity);
    printf("Hash table load factor: %.2f\n", (float)ht->size / ht->capacity);
    hash_table_print(ht);

    return 0;
}
