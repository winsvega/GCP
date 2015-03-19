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

namespace gcp
{
	const double GCP_RADTODEG = (double)180 / 3.14;
	const double GCP_DEGTORAD = (double)3.14 / 180;
	using namespace std;

	///
	template<class T>
	struct GCP_Point
	{
		T  X, Y;
		GCP_Point(T x, T y) { X = x; Y = y; }
		GCP_Point(){};
		GCP_Point(GCP_Point* point)
		{
			X = point->X;
			Y = point->Y;
		}
		~GCP_Point(){}
		operator GCP_Point<int>() { return GCP_Point<int>((int)X, (int)Y); }//приведение к типу GCP_Point<int>
	};

	///
	template<class T>
	struct GCP_Line
	{
		GCP_Point<T> pointA, pointB;					//Структура для линии
		GCP_Line(){};
		GCP_Line(GCP_Point<T> A, GCP_Point<T> B){ SetPoints(A, B); }
		GCP_Line(T x1, T y1, T x2, T y2) : pointA(x1, y1), pointB(x2, y2){}
		void SetPoints(GCP_Point<T> A, GCP_Point<T> B){ pointA = A; pointB = B; }
		double length()
		{
			return sqrt(pow(pointA.X - pointB.X, 2) + pow(pointA.Y - pointB.Y, 2));
		}
	};

	template<class T>
	struct GCP_Rect
	{
		GCP_Rect(){};
		GCP_Rect(const GCP_Point<T> &topLeft_, const GCP_Point<T> &bottomRight_) :topLeft(topLeft_), widthHeight(bottomRight_){}
		GCP_Rect(T x, T y, T width, T height) : topLeft(GCP_Point<T>(x, y)), widthHeight(GCP_Point<T>(width, height)) {}
		GCP_Point<T> topLeft, widthHeight;
		const T& x()const{ return topLeft.X; }
		const T& y()const{ return topLeft.Y; }
		const T& width()const{ return widthHeight.X; }
		const T& height()const{ return widthHeight.Y; }
		const GCP_Point<T> center()const{ return GCP_Point<T>(topLeft.X + widthHeight.X / 2, topLeft.Y + widthHeight.Y / 2); }
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

		template <class T>
		static bool isPointBelowLine(const GCP_Point<T> &P, const GCP_Line<T> &L)
		{
			// Возвращает находится ли точка снизу от линии или сверху
			bool isBelow = ((long double)(L.pointB.X - L.pointA.X)*(P.Y - L.pointA.Y) - (long double)(L.pointB.Y - L.pointA.Y)*(P.X - L.pointA.X) > 0);
			if (lineAngle(L) > 90) return  isBelow;
			return !isBelow;
		}

		static bool isInRadius(double x1, double y1, double x2, double y2, double r);
		static bool isInRect(double pointX, double pointY, double rectTopx, double rectTopy, double rectWidth, double rectHeight);

		///
		template<class T>
		static bool isPointInRect(const GCP_Point<T> &TopLeft, const GCP_Point<T> &BottomRight, const GCP_Point<T> &point)
		{
			return isInRect(point.X, point.Y, TopLeft.X, TopLeft.Y, BottomRight.X - TopLeft.X, BottomRight.Y - TopLeft.Y);
		}

		///
		template<class T>
		static double lineAngle(const GCP_Point<T> &p11, const GCP_Point<T> &p12)
		{
			double N1 = (double)(p12.X - p11.X);		//Направление линии относительно абсцисс
			double N2 = (double)(p12.Y - p11.Y);
			return pointDirection(0, 0, N1, N2);
		}

		///
		//Return rect of rectInside that is positioned in center inside rectBorder
		template<class T>
		static GCP_Rect<T> centerRectInRect(const GCP_Rect<T>& rectInside, const GCP_Rect<T>& rectBorder)
		{
			T x = rectBorder.width() / 2 - rectInside.width() / 2;
			T y = rectBorder.height() / 2 - rectInside.height() / 2;
			return GCP_Rect<T>(x, y, rectInside.width(), rectInside.height());
		}

		///
		template<class T>
		static GCP_Point<T> normalizeRectInRect(const GCP_Rect<T>& rectInside, const GCP_Rect<T>& rectBorder, T offset)
		{
			GCP_Point<T> drawPoint = GCP_Point<T>(rectInside.x(), rectInside.y());

			if (drawPoint.X + rectInside.width() + offset > rectBorder.x() + rectBorder.width())
				drawPoint.X -= drawPoint.X + rectInside.width() + offset - rectBorder.width();

			if (drawPoint.Y + rectInside.height() + offset > rectBorder.height())
				drawPoint.Y -= drawPoint.Y + rectInside.height() + offset - rectBorder.height();

			if (drawPoint.X < rectBorder.topLeft.X + offset)
				drawPoint.X = rectBorder.topLeft.X + offset;

			if (drawPoint.Y < rectBorder.topLeft.Y + offset)
				drawPoint.Y = rectBorder.topLeft.Y + offset;

			return drawPoint;
		}

		///
		template<class T>
		static GCP_Point<T> normalizePointInRect(const GCP_Point<T> &point, const GCP_Point<T> &pmin, const GCP_Point<T> &pmax)
		{
			GCP_Point<T> normPoint;
			normPoint.X = Max(Min(point.X, (double)pmax.X), (double)pmin.X);
			normPoint.Y = Max(Min(point.Y, (double)pmax.Y), (double)pmin.Y);
			return normPoint;
		}

		static double round(double value);
		static bool lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double *Px, double *Py, bool round = false);

		///
		template<class T>
		static bool lineIntersection(const GCP_Point<T> &p11, const GCP_Point<T> &p12, const GCP_Point<T> &p21, const GCP_Point<T> &p22, GCP_Point<T> *R, bool round = false)
		{
			double xx, yy;
			bool collision = lineIntersection(p11.X, p11.Y, p12.X, p12.Y, p21.X, p21.Y, p22.X, p22.Y, &xx, &yy, round);
			*R = GCP_Point<T>(xx, yy);
			return collision;
		}

		///
		template<class T>
		static bool lineIntersection(const GCP_Line<T> &A, const GCP_Line<T> &B, GCP_Point<T> *R, bool round = false)
		{
			return lineIntersection(A.pointA, A.pointB, B.pointA, B.pointB, R, round);
		}

		///
		template<class T>
		static bool lineRectIntersection(const GCP_Point<T> &TopLeft, const GCP_Point<T> &TopRight, const GCP_Point<T> &BottomLeft, const GCP_Point<T> &BottomRight, const GCP_Line<T> &L, GCP_Vector< GCP_Point<T> > *R)
		{
			//Поиск всех пересечений между гранями прямоугольника и линией L (*именно линией, не лучом)
			GCP_Point<T> intersection;
			bool isIntersect;
			L = GCP_Line<T>(GCP_Point<T>(round(L.pointA.X), round(L.pointA.Y)),
							GCP_Point<T>(round(L.pointB.X), round(L.pointB.Y)));

			isIntersect = lineIntersection(GCP_Line<T>(TopLeft, TopRight), L, &intersection, true);
			if (isIntersect)	{
				//Проверка что пересечение действительно на линии, а не где-то на луче
				if (isPointInLine(GCP_Line<T>(TopLeft, TopRight), intersection) && isPointInLine(L, intersection))
					R->push_back(intersection);
			}

			isIntersect = GCP_Math::lineIntersection(GCP_Line<T>(TopLeft, BottomLeft), L, &intersection, true);
			if (isIntersect)	{
				if (isPointInLine(GCP_Line<T>(TopLeft, BottomLeft), intersection) && isPointInLine(L, intersection))
					R->push_back(intersection);
			}

			isIntersect = GCP_Math::lineIntersection(GCP_Line<T>(BottomLeft, BottomRight), L, &intersection, true);
			if (isIntersect)	{
				if (isPointInLine(GCP_Line<T>(BottomLeft, BottomRight), intersection) && isPointInLine(L, intersection))
					R->push_back(intersection);
			}

			isIntersect = GCP_Math::lineIntersection(GCP_Line<T>(TopRight, BottomRight), L, &intersection, true);
			if (isIntersect)	{
				if (isPointInLine(GCP_Line<T>(TopRight, BottomRight), intersection) && isPointInLine(L, intersection))
					R->push_back(intersection);
			}

			return (R->size() > 0);
		}

		static bool compareDouble(double x, double y);
		static bool compareDoubleEqual(double x, double y);
		static double rnd();
		static double rnd(const char *dist, double a, double b);
		static double pointDirection(double x1, double y1, double x2, double y2);

		///
		template<class T>
		static double pointDirection(const GCP_Point<T> &A, const GCP_Point<T> &B)
		{
			return pointDirection(A.X, A.Y, B.X, B.Y);
		}

		static double pointDistance(double x1, double y1, double x2, double y2);

		///
		template<class T>
		static void lineRefractionAngle(const GCP_Point<T> &p11, const GCP_Point<T> &p12, const GCP_Point<T> &p21, const GCP_Point<T> &p22, double N1, double N2, double *refractedAngleOX, double *refractedAngle, int *error)
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

			*refractedAngle = abs(reflectedAngle);
			*error = 1;
		}

		///
		template<class T>
		static void lineReflectionAngle(const GCP_Point<T> &p11, const GCP_Point<T> &p12, const GCP_Point<T> &p21, const GCP_Point<T> &p22, double *reflectedAngleOX, double *reflectedAngle)
		{
			double alpha = lineAngle(p21, p22);
			double Nalpha = alpha + 90;										// Угол нормали к этой стенке OX
			double alpha2 = pointDirection(0, 0, p12.X - p11.X, p12.Y - p11.Y);  // Угол падающего луча относительно ОX
			*reflectedAngleOX = alpha2 - 2 * (alpha2 - Nalpha);				// Угол отражения падающего луча от стенки

			//Угол падения на стенку относительно перпендикуляра к ней
			*reflectedAngle = abs(norm_dir_dif(alpha2, Nalpha));
			if (*reflectedAngle > 90) *reflectedAngle = 180 - *reflectedAngle;
		}


		///
		template<class T>
		static void lineReflectionAngle(const GCP_Line<T> &A, const GCP_Line<T> &B, double *d, double *d2)
		{
			lineReflectionAngle(A.pointA, A.pointB, B.pointA, B.pointB, d, d2);
		}

		///
		template<class T>
		static double lineReflectionAngle(const GCP_Line<T> &A, const GCP_Line<T> &B)
		{
			double d, d2;
			lineReflectionAngle(A.pointA, A.pointB, B.pointA, B.pointB, &d, &d2);
			return d;
		}

		///
		template<class T>
		static double pointDistance(const GCP_Point<T> &X, const GCP_Point<T> &Y)
		{
			return pointDistance(X.X, X.Y, Y.X, Y.Y);
		}

		///
		template<class T>
		static double lineAngle(const GCP_Line<T> &L)
		{
			return lineAngle(L.pointA, L.pointB);
		}

		///
		template<class T>
		static void lineRefractionAngle(const GCP_Line<T> &L1, const GCP_Line<T> &L2, double N1, double N2, double *refractedAngleOX, double *refractedAngle, int *error)
		{
			lineRefractionAngle(L1.pointA, L1.pointB, L2.pointA, L2.pointB, N1, N2, refractedAngleOX, refractedAngle, error);
		}


		template<class T>
		static T Min(T a, T b)
		{
			if (a < b) return a;
			return b;
		}

		template<class T>
		static T Max(T a, T b)
		{
			if (a < b) return b;
			return a;
		}


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

		///
		template< class A>
		static void quickSort(GCP_Vector<A> *a, int l, int r)
		{
			if (a->size() < 2)
				return;
			A x = a->at(l + (r - l) / 2);
			//запись эквивалентна (l+r)/2,
			//но не вызввает переполнения на больших данных
			int i = l;
			int j = r;
			//код в while обычно выносят в процедуру particle
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
		}


		//depricated
		template< class A>
		static void quickSortComponent(GCP_Vector<A> *a, int l, int r, int criteria = -1)
		{
			if (a->size() < 2)
				return;

			A x = a->at(l + (r - l) / 2);
			//запись эквивалентна (l+r)/2,
			//но не вызввает переполнения на больших данных
			int i = l;
			int j = r;
			//код в while обычно выносят в процедуру particle
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

		static double ccos(double value);
		static double ssin(double value);
		static double arcsin(double value);

		///
		template<class T>
		static bool isPointInLine(const GCP_Line<T> &line, const GCP_Point<T> &checkPoint)
		{
			GCP_Point<T> TopLeft(Min(line.pointA.X, line.pointB.X), Min(line.pointA.Y, line.pointB.Y));
			GCP_Point<T> BottomRight(Max(line.pointA.X, line.pointB.X), Max(line.pointA.Y, line.pointB.Y));
			return isPointInRect(TopLeft, BottomRight, checkPoint);
		}


		///
		template<class T>
		static bool isPointNear(const GCP_Point<T> &pointA, const GCP_Point<T> &pointB, int dist)
		{
			return isPointInRect(GCP_Point<T>(pointB.X - dist / 2, pointB.Y - dist / 2), GCP_Point<T>(pointB.X + dist / 2, pointB.Y + dist / 2), pointA);
		}

		static double normAngle(double value);
		static string normAngleS(double value);
		static double norm_dir_dif(double dir1, double dir2);
		static string intToString(int value);
		static string doubleToString(double value);
		static int stringToInt(char* str);
		static double stringToDouble(char* str);
		static bool isNum(char *s)
		{
			int i = 0, flag = 1;
			static string engAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			static string rusAlphabet = "абвгдеёжзийклмнопрстуфхцчшщьыъэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
			static string symAlphabet = "+_-/*!@#$%^&()№;:?{}[]|'\\~\"";

			while (s[i]){
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
		static int readIntegerArray(char* strline, char separator, int *arr);
		static double uniqueValue();
		static size_t utf8_length(unsigned char c);
		static char *utf8_next(char *p);
		static char *utf8_advance(char *p, size_t distance);
		static string Font_StrToEng(const string &text);
		static void Font_StrToEng(const string &sTextIn, char* sTextOut, bool special_symbols);
		static string& DefineRusToEng();

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

	//#define CP1251_TO_WCHAR(str) GCP_Math::RUSCP1251_TO_WCHAR(str);
	inline std::string CP1251_TO_WCHAR(const char *str)
	{
		return GCP_Math::RUSCP1251_TO_WCHAR(str);
	}
}
#endif
