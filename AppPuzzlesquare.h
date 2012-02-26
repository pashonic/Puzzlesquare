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
#include "Square.h"

#define FRAMES_PER_SECOND 40

class AppPuzzletile
{
public:
    AppPuzzletile(int squareLength);
    void Run();

private:
    bool Init();
    bool Draw();
    void ShowWinnerMessage();
    void CleanUp();

    const int m_squareLength;
    SDL_Surface *m_screen;
    Square *m_square;
};
