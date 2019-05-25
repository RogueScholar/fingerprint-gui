#include <QtGui>

#include "GlobalsImg.h"

void createQPixmapFromFpImg ( QPixmap * pix, struct fp_pic_data *fp_pic, unsigned int mw, unsigned int mh ) {
	if ( fp_pic == NULL || (*fp_pic).data == NULL ) {
		*pix = QPixmap();
		return;
	}
	unsigned int width = (*fp_pic).width;
	unsigned int height = (*fp_pic).height;
	float aspect;
	QImage qImg = QImage( (unsigned char *)(*fp_pic).data, width, height, QImage::Format_RGB888 );
	if ( width > mw ) {
		aspect = (float)mw / (float)width;
		width = mw;
		height = (int)( aspect * (float)height );
	}
	if ( height > mh ) {
		aspect = (float)mh / (float)height;
		height = mh;
		width = (int)( aspect * (float)width );
	}
	*pix = QPixmap::fromImage( qImg.scaled ( width, height ) );
}

void freeQPixmapFromFpImg ( QPixmap * pix ) {
	*pix = QPixmap();
}
