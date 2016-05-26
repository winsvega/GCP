/// GCP MATH POINTS ///
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