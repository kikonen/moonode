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
    if(!freeuserdata(L, ud, "joint_plane2d")) return 0;
    jointdestroy(L, joint);
    return 0;
    }

static int newjoint(lua_State *L, joint_t joint, ud_t *world_ud)
    {
    ud_t *ud;
    ud = newuserdata(L, joint, JOINT_PLANE2D_MT, "joint_plane2d");
    ud->parent_ud = world_ud;
    ud->destructor = freejoint;
    return 1;
    }

static int Create(lua_State *L)
    {
    ud_t *world_ud;
    world_t world = checkworld(L, 1, &world_ud);
    joint_t joint = dJointCreatePlane2D(world, 0);
    return newjoint(L, joint, world_ud);
    }

SET_PARAM(SetXParam, dJointSetPlane2DXParam, plane2d)
SET_PARAM(SetYParam, dJointSetPlane2DYParam, plane2d)
SET_PARAM(SetAngleParam, dJointSetPlane2DAngleParam, plane2d)

DESTROY_FUNC(joint)

static const struct luaL_Reg Methods[] = 
    {
        { "set_x_param", SetXParam },
        { "set_y_param", SetYParam },
        { "set_angle_param", SetAngleParam },
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
        { "create_plane2d_joint", Create },
        { NULL, NULL } /* sentinel */
    };

void moonode_open_joint_plane2d(lua_State *L)
    {
    udata_define(L, JOINT_PLANE2D_MT, Methods, MetaMethods);
    udata_inherit(L, JOINT_PLANE2D_MT, JOINT_MT);
    luaL_setfuncs(L, Functions, 0);
    }

