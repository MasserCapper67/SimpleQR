#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static int window_height;
static int window_width;
static SDL_Window *window;
static SDL_Renderer *renderer;

static void draw_pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b)
{
  if (x < 0 || x > window_width)
  {
    fprintf(stderr, "The value of x(%d) is out of the screen\n", x);
    return;
  }

  if (y < 0 || y > window_height)
  {
    fprintf(stderr, "The value of y(%d) is out of the screen\n", y);
    return;
  }

  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderPoint(renderer, x, y);
}

int main(int argc, char* argv[])
{
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

  if (!SDL_CreateWindowAndRenderer("SimpleQR", 320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window and renderer: %s\n", SDL_GetError());
    return 3;
  }

  if (window == NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  if (!SDL_GetWindowSize(window, &window_width, &window_height))
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 30; i++)
    {
      for (int j = 0; j < 30; j++)
      {
        draw_pixel(100 + j, 100 + i, 255, 255, 255);
      }
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}

