class GeneticSpecies
{
public:
	std::string values;
	double result;
	GeneticSpecies &operator=(GeneticSpecies rhs)
	{
		result = rhs.result;
		values = rhs.values;
		return *this;
	}
	void breed(GeneticSpecies *other, int devideblocks)
	{
		int len = values.size();

		int rand;
		if (devideblocks<2)
			rand = devideblocks;
		rand = 2 + ceil(GCP_Math::rnd()*(devideblocks - 2));
		int blocksize = len / rand;

		//Какие блоки будем менять
		GCP_Vector<int> oursBlocks;
		GCP_Vector<int> othersBlocks;
		for (int i = 0; i<rand; i++){
			double probability = GCP_Math::rnd();
			if (probability>0.1)
			{
				int ourBlock = GCP_Math::rnd()*(rand - 1);
				int otherBlock = GCP_Math::rnd()*(rand - 1);
				if (!oursBlocks.has_value(ourBlock) && !othersBlocks.has_value(otherBlock))
				{
					oursBlocks.push_back(ourBlock);
					othersBlocks.push_back(otherBlock);
				}
			}
		}

		for (unsigned int i = 0; i<oursBlocks.size(); i++)
		{
			int ourBlockNum = oursBlocks.at(i);
			int otherBlockNum = othersBlocks.at(i);

			for (int j = 0; j<blocksize; j++)
			{
				char swap;
				swap = values[ourBlockNum*blocksize + j];
				values[ourBlockNum*blocksize + j] = other->values[otherBlockNum*blocksize + j];
				other->values[otherBlockNum*blocksize + j] = swap;
			}
		}
	}

	void mutation()
	{
		int len = values.size();
		int rand = GCP_Math::rnd() * 10;
		for (int i = 0; i<rand; i++)
		{
			int randV1 = GCP_Math::rnd()*(len - 1);
			int randV2 = GCP_Math::rnd()*(len - 1);
			char swap;
			swap = values[randV1];
			values[randV1] = values[randV2];
			values[randV2] = swap;
		}
	}
};

///////////// Genetic /////////////
/// @brief Бинарная строка в десятичную
///< Переводит бинарную строку в десятичную
int bin2dec(const std::string* binary)
{
	int len, dec = 0, exp;

	len = binary->size();
	exp = len - 1;

	for (int i = 0; i<len; i++, exp--)
		dec += binary->at(i) == '1' ? pow(2., exp) : 0;
	return dec;
}

int bin2dec(const char* binary)
{
	int len, dec = 0, exp;

	len = strlen(binary);
	exp = len - 1;

	for (int i = 0; i<len; i++, exp--)
		dec += binary[i] == '1' ? pow(2., exp) : 0;
	return dec;
}

/// @brief Выравнивание бинарной строки
///< Приводит бинарную строку к формату из 8 символов.
///< Если число в бинарном виде меньше восьми символов, слева дописываются нули
///< Предполагает что число не больше 8ми символов!!!
std::string* binchar_set_length(const std::string *buff, int size)
{
	string *buffNew = new string("00000000");
	int buffSize = buff->size() - 1;

	for (int i = size - 1; i >= 0; i--)
	{
		if (buffSize>-1)
		{
			char ch = buff->at(buffSize--);
			buffNew->at(i) = ch;
		}
		else
			buffNew->at(i) = 48;
	}
	return buffNew;
}

/// @brief Бинарная строка в массив
///< Конвертирует бинарную строку в массив чисел <255 берет за число каждые 8 бит.
int *binaryStringTointegers(const std::string &binary, int size, int *arr)
{
	for (int i = 0; i<size; i++)
	{
		char buff[9];
		for (int j = 0; j<8; j++)
			buff[j] = binary[i * 8 + j];
		buff[8] = 0;
		arr[i] = bin2dec(buff);
	}
	return arr;
}

/// @brief Массив в бинарную строку
///< Конвертирует массив чисел <255 в бинарную строку по 8 бит на число.
std::string integersToBinaryString(int *arr, int size)
{
	string buffMax = "";
	char buff[9] = "00000000";
	for (int i = 0; i<size; i++)
	{
		GCP_Math::itoa(arr[i], buff, 2);
		string *str = new string(buff);
		string *ret = binchar_set_length(str, 8);
		buffMax.append(ret->c_str());
		delete str;
		delete ret;
	}
	return buffMax;
}

/// @brief Генетическая апроксимация
/// @param i_class				- Указатель на класс-обработчик.
/// @param i_method				- Указатель на метод класса-обработчика (весовая функция).
/// @param baseInput			- Строка string с бинарными данными "00110101110".
/// @param populationsize		- Размер популяции объектов (особей).
/// @param devideblocks			- Количество разбиений на хромосомы при скрещивании.
/// @param mutationprobability  - Вероятность мутации особей
template< class T, class U >
static std::string GeneticApproximation(T* i_class, U i_method, const std::string &baseInput, int populationsize, int devideblocks, double mutationprobability)
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