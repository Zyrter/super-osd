/**
 * Configuration settings. A tree of configuration settings
 * is used. These settings can be edited from the Config
 * menu and are written to the flash when changed.
 */

#define 	TYPE_INT8		1	
#define 	TYPE_INT16		2
#define 	TYPE_INT32		3
#define 	TYPE_INT64		4
#define 	TYPE_FLOAT		5
#define 	TYPE_STR		6
#define 	TYPE_BOOLEAN	7

struct OSDSetting
{
	char typeof_var;
	char *name;
	char *longdesc;
	union {
		char cval; 				// byte/8-bit integer
		int ival;				// 16-bit integer
		long int lival;			// 32-bit integer
		long long int llival;	// 64-bit integer
		float fval;				// 32-bit IEEE754 float
		char *strval;			// string
		char boolval;			// boolean 0/1
	};
};

#define 	DEFINE_SETTING(type, key, name, desc, unionkey, unionval) \
			osd_settings[numsettings++] = { type, name, desc, { .unionkey = unionval } }, #

const struct OSDSetting osd_settings[] = {
	DEFINE_SETTING(TYPE_BOOLEAN, 
				   CFG_AUTO_POWER_OFF,
				   "Auto power off", 
	  			   "After no GPS activity for 15 minutes, go into standby",
	  			   boolval, 0),		// setting 0
	};

