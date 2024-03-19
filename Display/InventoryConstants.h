#ifndef GAMEPROJECT_INVENTORYCONSTANTS_H
#define GAMEPROJECT_INVENTORYCONSTANTS_H
#include "constants.h"

namespace InventoryConstants {
    //for items itself
    const int ItemWidth = 8;
    const int ItemHeight = 4;
    const int ItemHintLength = 10;
    const int ItemBoxHeight = ItemHeight + 3; //1 сверху и 2 снизу
    const int ItemBoxWidth = ItemWidth + ItemHintLength; //1 слева и 1 справа

    //for inventory manager
    const int ItemsInRow = 5;
    const int ItemsInColumn = 5;
    const int ColumnsBetweenItems = 2;
    const int RowsBetweenItems = 2;
}

#endif //GAMEPROJECT_INVENTORYCONSTANTS_H
