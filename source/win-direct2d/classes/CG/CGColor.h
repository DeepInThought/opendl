#pragma once

#include "../../../common/classes/CF/CFTypes.h"
#include "../../../opendl.h"
#include <objbase.h>
#include <d2d1.h>
#include <d2d1_1.h>

#include "../../caching.h"

class CGColor; typedef CGColor* CGColorRef;
class CGColor : public cf::Object {
protected:
	D2D1_COLOR_F color;
public:
	static CGColorRef White;
	static CGColorRef Black;
	static CGColorRef Clear;

	const char *getTypeName() const override { return "CGColor"; }

	CGColor(D2D1_COLOR_F color)
		:color(color) {}

	CGColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha = 1.0)
		:color(D2D1::ColorF(red, green, blue, alpha)) {}

	CGColor(D2D1::ColorF::Enum knownColor)
		:color(D2D1::ColorF(knownColor)) {}

	D2D1_COLOR_F getD2DColor() { return color; }
	ID2D1SolidColorBrush *getCachedBrush(ID2D1RenderTarget *target) { 
		return ::getCachedColorBrush(target, color.r, color.g, color.b, color.a);
	}

	virtual CGColorRef copy() {
		// immutable so return self
		return (CGColorRef)retain();
	};

	RETAIN_AND_AUTORELEASE(CGColor)
};
