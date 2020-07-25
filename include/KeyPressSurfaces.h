#ifndef KEYPRESSSURFACES_H
#define KEYPRESSSURFACES_H


enum KeyPressSurfaces
{
    NONE,
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST,
    ESCAPE,
    WAIT,
    F1,
    GRAB,
    MENUUP,
    MENUDOWN,
    PRESS,
		BAG,
		WEAR,
		DOFF,
		DROPITEM,
		SHOWCHARSCREEN,
		USE,
		EXITGAME,
};

extern KeyPressSurfaces Key;

#endif // KEYPRESSSURFACES_H
