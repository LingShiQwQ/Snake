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
    // Font 0x00AED1, Alpha = 0xA0

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
    vector<SDL_FRect> multi_text_rect;

    for (int i = text.size(); i > 0; i--) {
        multi_text_rect.push_back({window_x - 18 * i, 0, 16, 32});
    }

    //SDL_Log("DrawScore() -> to_string() called");

    for (int i = 0; i < text.size(); i++)
    {
        // 创建一个只包含单个字符的字符串
        char single_char_str[2] = {text[i], '\0'};

        // 正确的函数调用
        surf_text = TTF_RenderText_Blended(fnt, single_char_str, 1, {0x00, 0xAE, 0xD1});
        if (!surf_text)
            continue;

        tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
        if (!tex_text)
        {
            SDL_DestroySurface(surf_text);
            continue;
        }

        SDL_SetTextureBlendMode(tex_text, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(tex_text, 0xA0);
        SDL_RenderTexture(rdr, tex_text, NULL, &multi_text_rect[i]);

        SDL_DestroyTexture(tex_text);
        SDL_DestroySurface(surf_text);
    }
}
void DrawGameOver()
{
    string t_score = std::to_string(snake.score);
    string t_best = std::to_string(snake.history_best > snake.best ? snake.history_best : snake.best);
    string t_text_title = "YOU LOST!";
    string t_text_sub = "Scores: ";
    t_text_sub.append(t_score);
    t_text_sub = t_text_sub + "              Best: " + t_best;
    string t_text_sub2 = "Press ESC to EXIT                  Press ANY key to restart";

    TTF_SetFontSize(fnt, 58);
    text_rect = {window_x / 2 - window_x / 5 - 2, window_y / 2 - window_y / 3.6f, 360, 140};
    surf_text = TTF_RenderText_Blended(fnt, t_text_title.c_str(), t_text_title.size(), {0xff, 0xff, 0xff});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);

    TTF_SetFontSize(fnt, 32);
    text_rect = {window_x / 2 - window_x / 3.55f + 5, window_y / 2 + window_y / 32 - 10, 480, 60};
    surf_text = TTF_RenderText_Blended(fnt, t_text_sub.c_str(), t_text_sub.size(), {0xff, 0xff, 0xff});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);

    TTF_SetFontSize(fnt, 36);
    text_rect = {window_x / 2 - window_x / 2.6f - 5, window_y / 2 + window_y / 8, 680, 60};
    surf_text = TTF_RenderText_Blended(fnt, t_text_sub2.c_str(), t_text_sub2.size(), {0xff, 0xff, 0xff});
    tex_text = SDL_CreateTextureFromSurface(rdr, surf_text);
    SDL_RenderTexture(rdr, tex_text, NULL, &text_rect);
    SDL_DestroySurface(surf_text);
    SDL_DestroyTexture(tex_text);

    SDL_RenderPresent(rdr);
}