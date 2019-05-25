#ifndef _GLOBALSIMG_H
#define _GLOBALSIMG_H

#include "Globals.h"

void createQPixmapFromFpImg ( QPixmap * pix, struct fp_pic_data *fp_pic, unsigned int mw = 120, unsigned int mh = 240 );
void freeQPixmapFromFpImg ( QPixmap * pix );

#endif //_GLOBALSIMG_H
