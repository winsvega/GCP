#ifndef GCP_Math_Realisation
#define GCP_Math_Realisation

#include <cstring>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <string>
#include "GCP_Vector.h"
#include "GCP_Math.h"

using namespace gcp;
////////////////////
//GCP Math Functions
////////////////////



///
/*std::string CP1251_TO_WCHAR(const char *str)
{
	return GCP_Math::RUSCP1251_TO_WCHAR(str);
}*/

///
bool GCP_Math::isInRadius(double x1, double y1, double x2, double y2, double r)
{
	//Расстояние от точки (x1,y1) до точки (x2,y2)
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) < r);
}

///
bool GCP_Math::isInRect(double pointX, double pointY, double rectTopx, double rectTopy, double rectWidth, double rectHeight)
{
	if (GCP_Math::compareDouble(pointX, rectTopx) && GCP_Math::compareDouble(rectTopx + rectWidth, pointX) && GCP_Math::compareDouble(pointY, rectTopy) && GCP_Math::compareDouble(rectTopy + rectHeight, pointY))
		return true;
	return false;
}


///
double GCP_Math::round(double value)
{
	if (GCP_Math::compareDouble(value - floor(value), 0.5))
		return floor(value);
	return floor(value) + 1;
}

////////////////////
///2D Math Physics
////////////////////

///
/*bool GCP_Math::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double *Px, double *Py, bool round)
{

}*/


///
bool GCP_Math::compareDoubleEqual(double x, double y)
{
	//x == y ?
	double eps = 1e-5;
	if (std::abs(x - y) < eps)
		return true;
	return false;
}

///
bool GCP_Math::compareDouble(double x, double y)
{
	//x > y ?
	double eps = 1e-5;
	if (x - y > -eps)
		return true;
	return false;
}

///
double GCP_Math::rnd()
{
	//return (double)rand(RAND_MAX)/RAND_MAX;   //Случайное число от 0 до 1 равномерно распределенное
	return (double)rand() / RAND_MAX;
}


///
double GCP_Math::rnd(const char *dist, double a, double b)
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


///
double GCP_Math::pointDirection(double x1, double y1, double x2, double y2)
{
	//Направление из точки (x1,y1) в точку (x2,y2)
	double d;
	double yd = y1 - y2;
	double xd = x2 - x1;
	double atan = atan2(yd, xd);
	d = (double)(GCP_RADTODEG*atan);			//В градусах
	return normAngle(d);
}



///
double GCP_Math::pointDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));	//Расстояние от точки (x1,y1) до точки (x2,y2)
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// template< class A>
// void GCP_Math::quickSort(GCP_Vector<A> *a, int l, int r, int criteria)
//{
//	A x = a->at(l + (r - l) / 2);
//	//запись эквивалентна (l+r)/2,
//	//но не вызввает переполнения на больших данных
//	int i = l;
//	int j = r;
//	//код в while обычно выносят в процедуру particle
//	while(i <= j)
//	{
//		while((a->at(i))->compare(x,1,criteria)) i++;
//		while((a->at(j))->compare(x,2,criteria)) j--;
//		if(i <= j)
//		{
//			a->swap(i,j);
//			i++;
//			j--;
//		}
//	}
//	if (i<r)
//				quickSort<A>(a,i, r, criteria);
//
//	if (l<j)
//		quickSort<A>(a,l, j, criteria);
//}
//
///
double GCP_Math::ccos(double value)
{
	//GCP_FastTG.InitFSinCosTable();
	//return GCP_FastTG.fcosined(value);
	return cos(GCP_DEGTORAD*value);						//Косинус от значения в градусах
}

///
double GCP_Math::ssin(double value)
{
	//GCP_FastTG.InitFSinCosTable();
	//return GCP_FastTG.fsined(value);
	return sin((double)(GCP_DEGTORAD*value));			//Синус от значения в градусах
}

///
double GCP_Math::arcsin(double value)
{
	return asin(value);
}



///
double GCP_Math::normAngle(double value)
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


///
string GCP_Math::normAngleS(double value)
{
	int degree = (int)floor(value);
	double tempvalue = 60 * (value - degree);
	int minutes = (int)floor(tempvalue);
	int seconds = (int)floor(60 * (tempvalue - minutes));

	return intToString(degree) + "'" + intToString(minutes) + "'" + intToString(seconds);
}

///
double GCP_Math::norm_dir_dif(double dir1, double dir2)
{
	double dif = (double)dir1 - dir2;											//Кратчайшее расстояние от направления dir1 к направлению dir2
	if (dif > 180) { return(dif - 360); }											//Пример: из направления 90 в направлениее 300/-60 =  -150
	if (dif < -180) { return(dif + 360); }										//Пример: из направления 90 в направлениее 240/-120 =  150
	return dif; //if (dif<=180 && dif>=-180) {return dif;}
}


///* reverse:  переворачиваем строку s на месте */
void gcp_reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

///* itoa:  конвертируем n в символы в s */
void gcp_itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* записываем знак */
		n = -n;          /* делаем n положительным числом */
	i = 0;
	do {       /* генерируем цифры в обратном порядке */
		s[i++] = n % 10 + '0';   /* берем следующую цифру */
	} while ((n /= 10) > 0);     /* удаляем */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	gcp_reverse(s);
}

///
string GCP_Math::intToString(int value)
{
	char buff[256];
	//_itoa_s(value,buff,10) ;
	gcp_itoa(value, buff);
	return  string(buff);
}

///
string GCP_Math::doubleToString(double value)
{
	char buffer[32];
	sprintf(buffer, "%g", value);
	//gcp_itoa(value,buffer);
	/*#ifdef __WIN32__
   sprintf_s(buffer,32, "%g", value);
   #else
   //snprintf(buffer, sizeof(buffer), "%.10g", value);
   //sprintf_s(buffer,32, "%g", value);
   sprintf (buffer, "%g", 8, value);
   gcp_itoa(value,buffer);
   #endif*/

	string str(buffer);
	return str;
}

///
int GCP_Math::stringToInt(char* str)
{
	return atoi(str);
}

///
double GCP_Math::stringToDouble(char *str)
{
	return atof(str);
}

///
int GCP_Math::findStringInVector(const string &sTextIn, GCP_Vector<string> *vector)
{
	for (unsigned int i = 0; i<vector->size(); i++)
	{
		if (vector->at(i) == sTextIn)
			return i;
	}
	return -1;
}


///
int GCP_Math::readIntegerArray(char* strline, char separator, int* arr)
{
	//GCP_Vector<int>* result = new GCP_Vector<int>();
	char xx[50]; int i = 0, j = 0, k = 0;
	bool isExpectE = false;
	int iPointJ = 0;

	while (strline[i] != '\0'){
		while (strline[i] != separator){
			if ((strline[i] >= '0' && strline[i] <= '9')
					|| strline[i] == '-')
			{
				xx[j] = strline[i];
				j++;
			}
			i++;

			//Встретили точку
			if (strline[i] == '.')
			{
				i++;					//Предположим, мы считываем формат вида 1.24317e+006
				isExpectE = true;
				iPointJ = j;
			}

			//Встретили е
			if (strline[i] == 'e')
			{
				i++; //+
				i++; //firestDigit after e+
				char eNum[10];
				int i2 = 0;
				while (strline[i] >= '0' && strline[i] <= '9')
				{
					eNum[i2] = strline[i];
					i++; i2++;
				}

				eNum[i2] = '\0';
				int eParam = GCP_Math::stringToInt(eNum);

				//Допишем к числу необходимое количество знаков после точки, которая для e
				int eXtend = eParam - (j - iPointJ);
				for (int j2 = 0; j2<eXtend; j2++)
				{
					xx[j] = '0'; j++;
				}
				isExpectE = false;
			}
		}

		//На случай если мы встретили точку, но не встретили потом e
		//Вернемся к состоянию до точки (Считываем только целые числа)
		if (isExpectE == true)
			j = iPointJ;

		xx[j] = '\0'; j = 0; i++; isExpectE = false;	iPointJ = 0;
		if (xx[0] != 0)
			arr[k] = GCP_Math::stringToInt(xx);
		k++;
	}
	return k;
}

///
unsigned int GCP_Math::uniqueValue64()
{
	static RandomSequenceOfUnique randUniq((unsigned int)(rand()*100000), 4294967295);
	return randUniq.next();
}


//Calculatuions To Draw Russian Text As English Font Using Special Font Type
size_t GCP_Math::utf8_length(unsigned char c)
{
	c = (unsigned char)(0xff & c);
	if (c < 0x80)
		return 1;
	else if ((c >> 5) == 0x6)
		return 2;
	else if ((c >> 4) == 0xe)
		return 3;
	else if ((c >> 3) == 0x1e)
		return 4;
	else
		return 0;
}

char *GCP_Math::utf8_next(char *p)
{
	size_t len = utf8_length(*p);
	size_t i = 0;
	if (!len)
		return 0;

	for (; i < len; ++i)
	{
		++p;
		if (!*p)
			return 0;
	}
	return p;
}

char *GCP_Math::utf8_advance(char *p, size_t distance)
{
	size_t i = 0;
	for (; i < distance && p; ++i)
	{
		p = utf8_next(p);
	}
	return p;
}

string GCP_Math::Font_StrToEng(const string &text)
{
	char *buffer = new char[text.size() + 2];
	Font_StrToEng(text, buffer, false);
	string str = buffer;
	delete[]buffer;
	buffer = NULL;
	return str;
}

void GCP_Math::Font_StrToEng(const string &sTextIn, char* sTextOut, bool special_symbols)
{
	string RusToEng = GCP_Math::DefineRusToEng();

	unsigned int i, j;
	for (i = 0, j = 0; i<sTextIn.size(); i++, j++)
	{
		if ((sTextIn[j] == '\\') && (sTextIn[j + 1] == 'n'))
		{
			sTextOut[i] = '\\';
			sTextOut[i + 1] = 'n';
			i++;
			j++;
		}
		else
		{
			//&quot;
			if ((sTextIn[j] == '&') && (sTextIn[j + 1] == 'q') && (sTextIn[j + 2] == 'u') && (sTextIn[j + 3] == 'o') && (sTextIn[j + 4] == 't') && (sTextIn[j + 5] == ';'))
			{
				sTextOut[i] = '&';
				sTextOut[i + 1] = 'q';
				sTextOut[i + 2] = 'u';
				sTextOut[i + 3] = 'o';
				sTextOut[i + 4] = 't';
				sTextOut[i + 5] = ';';
				i += 5; j += 5;
			}
			else
			{
				string chr = "&";// OR ELSE DEDUCE
				if ((special_symbols) && (RusToEng[300 + sTextIn[j]] == '&'))//'&'))
				{
					chr = RusToEng[300 + sTextIn[j]];
					sTextOut[i] = (char)chr[0];
					sTextOut[i + 1] = 'a';
					sTextOut[i + 2] = 'm';
					sTextOut[i + 3] = 'p';
					sTextOut[i + 4] = ';';
					i += 4;					 //&amp;
				}
				else
				{
					chr = RusToEng[300 + sTextIn[j]];
					sTextOut[i] = (char)chr[0];
				}
			}
		}
		if (sTextIn[j] == 0){ break; }
	}
	sTextOut[i] = '\0';
	//delete[] RusToEng;
	//RusToEng = NULL;
}


string GCP_Math::RUSCP1251_TO_WCHAR(const wchar_t* str)
{
	/*АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ*/
	/*"абвгдеёжзийклмнопрстуфхцчшщьыъэюя1234567890"*/
	/*"!@#$%^&*()_+{}[]\":';\\.№?"*/

	wstring s = str;
	int value;
	char buffer[10000];
	for (int i = 0; i<10000; i++)
		buffer[i] = '1';
	string out = buffer;


	int k = 0;
	int shift = 1152;
	char a = -48;
	for (unsigned int i = 0; i< s.size(); i++)
	{
		value = str[i];

		if ((value>1103 && value != 1105 && value != 8470) || value < 1040){
			out[k] = value; k++;
		}
		else
		{
			a = -48;
			shift = 1152;
			char b = value - shift;
			if (value >= 1088){
				a = -47;
				shift = 1216;
				if (value == 1105) //"ё"
					b = -111;
				b = value - shift;
			}

			if (value == 8470)//"№"
			{
				a = -30;
				b = -124;
				char c = -106;
				out[k] = a; k++;
				out[k] = b; k++;
				out[k] = c; k++;
			}
			else {
				out[k] = a; k++;
				out[k] = b; k++;
			}
		}
	}

	out[k] = '\0';
	return out;
}
string GCP_Math::RUSCP1251_TO_WCHAR(const char* str)
{
	/*АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ*/
	/*"абвгдеёжзийклмнопрстуфхцчшщьыъэюя1234567890"*/
	/*"`~!@#$%^&*()_+{}[]\":';\\.№?"*/

	string s = str;
	int value;
	char *buffer;
	buffer = new char[s.size() * 3 + 1];

	string out;


	int k = 0;
	int shift = 1152;
	char a = -48;
	for (unsigned int i = 0; i< s.size(); i++)
	{
		value = str[i];

		if (value >= 0){
			buffer[k] = value; k++;
		}
		else
		{
			a = -48;
			shift = -a;
			if (value >= -16)
			{
				a = -47;
				shift = 112;
			}
			char b = value - shift;
			if (value < -64 && value != -88){
				a = -47;
				shift = -a;


				b = value - shift;
				if (value == -72) //"ё"
					b = -111;

			}



			if (value == -88) //"Ё"
				b = -127;



			if (value == -71)//"№"
			{
				a = -30;
				b = -124;
				char c = -106;
				buffer[k] = a; k++;
				buffer[k] = b; k++;
				buffer[k] = c; k++;
			}
			else {
				buffer[k] = a; k++;
				buffer[k] = b; k++;
			}
		}
	}

	buffer[k] = '\0';
	out = buffer;

	delete[]buffer;
	//out[k] = '\0';
	return out;
}
string& GCP_Math::DefineRusToEng()
{
	static string RusToEng;// = new string[1000];
	if (RusToEng.size() > 0)
		return RusToEng;

	RusToEng[300 + 'А'] = 'A';	RusToEng[300 + 'а'] = 'a';
	RusToEng[300 + 'Б'] = 'B';	RusToEng[300 + 'б'] = 'b';
	RusToEng[300 + 'В'] = 'C';	RusToEng[300 + 'в'] = 'c';
	RusToEng[300 + 'Г'] = 'D';	RusToEng[300 + 'г'] = 'd';
	RusToEng[300 + 'Д'] = 'E';	RusToEng[300 + 'д'] = 'e';
	RusToEng[300 + 'Е'] = 'F';	RusToEng[300 + 'е'] = 'f';
	RusToEng[300 + 'Ж'] = 'G';	RusToEng[300 + 'ж'] = 'g';
	RusToEng[300 + 'З'] = 'H';	RusToEng[300 + 'з'] = 'h';
	RusToEng[300 + 'И'] = 'I';	RusToEng[300 + 'и'] = 'i';
	RusToEng[300 + 'Й'] = 'J';	RusToEng[300 + 'й'] = 'j';
	RusToEng[300 + 'К'] = 'K';	RusToEng[300 + 'к'] = 'k';
	RusToEng[300 + 'Л'] = 'L';	RusToEng[300 + 'л'] = 'l';
	RusToEng[300 + 'М'] = 'M';	RusToEng[300 + 'м'] = 'm';
	RusToEng[300 + 'Н'] = 'N';	RusToEng[300 + 'н'] = '#';
	RusToEng[300 + 'О'] = 'O';	RusToEng[300 + 'о'] = 'o';
	RusToEng[300 + 'П'] = 'P';	RusToEng[300 + 'п'] = 'p';
	RusToEng[300 + 'Р'] = 'Q';	RusToEng[300 + 'р'] = 'q';
	RusToEng[300 + 'С'] = 'R';	RusToEng[300 + 'с'] = 'r';
	RusToEng[300 + 'Т'] = 'S';	RusToEng[300 + 'т'] = 's';
	RusToEng[300 + 'У'] = 'T';	RusToEng[300 + 'у'] = 't';
	RusToEng[300 + 'Ф'] = 'U';	RusToEng[300 + 'ф'] = 'u';
	RusToEng[300 + 'Х'] = 'V';	RusToEng[300 + 'х'] = 'v';
	RusToEng[300 + 'Ц'] = 'W';	RusToEng[300 + 'ц'] = 'w';
	RusToEng[300 + 'Ч'] = 'X';	RusToEng[300 + 'ч'] = 'x';
	RusToEng[300 + 'Ш'] = 'Y';	RusToEng[300 + 'ш'] = 'y';
	RusToEng[300 + 'Щ'] = '№';	RusToEng[300 + 'щ'] = 'z';

	RusToEng[300 + 'Ъ'] = 'Ъ';	RusToEng[300 + 'ъ'] = '&';
	RusToEng[300 + 'Ы'] = 'Ы';	RusToEng[300 + 'ы'] = '~';
	RusToEng[300 + 'Ь'] = 'Ь';	RusToEng[300 + 'ь'] = '}';
	RusToEng[300 + 'Э'] = '^';	RusToEng[300 + 'э'] = 'Z';
	RusToEng[300 + 'Ю'] = '+';	RusToEng[300 + 'ю'] = '_';
	RusToEng[300 + 'Я'] = 'n';	RusToEng[300 + 'я'] = '|';
	RusToEng[300 + 'Ё'] = '{';	RusToEng[300 + 'ё'] = '`';

	RusToEng[300 + '0'] = '0';
	RusToEng[300 + '1'] = '1';
	RusToEng[300 + '2'] = '2';
	RusToEng[300 + '3'] = '3';
	RusToEng[300 + '4'] = '4';
	RusToEng[300 + '5'] = '5';
	RusToEng[300 + '6'] = '6';
	RusToEng[300 + '7'] = '7';
	RusToEng[300 + '8'] = '8';
	RusToEng[300 + '9'] = '9';
	RusToEng[300 + '!'] = '!';
	RusToEng[300 + '?'] = '?';
	RusToEng[300 + ','] = ',';
	RusToEng[300 + '.'] = '.';
	RusToEng[300 + '('] = '(';
	RusToEng[300 + ')'] = ')';
	RusToEng[300 + '$'] = '$';
	RusToEng[300 + ':'] = ':';
	RusToEng[300 + ';'] = ';';
	RusToEng[300 + '-'] = '-';
	RusToEng[300 + ' '] = ' ';
	RusToEng[300 + '"'] = '"';
	RusToEng[300 + '*'] = '*';
	RusToEng[300 + '\''] = '\'';
	RusToEng[300 + '/'] = '/';
	RusToEng[300 + '\\'] = '\\';
	return RusToEng;
}

#endif
