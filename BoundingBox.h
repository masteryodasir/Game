#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

class BoundingBox {
public:
	BoundingBox();
	BoundingBox(float x, float y, float w, float h);
	~BoundingBox();

	float getX();
	float getY();
	float getW();
	float getH();

protected:
	float _bx, _by, _bw, _bh;

private:
};

#endif