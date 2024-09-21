#ifndef _BLOCK_H_

#include <stddef.h>

#include "raylib.h"

#define CHUNK_SIDE 16
#define CHUNK_AREA (CHUNK_SIDE * CHUNK_SIDE)

typedef enum {
  GRASS = 0,
} BlockType;

typedef struct {
  BlockType type;
  Vector2 chunk_pos;
} Block;

typedef struct {
  Block *blocks;
  Vector2 pivot_pos;
} Chunk;

typedef struct {
  char *buf;
  size_t capacity;
  size_t offset;
} Arena;

// Chunk
Chunk Chunk_new(Arena *arena, Vector2 pivot_pos);
void Chunk_draw(Chunk chunk);

// Arena
Arena Arena_init(size_t cap);
void *Arena_alloc(Arena *arena, size_t size);
void Arena_free(Arena *arena);

#endif // _BLOCK_H_
