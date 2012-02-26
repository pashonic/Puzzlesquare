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

#pragma once

class Square
{

public:
    Square(const int size, SDL_Surface *tileBackGround, TTF_Font *font, SDL_Color fontColor);
    ~Square();

    void Shuffle();
    void Draw(SDL_Surface *screen);
    bool IsWinner();
    void HandleEvent(SDL_Event &event);

private:
    struct Tile
    {
        Tile():m_tileImage(NULL), m_id(0){}
        ~Tile()
        {
            if (m_tileImage != NULL)
            {
                SDL_FreeSurface(m_tileImage);
            }
        }
        SDL_Surface *m_tileImage;
        int m_id;
        int m_x;
        int m_y;
        int m_xOrder;
        int m_yOrder;
    };

    void Init(const int size, SDL_Surface *tileBackGround, TTF_Font *font, SDL_Color fontColor);
    Tile *GetTile(const int x, const int y);
    Tile *GetTileAtPoint(const int x, const int y);
    void SwapTiles(Tile *tileA, Tile *tileB);
    bool AreNeighbors(Tile *tileA, Tile *tileB);
    static void ApplySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination);

    Tile *m_tiles;
    Tile *m_blankTile;
    const int m_size;
    const int m_tileCount;
    const int m_tileSize;
};
