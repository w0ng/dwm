/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus2-medium-r-*-*-12-*-*-*-*-*-*-*";
#define NUMCOLORS 15
static const char colors[NUMCOLORS][ColLast][8] = {
  // border foreground background
  { "#073642", "#657b83", "#002b36" }, // 1 = normal (grey on black)
  { "#b58900", "#eee8d5", "#002b36" }, // 2 = selected (white on black)
  { "#dc322f", "#002b36", "#b58900" }, // 3 = urgent (black on yellow)
  { "#073642", "#93a1a1", "#004354" }, // 4 = 
  { "#073642", "#004354", "#002b36" }, // 5 = 
  { "#073642", "#87d7ff", "#005f87" }, // 6 =
  { "#073642", "#005f87", "#004354" }, // 7 =
  { "#073642", "#aae3ff", "#0087af" }, // 8 =
  { "#073642", "#0087af", "#005f87" }, // 9 =
  { "#073642", "#005f5f", "#87d7ff" }, // a
  { "#073642", "#87d7ff", "#0087af" }, // b
  { "#073642", "#0087af", "#87d7ff" }, // c
  { "#073642", "#005f87", "#0087af" }, // d
  { "#073642", "#004354", "#005f87" }, // e
  { "#073642", "#002b36", "#004354" }, // f
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "À", "Á", "Â", "Ã", "Ä", "Å", "Æ", "Ç", "È" };

static const Rule rules[] = {
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp",     NULL,       NULL,       0,            True,        -1 },
  { "feh" ,     NULL,       NULL,       0,            True,        -1 },
  { "Xfd",      NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "Û É Û",      tile },    /* first entry is default */
  { "Û Ê Û",      NULL },    /* no layout function means floating behavior */
  { "Û Ë Û",      monocle },
  { "Û Ì Û",      bstack },
  { "Û Í Û",      gaplessgrid },
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
static const char  *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldncmd[] = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *mpctog[] = { "ncmpcpp", "toggle", NULL };
static const char *mpcstop[] = { "ncmpcpp", "stop", NULL };
static const char *mpcprev[] = { "ncmpcpp", "prev", NULL };
static const char *mpcnext[] = { "ncmpcpp", "next", NULL };

#include "push.c"
static Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_Insert, spawn,          {.v = mpctog } },
  { MODKEY,                       XK_Delete, spawn,          {.v = mpcstop } },
  { MODKEY,                       XK_Home,   spawn,          {.v = mpcprev } },
  { MODKEY,                       XK_End,    spawn,          {.v = mpcnext } },
  { MODKEY,                       XK_Prior,  spawn,          {.v = volupcmd } },
  { MODKEY,                       XK_Next,   spawn,          {.v = voldncmd } },
  { MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
  { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_Return, zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
  { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_p,      cycle,          {.i = -1 } },
  { MODKEY,                       XK_n,      cycle,          {.i = +1 } },
  { MODKEY|ShiftMask,             XK_p,      tagcycle,       {.i = -1 } },
  { MODKEY|ShiftMask,             XK_n,      tagcycle,       {.i = +1 } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

