//
// Created by b4cksl4sh on 2/22/24.
//

#ifndef DISPLAY_CONSTANTS_H
#define DISPLAY_CONSTANTS_H

namespace constants{
    //Основное окно для графики
    const int LinesInGraphixWindow = 52;
    const int ColumnsInGraphixWindow = 102;


    //Окно для вывода подсказок/биндов
    const int LinesInBindsWindow = LinesInGraphixWindow / 3;
    const int ColumnsInBindsWindow = 40;

    //Нижнее окно для вывода событий
    const int LinesInEventWindow = LinesInGraphixWindow - LinesInBindsWindow;
    //const int LinesInEventWindow = LinesInBindsWindow;
    const int ColumnsInEventWindow = ColumnsInBindsWindow;

    constexpr int LinesInScreen = LinesInGraphixWindow;
    constexpr int ColumnsInScreen = ColumnsInGraphixWindow + ColumnsInBindsWindow;
}

#endif //DISPLAY_CONSTANTS_H
