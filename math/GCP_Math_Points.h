/// GCP MATH POINTS ///
#include "GCP_Vector.h"
using namespace gcp;

template<class T>
struct GCP_Point;
template<class T>
struct GCP_Point3D;

template<class T>
struct GCP_Line;
typedef GCP_Point<int> GCP_PointInt;
typedef GCP_Point3D<float> GCP_Point3DFloat;
typedef GCP_Point<double> GCP_PointDouble;
typedef GCP_Line<double> GCP_LineDouble;

template<class T>
struct GCP_Point
{
	T  X, Y;
	GCP_Point(){}
	GCP_Point(T x, T y) : X(x), Y(y) {}
	GCP_Point(GCP_Point* point) : X(point->X), Y(point->Y) {}
	~GCP_Point(){}
	operator GCP_Point<int>() { return GCP_Point<int>((int)X, (int)Y); }//приведение к типу GCP_Point<int>
	inline friend bool operator == (GCP_Point const&  lhs, GCP_Point const& rhs)
	{
		return (lhs.X == rhs.X && lhs.Y == rhs.Y);
	}
	inline friend bool operator < (GCP_Point const&  lhs, GCP_Point const& rhs)
	{
		return (lhs.X < rhs.X && lhs.Y < rhs.Y);
	}
	inline friend bool operator >(GCP_Point const&  lhs, GCP_Point const& rhs)
	{
		return (lhs.X > rhs.X && lhs.Y > rhs.Y);
	}
	inline friend bool operator != (GCP_Point const&  lhs, GCP_Point const& rhs)
	{
		return (lhs.X != rhs.X && lhs.Y != rhs.Y);
	}
	GCP_Point& operator + (GCP_Point const& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}
	GCP_Point& operator - (GCP_Point const& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}
};

template<class T>
struct GCP_Point3D
{
	T  X, Y, Z;
	GCP_Point3D(){}
	GCP_Point3D(T x, T y, T z) : X(x), Y(y), Z(z) {}
	GCP_Point3D(GCP_Point3D* point) : X(point->X), Y(point->Y), Z(point->Z) {}
	~GCP_Point3D(){}
	operator GCP_Point3D<int>() { return GCP_Point3D<int>((int)X, (int)Y, (int)Z); }//приведение к типу GCP_Point3D<int>
	inline friend bool operator == (GCP_Point3D const&  lhs, GCP_Point3D const& rhs)
	{
		return (lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z);
	}
	inline friend bool operator < (GCP_Point3D const&  lhs, GCP_Point3D const& rhs)
	{
		return (lhs.X < rhs.X && lhs.Y < rhs.Y && lhs.Z < rhs.Z);
	}
	inline friend bool operator >(GCP_Point3D const&  lhs, GCP_Point3D const& rhs)
	{
		return (lhs.X > rhs.X && lhs.Y > rhs.Y && lhs.Z > rhs.Z);
	}
	inline friend bool operator != (GCP_Point3D const&  lhs, GCP_Point3D const& rhs)
	{
		return (lhs.X != rhs.X && lhs.Y != rhs.Y && lhs.Z != rhs.Z);
	}
	GCP_Point3D& operator + (GCP_Point3D const& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;
		return *this;
	}
	GCP_Point3D& operator - (GCP_Point3D const& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;
		return *this;
	}
};


template<class T>
struct GCP_Line
{
	GCP_Point<T> pointA, pointB;					//Структура для линии
	GCP_Line() {}
	GCP_Line(GCP_Point<T> const& A, GCP_Point<T> const& B) : pointA(A), pointB(B) {}
	GCP_Line(T x1, T y1, T x2, T y2) : pointA(x1, y1), pointB(x2, y2){}
	//void SetPoints(GCP_Point<T> const& A, GCP_Point<T> const& B){ pointA = A; pointB = B; }
	double length()
	{
		return sqrt(pow(pointA.X - pointB.X, 2) + pow(pointA.Y - pointB.Y, 2));
	}
};

template<class T>
struct GCP_Rect
{
private:
	GCP_Point<T> topLeftPoint, bottomRightPoint, widthHeight, centerPoint;
	inline void recalcCenter()	{
		centerPoint = GCP_Point<T>(topLeftPoint.X + widthHeight.X / 2, topLeftPoint.Y + widthHeight.Y / 2);
	}
public:
	GCP_Rect(){}
	GCP_Rect(const GCP_Point<T> &topLeft_, const GCP_Point<T> &widthHeight_) :
		topLeftPoint(topLeft_), bottomRightPoint(topLeft_.X + widthHeight_.X, topLeft_.Y + widthHeight_.Y), widthHeight(widthHeight_),
		centerPoint(GCP_Point<T>(topLeft_.X + widthHeight_.X / 2, topLeft_.Y + widthHeight_.Y / 2)) {}
	GCP_Rect(T x, T y, T width, T height) :
		topLeftPoint(GCP_Point<T>(x, y)), bottomRightPoint(GCP_Point<T>(x + width, y + height)), widthHeight(GCP_Point<T>(width, height)),
		centerPoint(GCP_Point<T>(x + width / 2, y + height / 2)) {}

	const T& x()const{ return topLeftPoint.X; }
	const T& y()const{ return topLeftPoint.Y; }
	const T& width()const{ return widthHeight.X; }
	const T& height()const{ return widthHeight.Y; }
	const GCP_Point<T>& topLeft()const{ return topLeftPoint; }
	const GCP_Point<T>& bottomRight()const{ return bottomRightPoint; }
	const GCP_Point<T>& center()const{ return centerPoint; }
	inline void setTopLeft(T x, T y){ topLeftPoint.X = x; topLeftPoint.Y = y; recalcCenter(); }
	inline void setWidthHeight(T width, T height) { widthHeight.X = width; widthHeight.Y = height; recalcCenter(); }
};

template <class T>
class GCP_HeightMap
{
public:
	GCP_HeightMap() : m_maxHeight(0), m_minHeight(0) {}
	int getXCells() const { return m_xPixels; }
	int getYCells() const { return m_yPixels; }
	unsigned int getMaxXValue() const { return m_maxX; }
	unsigned int getMaxYValue() const { return m_maxY; }
	T getMaxHeight() const { return m_maxHeight; }
	T getMinHeight() const { return m_minHeight; }

	T getHeight(int x, int y)
	{
		if (checkBounds(x, y))
			return m_map[y*m_xPixels + x];
		return 0;
	}

	double getHeightPhysicCoord(double x, double y)
	{
		if (x > m_maxX || x < 0 || y > m_maxY || y < 0)
			return 0;

		double roundXpercent = x * 100 / m_maxX;
		double roundYpercent = y * 100 / m_maxY;

		double roundX = roundXpercent*(m_xPixels - 1) / 100;
		double roundY = roundYpercent*(m_yPixels - 1) / 100;
		return getHeightInterpolation(roundX, roundY);
	}

	double getHeightInterpolation(double x, double y)
	{
		int florX = floor(x);
		int florY = floor(y);
		int ceilX = ceil(x);
		int ceilY = ceil(y);
		if (checkBounds(ceilX, ceilY) && checkBounds(florX, florY))
		{
			double x1 = x - florX;
			double y1 = y - florY;
			double value = getHeight(florX, florY)*(1 - x1)*(1 - y1) +
				getHeight(ceilX, florY)* x1 *(1 - y1) +
				getHeight(florX, ceilY)* (1 - x1) * y1 +
				getHeight(ceilX, ceilY)* x1 * y1;
			return value;
		}
		return 0;
	}

	void setHeight(int x, int y, T z)
	{
		if (checkBounds(x, y))
			m_map.at(0) = z;
	}

protected:
	int m_xPixels;
	int m_yPixels;
	unsigned int m_maxX;
	unsigned int m_maxY;
	GCP_Vector<T> m_map;
	T m_maxHeight;
	T m_minHeight;

private:

	bool checkBounds(int x, int y)
	{
		if (x < m_xPixels && y < m_yPixels && x >= 0 && y >= 0)
			if (y*m_xPixels + x < m_map.size())
				return true;
		return false;
	}
};
