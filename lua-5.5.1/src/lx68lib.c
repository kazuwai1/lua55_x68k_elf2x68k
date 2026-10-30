/*
	x68000 library
*/


#define lx68lib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"

#define __IOCS_INLINE__
#include <x68k/iocs.h>

static int x68k_iocs_crtmod( lua_State *L ) {
    int mode = lua_tointeger(L, 1);
    int ret = (short int)_iocs_crtmod( mode );
    lua_pushinteger(L, ret);
    return 1;

}

static int x68k_iocs_g_clr_on( lua_State *L ) {
    _iocs_g_clr_on();
    return 0;
}

static int x68k_iocs_g_palet( lua_State *L ) {
    int pno = lua_tointeger(L, 1);
    int color = lua_tointeger(L, 2);
    int ret = _iocs_gpalet( pno, color );
    lua_pushinteger(L, ret);
    return 1;
}

static int x68k_iocs_apage( lua_State *L ) {
    int page = lua_tointeger(L, 1);
    int ret = _iocs_apage( page );
    lua_pushinteger(L, ret);
    return 1;
}

static int x68k_iocs_vpage( lua_State *L ) {
    int page = lua_tointeger(L, 1);
    int ret = _iocs_vpage( page );
    lua_pushinteger(L, ret);
    return 1;
}

static int x68k_iocs_home( lua_State *L ) {
    int page = lua_tointeger(L, 1);
    int x = lua_tointeger(L, 2);
    int y = lua_tointeger(L, 3);
    int ret = _iocs_home( page, x, y );
    lua_pushinteger(L, ret);
    return 1;
}

static int x68k_iocs_window( lua_State *L ) {
    int x1 = lua_tointeger(L, 1);
    int y1 = lua_tointeger(L, 2);
    int x2 = lua_tointeger(L, 3);
    int y2 = lua_tointeger(L, 4);
    int ret = _iocs_window( x1, y1, x2, y2 );
    lua_pushinteger(L, ret);
    return 1;
}

static int x68k_iocs_wipe( lua_State *L ) {
    int ret = _iocs_wipe();
    lua_pushinteger(L, ret);
    return 1;
}

static int x68k_iocs_pset( lua_State *L ) {
    int ret;
    struct iocs_psetptr psetptr;
    psetptr.x = lua_tointeger(L, 1);
    psetptr.y = lua_tointeger(L, 2);
    psetptr.color = lua_tointeger(L, 3);
    ret = _iocs_pset( &psetptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_point( lua_State *L ) {
    int ret;
    struct iocs_pointptr pointptr;
    pointptr.x = lua_tointeger(L, 1);
    pointptr.y = lua_tointeger(L, 2);
    ret = _iocs_point( &pointptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_line( lua_State *L ) {
    int ret;
    struct iocs_lineptr lineptr;
    lineptr.x1 = lua_tointeger(L, 1);
    lineptr.y1 = lua_tointeger(L, 2);
    lineptr.x2 = lua_tointeger(L, 3);
    lineptr.y2 = lua_tointeger(L, 4);
    lineptr.color = lua_tointeger(L, 5);
    lineptr.linestyle = lua_tointeger(L, 6);
    ret = _iocs_line( &lineptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_box( lua_State *L ) {
    int ret;
    struct iocs_boxptr boxptr;
    boxptr.x1 = lua_tointeger(L, 1);
    boxptr.y1 = lua_tointeger(L, 2);
    boxptr.x2 = lua_tointeger(L, 3);
    boxptr.y2 = lua_tointeger(L, 4);
    boxptr.color = lua_tointeger(L, 5);
    boxptr.linestyle = lua_tointeger(L, 6);
    ret = _iocs_box( &boxptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_fill( lua_State *L ) {
    int ret;
    struct iocs_fillptr fillptr;
    fillptr.x1 = lua_tointeger(L, 1);
    fillptr.y1 = lua_tointeger(L, 2);
    fillptr.x2 = lua_tointeger(L, 3);
    fillptr.y2 = lua_tointeger(L, 4);
    fillptr.color = lua_tointeger(L, 5);
    ret = _iocs_fill( &fillptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_circle( lua_State *L ) {
    int ret;
    struct iocs_circleptr circleptr;
    circleptr.x = lua_tointeger(L, 1);
    circleptr.y = lua_tointeger(L, 2);
    circleptr.radius = lua_tointeger(L, 3);
    circleptr.color = lua_tointeger(L, 4);
    circleptr.start = lua_tointeger(L, 5);
    circleptr.end = lua_tointeger(L, 6);
    circleptr.ratio = lua_tointeger(L, 7);
    ret = _iocs_circle( &circleptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_paint( lua_State *L ) {
    int ret;
    struct iocs_paintptr paintptr;
    static unsigned char buffer[32*1024];  // ペイント用のバッファ
    paintptr.x = lua_tointeger(L, 1);
    paintptr.y = lua_tointeger(L, 2);
    paintptr.color = lua_tointeger(L, 3);
    paintptr.buf_start = buffer;
    paintptr.buf_end = buffer + sizeof(buffer);
    ret = _iocs_paint( &paintptr );
    lua_pushinteger(L, ret);

    return 1;
}

static int x68k_iocs_symbol( lua_State *L ) {
    int ret;
    struct iocs_symbolptr symbolptr;
    symbolptr.x1 = lua_tointeger(L, 1);
    symbolptr.y1 = lua_tointeger(L, 2);
    symbolptr.string_address = lua_tostring(L, 3);
    symbolptr.mag_x = lua_tointeger(L, 4);
    symbolptr.mag_y = lua_tointeger(L, 5);
    symbolptr.color = lua_tointeger(L, 6);
    symbolptr.font_type = lua_tointeger(L, 7);
    symbolptr.angle = lua_tointeger(L, 8);
    ret = _iocs_symbol( &symbolptr );
    lua_pushinteger(L, ret);

    return 1;
}

static const luaL_Reg x68k_iocslib[] = {
#if 1
    { "crtmod", x68k_iocs_crtmod },
    { "g_clr_on", x68k_iocs_g_clr_on },
    { "gpalet", x68k_iocs_g_palet },
    { "apage", x68k_iocs_apage },
    { "vpage", x68k_iocs_vpage },
    { "home", x68k_iocs_home },
    { "window", x68k_iocs_window },
    { "wipe", x68k_iocs_wipe },
    { "pset", x68k_iocs_pset },
    { "point", x68k_iocs_point },
    { "line", x68k_iocs_line },
    { "box", x68k_iocs_box },
    { "fill", x68k_iocs_fill },
    { "circle", x68k_iocs_circle },
    { "paint", x68k_iocs_paint }, 
    { "symbol", x68k_iocs_symbol },
#else
    { "crtmod", x68k_crtmod },
	{ "curon", x68k_curon },
	{ "curoff", x68k_curoff },
	{ "locate", x68k_locate },
	{ "cls", x68k_cls },
	{ "color", x68k_color },
	{ "vsync", x68k_vsync },
	{ "SP_REGST", x68k_SP_REGST },
#if 1
	{ "a_rec", x68k_a_rec },
	{ "a_stat", x68k_a_stat },
	{ "a_end", x68k_a_end },
	{ "a_stop", x68k_a_stop },
	{ "a_cont", x68k_a_cont },
	{ "a_play", x68k_a_play },
#endif
	{ "apage", x68k_apage },
	{ "box", x68k_box },
	{ "circle", x68k_circle },
	{ "contrast", x68k_contrast },
	{ "fill", x68k_fill },
	{ "get", x68k_get },
	{ "home", x68k_home },
	{ "hsv", x68k_hsv },
	{ "line", x68k_line },
	{ "paint", x68k_paint },
	{ "palet", x68k_palet },
	{ "point", x68k_point },
	{ "pset", x68k_pset },
	{ "rgb", x68k_rgb },
	{ "vpage", x68k_vpage },
	{ "window", x68k_window },
	{ "wipe", x68k_wipe },
	{ "put", x68k_put },
	{ "symbol", x68k_symbol },
	{ "mouse", x68k_mouse },
	{ "msarea", x68k_msarea },
	{ "msbtn", x68k_msbtn },
	{ "mspos", x68k_mspos },
	{ "msstat", x68k_msstat },
	{ "setmspos", x68k_setmspos },
	{ "sp_clr", x68k_sp_clr },
	{ "sp_color", x68k_sp_color },
	{ "sp_disp", x68k_sp_disp },
	{ "sp_move", x68k_sp_move },
	{ "sp_off", x68k_sp_off },
	{ "sp_on", x68k_sp_on },
	{ "sp_pat", x68k_sp_pat },
	{ "sp_init", x68k_sp_init },
	{ "sp_set", x68k_sp_set },
	{ "sp_stat", x68k_sp_stat },
	{ "bg_scroll", x68k_bg_scroll },
	{ "bg_set", x68k_bg_set },
	{ "bg_stat", x68k_bg_stat },
	{ "bg_fill", x68k_bg_fill },
	{ "bg_put", x68k_bg_put },
	{ "bg_get", x68k_bg_get },
	{ "sp_def", x68k_sp_def },
	{ "stick", x68k_stick },
	{ "strig", x68k_strig },
#endif
    {NULL, NULL}
};

/* }====================================================== */


LUAMOD_API int luaopen_iocs (lua_State *L) {
  luaL_newlib(L, x68k_iocslib );
  return 1;
}
