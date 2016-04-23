#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "Symbol.h"

Symbol::Symbol(int type) {
	this->valid = true;
	this->width = OCV_HERO_DEFAULT_WIDTH;
	this->height = OCV_HERO_DEFAULT_HEIGHT;
	this->type = type;
	pos = new CvPoint();
	pos->y = 140;
	if (this->type==TYPE_LEFT_SYMBOL) {
		pos->x = 280;
	} else if (this->type==TYPE_CENTERED_SYMBOL) {
		pos->x = 330;
	} else if (this->type==TYPE_RIGHT_SYMBOL) {
		pos->x = 380;
	}
	this->started = false;
	this->hitted = false;
}

/**
 * destruye la instancia de la clase
 */
Symbol::~Symbol(void) {

}

/**
 * Mueve la figura en el eje Y
 */
void Symbol::move(void) {
	// no se ha salido de la pantalla?
	if(valid) {
		if (this->type==TYPE_LEFT_SYMBOL) {
			pos->y += MOVEMENT_Y_AXIS;
			pos->x -= MOVEMENT_X_AXIS;
		} else if (this->type==TYPE_CENTERED_SYMBOL) {
			pos->y += MOVEMENT_Y_AXIS;
		} else if (this->type==TYPE_RIGHT_SYMBOL) {
			pos->y += MOVEMENT_Y_AXIS;
			pos->x += MOVEMENT_X_AXIS;
		}
	}
}

/**
 * Dibuja la figura en su posici&oacute;n actual
 */
void Symbol::draw(IplImage* in) {
	// no se ha salido de la pantalla?
	if (valid) {
		// no se ha salido de la pantalla?
		if (pos->y < in->height) {
			CvScalar color;
			if (this->hitted) {
				color = OCV_HERO_WHITE_COLOR;
			} else if (this->type==TYPE_LEFT_SYMBOL) {
				color = OCV_HERO_GREEN_COLOR;
			} else if (this->type==TYPE_CENTERED_SYMBOL) {
				color = OCV_HERO_RED_COLOR;
			} else if (this->type==TYPE_RIGHT_SYMBOL) {
				color = OCV_HERO_YELLOW_COLOR;
			}
			cvCircle(in, cvPoint(pos->x-width/2, pos->y-height/2),
				this->width, color, CV_FILLED);
		} else {
			this->valid = false;
		}
	}
}

/**
 * Verifica si la figura se encuentra en el &aacute;rea especificada
 */
bool Symbol::inside(CvRect areaToCheck) {
	CvPoint *start = new CvPoint();
	CvPoint *finish = new CvPoint();
	start->x = areaToCheck.x;
	start->y = areaToCheck.y;

	finish->x = start->x + areaToCheck.width;
	finish->y = start->y + areaToCheck.height;

	bool result = false;
	if (started && valid) {
		result = (this->pos->x >= start->x) &&
			(this->pos->x <= finish->x) &&
			(this->pos->y >= start->y)&&
			(this->pos->y <= finish->y);
	}
	return	result;
}
