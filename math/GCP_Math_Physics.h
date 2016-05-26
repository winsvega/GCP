struct reflectinfo
{
	double reflectedAngleOX;
	double reflectedAngle;
	double refractedAngleOX;
	double refractedAngle;
	bool refractionError;
	double N1, N2;
};

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