/* The MIT License (MIT)
 *
 * Copyright (c) 2021 Stefano Trettel
 *
 * Software repository: MoonODE, https://github.com/stetre/moonode
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "internal.h"
#include "joint.h"

static int freejoint(lua_State *L, ud_t *ud)
    {
    joint_t joint = (joint_t)ud->handle;
    if(!freeuserdata(L, ud, "joint_piston")) return 0;
    jointdestroy(L, joint);
    return 0;
    }

static int newjoint(lua_State *L, joint_t joint, ud_t *world_ud)
    {
    ud_t *ud;
    ud = newuserdata(L, joint, JOINT_PISTON_MT, "joint_piston");
    ud->parent_ud = world_ud;
    ud->destructor = freejoint;
    return 1;
    }

static int Create(lua_State *L)
    {
    ud_t *world_ud;
    world_t world = checkworld(L, 1, &world_ud);
    joint_t joint = dJointCreatePiston(world, 0);
    return newjoint(L, joint, world_ud);
    }

SETVEC3(SetAnchor, dJointSetPistonAnchor, piston)
//SETVEC3VEC3(SetAnchorOffset, dJointSetPistonAnchorOffset, piston)
SETVEC3(SetAxis, dJointSetPistonAxis, piston)
SETNUM(AddForce, dJointAddPistonForce, piston)
GETNUM(GetPosition, dJointGetPistonPosition, piston)
GETNUM(GetPositionRate , dJointGetPistonPositionRate , piston)
GETNUM(GetAngle, dJointGetPistonAngle, piston)
GETNUM(GetAngleRate , dJointGetPistonAngleRate , piston)
GETVEC3(GetAnchor, dJointGetPistonAnchor, piston)
GETVEC3(GetAnchor2, dJointGetPistonAnchor2, piston)
GETVEC3(GetAxis, dJointGetPistonAxis, piston)

SET_PARAM(SetParam, dJointSetPistonParam, piston)
GET_PARAM(GetParam, dJointGetPistonParam, piston)
DESTROY_FUNC(joint)

static const struct luaL_Reg Methods[] = 
    {
        { "set_param", SetParam },
        { "get_param", GetParam },
        { "set_anchor1", SetAnchor },
//      { "set_anchor_offset", SetAnchorOffset },
        { "set_axis", SetAxis },
        { "add_force", AddForce },
        { "get_position", GetPosition },
        { "get_position_rate", GetPositionRate },
        { "get_angle", GetAngle },
        { "get_angle_rate", GetAngleRate },
        { "get_anchor1", GetAnchor },
        { "get_anchor2", GetAnchor2 },
        { "get_axis", GetAxis },
        { "destroy", Destroy },
        { NULL, NULL } /* sentinel */
    };

static const struct luaL_Reg MetaMethods[] = 
    {
        { "__gc", Destroy },
        { NULL, NULL } /* sentinel */
    };

static const struct luaL_Reg Functions[] = 
    {
        { "create_piston_joint", Create },
        { NULL, NULL } /* sentinel */
    };

void moonode_open_joint_piston(lua_State *L)
    {
    udata_define(L, JOINT_PISTON_MT, Methods, MetaMethods);
    udata_inherit(L, JOINT_PISTON_MT, JOINT_MT);
    luaL_setfuncs(L, Functions, 0);
    }

