#ifndef __KEY_H_
#define __KEY_H_

#ifdef  KEY_GLOBAL
#define EXT_KEY
#else
#define EXT_KEY extern
#endif


EXT_KEY  volatile UINT8  KeyStatus_flag;		//°´¼ü×´Ì¬±êÖ¾





extern void key_status();


#endif
