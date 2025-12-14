#include "draw.h"
#include "core.h"

SDL_Renderer *rdr, *fd, *hd, *bd;
SDL_Surface *surf_text;
SDL_Texture *tex_text;
SDL_FRect text_rect;

bool InitRenders()
{
    rdr = SDL_CreateRenderer(win, NULL);
    if (rdr == nullptr)
    {
        SDL_Log("rdr: SDL_CreateRenderer() failed: %s", SDL_GetError());
        return false;
    }
    fd = rdr;
    hd = rdr;
    bd = rdr;
    

    // BackGround 0xBFF4FF
    // Snake  0xCABFFF
    // Food 0xF4FFBF
    // Font 0x00AED1, Alpha = 0xA6

    return true;
}
void DestroyRenderers()
{
    SDL_DestroyRenderer(rdr);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);
}

void DrawAll()
{
    DrawBackground();
    DrawBody();
    DrawFood();
    DrawScore();

    PresentRenders();
}
void PresentRenders()
{
    //SDL_Log("PresentRenders() called");
    SDL_RenderPresent(rdr);
}
void DrawBackground()
{
    //SDL_Log("DrawBackground() called");
    SDL_SetRenderDrawColor(rdr, 0xBF, 0xF4, 0xFF, 0xFF);
    SDL_RenderClear(rdr);
}
void DrawFood()
{
    //SDL_Log("DrawFood() called");
    SDL_SetRenderDrawColor(fd, 0xF4, 0xFF, 0xBF, 0xFF);
    SDL_RenderFillRect(fd, &food.rect);
}
void DrawBody()
{
    SDL_SetRenderDrawColor(bd, 0xCA, 0xBF, 0xFF, 0xFF);
    // SDL_Log("DrawBody() called");
    int i = 0;
    for (auto inter_draw : snake.body) {
        //SDL_Log("Called DrawBody(): %d in %d", i, snake.body.size());
        SDL_RenderFillRect(bd, &inter_draw);
        i++;
    }

}
void DrawScore()
{
    //SDL_Log("DrawScore() called");
    string text = std::to_string(snake.score);
    text_rect = {window_x - 24, 0, 20, 36};
    //SDL_Log("DrawScore() -> to_string() called");

    surf_text = TTF_RenderText_Blended(fnt, text.c_str(), text.size(), {0x00, 0xAE, 0xD1});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    //SDL_Log("DrawScore() -> Transformared Surface to Texture");

    SDL_SetTextureBlendMode(tex_text, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(tex_text, 0xA6);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);

    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);
    //SDL_Log("DrawScore() -> SDL_RenderTexture() called");
}
void DrawGameOver()
{
    string t_score = std::to_string(snake.score);
    string t_text_title = "YOU LOST!";
    string t_text_sub = "Your Scores: ";
    t_text_sub.append(t_score);
    string t_text_sub2 = "Press ESC to EXIT                  Press ANY key to restart";

    TTF_SetFontSize(fnt, 50);
    text_rect = {window_x / 2 - window_x / 5 - 10, window_y / 2 - window_y / 3.6f, 360, 160};
    surf_text = TTF_RenderText_Blended(fnt, t_text_title.c_str(), t_text_title.size(), {0xff, 0xff, 0xff});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);

    TTF_SetFontSize(fnt, 24);
    text_rect = {window_x / 2 - window_x / 6.5f, window_y / 2 + window_y / 32 - 10, 240, 60};
    surf_text = TTF_RenderText_Blended(fnt, t_text_sub.c_str(), t_text_sub.size(), {0xff, 0xff, 0xff});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);

    TTF_SetFontSize(fnt, 32);
    text_rect = {window_x / 2 - window_x / 3, window_y / 2 + window_y / 8, 600, 60};
    surf_text = TTF_RenderText_Blended(fnt, t_text_sub2.c_str(), t_text_sub2.size(), {0xff, 0xff, 0xff});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);

    SDL_RenderPresent(rdr);
}