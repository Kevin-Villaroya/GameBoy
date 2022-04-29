#ifndef __EVENT_H__
#define __EVENT_H__

enum class Event{
    QUIT,
    SKIP,
    TICK,
    WAIT_OPCODE_BREAKER,
    DUMP_RAM,
    CONTINUE,
    A,
    S,
    RETURN,
    SPACE,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};

#endif