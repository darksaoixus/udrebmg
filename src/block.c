#include "block.h"

Texture2D block_textures[BLOCK_NUM];

// Block textures
void Block_load_textures() {
  block_textures[GRASS] = LoadTexture("assets/blocks/grass.png");
  block_textures[ROAD] = LoadTexture("assets/blocks/road.png");
}

void Block_unload_textures() {
  for (int i = 0; i < BLOCK_NUM; ++i) {
    if (block_textures[i].width == 0) continue;

    UnloadTexture(block_textures[i]);
  }
}

// Chunk
void Chunk_init(Chunk *chunk) {
  for (int i = 0; i < CHUNK_SIDE; ++i) {
    for (int j = 0; j < CHUNK_SIDE; ++j) {
      BlockType type = GRASS;
      if (i == 2 || j == 2) type = ROAD;

      int idx = i * CHUNK_SIDE + j;
      chunk->blocks[idx] = CLITERAL(Block){ 
        .type = type,
        .chunk_pos = CLITERAL(Vector2){ j, i },
      };
    }
  }
}

void Chunk_draw(Chunk *chunk) {
  for (int i = 0; i < CHUNK_SIDE * CHUNK_SIDE; ++i) {
    Block block = chunk->blocks[i];
    Vector2 block_pos = CLITERAL(Vector2){
      .x = chunk->position.x + block.chunk_pos.x * BLOCK_SIDE,
      .y = chunk->position.y + block.chunk_pos.y * BLOCK_SIDE,
    };
    DrawTextureV(block_textures[block.type], block_pos, WHITE);
  }
}

// Region
void Region_init(Region *region) {
  int center_x = region->center.x / (CHUNK_SIDE * BLOCK_SIDE);
  int center_y = region->center.y / (CHUNK_SIDE * BLOCK_SIDE);

  for (int dy = -RENDER_DISTANCE; dy <= RENDER_DISTANCE; ++dy) {
    for (int dx = -RENDER_DISTANCE; dx <= RENDER_DISTANCE; ++dx) {
      Chunk *chunk = &(region->chunks[region->chunk_count++]);
      chunk->position.x = (center_x + dx) * CHUNK_SIDE * BLOCK_SIDE;
      chunk->position.y = (center_y + dy) * CHUNK_SIDE * BLOCK_SIDE;
      Chunk_init(chunk);
    }
  }
}

void Region_update(Region *region) {
  for (int i = 0; i < RENDER_SIDE * RENDER_SIDE; ++i) {
    Chunk_draw(&(region->chunks[i]));
  }
}

