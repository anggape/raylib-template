#include <raylib.h>

int main(int argc, char **argv) {
    InitWindow(720, 360, "sample");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    return 0;
}