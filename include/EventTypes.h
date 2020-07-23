
#ifndef EVENTTYPES_H
#define EVENTTYPES_H

enum EventTypes
{
    MOVE,
    ATTACK,
    ONHIT,
		CRITICALHIT,
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
		PLAYERTURNOVER,
};

extern EventTypes EventType;

#endif
