#ifndef __MYGA_H__
#define __MYGA_H__


class MyGA : public GASteadyStateGA {
public:
  GADefineIdentity("MyGA", 288);
  MyGA(const GAGenome& g) : GASteadyStateGA(g) {}
  virtual ~MyGA() {}
  virtual void step() 
	{ 
		GAGenome *mom,*dad;
		int i, k;
		for(i=0; i<tmpPop->size(); i++){
			mom = &(pop->select()); 
			k=0;
			do { k++; dad = &(pop->select()); }
			while(k<pop->size());
			stats.numsel += 2;
			if(i+1 < tmpPop->size() && GAFlipCoin(pCrossover()))
				stats.numcro += (*scross)(*mom, *dad, &tmpPop->individual(i), &tmpPop->individual(i+1));
			else
				tmpPop->individual(i).copy(*mom);
			stats.nummut += tmpPop->individual(i).mutate(pMutation());
		}

		for(i=0; i<tmpPop->size(); i++)
			pop->add(tmpPop->individual(i));
		
		pop->evaluate(gaTrue);		// get info about current pop for next time
		pop->scale();			// remind the population to do its scaling

		for(i=0; i<tmpPop->size(); i++)
			pop->destroy(GAPopulation::WORST, GAPopulation::SCALED);

		stats.update(*pop);		// update the statistics by one generation
	}

  MyGA & operator++() { step(); return *this; }
};


#endif
