#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
  int width;
  int height;
  SDL_Window *window;
  SDL_Renderer *renderer;
} App;

static void draw_pixel(App *app, float x, float y, uint8_t r, uint8_t g, uint8_t b)
{
  if (x < 0 || x > app->width || y < 0 || y > app->height)
  {
    return;
  }

  SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
  SDL_RenderPoint(app->renderer, x, y);
}

int main(int argc, char* argv[])
{
  App app = {0};
  bool done = false;
  SDL_FRect rectangle = {
    .x = 0.0,
    .y = 0.0,
    .h = 30.0,
    .w = 30.0
  };

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
    return 3;
  }

  if (!SDL_CreateWindowAndRenderer("SimpleQR", 320, 240, SDL_WINDOW_RESIZABLE, &app.window, &app.renderer))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window and renderer: %s\n", SDL_GetError());
    return 3;
  }

  if (app.window == NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  if (!SDL_GetWindowSize(app.window, &app.width, &app.height))
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get width and height from the screen: %s\n", SDL_GetError());
    return 1;
  }

  while (!done)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        done = true;
      }
    }
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

    for (int i = 0; i < 30; i++)
    {
      for (int j = 0; j < 30; j++)
      {
        draw_pixel(&app, 100 + j, 100 + i, 255, 255, 255);
      }
    }

    SDL_RenderPresent(app.renderer);
  }

  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);

  SDL_Quit();
  return 0;
}

