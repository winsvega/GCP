#ifndef GCP_MathH
#define GCP_MathH
 
#include <string>
#include <sstream>
#ifndef M_PI
#include <cmath>
#endif
#include <cstdio> 
#include <ctype.h>
#include "GCP_Vector.h"
const double GCP_RADTODEG = (double)180/3.14;
const double GCP_DEGTORAD = (double)3.14/180;
using namespace std;
#include "GCP_Delegate.h"
//typedef enum {false, true} bool; 
//#define bool int
//#define true 1
//#define false 0




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
struct GCP_Point
{
	double X,Y;		
	//GCP_Point(int x, int y) {X = x; Y = y;}
	GCP_Point(double x, double y) {X = x; Y = y;}
	GCP_Point(int x, int y) {X = (double)x; Y = (double)y;}
	GCP_Point(){};
	GCP_Point(GCP_Point* point) 
	{
		X = point->X;
		Y = point->Y;
	}
	~GCP_Point(){}
};
/////////////////////////////////////////////////////////////////////////
struct GCP_Line
{
	GCP_Point pointA, pointB;					//Структура для линии
	GCP_Line(){};
	GCP_Line(GCP_Point A, GCP_Point B){SetPoints(A,B);}
	GCP_Line(double x1, double y1, double x2, double y2): pointA(x1,y1), pointB(x2,y2){}
	void SetPoints(GCP_Point A, GCP_Point B){pointA = A; pointB = B;}
	double length()
	{
		return sqrt(pow(pointA.X-pointB.X,2)+pow(pointA.Y-pointB.Y,2));
	}
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
		static string RUSCP1251_TO_WCHAR(wchar_t* str);
		static string RUSCP1251_TO_WCHAR(char* str);
		static bool isPointBelowLine(GCP_Point P, GCP_Line L);
		static bool isInRadius(double x1,double y1, double x2, double y2, double r);
		static bool isInRect(double pointX, double pointY, double rectTopx, double rectTopy, double rectWidth, double rectHeight);
		static bool isPointInRect(GCP_Point TopLeft, GCP_Point BottomRight, GCP_Point point);
		static double lineAngle(GCP_Point p11, GCP_Point p12);
		static GCP_Point normalizeRectInRect(GCP_Point TopLeft, GCP_Point BottomRight, double x, double y, int width, int height, int offset);
		static GCP_Point normalizePointInRect(GCP_Point point, GCP_Point pmin, GCP_Point pmax);		
		static double round(double value);
		static bool lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double *Px, double *Py, bool round);
		static bool lineIntersection(GCP_Point p11, GCP_Point p12, GCP_Point p21, GCP_Point p22, GCP_Point *R, bool round);
		static bool lineIntersection(GCP_Line A, GCP_Line B, GCP_Point *R,bool round=false);
		static bool lineRectIntersection(GCP_Point TopLeft, GCP_Point TopRight, GCP_Point BottomLeft, GCP_Point BottomRight, GCP_Line L, GCP_Vector<GCP_Point> *R);
		static bool compareDouble(double x, double y);
		static double rnd();
		static double rnd(const char *dist, double a, double b);
		static double pointDirection(double x1, double y1, double x2, double y2);
		static double pointDirection(GCP_Point A, GCP_Point B);
		static void lineRefractionAngle(GCP_Point p11, GCP_Point p12, GCP_Point p21, GCP_Point p22, double N1, double N2, double *refractedAngleOX, double *refractedAngle, int *error);
		static void lineReflectionAngle(GCP_Point p11, GCP_Point p12, GCP_Point p21, GCP_Point p22, double *reflectedAngleOX, double *reflectedAngle);
		static void lineReflectionAngle(GCP_Line A, GCP_Line B, double *d, double *d2);
		static double lineReflectionAngle(GCP_Line A, GCP_Line B);
		static double pointDistance(double x1, double y1, double x2, double y2);
		static double pointDistance(GCP_Point X, GCP_Point Y);
		static double lineAngle(GCP_Line L);
		static int Min(int a, int b)
		{
			if(a<b) return a;
			return b;
		}
		static void lineRefractionAngle(GCP_Line L1, GCP_Line L2, double N1, double N2, double *refractedAngleOX, double *refractedAngle, int *error);
		static GCP_Vector<string> *strToLines(string Text)
		{
			char str;
			unsigned int i=0;
			string line;
			GCP_Vector<std::string> *strings = new GCP_Vector<std::string>();
			while(i < Text.size())
			{
				line = "";
				str = Text.at(i);
				while( str != '\n')
				{
					line += str;
					i++;
					if(i >= Text.size())
						break;
					str = Text.at(i);				
				}
				strings->push_back(line);
				i++;
			}
			return strings;
		}

		//ХЗ как описать эту функцию в отдельном CPP
		template< class A>
		static void quickSort(GCP_Vector<A> *a, int l, int r, int criteria = -1)
		{
			A x = a->at(l + (r - l) / 2);
			//запись эквивалентна (l+r)/2,
			//но не вызввает переполнения на больших данных
			int i = l;
			int j = r;
			//код в while обычно выносят в процедуру particle
			while(i <= j)
			{
				while((a->at(i))->compare(x,1,criteria)) i++;
				while((a->at(j))->compare(x,2,criteria)) j--;
				if(i <= j)
				{
					a->swap(i,j);
					i++;
					j--;
				}
			}
			if (i<r)
						quickSort(a,i, r, criteria);
		   
			if (l<j)   
				quickSort(a,l, j, criteria);  
		}
		static double ccos(double value);
		static double ssin(double value);
		static double arcsin(double value);
		static bool isPointInLine(GCP_Line line, GCP_Point checkPoint);
		static bool isPointNear(GCP_Point pointA, GCP_Point pointB, int dist);
		static double normAngle(double value);
		static string normAngleS(double value);
		static double norm_dir_dif(double dir1, double dir2);
		static string intToString(int value);
		static string doubleToString(double value);
		static int stringToInt(char* str);
		static double stringToDouble(char* str);
		static bool isNum(char *s) {
			int i = 0,  flag;

			while(s[i]){
					//if there is a letter in a string then string is not a number
				if(isalpha(s[i])){
					flag = 0;
					break;
				}
				else {
					flag = 1;
					if(strstr("+_-/*!@#$%^&()№;:?{}[]|'\\~\"",s)!=NULL)
						flag = 0;
					
				}
				
				i++;
			}
			if (flag == 1) return true;
			else return false;
		}
		static int findStringInVector(string sTextIn, GCP_Vector<string> *vector);
		static int readIntegerArray(char* strline, char separator, int *arr);
		static double uniqueValue();
		static size_t utf8_length(unsigned char c);
		static char *utf8_next(char *p);
		static char *utf8_advance(char *p, size_t distance);
		static string Font_StrToEng(string text);
		static void Font_StrToEng(string sTextIn, char* sTextOut,bool special_symbols);
		static string* DefineRusToEng();
		
		///////////// Genetic /////////////
		int bin2dec(const string* binary);
		int GCP_Math::bin2dec(const char* binary);
		string* binchar_set_length(const string *buff, int size);
		int *binaryStringTointegers(string binary, int size, int *arr);
		string integersToBinaryString(int *arr, int size);
		/// @brief Генетическая апроксимация
		/// @param i_class				- Указатель на класс-обработчик.
		/// @param i_method				- Указатель на метод класса-обработчика (весовая функция).
		/// @param baseInput			- Строка string с бинарными данными "00110101110".
		/// @param populationsize		- Размер популяции объектов (особей).
		/// @param devideblocks			- Количество разбиений на хромосомы при скрещивании.
		/// @param mutationprobability  - Вероятность мутации особей
		template< class T, class U >
		static string GeneticApproximation(T* i_class, U i_method, string baseInput, int populationsize, int devideblocks, double mutationprobability)
		{
			IContainer* func = new  Container< T, U > ( i_class, i_method);

			GCP_Vector<GeneticSpecies*> generation;	
			GCP_Vector<GeneticSpecies*> next_generation;
			for(int i=0; i<populationsize; i++){
				GeneticSpecies *specie = new GeneticSpecies();
				specie->values = baseInput;
				specie->result = 1;
			    generation.push_back(specie);
			}
			
			//Iteration
			int iK=0,spawn=0;
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
				for(int i=0; i<next_generation.size(); i++)
					delete next_generation.at(i);
				next_generation.clear();
				
				iK = 0;	
                for (int i = 0; i < generation.size(); i++)
                {                   			
                    if (generation.at(i)->result <= dBestResult)
                    {						
						int iRandomElement = GCP_Math::rnd()*(generation.size()-1);
						GeneticSpecies *obj = new GeneticSpecies();
						obj->result =  generation.at(i)->result;
						obj->values =   generation.at(i)->values;
						if(GCP_Math::rnd() < mutationprobability)
                           obj->mutation();
                        obj->breed(generation.at(iRandomElement),devideblocks);
						obj->result =  (int)func->Call((void*)&obj->values);

						if(obj->result < generation.at(i)->result)
							next_generation.push_back(obj);	
						else 
						{							
							obj->result =  generation.at(i)->result;
							obj->values =  generation.at(i)->values;
							next_generation.push_back(obj);							
						}						
                        iK++; 
                    }
                }

				//Clear previous pointers
				for(int i=0; i<generation.size(); i++)
					delete generation.at(i);				
				generation.clear();

				for(int i=0; i<next_generation.size(); i++)
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
			for(int i=0; i<generation.size(); i++)
			{
				if(generation.at(i)->result<minResult){
					minResult = generation.at(i)->result;
					minResultIndex = i;
				}
			}

			string RetVal;
			int iRandomElement = GCP_Math::rnd()*(generation.size()-1);
			if (minResultIndex != -1)
				RetVal =  generation.at(minResultIndex)->values;
			if (iRandomElement > -1 && iRandomElement < generation.size())
				RetVal = generation.at(iRandomElement)->values;
			else RetVal = baseInput;
			
			//Clear All pointers
			for(int i=0; i<generation.size(); i++)
					delete generation.at(i);
			for(int i=0; i<next_generation.size(); i++)
					delete next_generation.at(i);
					
			generation.clear();
			next_generation.clear();
			delete func;
			return RetVal;
		}
};

#define CP1251_TO_WCHAR(str) GCP_Math::RUSCP1251_TO_WCHAR(str);


#endif