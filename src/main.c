#include "raylib.h"

#include "block.h"

int main(void) {
  InitWindow(800, 600, "UdreBMG - Demo");
  SetTargetFPS(60);

  Arena arena = Arena_init(sizeof(Block) * CHUNK_AREA * 5);
  Chunk chunk = Chunk_new(&arena, CLITERAL(Vector2){ 20, 20 });

  Camera2D camera = {0};
  camera.target = CLITERAL(Vector2){
    chunk.pivot_pos.x + 40,
    chunk.pivot_pos.y + 40
  };
  camera.offset = CLITERAL(Vector2){ 400, 300 };
  camera.rotation = 0;
  camera.zoom = 1;

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 2;
    if (IsKeyDown(KEY_LEFT)) camera.target.x -= 2;
    if (IsKeyDown(KEY_DOWN)) camera.target.y += 2;
      if (IsKeyDown(KEY_UP)) camera.target.y -= 2;

    BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode2D(camera);
        Chunk_draw(chunk);
      EndMode2D();

      DrawText("I'm alive", 190, 200, 20, RED);
    EndDrawing();
  }

  CloseWindow();
  Arena_free(&arena);
  
  return 0;
}

