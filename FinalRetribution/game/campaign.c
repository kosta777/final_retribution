#include "campaign.h"

int campaign_background[3][30][BACKGROUND_GRID_X+1] =
{
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {2, 0, 0, 0}
    },

    {
        {3, 3, 3, 3},
        {3, 4, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 4, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {4, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 4, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 4, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {4, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 4, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 4, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {4, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 3},
        {3, 3, 3, 4},
        {3, 3, 3, 3},
        {3, 4, 3, 3},
        {3, 3, 3, 3}
    },

    {
        {5, 5, 5, 5},
        {5, 7, 5, 5},
        {5, 5, 5, 5},
        {8, 8, 8, 8},
        {5, 5, 5, 5},
        {5, 5, 5, 5},
        {5, 5, 7, 5},
        {7, 5, 5, 5},
        {5, 5, 5, 5},
        {5, 5, 5, 5},
        {6, 6, 6, 6},
        {5, 5, 5, 5},
        {5, 7, 5, 5},
        {5, 5, 5, 5},
        {5, 5, 7, 5},
        {5, 5, 5, 5},
        {8, 8, 8, 8},
        {5, 5, 5, 5},
        {5, 5, 7, 5},
        {7, 5, 5, 5},
        {5, 5, 5, 5},
        {5, 5, 5, 7},
        {6, 6, 6, 6},
        {7, 5, 5, 5},
        {5, 5, 5, 5},
        {5, 7, 5, 5},
        {5, 5, 5, 5},
        {5, 5, 5, 5},
        {7, 5, 5, 5},
        {8, 8, 8, 8}
    }
};  /** niz delova pozadine u redosledu kojim treba da se pojavljuju tokom prelaska nivoa */
