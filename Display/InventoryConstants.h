#ifndef GAMEPROJECT_INVENTORYCONSTANTS_H
#define GAMEPROJECT_INVENTORYCONSTANTS_H
#include "constants.h"

namespace InventoryConstants {
    //for items itself
    const int ItemWidth = 18;
    const int ItemHeight = 9;
    const int ItemHintLength = ItemWidth;
    const int ItemBoxHeight = ItemHeight + 5; //5 снизу
    const int ItemBoxWidth = ItemWidth;

    //for inventory manager
    const int ItemsInRow = 5;
    const int ItemsInColumn = 5;
    const int ColumnsBetweenItems = 2;
    const int RowsBetweenItems = 1;
}

#endif //GAMEPROJECT_INVENTORYCONSTANTS_H
