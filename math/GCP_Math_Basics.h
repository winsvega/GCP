
static double ccos(double value) { return cos(GCP_DEGTORAD*value); }
static double ssin(double value) { return sin((double)(GCP_DEGTORAD*value)); }
static double arcsin(double value) { return asin(value); }
static double rnd() { return (double)rand() / RAND_MAX; }
static double rnd(const char *dist, double a, double b)
{
	if (strcmp(dist, "norm") == 0)
	{
		//Подпрограмма нормального распределения - возв СВ по гауссу с МО a и дисп 1.
		while (1)
		{
			double v1, v2, s;
			v1 = (double)(2.*rnd()) - 1.;
			v2 = (double)(2.*rnd()) - 1.;
			s = v1*v1 + v2*v2;
			if ((s <= 1.) && (s>0.))
			{
				//double r;
				//r=v1*sqrt((-2.)*log(s)/s); //за один раз получаем 2 СВ
				return a + (v2*sqrt((-2.)*log(s) / s));
			}
		}
	}
	return -1;
}

static double round(double value)
{
	if (GCP_Math::compareDouble(value - floor(value), 0.5))
		return floor(value);
	return floor(value) + 1;
}

static bool compareDouble(double x, double y)
{
	//x > y ?
	double eps = 1e-5;
	if (x - y > -eps)
		return true;
	return false;
}

static bool compareDoubleEqual(double x, double y)
{
	//x == y ?
	double eps = 1e-5;
	if (std::abs(x - y) < eps)
		return true;
	return false;
}

static double pointDirection(double x1, double y1, double x2, double y2)
{
	//Направление из точки (x1,y1) в точку (x2,y2)
	double d;
	double yd = y1 - y2;
	double xd = x2 - x1;
	double atan = atan2(yd, xd);
	d = (double)(GCP_RADTODEG*atan);			//В градусах
	return normAngle(d);
}

template<class T>
static T Min(T a, T b) 	{ return (a < b) ? a : b; }
template<class T>
static T Max(T a, T b)  { return (a < b) ? b : a; }
template<class T>
static double pointDirection(GCP_Point<T> const&A, GCP_Point<T> const&B)	{ return pointDirection(A.X, A.Y, B.X, B.Y); }
static double pointDistance(double x1, double y1, double x2, double y2)	{	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));	}
template<class T>
static double pointDistance(GCP_Point<T> const&X, GCP_Point<T> const&Y) { return pointDistance(X.X, X.Y, Y.X, Y.Y); }

static double normAngle(double value)
{
	value = fmod(value, 360);		//Нормировка угла в отрезок [0,360)
	//try{
	if (value<0) value += 360;
	//	}
	/*catch(System::ArithmeticException ^e)
	{
	value = 0;
	}*/
	return value;
}

static std::string normAngleS(double value)
{
	int degree = (int)floor(value);
	double tempvalue = 60 * (value - degree);
	int minutes = (int)floor(tempvalue);
	int seconds = (int)floor(60 * (tempvalue - minutes));

	return intToString(degree) + "'" + intToString(minutes) + "'" + intToString(seconds);
}

static double norm_dir_dif(double dir1, double dir2)
{
	double dif = (double)dir1 - dir2;											//Кратчайшее расстояние от направления dir1 к направлению dir2
	if (dif > 180) { return(dif - 360); }											//Пример: из направления 90 в направлениее 300/-60 =  -150
	if (dif < -180) { return(dif + 360); }										//Пример: из направления 90 в направлениее 240/-120 =  150
	return dif; //if (dif<=180 && dif>=-180) {return dif;}
}

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

template<class T>
static double vectorMultiplication(GCP_Line<T> const& a, GCP_Line<T> const& b)
{
	T lena = std::abs(pointDistance(a.pointA, a.pointB));
	T lenb = std::abs(pointDistance(b.pointA, b.pointB));
	double ax = (double)(a.pointB.X - a.pointA.X) / lena;
	double ay = (double)(a.pointB.Y - a.pointA.Y) / lena;
	double bx = (double)(b.pointB.X - b.pointA.X) / lenb;
	double by = (double)(b.pointB.Y - b.pointA.Y) / lenb;
	return 	(double)(ax*by - ay*bx);
}

//Направление линии относительно абсцисс OX
template<class T>
static double lineAngle(const GCP_Point<T> &p11, const GCP_Point<T> &p12)
{
	double N1 = (double)(p12.X - p11.X);
	double N2 = (double)(p12.Y - p11.Y);
	return pointDirection(0, 0, N1, N2);
}
template<class T>
static double lineAngle(const GCP_Line<T> &L) 	{ return lineAngle(L.pointA, L.pointB); }

//Functions for structs
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

static unsigned int uniqueValue64()
{
	static RandomSequenceOfUnique randUniq((unsigned int)(rand() * 100000), 4294967295);
	return randUniq.next();
}