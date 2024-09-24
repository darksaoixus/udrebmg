#include "raylib.h"
#include "raymath.h"

#include "block.h"

int main(void) {
  InitWindow(800, 600, "UdreBMG - Demo");
  SetTargetFPS(60);

  Block_load_textures();

  Region region = {0};
  region.center = CLITERAL(Vector2){ 400, 300 };
  Region_init(&region);

  Camera2D camera = {0};
  camera.offset = CLITERAL(Vector2){ CHUNK_SIDE / 2, CHUNK_SIDE / 2 };
  camera.target = region.center;
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  char buffer[256];

  while (!WindowShouldClose()) {
    Vector2 dir = {0};
    dir.x = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
    dir.y = (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));

    Vector2 normal_dir = Vector2Normalize(dir);
    camera.target.x += normal_dir.x * 3.0f;
    camera.target.y += normal_dir.y * 3.0f;
    BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode2D(camera);
        Region_update(&region);
      EndMode2D();

      snprintf(buffer, 256, "Camera pos: (%f, %f)", camera.target.x, camera.target.y);
      DrawText(buffer, 190, 200, 20, RED);
    EndDrawing();
  }

  Block_unload_textures();
  CloseWindow();
  
  return 0;
}

