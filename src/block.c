#include "block.h"

#include <stdlib.h>

Chunk Chunk_new(Arena *arena, Vector2 pivot_pos) {
  Chunk chunk = {0};
  chunk.pivot_pos = pivot_pos;
  chunk.blocks = (Block *)Arena_alloc(arena, sizeof(Block) * CHUNK_AREA);
  if (chunk.blocks == NULL) return chunk;

  for (size_t i = 0; i < CHUNK_SIDE; ++i) {
    for (size_t j = 0; j < CHUNK_SIDE; ++j) {
      size_t idx = (i * CHUNK_SIDE) + j;
      chunk.blocks[idx] = CLITERAL(Block){
        .type = GRASS,
        .chunk_pos = CLITERAL(Vector2){ .x = j, .y = i },
      };
    }
  }

  return chunk;
}

void Chunk_draw(Chunk chunk) {
  for (size_t i = 0; i < CHUNK_AREA; ++i) {
    Color col = LIME;
    Block block = chunk.blocks[i];
    Vector2 block_pos = CLITERAL(Vector2){
      .x = chunk.pivot_pos.x + CHUNK_SIDE * block.chunk_pos.x,
      .y = chunk.pivot_pos.y + CHUNK_SIDE * block.chunk_pos.y,
    };
    if (block.chunk_pos.x == 2) col = PURPLE;
    DrawRectangleV(block_pos, CLITERAL(Vector2){ CHUNK_SIDE, CHUNK_SIDE }, col);
  }
}

// Arena
Arena Arena_init(size_t cap) {
  Arena arena = {0};
  arena.buf = (char *)malloc(cap);
  arena.capacity = cap;
  arena.offset = 0;

  return arena;
}

void *Arena_alloc(Arena *arena, size_t size) {
  if (arena->offset + size >= arena->capacity) return NULL;

  void *offset = (void *)(arena->buf + arena->offset);
  arena->offset += size;
  return offset;
}

void Arena_free(Arena *arena) {
  free(arena->buf);
}

