// Возвращает находится ли точка снизу от линии или сверху
template <class T>
static bool isPointBelowLine(const GCP_Point<T> &P, const GCP_Line<T> &L)
{
	bool isBelow = ((long double)(L.pointB.X - L.pointA.X)*(P.Y - L.pointA.Y) - (long double)(L.pointB.Y - L.pointA.Y)*(P.X - L.pointA.X) > 0);
	if (lineAngle(L) > 90) return  isBelow;
	return !isBelow;
}

//Расстояние от точки (x1,y1) до точки (x2,y2)
static bool isInRadius(double x1, double y1, double x2, double y2, double r) {	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) < r); }
static bool isInRect(double pointX, double pointY, double rectTopx, double rectTopy, double rectWidth, double rectHeight)
{
	if (GCP_Math::compareDouble(pointX, rectTopx) && GCP_Math::compareDouble(rectTopx + rectWidth, pointX) && GCP_Math::compareDouble(pointY, rectTopy) && GCP_Math::compareDouble(rectTopy + rectHeight, pointY))
		return true;
	return false;
}

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

//Пересечение линии и прямоугольника
template<class T>
static bool lineRectIntersection(GCP_Rect<T> const& rect, GCP_Line<T> const& line, GCP_Vector< GCP_Point<T> > *R)
{
	GCP_Point<T> TopLeft(rect.topLeft());
	GCP_Point<T> TopRight(rect.x() + rect.width(), rect.y());
	GCP_Point<T> BottomLeft(rect.x(), rect.y() + rect.height());
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
static bool isPointInMultiRect(GCP_Vector< GCP_Line<T> > const& rect, GCP_Point<T> const& point)
{
	double sum = 0;
	for (size_t i = 0; i < rect.size(); i++)
	{
		GCP_Line<T> a(point, rect.at(i).pointA);
		GCP_Line<T> b(point, rect.at(i).pointB);
		double dira = pointDirection(point, rect.at(i).pointA);
		double dirb = pointDirection(point, rect.at(i).pointB);
		double angle = std::abs(norm_dir_dif(dira, dirb));
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

//Пересечение двух линий
template<class T>
static bool lineIntersection(GCP_Line<T> const& A, GCP_Line<T> const& B, GCP_Point<T> *R, bool IsRayIntersection = false)
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