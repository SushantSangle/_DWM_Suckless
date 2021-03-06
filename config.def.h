/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 0;
static const unsigned int snap      = 20;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int swallowfloating    = 0;
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const char *fonts[]          = { "nunito:size=14" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#f4544c";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char col_blue[]        = "#1f367a";
static const char col_pale[]        = "#e4dfd5";
static const unsigned int baralpha = 100;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int selalpha = baralpha;


static const char *colors[][3]      = {
	/*					fg         bg          border   */
	[SchemeNorm] =	 { col_pale, col_black,  col_gray2 },
	[SchemeSel]  =	 { col_red, col_black,   col_red },

};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, selalpha, borderalpha },
};

static const char *const autostart[] = {
    "rolling_wallpaper",">>/dev/null",NULL,
   "dwmblocks",">>/dev/null",NULL,
   "flameshot",">>/dev/null",NULL,
   "dunst",">>/dev/null",NULL,
   "xcompmgr",">>/dev/null",NULL,
   "lxpolkit",">>/dev/null",NULL,
	 "clipmenud",">>/dev/null",NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5","6"};

/* launcher commands (They must be NULL terminated) */
#define charCmd(cmd) (const char*[]){ "/bin/sh", "-c", cmd, NULL }

static const Launcher launchers[] = {
       /* command       name to display */
    { charCmd("launcher.sh"), "[Menu]"},
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isTerminal  noswallow   monitor */
	{ "firefox",     NULL,       NULL,       2,         0,           0,          -1,         -1 },
	{ "TelegramDesktop",NULL,    NULL,       1<<3,      0,           0,          -1,         -1 },
	{ "code-oss"    ,NULL,       NULL,       1<<2,      0,           0,          -1,         -1 },
	{ "subl"        ,NULL,       NULL,       1<<2,      0,           0,          -1,         -1 },
	{ "discord",     NULL,       NULL,       1<<3,      1,           0,          -1,         -1 },
	{ "minecraft-launcher",NULL, NULL,       1<<4,      0,           0,          -1,         -1 },
	{ "Gimp",        NULL,       NULL,       0,         1,           0,          -1,         -1 },
	{ "St",					 NULL,       NULL,       0,         1,           1,           0,         -1 },
	{ "Blueman-manager",NULL,    NULL,       0,         1,           0,          -1,         -1 },
	{ "gnome-contacts", NULL,    NULL,       0,         1,           0,          -1,         -1 },
	{ "Alacritty",   NULL,       NULL,       0,         0,           1,           0,         -1 },
	{ NULL,      NULL,     "Event Tester",   0,         0,           0,           1,         -1 },
};
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static int attachbelow = 0;    /* 1 means attach after the currently active window */

#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",     monocle },
    { "[🐚]",     spiral },
    { "[\\]",    dwindle },
    { "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = charCmd(cmd) }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_i", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "selfrestart.c"
#include "movestack.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod1Mask,                     XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox")},
 	{ MODKEY,                       XK_period, spawn,          SHCMD("dmenu-unicode")},
 	{ MODKEY,                       XK_c,      spawn,          SHCMD("clipmenu -p 'Copied Items '")},
 	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("dolphin")},
 	{ MODKEY,                       XK_e,      spawn,          SHCMD("alacritty -e ranger")},
 	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("flameshot gui -p /home/sushant/Pictures/Screenshots")},
 	{ 0,                            XK_Print,  spawn,          SHCMD("flameshot full -p /home/sushant/Pictures/Screenshots")},
 	{ MODKEY,                       XK_Print,  spawn,          SHCMD("flameshot full -c")},
  { MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
//	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("dm-tool switch-to-greeter")},
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    toggleAttachBelow, {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
    { MODKEY|ControlMask|ShiftMask, XK_q,      self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                       XF86XK_AudioLowerVolume,  spawn,SHCMD("pamixer -d 5;killall -42 dwmblocks") },
	{ 0,                       XF86XK_AudioRaiseVolume,  spawn,SHCMD("pamixer -i 5;killall -42 dwmblocks") },
	{ 0,                       XF86XK_AudioMute,         spawn,SHCMD("pamixer -t;killall -42 dwmblocks") },
	{ 0,                       XF86XK_AudioPrev,         spawn,SHCMD("playerctl previous") },
	{ 0,                       XF86XK_AudioNext,         spawn,SHCMD("playerctl next") },
	{ 0,                       XF86XK_AudioPlay,         spawn,SHCMD("playerctl play-pause") },
	{ MODKEY,                       XK_F11,         spawn,    SHCMD("xbacklight -dec 3;killall -45 dwmblocks") },
	{ MODKEY,                       XK_F12,         spawn,    SHCMD("xbacklight -inc 3;killall -45 dwmblocks") },
};

#define LEFT_CLICK Button1
#define RIGHT_CLICK Button3
#define MIDDLE_CLICK Button2
#define SCROLL_UP_TRACKPAD Button5
#define SCROLL_DOWN_TRACKPAD Button4
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button               function        argument */
	{ ClkLtSymbol,          0,              LEFT_CLICK,             setlayout,      {0} },
	{ ClkLtSymbol,          0,              RIGHT_CLICK,            setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              MIDDLE_CLICK,           killclient,     {0} },
	{ ClkStatusText,        0,              LEFT_CLICK,             sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        MODKEY|ShiftMask,LEFT_CLICK,            sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,        0,              MIDDLE_CLICK,           sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              RIGHT_CLICK,            sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              SCROLL_DOWN_TRACKPAD,   sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              SCROLL_UP_TRACKPAD,     sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         LEFT_CLICK,             movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         MIDDLE_CLICK,           togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,LEFT_CLICK,            resizemouse,    {0} },
	{ ClkTagBar,            0,              LEFT_CLICK,             view,           {0} },
	{ ClkTagBar,            0,              RIGHT_CLICK,            toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         LEFT_CLICK,             tag,            {0} },
	{ ClkTagBar,            MODKEY,         RIGHT_CLICK,            toggletag,      {0} },
};
