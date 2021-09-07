#ifndef APPCONFIG_H_INCLUDED
#define APPCONFIG_H_INCLUDED

#ifdef USE_KCONFIG

#include "config.h"

#endif // USE_KCONFIG

/*
默认配置
注意：可通过配置关闭Kconfig,因此config.h中的内容不可直接使用
*/
#ifndef CONFIG_CPP_OP_NEW_DEBUG
#define CONFIG_CPP_OP_NEW_DEBUG 0
#endif // CONFIG_CPP_OP_NEW_DEBUG


#ifndef CONFIG_CPP_OP_DELETE_DEBUG
#define CONFIG_CPP_OP_DELETE_DEBUG 0
#endif // CONFIG_CPP_OP_DELETE_DEBUG



#endif // APPCONFIG_H_INCLUDED
