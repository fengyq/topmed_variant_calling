#ifndef __GENOTYPE_ELIMINATION__
#define __GENOTYPE_ELIMINATION__

#include "Pedigree.h"

class GenotypeList
   {
   public:

      IntArray allele1, allele2;
      IntArray alleles;

      bool ignore;
      int  checked;

      GenotypeList();

      static bool EliminateGenotypes(Pedigree & ped, Family * family, int marker);

      void   Dimension(int genotypes);
      void   Delete(int genotype);

      bool   Matches(int genotype, int allele);
      bool   Matches(int allele);

      int    SaveGenotype(int genotype);
      void   SetGenotype(int genotype, int al1, int al2);

   private:
      static void InitializeList(GenotypeList * list, Pedigree & p, Family * f, int marker);
      static bool PairwiseCheck(GenotypeList * list, Pedigree & p, Family * f);
      static bool FamilyCheck(GenotypeList * list, Pedigree & p, Family * f);

      static bool CheckTrio(GenotypeList * list, int fatid, int motid, int child, int i, int j, int k);
      static bool TrimParent(GenotypeList * list, Person & person, int fatid, int motid);
      static bool Cleanup(GenotypeList * list, Person & person, int fatid, int motid, int child, int geno);

      static void Print(GenotypeList * List, Pedigree & p, Family * f, int marker);
   };



#endif
