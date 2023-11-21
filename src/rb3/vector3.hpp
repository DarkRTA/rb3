#ifndef RB3_VECTOR3_HPP
#define RB3_VECTOR3_HPP

class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3() {};
	Vector3(float, float, float); 
	Vector3(const Vector3&);
	void Set(float, float, float); // fn_800CB1A4 - same as as __ct__7Vector3Ffff?
	Vector3* operator=(const Vector3&); // fn_800D8AC8
	void operator*=(float);
	Vector3* operator-=(const Vector3&);
	Vector3* operator+=(const Vector3&);
	void Zero();
	bool operator==(const Vector3&) const;
	bool operator!=(const Vector3&) const;
};

#endif
