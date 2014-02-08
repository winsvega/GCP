#include "GCP_Math.h"

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
