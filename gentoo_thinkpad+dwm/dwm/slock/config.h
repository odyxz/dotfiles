/* user and group to drop privileges to */
static const char *user  = "odyssey";
static const char *group = "odyssey";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#054a18",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
	[PAM] = "9400D3",	/* waiting for PAM */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* time in seconds before the monitor shuts down */
static const int monitortime = 2;

static const char* pam_service = "login";

static const char * message = "Type password for login";

/* text color */
static const char * text_color = "#ffffff";

/* text size (must be a valid size) */
static const char * font_name = "xos4 Terminus:size:pixelsize=24:antialias=true:autohint=true";
