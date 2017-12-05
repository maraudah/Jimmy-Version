#include <pokeagb/pokeagb.h>

extern void dprintf(const char * str, ...);
extern struct Object* apply_step_delta_5_bike(struct Object* npc_obj, u8 direction);
extern struct Object* apply_step_delta_6_bike(struct Object* npc_obj, u8 direction);
typedef struct Object* (*MovementDeltaCB)(struct Object*, u8 dir);

/* 16 units moved, 1 unit at a time. Slow movement */
MovementDeltaCB vslow_movement[16] =
{
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
    (MovementDeltaCB)0x8068A8D, (MovementDeltaCB)0x8068A8D,
};

/* 16 units moved, 2 units at a time. Slow movement */
MovementDeltaCB walk_movement[8] =
{
    (MovementDeltaCB)0x8068AAD, (MovementDeltaCB)0x8068AAD,
    (MovementDeltaCB)0x8068AAD, (MovementDeltaCB)0x8068AAD,
    (MovementDeltaCB)0x8068AAD, (MovementDeltaCB)0x8068AAD,
    (MovementDeltaCB)0x8068AAD, (MovementDeltaCB)0x8068AAD,
};

/* 16 units moved in 6 steps */
MovementDeltaCB run_movement[6] =
{
    (MovementDeltaCB)0x8068AAD, (MovementDeltaCB)0x8068AD1,
    (MovementDeltaCB)0x8068AD1, (MovementDeltaCB)0x8068AAD,
    (MovementDeltaCB)0x8068AD1, (MovementDeltaCB)0x8068AD1,
};

/* 16 units moved in 4 steps */
MovementDeltaCB bike_maybe_movement[4] =
{
    (MovementDeltaCB)0x8068AF9, (MovementDeltaCB)0x8068AF9,
    (MovementDeltaCB)0x8068AF9, (MovementDeltaCB)0x8068AF9,
};

/* 16 units moved in 4 steps */
MovementDeltaCB mach_movement[2] =
{
    (MovementDeltaCB)apply_step_delta_5_bike,
    (MovementDeltaCB)apply_step_delta_5_bike
};

MovementDeltaCB* speeds_array[5] = {
    (MovementDeltaCB*)&vslow_movement, (MovementDeltaCB*)&walk_movement,
    (MovementDeltaCB*)&run_movement, (MovementDeltaCB*)&bike_maybe_movement,
    (MovementDeltaCB*)&mach_movement,
};

const u16 animation_counts[5] = {16, 8, 6, 4, 2};
void (*default_bike)(u8 dir) = (void*)0x80BD2C9;

void mach_bike_speed(u8 direction)
{
    if (super.buttons_held & KEY_B) {
        default_bike(direction);
        return;
    }
    u8 blocked = player_try_apply_direction(direction);
    if (blocked == 0) {
        // regular movement
        player_set_animation_downhill(direction);
    } else if (blocked == 6) {
        // ledge jump
        player_jump_ledge(direction);
    } else if (blocked < 3) {
        // play sound and move inplace
        player_cant_move_anim(direction);
    }
}

struct Object* apply_step_delta_5_bike(struct Object* npc_obj, u8 direction)
{
    npc_obj->pos1.x += 8 * directions[direction].x;
    npc_obj->pos1.y += 8 * directions[direction].y;
    return npc_obj;
}

struct Object* apply_step_delta_6_bike(struct Object* npc_obj, u8 direction)
{
    npc_obj->pos1.x += 6 * directions[direction].x;
    npc_obj->pos1.y += 6 * directions[direction].y;
    return npc_obj;
}




