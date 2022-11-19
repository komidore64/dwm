/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* dracula standard colors */
#define dracula_std_background "#282A36"
#define dracula_std_foreground "#F8F8F2"
#define dracula_std_selection  "#44475A"
#define dracula_std_comment    "#6272A4"
#define dracula_std_red        "#FF5555"
#define dracula_std_orange     "#FFB86C"
#define dracula_std_yellow     "#F1FA8C"
#define dracula_std_green      "#50FA7B"
#define dracula_std_purple     "#BD93F9"
#define dracula_std_cyan       "#8BE9FD"
#define dracula_std_pink       "#FF79C6"

/* dracula ansi colors */
#define dracula_ansi_black   "#21222C"
#define dracula_ansi_red     "#FF5555"
#define dracula_ansi_green   "#50FA7B"
#define dracula_ansi_yellow  "#F1FA8C"
#define dracula_ansi_blue    "#BD93F9"
#define dracula_ansi_magenta "#FF79C6"
#define dracula_ansi_cyan    "#8BE9FD"
#define dracula_ansi_white   "#F8F8F2"

/* dracula ansi bright colors */
#define dracula_ansi_bright_black   "#6272A4"
#define dracula_ansi_bright_red     "#FF6E6E"
#define dracula_ansi_bright_green   "#69FF94"
#define dracula_ansi_bright_yellow  "#FFFFA5"
#define dracula_ansi_bright_blue    "#D6ACFF"
#define dracula_ansi_bright_magenta "#FF92DF"
#define dracula_ansi_bright_cyan    "#A4FFFF"
#define dracula_ansi_bright_white   "#FFFFFF"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Input:antialias=true:autohint=true:size=9" };
static const char *colors[][3]      = {
    /*               fg                      bg                      border */
    [SchemeNorm] = { dracula_std_comment,    dracula_std_background, dracula_std_comment },
    [SchemeSel]  = { dracula_std_foreground, dracula_std_selection,  dracula_std_pink },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Firefox",  NULL,       NULL,       1,            0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 0;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           { .ui = 1 << TAG } }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     { .ui = 1 << TAG } }, \
    { MODKEY|ShiftMask,             KEY,      tag,            { .ui = 1 << TAG } }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      { .ui = 1 << TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]         = { "dmenu_run", NULL };
static const char *termcmd[]          = { "st", NULL };

/* sound controls */
static const char *volumeUp1[]        = { "amixer", "set", "Master", "1%+", NULL };
static const char *volumeDown1[]      = { "amixer", "set", "Master", "1%-", NULL };
static const char *volumeUp5[]        = { "amixer", "set", "Master", "5%+", NULL };
static const char *volumeDown5[]      = { "amixer", "set", "Master", "5%-", NULL };
static const char *volumeMuteToggle[] = { "amixer", "set", "Master", "toggle", NULL };

static const Key keys[] = {
    /* modifier           key                      function        argument */
    { MODKEY,             XK_p,                    spawn,          { .v = dmenucmd } },
    { MODKEY|ShiftMask,   XK_Return,               spawn,          { .v = termcmd } },
    { MODKEY,             XK_b,                    togglebar,      { 0 } },
    { MODKEY,             XK_j,                    focusstack,     { .i = +1 } },
    { MODKEY,             XK_k,                    focusstack,     { .i = -1 } },
    { MODKEY,             XK_i,                    incnmaster,     { .i = +1 } },
    { MODKEY,             XK_d,                    incnmaster,     { .i = -1 } },
    { MODKEY,             XK_h,                    setmfact,       { .f = -0.05 } },
    { MODKEY,             XK_l,                    setmfact,       { .f = +0.05 } },
    { MODKEY,             XK_Return,               zoom,           { 0 } },
    { MODKEY,             XK_Tab,                  view,           { 0 } },
    { MODKEY|ShiftMask,   XK_c,                    killclient,     { 0 } },
    { MODKEY,             XK_t,                    setlayout,      { .v = &layouts[0] } },
    { MODKEY,             XK_f,                    setlayout,      { .v = &layouts[1] } },
    { MODKEY,             XK_m,                    setlayout,      { .v = &layouts[2] } },
    { MODKEY,             XK_space,                setlayout,      { 0 } },
    { MODKEY|ShiftMask,   XK_space,                togglefloating, { 0 } },
    { MODKEY,             XK_0,                    view,           { .ui = ~0 } },
    { MODKEY|ShiftMask,   XK_0,                    tag,            { .ui = ~0 } },
    { MODKEY,             XK_comma,                focusmon,       { .i = -1 } },
    { MODKEY,             XK_period,               focusmon,       { .i = +1 } },
    { MODKEY|ShiftMask,   XK_comma,                tagmon,         { .i = -1 } },
    { MODKEY|ShiftMask,   XK_period,               tagmon,         { .i = +1 } },
    { MODKEY|ControlMask, XK_q,                    quit,           { 0 } },
    { ShiftMask,          XF86XK_AudioRaiseVolume, spawn,          { .v = volumeUp1 } },
    { ShiftMask,          XF86XK_AudioLowerVolume, spawn,          { .v = volumeDown1 } },
    { 0,                  XF86XK_AudioRaiseVolume, spawn,          { .v = volumeUp5 } },
    { 0,                  XF86XK_AudioLowerVolume, spawn,          { .v = volumeDown5 } },
    { 0,                  XF86XK_AudioMute,        spawn,          { .v = volumeMuteToggle } },
    TAGKEYS(              XK_1,                                    0)
    TAGKEYS(              XK_2,                                    1)
    TAGKEYS(              XK_3,                                    2)
    TAGKEYS(              XK_4,                                    3)
    TAGKEYS(              XK_5,                                    4)
    TAGKEYS(              XK_6,                                    5)
    TAGKEYS(              XK_7,                                    6)
    TAGKEYS(              XK_8,                                    7)
    TAGKEYS(              XK_9,                                    8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      { 0 } },
    { ClkLtSymbol,          0,              Button3,        setlayout,      { .v = &layouts[2] } },
    { ClkWinTitle,          0,              Button2,        zoom,           { 0 } },
    { ClkStatusText,        0,              Button2,        spawn,          { .v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      { 0 } },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, { 0 } },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    { 0 } },
    { ClkTagBar,            0,              Button1,        view,           { 0 } },
    { ClkTagBar,            0,              Button3,        toggleview,     { 0 } },
    { ClkTagBar,            MODKEY,         Button1,        tag,            { 0 } },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      { 0 } },
};
