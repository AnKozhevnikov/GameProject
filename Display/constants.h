//
// Created by b4cksl4sh on 2/22/24.
//

#ifndef DISPLAY_CONSTANTS_H
#define DISPLAY_CONSTANTS_H

namespace constants{
    //Основное окно для графики
    const int LinesInGraphixWindow = 50;
    const int ColumnsInGraphixWindow = 100;

    //Окно для вывода подсказок/биндов
    const int LinesInBindsWindow = LinesInGraphixWindow / 2;
    const int ColumnsInBindsWindow = 30;

    //Нижнее окно для вывода событий
    const int LinesInEventWindow = LinesInGraphixWindow - LinesInBindsWindow;
    const int ColumnsInEventWindow = ColumnsInBindsWindow;

    constexpr int LinesInScreen = LinesInGraphixWindow;
    constexpr int ColumnsInScreen = ColumnsInGraphixWindow + ColumnsInBindsWindow;
}

#endif //DISPLAY_CONSTANTS_H