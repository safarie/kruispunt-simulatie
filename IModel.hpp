#pragma once
class IModel
{
public:
	bool isMoving = true;

	void update(float &delta) {
		if (isMoving) {
			time += delta;
			// updatePosition(time);
		}
	};

private:
	float time;
};