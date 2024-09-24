#ifndef _BLOCK_H_
#define _BLOCK_H_

#define BLOCK_SIDE 16
#define CHUNK_SIDE 10

#define RENDER_DISTANCE 3
#define RENDER_SIDE (RENDER_DISTANCE * 2 + 1)

#include "raylib.h"


typedef enum {
  GRASS = 0,
  ROAD,
  BLOCK_NUM
} BlockType;

extern Texture2D block_textures[BLOCK_NUM];

typedef struct {
  BlockType type;
  Vector2 chunk_pos;
} Block;

typedef struct {
  Block blocks[CHUNK_SIDE * CHUNK_SIDE];
  Vector2 position;
} Chunk;

typedef struct {
  Chunk chunks[RENDER_SIDE * RENDER_SIDE];
  int free_chunks[RENDER_SIDE * RENDER_SIDE];
  Vector2 center;
  int chunk_count;
} Region;

// Block textures
void Block_load_textures();
void Block_unload_textures();

// Chunk
void Chunk_init(Chunk *chunk);
void Chunk_draw(Chunk *chunk);

// Region
void Region_init(Region *region);
void Region_update(Region *region);

#endif // _BLOCK_H_
