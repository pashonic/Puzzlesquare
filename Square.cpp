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
#include "Square.h"

Square::Square(const int size, SDL_Surface *tileBackGround, TTF_Font *font, SDL_Color fontColor): m_tiles(NULL),
                                                                                                  m_blankTile(NULL),
                                                                                                  m_size(size),
                                                                                                  m_tileCount(m_size * m_size),
                                                                                                  m_tileSize(tileBackGround->h)
{
    Init(size, tileBackGround, font, fontColor);
}

void Square::Init(const int size, SDL_Surface *tileBackGround, TTF_Font *font, SDL_Color fontColor)
{
    m_tiles = new Tile[m_tileCount];

    int tileCount = 0;
    Tile *tile = m_tiles;
    SDL_Surface *tileImage = NULL;

    for (int y = 0; y < m_size; y++)
    {
        for (int x = 0; x < m_size; x++)
        {
            if (tileCount > m_tileCount - 2)
            {
                tileImage = SDL_CreateRGBSurface(SDL_SWSURFACE, m_tileSize, m_tileSize, 32, 135, 135, 135, 255); //Grey black surface
                m_blankTile = tile;
            }
            else
            {
                char tileCountTextString[10];
                SDL_Color textColor = {0, 0, 0}; //Black text
                sprintf(tileCountTextString, "%d",tileCount + 1);
                SDL_Surface *fontImage = TTF_RenderText_Solid(font, tileCountTextString, textColor);

                tileImage = SDL_ConvertSurface(tileBackGround, tileBackGround->format, SDL_SWSURFACE);
                ApplySurface((m_tileSize - fontImage->w)/2, (m_tileSize - fontImage->h)/2, fontImage, tileImage);
                SDL_FreeSurface(fontImage);
            }

            tile->m_tileImage = tileImage;
            tile->m_id = tileCount;
            tile->m_xOrder = x;
            tile->m_yOrder = y;
            tile->m_x = x * m_tileSize;
            tile->m_y = y * m_tileSize;

            tile++;
            tileCount++;
        }
    }
}

void Square::Draw(SDL_Surface *screen)
{
    for (int i = 0; i < m_tileCount; i++)
    {
        ApplySurface(m_tiles[i].m_x, m_tiles[i].m_y, m_tiles[i].m_tileImage, screen);
    }
}

void Square::Shuffle()
{
    srand((unsigned)time(0));
    for (int i = 0; i < 1000; i++) // Shuffle square 1000 times
    {
        int x = m_blankTile->m_xOrder;
        int y = m_blankTile->m_yOrder;

        switch (rand() % 4)
        {
            case 0:
                x++;
                break;
            case 1:
                x--;
                break;
            case 2:
                y++;
                break;
            case 3:
                y--;
                break;
        }

        if (x >= 0 && x < m_size && y >= 0 && y < m_size)
        {
            SwapTiles(m_blankTile, GetTile(x, y));
        }
    }
}

Square::Tile *Square::GetTile(const int x, const int y)
{
    return &m_tiles[(y * m_size) + x];
}

Square::Tile *Square::GetTileAtPoint(const int x, const int y)
{
    return &m_tiles[y / m_tileSize * m_size + x / m_tileSize];
}

void Square::HandleEvent(SDL_Event &event)
{
    if (event.type != SDL_MOUSEBUTTONDOWN || event.button.button != SDL_BUTTON_LEFT)
    {
        return;
    }

    Tile *clickedTile = GetTileAtPoint(event.button.x, event.button.y);
    if (clickedTile == NULL)
    {
        return;
    }

    if (AreNeighbors(m_blankTile, clickedTile))
    {
        SwapTiles(clickedTile, m_blankTile);
    }
}

bool Square::IsWinner()
{
    for (int i = 0; i < m_tileCount; i++)
    {
        if (m_tiles[i].m_id != i)
        {
            return false;
        }
    }
    return true;
}

bool Square::AreNeighbors(Tile *tileA, Tile *tileB)
{
    if (((abs(tileA->m_xOrder - tileB->m_xOrder) == 1 && tileA->m_yOrder == tileB->m_yOrder))||
        ((abs(tileA->m_yOrder - tileB->m_yOrder) == 1 && tileA->m_xOrder == tileB->m_xOrder)))
    {
        return true;
    }
    return false;
}

void Square::SwapTiles(Tile *tileA, Tile *tileB)
{

    if (m_blankTile == tileA)
    {
        m_blankTile = tileB;
    }
    else if (m_blankTile == tileB)
    {
        m_blankTile = tileA;
    }

    std::swap(tileA->m_tileImage, tileB->m_tileImage);
    std::swap(tileA->m_id, tileB->m_id);
}

Square::~Square()
{
    delete [] m_tiles;
}

void Square::ApplySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    if (source == NULL || destination == NULL)
    {
        return;
    }

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

