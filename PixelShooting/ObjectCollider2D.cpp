#include "Core.h"
#include <DirectXMath.h>
#include "ObjectCollider2D.h"

Collider2D::Collider2D(Object * _object, const std::wstring & _tag, Line * _line, const AABB * _aabb, const Circle * _circle)
{
	if (_line)
	{
		type = Type::kLine;
		line = *_line;
	}
	else if (_aabb)
	{
		type = Type::kAABB;
		aabb = *_aabb;
	}
	else if (_circle)
	{
		type = Type::kCircle;
		circle = *_circle;
	}
	tag = _tag;
	object = _object;
}


bool IntersectCollider2D(const Collider2D & _coli1, const Collider2D & _coli2)
{
	if (_coli1.type == Collider2D::Type::kLine && _coli2.type == Collider2D::Type::kLine)
	{
		return IntersectLineLine(_coli1.object->pos + _coli1.line.p1, _coli1.object->pos + _coli1.line.p2,
			_coli2.object->pos + _coli2.line.p1, _coli2.object->pos + _coli2.line.p2, NULL);
	}

	else if (_coli1.type == Collider2D::Type::kAABB && _coli2.type == Collider2D::Type::kAABB)
	{
		return IntersectAABBAABB(_coli1.object->pos + _coli1.aabb.min, _coli1.object->pos + _coli1.aabb.max, 
			_coli2.object->pos + _coli2.aabb.min, _coli2.object->pos + _coli2.aabb.max);
	}

	else if (_coli1.type == Collider2D::Type::kCircle && _coli2.type == Collider2D::Type::kCircle)
	{
		return IntersectCircleCircle(_coli1.object->pos, _coli1.circle.radius, _coli2.object->pos, _coli2.circle.radius);
	}

	return false;
}

inline double Det(double a, double b, double c, double d)
{
	return a * d - b * c;
}

bool IntersectLineLine(const D3DXVECTOR2& _p1, const D3DXVECTOR2& _p2, const D3DXVECTOR2& _p3, const D3DXVECTOR2& _p4, D3DXVECTOR2* _out)
{
    float t;
    float s; 
	float under = (_p4.y - _p3.y)*(_p2.x - _p1.x) - (_p4.x - _p3.x)*(_p2.y - _p1.y);
	if (under == 0) return false;

	float _t = (_p4.x - _p3.x)*(_p1.y - _p3.y) - (_p4.y - _p3.y)*(_p1.x - _p3.x);
	float _s = (_p2.x - _p1.x)*(_p1.y - _p3.y) - (_p2.y - _p1.y)*(_p1.x - _p3.x);

	t = _t / under;
	s = _s / under;

	if (t<0.0f || t>1.0f || s<0.0f || s>1.0f) return false;
	if (_t == 0 && _s == 0) return false;

	if (_out)
	{
		_out->x = _p1.x + t * (float)(_p2.x - _p1.x);
		_out->y = _p1.y + t * (float)(_p2.y - _p1.y);
	}

    return true;
}

bool IntersectAABBAABB(const D3DXVECTOR2 & _min1, const D3DXVECTOR2 & _max1, const D3DXVECTOR2 & _min2, const D3DXVECTOR2 & _max2)
{
	return (_min1.x < _max2.x) && (_max1.x > _min2.x) && (_min1.y < _max2.y) && (_max1.y > _min2.y);
}

bool IntersectAABBPos(const D3DXVECTOR2 & _min, const D3DXVECTOR2 & _max, const D3DXVECTOR2 & _pos)
{
	return _min.x < _pos.x && _max.x > _pos.x && _min.y < _pos.y && _max.y > _pos.y;
}

bool IntersectCircleCircle(const D3DXVECTOR2 & _p1, const float & _r1, const D3DXVECTOR2 & _p2, const float & _r2)
{
	auto p = _p2 - _p1;
	return p.x * p.x + p.y * p.y < (_r1 + _r2) * (_r1 + _r2);
}

float D3DXVec2Angle(const D3DXVECTOR2& _dest, const D3DXVECTOR2& _src)
{
	auto len1 = D3DXVec2Length(&_dest);
	auto len2 = D3DXVec2Length(&_src);
	if (len1 == 0.0f || len2 == 0.0f)
		return 0.0f;

	auto theta = acos(D3DXVec2Dot(&_src, &_dest) / (len1 * len2));
	return D3DXToDegree(theta);
}

D3DXVECTOR2 D3DXVec2Rotation(const D3DXVECTOR2 & vec1, const float & rotate)
{
	if (vec1 == D3DXVECTOR2(0.0f, 0.0f))
		return D3DXVECTOR2(0.0f, 0.0f);

	float radian = D3DXToRadian(-rotate);
	float sin = sinf(radian);
	float cos = cosf(radian);
	return D3DXVECTOR2(cos * vec1.x - sin * vec1.y, sin * vec1.x + cos * vec1.y);
}
