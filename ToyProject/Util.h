#pragma once
#include "Struct.h"

class CRectangle;
class CPolygon;
class CLine;
class CDot;
class CCircle;

namespace EngineUtil
{
	template<class T>
	FString ToString(const T& Value)
	{
#ifdef UNICODE
		return std::to_wstring(Value);
#else
		return std::to_string(Value);
#endif
	}

	template<class T>
	T RandomRange(T Min, T Max)
	{
		std::random_device rd{};
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min(static_cast<int>(Min), static_cast<int>(Max)), max(static_cast<int>(Min), static_cast<int>(Max)));
		return static_cast<T>(dis(gen));
	}

	template<class T>
	double CrossProduct(const T& A, const T& B, const T& C)
	{
		return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
	}

	// 사각형, 사각형
	bool IsOverlap(std::shared_ptr<CRectangle> Lhs, std::shared_ptr<CRectangle> Rhs);
	// 사각형, 삼각형
	bool IsOverlap(std::shared_ptr<CRectangle> Lhs, std::shared_ptr<CPolygon> Rhs);
	// 사각형, 선
	bool IsOverlap(std::shared_ptr<CRectangle> Lhs, std::shared_ptr<CLine> Rhs);
	// 사각형, 점
	bool IsOverlap(std::shared_ptr<CRectangle> Lhs, std::shared_ptr<CDot> Rhs);
	// 사각형, 원
	bool IsOverlap(std::shared_ptr<CRectangle> Lhs, std::shared_ptr<CCircle> Rhs);

	// 삼각형, 삼각형
	bool IsOverlap(std::shared_ptr<CPolygon> Lhs, std::shared_ptr<CPolygon> Rhs);
	// 삼각형, 선
	bool IsOverlap(std::shared_ptr<CPolygon> Lhs, std::shared_ptr<CLine> Rhs);
	// 삼각형, 점
	bool IsOverlap(std::shared_ptr<CPolygon> Lhs, std::shared_ptr<CDot> Rhs);
	// 삼각형, 원
	bool IsOverlap(std::shared_ptr<CPolygon> Lhs, std::shared_ptr<CCircle> Rhs);

	// 선, 선
	bool IsOverlap(std::shared_ptr<CLine> Lhs, std::shared_ptr<CLine> Rhs);
	// 선, 점
	bool IsOverlap(std::shared_ptr<CLine> Lhs, std::shared_ptr<CDot> Rhs);
	// 선, 원
	bool IsOverlap(std::shared_ptr<CLine> Lhs, std::shared_ptr<CCircle> Rhs);

	// 점, 점
	bool IsOverlap(std::shared_ptr<CDot> Lhs, std::shared_ptr<CDot> Rhs);
	// 점, 원
	bool IsOverlap(std::shared_ptr<CDot> Lhs, std::shared_ptr<CCircle> Rhs);

	// 원, 원
	bool IsOverlap(std::shared_ptr<CCircle> Lhs, std::shared_ptr<CCircle> Rhs);
}


inline POINT operator+(const POINT& Lhs, const POINT& Rhs)
{
	return POINT{ Lhs.x + Rhs.x, Lhs.y + Rhs.y };
}


inline POINT operator-(const POINT& Lhs, const POINT& Rhs)
{
	return POINT{ Lhs.x - Rhs.x, Lhs.y - Rhs.y };
}

inline void operator+=(POINT& Lhs, const POINT& Rhs)
{
	Lhs.x += Rhs.x;
	Lhs.y += Rhs.y;
}

inline void operator-=(POINT& Lhs, const POINT& Rhs)
{
	Lhs.x -= Rhs.x;
	Lhs.y -= Rhs.y;
}