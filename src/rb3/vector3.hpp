#ifndef RB3_VECTOR3_HPP
#define RB3_VECTOR3_HPP

class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3(float, float, float);
	Vector3(const Vector3&);
	void Set(float, float, float);
	void operator=(const Vector3&);
	void operator*=(float);
	void operator-=(const Vector3&);
	void operator+=(const Vector3&);
	void Zero();
	bool operator==(const Vector3&) const;
}

#endif
