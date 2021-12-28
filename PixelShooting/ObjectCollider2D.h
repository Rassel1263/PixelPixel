#pragma once

class Collider2D
{
public:

	enum class Type
	{
		kLine,
		kCircle,
		kAABB
	} type;
	struct Line
	{
		D3DXVECTOR2 p1 = D3DXVECTOR2(0.0f, 0.0f), p2 = D3DXVECTOR2(0.0f, 0.0f);
	} line;
	struct AABB
	{
		D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f), max = D3DXVECTOR2(0.0f, 0.0f);
	} aabb;
	struct Circle
	{
		float radius = 0.0f;
	} circle;
	
	Collider2D(Object* _object, const std::wstring& _tag, Line* _line, const AABB* _aabb, const Circle* _circle);
	Object* object;
	std::wstring tag;
};

bool IntersectCollider2D(const Collider2D& _coli1, const Collider2D& _coli2);
bool IntersectLineLine(const D3DXVECTOR2& _p1, const D3DXVECTOR2& _p2, const D3DXVECTOR2& _p3, const D3DXVECTOR2& _p4, D3DXVECTOR2* _out);
bool IntersectAABBAABB(const D3DXVECTOR2& _min1, const D3DXVECTOR2& _max1, const D3DXVECTOR2& _min2, const D3DXVECTOR2& _max2);
bool IntersectAABBPos(const D3DXVECTOR2& _min, const D3DXVECTOR2& _max, const D3DXVECTOR2& _pos);
bool IntersectCircleCircle(const D3DXVECTOR2& _p1, const float& _r1, const D3DXVECTOR2& _p2, const float& _r2);

// return 0 ~ 360
float D3DXVec2Angle(const D3DXVECTOR2& _dest, const D3DXVECTOR2& _src = D3DXVECTOR2(0.0f, 1.0f));
D3DXVECTOR2 D3DXVec2Rotation(const D3DXVECTOR2& _vec1, const float& _rotate);