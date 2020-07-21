
#ifndef EVENTTYPES_H
#define EVENTTYPES_H

enum EventTypes
{
    MOVE,
    ATTACK,
    ONHIT,
    ONMISS,
    DAMAGE,
    DEAD,
    TAKE,
    ONPICKUP,
    PUSHSCENE,
    POPSCENE,
    QUIT,
		DROP,
		EQUIP,
		UNEQUIP,
		USEITEM,
		PASSUSERINFO,
		MESSAGE,
};

extern EventTypes EventType;

#endif
