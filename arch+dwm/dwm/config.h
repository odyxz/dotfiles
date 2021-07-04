/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:size=10" };
static const char dmenufont[]       = "xos4 Terminus:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#424242";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#1e4620";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  "#9ccc9c"  },
};

/* tagging */
static const char *tags[] = { "1:main", "2:term", "3:web", "4:dev", "5:docs", "6:irc", "7:file", "8:misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,       0,            1,           -1 },
	{ "Chromium",		NULL,       NULL,       1 << 2,       0,           -1 },
//	{ "Zathura",  		NULL,       NULL,       1 << 4,       0,           -1 },
	{ "code-oss",           NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Emacs",    		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "TelegramDesktop",    NULL,       NULL,       1 << 5,       0,           -1 },
	{ "discord",    NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Pcmanfm",  		NULL,	    NULL,       1 << 6,       0,           -1 },
//	{ "Firefox",  		NULL, 	    NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[F]",      fullscreen },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const char *slockcmd[] = { "slock", NULL };

void view_adjacent(const Arg *arg)
{
	int i, curtags;
	int seltag = 0;
	Arg a;

	curtags = selmon->tagset[selmon->seltags];
	for(i = 0; i < LENGTH(tags); i++)
		if(curtags & (1 << i)){
			seltag = i;
			break;
		}

	seltag = (seltag + arg->i) % (int)LENGTH(tags);
	if(seltag < 0)
		seltag += LENGTH(tags);

	a.i = (1 << seltag);
	view(&a);
}

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_Left,   focusstack,     {.i = +1 } },
        { MODKEY,                       XK_Right,  focusstack,     {.i = -1 } },
	{ MODKEY,			XK_space,  focusmaster,    {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,	   spawn,	   {.v = slockcmd } },
	{ 0,                            XK_Print,  spawn,          SHCMD("maim ~/Pictures/Screenshots/$(date +%Y-%m-%d-%H%M%S)_scrot.png ; notify-send 'Screen captured'") },
	{ ShiftMask,                    XK_Print,  spawn,          SHCMD("maim -s ~/Pictures/Screenshots/$(date +%Y-%m-%d-%H%M%S)_scrot.png -u | xclip -selection clipboard -t image/png ; notify-send 'Screen captured'") },
        { 0,              XF86XK_AudioRaiseVolume, spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +1000 ; notify-send --app-name=volume_notifiers Volume: $(amixer get Master | awk '$0~/%/{print $4}' | tr -d '[]')") },
        { 0,              XF86XK_AudioLowerVolume, spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -1000 ; notify-send --app-name=volume_notifiers Volume: $(amixer get Master | awk '$0~/%/{print $4}' | tr -d '[]')")  },
        { 0,              XF86XK_AudioMute,        spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle ; notify-send 'Volume: Mute'") },
	{ 0,              XF86XK_MonBrightnessUp,  spawn,          SHCMD("xbacklight -inc 10; notify-send --app-name=brightness_notifiers Brightness: $(xbacklight -get | awk '{print int($1)}')%") },
	{ 0,              XF86XK_MonBrightnessDown,spawn,          SHCMD("xbacklight -dec 10; notify-send --app-name=brightness_notifiers Brightness: $(xbacklight -get | awk '{print int($1)}')%") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_Right,           	view_adjacent,  { .i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,           	view_adjacent,  { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
