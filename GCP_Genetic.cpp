#include "GCP_Math.h"

//ГЕНЕТИЧЕСКИЙ АЛГОРИТМ ОБЩИЙ СЛУЧАЙ
void GeneticSpecies::breed(GeneticSpecies *other, int devideblocks)
{
		int len = values.size();
		
		int rand;
		if(devideblocks<2)
			rand = devideblocks;
		rand = 2+ceil(GCP_Math::rnd()*(devideblocks-2));
		int blocksize = len / rand;

		//Какие блоки будем менять 
		GCP_Vector<int> oursBlocks;
		GCP_Vector<int> othersBlocks;
		for(int i=0; i<rand; i++){
			double probability = GCP_Math::rnd();
			if(probability>0.1)
			{			
				int ourBlock = GCP_Math::rnd()*(rand-1);
				int otherBlock = GCP_Math::rnd()*(rand-1);
				if(!oursBlocks.has_value(ourBlock) && !othersBlocks.has_value(otherBlock))
				{
					oursBlocks.push_back(ourBlock);
					othersBlocks.push_back(otherBlock);
				}
			}
		}
		

		for(int i=0; i<oursBlocks.size(); i++)
		{
			int ourBlockNum = oursBlocks.at(i);
			int otherBlockNum = othersBlocks.at(i);

			for(int j=0; j<blocksize; j++)
			{
				char swap;
				swap = values[ourBlockNum*blocksize+j];		
				values[ourBlockNum*blocksize+j] = other->values[otherBlockNum*blocksize+j];
				other->values[otherBlockNum*blocksize+j] = swap;					
			}
		}

	}

void GeneticSpecies::mutation()
{		
	int len = values.size();
	int rand = GCP_Math::rnd()*10;
	for(int i=0; i<rand; i++)
	{
		int randV1 = GCP_Math::rnd()*(len-1);
		int randV2 = GCP_Math::rnd()*(len-1);
		char swap;
		swap = values[randV1];
		values[randV1] = values[randV2];
		values[randV2] = swap;
	}
}

/// @brief Бинарная строка в десятичную
///< Переводит бинарную строку в десятичную
int GCP_Math::bin2dec(const string* binary)
{
	int len,dec=0,i,exp;

	len = binary->size();
	exp = len - 1;

	for(int i=0; i<len; i++,exp--)
		dec += binary->at(i)=='1'?pow(2.,exp):0;
	return dec;
}
int GCP_Math::bin2dec(const char* binary)
{
	int len,dec=0,i,exp;

	len = strlen(binary);
	exp = len - 1;

	for(int i=0; i<len; i++,exp--)
		dec += binary[i]=='1'?pow(2.,exp):0;
	return dec;
}

/// @brief Выравнивание бинарной строки
///< Приводит бинарную строку к формату из 8 символов. 
///< Если число в бинарном виде меньше восьми символов, слева дописываются нули
///< Предполагает что число не больше 8ми символов!!!
string* GCP_Math::binchar_set_length(const string *buff, int size)
{
	string *buffNew = new string("00000000");
	int buffSize = buff->size()-1;

	for(int i=size-1; i>=0; i--)
	{
		if(buffSize>-1)
		{
			char ch = buff->at(buffSize--);
			buffNew->at(i) = ch;
		}
		else
			buffNew->at(i) = 48;
	}
	return buffNew;
}

/// @brief Массив в бинарную строку
///< Конвертирует массив чисел <255 в бинарную строку по 8 бит на число.
string GCP_Math::integersToBinaryString(int *arr, int size)
{
	string buffMax="";
	char buff[9]="00000000";		
	for(int i=0; i<size; i++)
	{
		itoa(arr[i],buff,2);
		string *str = new string(buff);
		string *ret = binchar_set_length(str,8);
		buffMax.append(ret->c_str());
		delete str;
		delete ret;
	}
	return buffMax;
}

/// @brief Бинарная строка в массив 
///< Конвертирует бинарную строку в массив чисел <255 берет за число каждые 8 бит.
int *GCP_Math::binaryStringTointegers(string binary, int size, int *arr)
{
	for(int i=0; i<size; i++)
	{
		char buff[9];
		for(int j=0; j<8; j++)
			buff[j] = binary[i*8+j];
		buff[8]= 0;
		arr[i] = bin2dec(buff);
	}
	return arr;
}


