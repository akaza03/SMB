#include "VECTOR2.h"

VECTOR2::VECTOR2()
{
	x = 0;
 	y = 0;
}

//VECTOR2::VECTOR2(int x, int y)
//{
//	this->x = x;
//	this->y = y;
//}


VECTOR2::VECTOR2(float x, float y)
{
	this->x = x;
	this->y = y;
}

VECTOR2::~VECTOR2()
{

}

VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
 	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

int & VECTOR2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}

VECTOR2 & VECTOR2::operator/=(int k)
{
	this->x /= k;
	this->y /= k;
	return *this;
}

VECTOR2 VECTOR2::operator+() const
{
	return *this;
}

VECTOR2 VECTOR2::operator-() const
{
	return VECTOR2(-this->x, -this->y);

	//	ˆø”•t‚«ºÝ½Ä×¸À‚ðì‚ç‚È‚¢ê‡
	//VECTOR2 vec;
	//vec.x = -this->x;
	//vec.y = -this->y;
	//return vec;
}


VECTOR2 operator+(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
	//	‚à‚µ‚­‚Í
	//return VECTOR2(u.x + v.x, u.y + v.y);

}

VECTOR2 operator-(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

VECTOR2 operator*(const VECTOR2 & v, int k)
{
	VECTOR2 vec;
	vec.x = v.x * k;
	vec.y = v.y * k;
	return vec;
}

VECTOR2 operator*(int k, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = k * v.x;
	vec.y = k * v.y;
	return vec;
}

VECTOR2 operator/(const VECTOR2 & v, int k)
{
	VECTOR2 vec;
	vec.x = v.x / k;
	vec.y = v.y / k;
	return vec;
}

VECTOR2 operator%(const VECTOR2 & v, int k)
{
	VECTOR2 vec;
	vec.x = v.x % k;
	vec.y = v.y % k;
	return vec;
}
