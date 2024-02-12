#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <qrencode.h>

void generateQRCode(const char *data, int size) {
    QRcode *qrcode = QRcode_encodeString(data, 0, QR_ECLEVEL_L, QR_MODE_8, 1);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_CreateWindowAndRenderer(size, size, SDL_WINDOW_FULLSCREEN | SDL_RENDERER_PRESENTVSYNC, &window, &renderer);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);
    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int y = 0; y < qrcode->width; y++) {
        for (int x = 0; x < qrcode->width; x++) {
            if (qrcode->data[y * qrcode->width + x] & 1) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                        quit = 1;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        for (int y = 0; y < qrcode->width; y++) {
            for (int x = 0; x < qrcode->width; x++) {
                if (qrcode->data[y * qrcode->width + x] & 1) {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    QRcode_free(qrcode);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int SDL_main(int argc, char* argv[]) {
    const char *data = "Pratham";
    int size = 0;

    generateQRCode(data, size);

    return 0;
}
