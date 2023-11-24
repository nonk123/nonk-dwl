#define COLOR(hex)                                                             \
  {                                                                            \
    ((hex >> 24) & 0xFF) / 255.0f, ((hex >> 16) & 0xFF) / 255.0f,              \
        ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f                    \
  }

static const int sloppyfocus = 0;
static const int bypass_surface_visibility = 0;
static const unsigned int borderpx = 1;
static const float bordercolor[] = COLOR(0x444444ff);
static const float focuscolor[] = COLOR(0x005577ff);
static const float urgentcolor[] = COLOR(0xff0000ff);
static const float fullscreen_bg[] = {0.1, 0.1, 0.1, 1.0};

#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

#define DMENU "bemenu"
static const char *startup_cmd = "dwl-initrc";

static const Rule rules[] = {
    /* app_id     title       tags mask     isfloating   monitor */
    {"firefox", NULL, 1 << 0, 0, -1},
    {"discord", NULL, 1 << 1, 0, -1},
    {"Gimp", NULL, 0, 1, -1},
};

/* layout(s) */
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile},
    {"><>", NULL},
    {"[M]", monocle},
};

/* monitors */
static const MonitorRule monrules[] = {
    /* name       mfact nmaster scale layout       rotate/reflect x    y */
    {NULL, 0.5, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1},
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    .layout = "us,ru",
    .options = "grp:win_space_toggle",
};

static const int repeat_rate = 30;
static const int repeat_delay = 200;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method scroll_method =
    LIBINPUT_CONFIG_SCROLL_2FG;

static const enum libinput_config_click_method click_method =
    LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

static const enum libinput_config_accel_profile accel_profile =
    LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

static const enum libinput_config_tap_button_map button_map =
    LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY, SKEY, TAG)                                                \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | WLR_MODIFIER_CTRL, KEY, toggleview, {.ui = 1 << TAG}},         \
      {MODKEY | WLR_MODIFIER_SHIFT, SKEY, tag, {.ui = 1 << TAG}}, {            \
    MODKEY | WLR_MODIFIER_CTRL | WLR_MODIFIER_SHIFT, SKEY, toggletag, {        \
      .ui = 1 << TAG                                                           \
    }                                                                          \
  }

/* commands */
static const char *termcmd[] = {"foot", NULL};
static const char *menucmd[] = {"bemenu-run", NULL};

static const char *clipboard[] = {
    "bash", "-c", "cliphist list | " DMENU " | cliphist decode | wl-copy",
    NULL};

static const char *vol_lower[] = {"volumectl", "lower", NULL};
static const char *vol_raise[] = {"volumectl", "raise", NULL};

static const char *datetime[] = {
    "bash", "-c", "notify-send \"Date and time\" \"$(date \"+%r, %a, %F\")\"",
    NULL};

static const char *sensors[] = {
    "bash", "-c", "notify-send \"CPU temperature\" \"$(sensors -A)\"", NULL};

static const char *scrt_area[] = {"grimshot", "copy", "area", NULL};
static const char *scrt_screen[] = {"grimshot", "copy", "output", NULL};

static const Key keys[] = {
    {MODKEY, XKB_KEY_d, spawn, {.v = menucmd}},
    {MODKEY, XKB_KEY_v, spawn, {.v = clipboard}},
    {MODKEY, XKB_KEY_Return, spawn, {.v = termcmd}},
    {MODKEY, XKB_KEY_i, spawn, {.v = datetime}},
    {MODKEY, XKB_KEY_o, spawn, {.v = sensors}},
    {MODKEY, XKB_KEY_bracketleft, spawn, {.v = vol_lower}},
    {MODKEY, XKB_KEY_bracketright, spawn, {.v = vol_raise}},
    {0, XKB_KEY_Print, spawn, {.v = scrt_area}},
    {WLR_MODIFIER_SHIFT, XKB_KEY_Print, spawn, {.v = scrt_screen}},
    {MODKEY, XKB_KEY_j, focusstack, {.i = +1}},
    {MODKEY, XKB_KEY_k, focusstack, {.i = -1}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_J, incnmaster, {.i = +1}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_K, incnmaster, {.i = -1}},
    {MODKEY, XKB_KEY_h, setmfact, {.f = -0.05}},
    {MODKEY, XKB_KEY_l, setmfact, {.f = +0.05}},
    {MODKEY, XKB_KEY_f, zoom, {0}},
    {MODKEY, XKB_KEY_Tab, view, {0}},
    {MODKEY, XKB_KEY_q, killclient, {0}},
    {MODKEY, XKB_KEY_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XKB_KEY_z, setlayout, {.v = &layouts[1]}},
    {MODKEY, XKB_KEY_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XKB_KEY_g, setlayout, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_F, togglefloating, {0}},
    {MODKEY, XKB_KEY_e, togglefullscreen, {0}},
    {MODKEY, XKB_KEY_0, view, {.ui = ~0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag, {.ui = ~0}},
    {MODKEY, XKB_KEY_comma, focusmon, {.i = WLR_DIRECTION_LEFT}},
    {MODKEY, XKB_KEY_period, focusmon, {.i = WLR_DIRECTION_RIGHT}},
    {MODKEY | WLR_MODIFIER_SHIFT,
     XKB_KEY_less,
     tagmon,
     {.i = WLR_DIRECTION_LEFT}},
    {MODKEY | WLR_MODIFIER_SHIFT,
     XKB_KEY_greater,
     tagmon,
     {.i = WLR_DIRECTION_RIGHT}},
    TAGKEYS(XKB_KEY_1, XKB_KEY_exclam, 0),
    TAGKEYS(XKB_KEY_2, XKB_KEY_at, 1),
    TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign, 2),
    TAGKEYS(XKB_KEY_4, XKB_KEY_dollar, 3),
    TAGKEYS(XKB_KEY_5, XKB_KEY_percent, 4),
    TAGKEYS(XKB_KEY_6, XKB_KEY_asciicircum, 5),
    TAGKEYS(XKB_KEY_7, XKB_KEY_ampersand, 6),
    TAGKEYS(XKB_KEY_8, XKB_KEY_asterisk, 7),
    TAGKEYS(XKB_KEY_9, XKB_KEY_parenleft, 8),
    {MODKEY | WLR_MODIFIER_CTRL, XKB_KEY_q, quit, {0}},

    /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
    {WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_Terminate_Server, quit, {0}},
#define CHVT(n)                                                                \
  {                                                                            \
    WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {   \
      .ui = (n)                                                                \
    }                                                                          \
  }
    CHVT(1),
    CHVT(2),
    CHVT(3),
    CHVT(4),
    CHVT(5),
    CHVT(6),
    CHVT(7),
    CHVT(8),
    CHVT(9),
    CHVT(10),
    CHVT(11),
    CHVT(12),
};

static const Button buttons[] = {
    {MODKEY, BTN_LEFT, moveresize, {.ui = CurMove}},
    {MODKEY, BTN_MIDDLE, togglefloating, {0}},
    {MODKEY, BTN_RIGHT, moveresize, {.ui = CurResize}},
};
