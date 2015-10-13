#ifndef GCP_MathH
#define GCP_MathH

#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <cstdio>
#include <ctype.h>
#include "GCP_Vector.h"
#include "GCP_Delegate.h"
#include "GCP_IO.h"
namespace gcp
{
const double GCP_RADTODEG = (double)180 / 3.14;
const double GCP_DEGTORAD = (double)3.14 / 180;
const int GCP_INT32MAX = 2147483647;
using namespace std;

template<class T>
struct GCP_Point;

template<class T>
struct GCP_Line;
typedef GCP_Point<int> GCP_PointInt;
typedef GCP_Point<double> GCP_PointDouble;
typedef GCP_Line<double> GCP_LineDouble;
///
template<class T>
struct GCP_Point
{
	T  X, Y;
	GCP_Point(){}
	GCP_Point(T x, T y): X(x), Y(y) {}
	GCP_Point(GCP_Point* point): X(point->X), Y(point->Y) {}
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
	inline friend bool operator > (GCP_Point const&  lhs, GCP_Point const& rhs)
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

///
template<class T>
struct GCP_Line
{
	GCP_Point<T> pointA, pointB;					//Структура для линии
	GCP_Line() {}
	GCP_Line(GCP_Point<T> const& A, GCP_Point<T> const& B): pointA(A), pointB(B) {}
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
		topLeftPoint(GCP_Point<T>(x, y)), bottomRightPoint(GCP_Point<T>(x+width, y+height)), widthHeight(GCP_Point<T>(width, height)),
		centerPoint(GCP_Point<T>(x + width / 2, y + height / 2)) {}

	const T& x()const{ return topLeftPoint.X; }
	const T& y()const{ return topLeftPoint.Y; }
	const T& width()const{ return widthHeight.X; }
	const T& height()const{ return widthHeight.Y; }
	const GCP_Point<T>& topLeft()const{ return topLeftPoint;}
	const GCP_Point<T>& bottomRight()const{ return bottomRightPoint;}
	const GCP_Point<T>& center()const{ return centerPoint;}
	inline void setTopLeft(T x, T y){topLeftPoint.X = x; topLeftPoint.Y = y; recalcCenter();}
	inline void setWidthHeight(T width, T height) {widthHeight.X = width; widthHeight.Y = height; recalcCenter();}
};

struct reflectinfo
{
	double reflectedAngleOX;
	double reflectedAngle;
	double refractedAngleOX;
	double refractedAngle;
	bool refractionError;
	double N1, N2;
};

/////////////////////////////////////////////////////////////////////////
class GeneticSpecies
{
public:
	string values;
	double result;
	GeneticSpecies &operator=(GeneticSpecies rhs)
	{
		result = rhs.result;
		values = rhs.values;
		return *this;
	}
	void breed(GeneticSpecies *other, int devideblocks);
	void mutation();
};
/////////////////////////////////////////////////////////////////////////

class GCP_Math
{
public:
	static string RUSCP1251_TO_WCHAR(const wchar_t* str);
	static string RUSCP1251_TO_WCHAR(const char* str);
	static double ccos(double value);
	static double ssin(double value);
	static double arcsin(double value);
	static double rnd();
	static double rnd(const char *dist, double a, double b);
	static double round(double value);
	static bool compareDouble(double x, double y);
	static bool compareDoubleEqual(double x, double y);
	static double pointDirection(double x1, double y1, double x2, double y2);
	template<class T>
	static T Min(T a, T b) 	{ return (a < b) ? a : b; }
	template<class T>
	static T Max(T a, T b)  { return (a < b) ? b : a; }
	template<class T>
	static double pointDirection(GCP_Point<T> const&A, GCP_Point<T> const&B) 	{ 	return pointDirection(A.X, A.Y, B.X, B.Y); 	}
	static double pointDistance(double x1, double y1, double x2, double y2);
	template<class T>
	static double pointDistance(GCP_Point<T> const&X, GCP_Point<T> const&Y) {  return pointDistance(X.X, X.Y, Y.X, Y.Y); 	}

	template<class T>
	static GCP_Point<T> abs(GCP_Point<T> const& point)
	{
		return GCP_Point<T>(std::abs(point.X), std::abs(point.Y));
	}

	template<class T>
	static GCP_Point<T> max(GCP_Point<T> const& pointA, GCP_Point<T> const& pointB)
	{
		return (pointA < pointB) ? pointB : pointA;
	}

	// Возвращает находится ли точка снизу от линии или сверху
	template <class T>
	static bool isPointBelowLine(const GCP_Point<T> &P, const GCP_Line<T> &L)
	{
		bool isBelow = ((long double)(L.pointB.X - L.pointA.X)*(P.Y - L.pointA.Y) - (long double)(L.pointB.Y - L.pointA.Y)*(P.X - L.pointA.X) > 0);
		if (lineAngle(L) > 90) return  isBelow;
		return !isBelow;
	}

	static bool isInRadius(double x1, double y1, double x2, double y2, double r);
	static bool isInRect(double pointX, double pointY, double rectTopx, double rectTopy, double rectWidth, double rectHeight);
	template<class T>
	static bool isPointInRect(const GCP_Point<T> &TopLeft, const GCP_Point<T> &BottomRight, const GCP_Point<T> &point)
	{
		return isInRect(point.X, point.Y, TopLeft.X, TopLeft.Y, BottomRight.X - TopLeft.X, BottomRight.Y - TopLeft.Y);
	}
	template<class T>
	static bool isPointInRect(GCP_Rect<T> const& rect, GCP_Point<T> const& point)
	{
		return isPointInRect<T>(rect.topLeft(), rect.bottomRight(), point);
	}

	template<class T>
	static bool isPointInLine(const GCP_Line<T> &line, const GCP_Point<T> &checkPoint)
	{
		GCP_Point<T> TopLeft(Min(line.pointA.X, line.pointB.X), Min(line.pointA.Y, line.pointB.Y));
		GCP_Point<T> BottomRight(Max(line.pointA.X, line.pointB.X), Max(line.pointA.Y, line.pointB.Y));
		return isPointInRect(TopLeft, BottomRight, checkPoint);
	}
	template<class T>
	static bool isPointNear(const GCP_Point<T> &pointA, const GCP_Point<T> &pointB, int dist)
	{
		return isPointInRect(GCP_Point<T>(pointB.X - dist / 2, pointB.Y - dist / 2), GCP_Point<T>(pointB.X + dist / 2, pointB.Y + dist / 2), pointA);
	}

	//Направление линии относительно абсцисс OX
	template<class T>
	static double lineAngle(const GCP_Point<T> &p11, const GCP_Point<T> &p12)
	{
		double N1 = (double)(p12.X - p11.X);
		double N2 = (double)(p12.Y - p11.Y);
		return pointDirection(0, 0, N1, N2);
	}

	//Return rect of rectInside that is positioned in center (inside) of rectBorder
	template<class T>
	static GCP_Rect<T> centerRectInRect(const GCP_Rect<T>& rectInside, const GCP_Rect<T>& rectBorder)
	{
		T x = rectBorder.width() / 2 - rectInside.width() / 2;
		T y = rectBorder.height() / 2 - rectInside.height() / 2;
		return GCP_Rect<T>(x, y, rectInside.width(), rectInside.height());
	}

	//Поправить rectInside внутрь rectBorder
	template<class T>
	static GCP_Point<T> normalizeRectInRect(const GCP_Rect<T>& rectInside, const GCP_Rect<T>& rectBorder, T offset)
	{
		GCP_Point<T> drawPoint = GCP_Point<T>(rectInside.x(), rectInside.y());

		if (drawPoint.X + rectInside.width() + offset > rectBorder.x() + rectBorder.width())
			drawPoint.X -= drawPoint.X + rectInside.width() + offset - rectBorder.width();

		if (drawPoint.Y + rectInside.height() + offset > rectBorder.y() + rectBorder.height())
			drawPoint.Y -= drawPoint.Y + rectInside.height() + offset - rectBorder.height();

		if (drawPoint.X < rectBorder.topLeft().X + offset)
			drawPoint.X = rectBorder.topLeft().X + offset;

		if (drawPoint.Y < rectBorder.topLeft().Y + offset)
			drawPoint.Y = rectBorder.topLeft().Y + offset;

		return drawPoint;
	}

	//Поправить точку point внутрь прямоугольника
	template<class T>
	static GCP_Point<T> normalizePointInRect(const GCP_Point<T> &point, const GCP_Point<T> &pmin, const GCP_Point<T> &pmax)
	{
		GCP_Point<T> normPoint;
		normPoint.X = Max(Min(point.X, (double)pmax.X), (double)pmin.X);
		normPoint.Y = Max(Min(point.Y, (double)pmax.Y), (double)pmin.Y);
		return normPoint;
	}

	//Пересечение двух линий
	template<class T>
	static bool lineIntersection(GCP_Line<T> const& A, GCP_Line<T> const& B,  GCP_Point<T> *R, bool IsRayIntersection = false)
	{
		typedef long double L;
		//Пересечение двух линий L1(x1,y1,x2,y2) L2(x3,y3,x4,y4) в точке (Rx,Ry)
		L x1, y1, x2, y2, x3, y3, x4, y4;
		x1 = A.pointA.X;	y1 = A.pointA.Y;
		x2 = A.pointB.X;	y2 = A.pointB.Y;
		x3 = B.pointA.X;	y3 = B.pointA.Y;
		x4 = B.pointB.X;	y4 = B.pointB.Y;

		L fDevide = (L)((x1 - x2)*(y3 - y4)) - (L)((y1 - y2)*(x3 - x4));
		if (fDevide != 0)
		{
			L statmentx = (x3 - x4)*((L)x1*y2 - (L)y1*x2)
						- (x1 - x2)*((L)x3*y4 - (L)y3*x4);
			R->X = ((L)(statmentx / fDevide));
			L statmenty = (y3 - y4)*((L)x1*y2 - (L)y1*x2)
						- (y1 - y2)*((L)x3*y4 - (L)y3*x4);
			R->Y = ((L)(statmenty / fDevide));
			//Проверка что пересечение действительно на линии, а не где-то на луче
			if (IsRayIntersection)
				return true;
			return (isPointInLine(A, *R) && isPointInLine(B, *R)) ? true : false;
		}
		else
		{
			R->X = 0;
			R->Y = 0;
			return false;
		}
	}

	//Пересечение линии и прямоугольника
	template<class T>
	static bool lineRectIntersection(GCP_Rect<T> const& rect, GCP_Line<T> const& line, GCP_Vector< GCP_Point<T> > *R)
	{
		GCP_Point<T> TopLeft(rect.topLeft());
		GCP_Point<T> TopRight(rect.x()+rect.width(), rect.y());
		GCP_Point<T> BottomLeft(rect.x(), rect.y()+rect.height());
		GCP_Point<T> BottomRight(rect.bottomRight());
		//Поиск всех пересечений между гранями прямоугольника и линией L (*именно линией, не лучом)
		GCP_Point<T> intersection;

		if (lineIntersection(GCP_Line<T>(TopLeft, TopRight), line, &intersection))
			R->push_back(intersection);

		if (lineIntersection(GCP_Line<T>(TopLeft, BottomLeft), line, &intersection))
			R->push_back(intersection);

		if (lineIntersection(GCP_Line<T>(BottomLeft, BottomRight), line, &intersection))
			R->push_back(intersection);

		if (lineIntersection(GCP_Line<T>(TopRight, BottomRight), line, &intersection))
			R->push_back(intersection);

		return (R->size() > 0);
	}

	template<class T>
	static double vectorMultiplication(GCP_Line<T> const& a, GCP_Line<T> const& b)
	{
		T lena = std::abs(pointDistance(a.pointA, a.pointB));
		T lenb = std::abs(pointDistance(b.pointA, b.pointB));
		double ax = (double)(a.pointB.X - a.pointA.X)/lena;
		double ay = (double)(a.pointB.Y - a.pointA.Y)/lena;
		double bx = (double)(b.pointB.X - b.pointA.X)/lenb;
		double by = (double)(b.pointB.Y - b.pointA.Y)/lenb;
		return 	(double)(ax*by - ay*bx);
	}

	template<class T>
	static bool isPointInMultiRect(GCP_Vector< GCP_Line<T> > const& rect, GCP_Point<T> const& point)
	{
		double sum = 0;
		for (size_t i = 0; i < rect.size(); i++)
		{
			GCP_Line<T> a(point, rect.at(i).pointA);
			GCP_Line<T> b(point, rect.at(i).pointB);
			double dira = pointDirection(point, rect.at(i).pointA);
			double dirb = pointDirection(point, rect.at(i).pointB);
			double angle = std::abs(norm_dir_dif(dira,dirb));
			if (vectorMultiplication(a, b) >= 0)
				sum += angle;
			else sum -= angle;
		}
		return (std::abs(sum) < 1) ? false : true;
	}

	//Пересечение многоугольников (наборов линий)
	template<class T>
	static bool rectRectIntersection(GCP_Vector< GCP_Line<T> > const& rect1, GCP_Vector< GCP_Line<T> > const& rect2)
	{
		GCP_Point<T> R;
		//все линии рект1 со всеми линиями рект2
		for (size_t i = 0; i < rect1.size(); i++)
		{
			GCP_Line<T>& line_a = rect1.at(i);
			for (size_t j = 0; j < rect2.size(); j++)
			{
				GCP_Line<T>& line_b = rect2.at(j);
				if (lineIntersection(line_a, line_b, &R))
					return true;
			}
		}
		return false;
	}


	//преломление и отражение line1 от line2
	template<class T>
	static void lineRefractReflect(GCP_Line<T> const& line1, GCP_Line<T> const& line2, reflectinfo& info)
	{
		///отражение
		double alpha = lineAngle(line2);	// Угол line2 относительно OX
		double Nalpha = alpha + 90;			// Угол нормали к line2 OX

		// Угол line1 относительно ОX
		double alpha2 = pointDirection(0, 0, line1.pointB.X - line1.pointA.X, line1.pointB.Y - line1.pointA.Y);

		// Угол отражения line1 от line2
		info.reflectedAngleOX = alpha2 - 2 * (alpha2 - Nalpha);

		//Угол падения на line2 относительно перпендикуляра к ней
		info.reflectedAngle = std::abs(norm_dir_dif(alpha2, Nalpha));
		if (info.reflectedAngle > 90) info.reflectedAngle = 180 - info.reflectedAngle;

		///преломление
		if (alpha < 90)						// Берем самый большой наклон
			alpha += 180;
		Nalpha = alpha - 90;				// Угол нормали к line2
		double alpha3 = norm_dir_dif(alpha2, Nalpha);	// угол падения луча относительно линии

		double x = (info.N1 * ssin(alpha3)) / info.N2;
		if (x < -1 || x > 1)
		{
			info.refractedAngle = 0;
			info.refractedAngleOX = 0;
			info.refractionError = true;
			return;
		}

		// Угол преломления
		double refractedAngle = GCP_RADTODEG*asin(x);
		bool isBelowLine = isPointBelowLine(line1.pointA, line2);
		if (isBelowLine)
			info.refractedAngleOX = Nalpha + 180 - refractedAngle;
		else info.refractedAngleOX = Nalpha + refractedAngle;

		info.refractedAngleOX = normAngle(info.refractedAngleOX);
		info.refractedAngle = std::abs(refractedAngle);
		info.refractionError = false;
	}

	//Угол преломления ray(p11,p12) сквозь line(p21,p22) из N1 в N2
	//refractedAngleOX - угол относительно OX
	//refractedAngle   - угол относительно line
	//error = 1        - преломление невозможно
	template<class T>
	static void lineRefractionAngle(GCP_Point<T> const& p11, GCP_Point<T> const& p12, GCP_Point<T> const& p21, GCP_Point<T> const& p22, double N1, double N2, double *refractedAngleOX, double *refractedAngle, int *error)
	{
		double alpha = lineAngle(p21, p22);								 // Угол стенки относительно ОX
		if (alpha < 90) alpha += 180;									 // Берем самый большой наклон
		double Nalpha = alpha - 90;                                      // Угол нормали к этой стенке
		double alpha2 = pointDirection(0, 0, p12.X - p11.X, p12.Y - p11.Y);   // Угол падающего луча относительно ОX
		double alpha3 = norm_dir_dif(alpha2, Nalpha);					 // угол падения луча относительно линии

		double x = (N1 * ssin(alpha3)) / N2;
		if (x < -1 || x > 1)	{		//wrong asin
			*refractedAngleOX = 0;
			*refractedAngle = 0;
			*error = -1;
			return;
		}

		double reflectedAngle = GCP_RADTODEG*asin(x);	 // Угол преломления
		bool isBelowLine = isPointBelowLine(p11, GCP_Line<T>(p21, p22));
		if (isBelowLine)
			*refractedAngleOX = Nalpha + 180 - reflectedAngle;
		else *refractedAngleOX = Nalpha + reflectedAngle;

		*refractedAngle = std::abs(reflectedAngle);
		*error = 1;
	}
	template<class T>
	static void lineRefractionAngle(const GCP_Line<T> &L1, const GCP_Line<T> &L2, double N1, double N2, double *refractedAngleOX, double *refractedAngle, int *error)
	{
		lineRefractionAngle(L1.pointA, L1.pointB, L2.pointA, L2.pointB, N1, N2, refractedAngleOX, refractedAngle, error);
	}

	//Угол отражения ray(p11, p12) от line (p21, p22)
	//reflectedAngle - относительно line
	template<class T>
	static void lineReflectionAngle(GCP_Point<T> const& p11, GCP_Point<T> const& p12, GCP_Point<T> const& p21, GCP_Point<T> const& p22, double *reflectedAngleOX, double *reflectedAngle)
	{
		double alpha = lineAngle(p21, p22);
		double Nalpha = alpha + 90;										// Угол нормали к этой стенке OX
		double alpha2 = pointDirection(0, 0, p12.X - p11.X, p12.Y - p11.Y);  // Угол падающего луча относительно ОX
		*reflectedAngleOX = alpha2 - 2 * (alpha2 - Nalpha);				// Угол отражения падающего луча от стенки

		//Угол падения на стенку относительно перпендикуляра к ней
		*reflectedAngle = std::abs(norm_dir_dif(alpha2, Nalpha));
		if (*reflectedAngle > 90) *reflectedAngle = 180 - *reflectedAngle;
	}
	template<class T>
	static void lineReflectionAngle(const GCP_Line<T> &A, const GCP_Line<T> &B, double *d, double *d2)
	{
		lineReflectionAngle(A.pointA, A.pointB, B.pointA, B.pointB, d, d2);
	}
	template<class T>
	static double lineReflectionAngle(const GCP_Line<T> &A, const GCP_Line<T> &B)
	{
		double d, d2;
		lineReflectionAngle(A.pointA, A.pointB, B.pointA, B.pointB, &d, &d2);
		return d;
	}


	template<class T>
	static double lineAngle(const GCP_Line<T> &L) 	{ 	return lineAngle(L.pointA, L.pointB); 	}

	static GCP_Vector<string> *strToLines(const string &Text)
	{
		char str;
		unsigned int i = 0;
		string line;
		GCP_Vector<std::string> *strings = new GCP_Vector<std::string>();
		while (i < Text.size())
		{
			line = "";
			str = Text.at(i);
			while (str != '\n')
			{
				line += str;
				i++;
				if (i >= Text.size())
					break;
				str = Text.at(i);
			}
			strings->push_back(line);
			i++;
		}
		return strings;
	}

	//depricated
	/*template< class A>
	static void quickSort(GCP_Vector<A> *a, int l, int r)
	{
		if (a->size() < 2)
			return;

		A x = a->at(l + (r - l) / 2); //запись эквивалентна (l+r)/2,
		int i = l;					  //но не вызввает переполнения на больших данных
		int j = r;

		while (i <= j)
		{
			while (a->compareAltB(a->at(i), x)) i++;    //a(i) < x
			while (a->compareAgtB(a->at(j), x)) j--;    //a(j) > x
			if (i <= j)
			{
				a->swap(i, j);
				i++;
				j--;
			}
		}
		if (i < r)
			quickSort(a, i, r);

		if (l < j)
			quickSort(a, l, j);
	}*/


	///!REV
	template< class A>
	static void quickSortComponent(GCP_Vector<A> *a, int l, int r, int criteria = -1)
	{
		if (a->size() < 2)
			return;

		A x = a->at(l + (r - l) / 2); //запись эквивалентна (l+r)/2,
		int i = l;					  //но не вызввает переполнения на больших данных
		int j = r;

		while (i <= j)
		{
			while ((a->at(i))->compare(x, 1, criteria)) i++;
			while ((a->at(j))->compare(x, 2, criteria)) j--;
			if (i <= j)
			{
				a->swap(i, j);
				i++;
				j--;
			}
		}
		if (i < r)
			quickSortComponent(a, i, r, criteria);

		if (l < j)
			quickSortComponent(a, l, j, criteria);
	}


	static double normAngle(double value);
	static string normAngleS(double value);
	static double norm_dir_dif(double dir1, double dir2);
	static string intToString(int value);
	static string doubleToString(double value);
	static int stringToInt(char* str);
	static double stringToDouble(char* str);

	static bool isOneByteChar(const char s)
	{
		static string engAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		static string symAlphabet = ".+_-/*!@#$%^&()№;:?{}[]|'\\~\"0123456789";

		return (isCharInStr(engAlphabet, &s) || isCharInStr(symAlphabet, &s));
	}

	static bool isCharInStr(string const& str, const char* ch)
	{
		const char * chars = str.c_str();
		for (size_t i = 0; i < str.size(); i++)
		{
			if (chars[i] == *ch)
				return true;
		}
		return false;
	}
	static bool isNum(char *s)
	{
		int i = 0, flag = 1;
		static string engAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		static string rusAlphabet = "абвгдеёжзийклмнопрстуфхцчшщьыъэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
		static string symAlphabet = "+_-/*!@#$%^&()№;:?{}[]|'\\~\"";

		while (s[i])
		{
			//if there is a letter in a string then string is not a number
			//if (isalpha(s[i]))//Does not work on russina characters

			if (strstr(engAlphabet.c_str(), s) != NULL || strstr(rusAlphabet.c_str(), s) != NULL
					|| strstr(symAlphabet.c_str(), s) != NULL
					)
			{
				flag = 0;
				break;
			}
			/*else
				{
				flag = 1;
				if (strstr("+_-/*!@#$%^&()№;:?{}[]|'\\~\"", s) != NULL)
				flag = 0;

				}*/

			i++;
		}
		if (flag == 1) return true;
		else return false;
	}
	static int findStringInVector(const string &sTextIn, GCP_Vector<string> *vector);
	static int readIntegerArray(char* strline, char separator, GCP_Vector<int>& _arr);
	static unsigned int uniqueValue64();
	static size_t utf8_length(unsigned char c);
	static char *utf8_next(char *p);
	static char *utf8_advance(char *p, size_t distance);
	static string Font_StrToEng(const string &text);
	static void Font_StrToEng(const string &sTextIn, char* sTextOut, bool special_symbols);
	static string& DefineRusToEng();
	//static int convert_utf8_to_windows1251(const char* utf8, char* windows1251, size_t n);

	///////////// Genetic /////////////
	int bin2dec(const string* binary);
	int bin2dec(const char* binary);
	string* binchar_set_length(const string *buff, int size);
	int *binaryStringTointegers(const string &binary, int size, int *arr);
	string integersToBinaryString(int *arr, int size);
	/// @brief Генетическая апроксимация
	/// @param i_class				- Указатель на класс-обработчик.
	/// @param i_method				- Указатель на метод класса-обработчика (весовая функция).
	/// @param baseInput			- Строка string с бинарными данными "00110101110".
	/// @param populationsize		- Размер популяции объектов (особей).
	/// @param devideblocks			- Количество разбиений на хромосомы при скрещивании.
	/// @param mutationprobability  - Вероятность мутации особей
	template< class T, class U >
	static string GeneticApproximation(T* i_class, U i_method, const string &baseInput, int populationsize, int devideblocks, double mutationprobability)
	{
		IContainer* func = new  Container< T, U >(i_class, i_method);

		GCP_Vector<GeneticSpecies*> generation;
		GCP_Vector<GeneticSpecies*> next_generation;
		for (int i = 0; i < populationsize; i++){
			GeneticSpecies *specie = new GeneticSpecies();
			specie->values = baseInput;
			specie->result = 1;
			generation.push_back(specie);
		}

		//Iteration
		int iK = 0, spawn = 0;
		double dBestResult = (int)func->Call((void*)&baseInput);

		do
		{
			//Solve problem
			for (int i = 0; i < generation.size(); i++)
			{
				GeneticSpecies *obj = generation.at(i);
				obj->result = (int)func->Call((void*)&obj->values);
				if (obj->result < dBestResult)
					dBestResult = obj->result;
			}

			//Clear previous pointers
			for (int i = 0; i < next_generation.size(); i++)
				delete next_generation.at(i);
			next_generation.clear();

			iK = 0;
			for (int i = 0; i < generation.size(); i++)
			{
				if (generation.at(i)->result <= dBestResult)
				{
					int iRandomElement = GCP_Math::rnd()*(generation.size() - 1);
					GeneticSpecies *obj = new GeneticSpecies();
					obj->result = generation.at(i)->result;
					obj->values = generation.at(i)->values;
					if (GCP_Math::rnd() < mutationprobability)
						obj->mutation();
					obj->breed(generation.at(iRandomElement), devideblocks);
					obj->result = (int)func->Call((void*)&obj->values);

					if (obj->result < generation.at(i)->result)
						next_generation.push_back(obj);
					else
					{
						obj->result = generation.at(i)->result;
						obj->values = generation.at(i)->values;
						next_generation.push_back(obj);
					}
					iK++;
				}
			}

			//Clear previous pointers
			for (int i = 0; i < generation.size(); i++)
				delete generation.at(i);
			generation.clear();

			for (int i = 0; i < next_generation.size(); i++)
			{
				GeneticSpecies *obj = new GeneticSpecies();
				obj->result = next_generation.at(i)->result;
				obj->values = next_generation.at(i)->values;
				generation.push_back(obj);
			}
			spawn++;
		} while (iK > 1 && spawn < 100);


		int minResult = 500000;	//! MAX REWARD
		int minResultIndex = -1;
		for (int i = 0; i < generation.size(); i++)
		{
			if (generation.at(i)->result<minResult){
				minResult = generation.at(i)->result;
				minResultIndex = i;
			}
		}

		string RetVal;
		int iRandomElement = GCP_Math::rnd()*(generation.size() - 1);
		if (minResultIndex != -1)
			RetVal = generation.at(minResultIndex)->values;
		if (iRandomElement > -1 && iRandomElement < generation.size())
			RetVal = generation.at(iRandomElement)->values;
		else RetVal = baseInput;

		//Clear All pointers
		for (int i = 0; i < generation.size(); i++)
			delete generation.at(i);
		for (int i = 0; i < next_generation.size(); i++)
			delete next_generation.at(i);

		generation.clear();
		next_generation.clear();
		delete func;
		return RetVal;
	}

	/**
		 * C++ version 0.4 char* style "itoa":
		 * Written by Luk?s Chmela
		 * Released under GPLv3.
		 */
	char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}
};

inline std::string CP1251_TO_WCHAR(const char *str)
{
	return GCP_Math::RUSCP1251_TO_WCHAR(str);
}

struct GCP_UID
{
	unsigned int key_a; //64
	unsigned int key_b; //128
	unsigned int key_c; //192
	unsigned int key_d; //256
	GCP_UID(unsigned int a, unsigned int b, unsigned int c, unsigned int d):
		key_a(a), key_b(b), key_c(c), key_d(d) {}

	GCP_UID()
	{
		key_a = GCP_Math::uniqueValue64();
		key_b = GCP_Math::uniqueValue64();
		key_c = GCP_Math::uniqueValue64();
		key_d = GCP_Math::uniqueValue64();
	}

	string toStr() const
	{
		int key_a1 = key_a - GCP_INT32MAX;
		int key_b1 = key_b - GCP_INT32MAX;
		int key_c1 = key_c - GCP_INT32MAX;
		int key_d1 = key_d - GCP_INT32MAX;
		return GCP_Math::intToString(key_a1)+GCP_Math::intToString(key_b1)+GCP_Math::intToString(key_c1)+GCP_Math::intToString(key_d1);
	}

	void readFromFile(GCP_IO *io)
	{
		io->readInt(&key_a);
		io->readInt(&key_b);
		io->readInt(&key_c);
		io->readInt(&key_d);
	}

	void writeToFile(GCP_IO *io) const
	{
		io->writeInt(key_a);
		io->writeInt(key_b);
		io->writeInt(key_c);
		io->writeInt(key_d);
	}
	inline friend bool operator == (const GCP_UID& lhs, const GCP_UID& rhs)
	{
		return (lhs.key_a == rhs.key_a && lhs.key_b == rhs.key_b && lhs.key_c == rhs.key_c && lhs.key_d == rhs.key_d);
	}
	bool operator == (const GCP_UID& rhs)
	{
		return (key_a == rhs.key_a && key_b == rhs.key_b && key_c == rhs.key_c && key_d == rhs.key_d);
	}
};

class RandomSequenceOfUnique
{
private:
	unsigned int m_index;
	unsigned int m_intermediateOffset;
	static unsigned int permuteQPR(unsigned int x)
	{
		static const unsigned int prime = 4294967291u;
		if (x >= prime)
			return x; // The 5 integers out of range are mapped to themselves.
		unsigned int residue = ((unsigned long long) x * x) % prime;
		return (x <= prime / 2) ? residue : prime - residue;
	}
public:
	RandomSequenceOfUnique(unsigned int seedBase, unsigned int seedOffset)
	{
		m_index = permuteQPR(permuteQPR(seedBase) + 0x682f0161);
		m_intermediateOffset = permuteQPR(permuteQPR(seedOffset) + 0x46790905);
	}
	unsigned int next()
	{
		return permuteQPR((permuteQPR(m_index++) + m_intermediateOffset) ^ 0x5bf03635);
	}
};

}
#endif
