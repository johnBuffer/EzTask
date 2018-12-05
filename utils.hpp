#pragma once

struct Bbox
{
	Bbox() = default;
	Bbox(double x_, double y_, double w_, double h_) :
		x(x_),
		y(y_),
		w(w_),
		h(h_)
	{}

	double x, y, w, h;
};
