//   Puzzlesquare  Copyright (C) 2009  Aaron Greene

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.

//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.

//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "Pch.h"
#include "AppPuzzlesquare.h"

AppPuzzletile::AppPuzzletile(int squareLength): m_squareLength(squareLength),
                                                m_screen(NULL),
                                                m_square(NULL)
{}

bool AppPuzzletile::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    if(TTF_Init() == -1)
    {
        return false;
    }

    SDL_Surface *tileImage = IMG_Load("square.png");
    if (tileImage == NULL)
    {
        return false;
    }

    TTF_Font *font = TTF_OpenFont("Verdana.ttf", 20);
    if (font == NULL)
    {
        SDL_FreeSurface(tileImage);
        return false;
    }

    m_screen = SDL_SetVideoMode(m_squareLength * tileImage->h, m_squareLength * tileImage->h, 32, SDL_SWSURFACE);
    if (m_screen == NULL)
    {
        TTF_CloseFont(font);
        SDL_FreeSurface(tileImage);
        return false;
    }

    SDL_Color textColor = {0, 0, 0}; //Black text
    m_square = new Square(m_squareLength, tileImage, font, textColor);

    SDL_WM_SetCaption("Puzzlesquare", NULL);

    TTF_CloseFont(font);
    SDL_FreeSurface(tileImage);
    return true;
}

void AppPuzzletile::Run()
{
    if (!Init())
    {
        CleanUp();
        return;
    }

    m_square->Shuffle();

    bool winner = false;
    int winnerTick = 0;
    SDL_Event event;

    while(true)
    {
        int startTick = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            if (!winner)
            {
                m_square->HandleEvent(event);
            }
        }

        if (event.type == SDL_QUIT)
        {
            break; //Quitter! quit game
        }

        SDL_FillRect(m_screen, &m_screen->clip_rect, SDL_MapRGB(m_screen->format, 135, 135, 135)); //Draw grey screen
        m_square->Draw(m_screen);

        if (winner)
        {
            if ((SDL_GetTicks() - winnerTick) > 2500)
            {
                break; //Winner! quit game
            }
            ShowWinnerMessage();
        }
        else
        {
            if (m_square->IsWinner())
            {
                winner = true;
                winnerTick = SDL_GetTicks();
            }
        }

        SDL_Flip(m_screen);

        int deltaTime = SDL_GetTicks() - startTick;
        if(deltaTime < 1000 / FRAMES_PER_SECOND)
        {
            SDL_Delay(( 1000 / FRAMES_PER_SECOND ) - deltaTime);
        }
    }

    CleanUp();
}

void AppPuzzletile::ShowWinnerMessage()
{
    TTF_Font *font = TTF_OpenFont("Verdana.ttf", 45);
    SDL_Color textColor = {87, 174, 255}; //Blueish color
    SDL_Surface *message = TTF_RenderText_Solid(font, "You Won!", textColor);

    SDL_Rect offset;
    offset.x = (m_screen->w - message->w)/2;
    offset.y = (m_screen->h - message->h)/2;

    SDL_BlitSurface(message, NULL, m_screen, &offset);

    TTF_CloseFont(font);
    SDL_FreeSurface(message);
}

void AppPuzzletile::CleanUp()
{
    if (m_square != NULL)
    {
        delete m_square;
    }

    SDL_FreeSurface(m_screen);
    SDL_Quit();
    TTF_Quit();
}
