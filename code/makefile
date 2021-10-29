#CCMALLOC = ccmalloc
COMPILER = g++
PROBLEM = .
VPATH= $(PROBLEM)
DEBUG    = -g
OPTIMIZE = -O2
WARNINGS = -Wall 
INCDIR =  $(PROBLEM) 
LIBS     = -lXaw -lXt -lXmu -lX11 -lm -lfl 
LIBDIR   =   $(LIBS)  -L  /usr/X11R6/lib 
#GPROF = -pg 
CFLAGS   = $(OPTIMIZE) -Wall -I $(INCDIR)
CPP = $(COMPILER) $(DEBUG) $(CFLAGS) -c  $(GPROF) 
CC_ = $(CCMALLOC) $(COMPILER)  -o 
#PURIFY = purify -best-effort  -log-file="theLog.txt" 

INCLUDES = defines.h Metaheuristic.hpp TabuSearch.hpp SimulatedAnnealing.hpp RandomSearch.hpp BiasedRandomSearch.hpp RandomSearchFD.hpp HillClimbing.hpp Experiment.hpp Configuration.hpp HcConfiguration.hpp SaConfiguration.hpp TabuConfiguration.hpp RsConfiguration.hpp Genome.hpp Random.hpp Results.hpp ge.hpp ge_gep.hpp grammar.hpp grammar_gep.hpp interpreter.hpp interpreter_gep.hpp GEant.hpp GEtrail.hpp converter.hpp TabuList.hpp FrequencyDistribution.hpp FrequencyDistributionElement.hpp Analyser.hpp  AnalyserConfig.hpp Generator.hpp Population.hpp EsConfiguration.hpp  EpConfiguration.hpp EvolutionaryStrategy.hpp  EvolutionaryProgramming.hpp Crossover.hpp Mutation.hpp Selection.hpp 

OBJS = main.o Metaheuristic.o TabuSearch.o SimulatedAnnealing.o RandomSearch.o BiasedRandomSearch.o RandomSearchFD.o HillClimbing.o Experiment.o Configuration.o HcConfiguration.o SaConfiguration.o TabuConfiguration.o RsConfiguration.o TabuList.o Genome.o Random.o parser.o Results.o ge.o ge_gep.o grammar.o grammar_gep.o interpreter.o interpreter_gep.o GEant.o GEtrail.o converter.o  FrequencyDistribution.o FrequencyDistributionElement.o Population.o EsConfiguration.o EpConfiguration.o EvolutionaryStrategy.o  EvolutionaryProgramming.o Crossover.o Mutation.o Selection.o 


OBJS2 = getest.o ge.o grammar.o interpreter.o GEant.o GEtrail.o Random.o ge_gep.o grammar_gep.o interpreter_gep.o

OBJS3 = analyser_main.o Analyser.o  AnalyserConfig.o Genome.o Random.o parser.o Results.o ge.o grammar.o ge_gep.o grammar_gep.o interpreter.o GEant.o GEtrail.o converter.o Mutation.o interpreter_gep.o 

OBJS4 = generator_main.o Generator.o AnalyserConfig.o  Genome.o Random.o parser.o Results.o ge.o grammar.o interpreter.o GEant.o GEtrail.o converter.o Mutation.o ge_gep.o grammar_gep.o interpreter_gep.o 

#This rule will make all the executable getest
# it first forces the compilation of all of the files specified in $(OBJS)

default:
	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator
santafe:
	cp SANTAFE/grammar.cc .
	cp SANTAFE/grammar.hpp .
	cp SANTAFE/grammar_gep.cc .
	cp SANTAFE/grammar_gep.hpp .
	cp SANTAFE/interpreter.cc .
	cp SANTAFE/interpreter.hpp .
	cp SANTAFE/interpreter_gep.cc .
	cp SANTAFE/interpreter_gep.hpp .
	cp SANTAFE/defines.h .
	cp SANTAFE/GEtrail.cc .	
	cp SANTAFE/GEtrail.hpp .
	cp SANTAFE/GEant.cc .
	cp SANTAFE/GEant.hpp .
	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator
symreg:
	cp SYMREG/grammar.cc .
	cp SYMREG/grammar.hpp .	
	cp SYMREG/grammar_gep.cc .
	cp SYMREG/grammar_gep.hpp .
	cp SYMREG/interpreter.cc .
	cp SYMREG/interpreter.hpp .
	cp SYMREG/interpreter_gep.cc .
	cp SYMREG/interpreter_gep.hpp .
	cp SYMREG/defines.h .
	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator
symint:
	cp SYMINT/grammar.cc .
	cp SYMINT/grammar.hpp .
	cp SYMINT/grammar_gep.cc .
	cp SYMINT/grammar_gep.hpp .
	cp SYMINT/interpreter.cc .
	cp SYMINT/interpreter.hpp .

	cp SYMINT/interpreter_gep.cc .
	cp SYMINT/interpreter_gep.hpp .
	cp SYMINT/defines.h .
	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator
simple:
	cp SIMPLE/grammar.cc .
	cp SIMPLE/grammar.hpp .
	cp SIMPLE/interpreter.cc .
	cp SIMPLE/interpreter.hpp .
	cp SIMPLE/defines.h .
	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator

blocks:
	cp BLOCKS2/grammar.cc .
	cp BLOCKS2/grammar.hpp .
	cp BLOCKS2/interpreter.cc .
	cp BLOCKS2/interpreter.hpp .
	cp BLOCKS2/defines.h .


	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator
spirals:
	cp SPIRALS/grammar.cc .
	cp SPIRALS/grammar.hpp .
	cp SPIRALS/interpreter.cc .
	cp SPIRALS/interpreter.hpp .
	cp SPIRALS/defines.h .
	$(MAKE) GramaEvovle
	$(MAKE) Analyser
	$(MAKE) Generator
#************************************************************************
#GramaEvovle: $(OBJS) $(INCLUDES)
#	purify -best-effort $(CC_) $@ $(OBJS) -I $(INCDIR) $(LIBDIR) $(DEBUG) $(OPTIMIZE) $(GPROF) 
#
#************************************************************************

#************************************************************************
GramaEvovle: $(OBJS) $(INCLUDES)
	$(PURIFY) $(CC_) $@ $(OBJS) -I $(INCDIR) $(LIBDIR) $(DEBUG) $(OPTIMIZE) $(GPROF)

#************************************************************************

#************************************************************************
Analyser: $(OBJS3) $(INCLUDES)
	$(PURIFY) $(CC_) $@ $(OBJS3) -I $(INCDIR) $(LIBDIR) $(DEBUG) $(OPTIMIZE) $(GPROF)

#************************************************************************
#************************************************************************
Generator: $(OBJS4) $(INCLUDES)
	$(PURIFY) $(CC_) $@ $(OBJS4) -I $(INCDIR) $(LIBDIR) $(DEBUG) $(OPTIMIZE) $(GPROF)

#************************************************************************
#************************************************************************
getest: $(OBJS2) $(INCLUDES)
	$(CC_) $@ $(OBJS2) -I $(INCDIR) $(LIBDIR) $(DEBUG) $(OPTIMIZE) $(GPROF)

#************************************************************************

getest.o : getest.cc 
	$(CPP)  getest.cc  -o getest.o

main.o : main.cpp 
	$(CPP)  main.cpp  -o main.o

Metaheuristic.o : Metaheuristic.cpp 
	$(CPP)  Metaheuristic.cpp  -o Metaheuristic.o

TabuList.o : TabuList.cpp 
	$(CPP)  TabuList.cpp  -o TabuList.o


TabuSearch.o : TabuSearch.cpp 
	$(CPP)  TabuSearch.cpp  -o TabuSearch.o


SimulatedAnnealing.o : SimulatedAnnealing.cpp 
	$(CPP)  SimulatedAnnealing.cpp  -o SimulatedAnnealing.o

EvolutionaryStrategy.o : EvolutionaryStrategy.cpp 
	$(CPP)  EvolutionaryStrategy.cpp  -o EvolutionaryStrategy.o

EvolutionaryProgramming.o : EvolutionaryProgramming.cpp 
	$(CPP)  EvolutionaryProgramming.cpp  -o EvolutionaryProgramming.o

RandomSearch.o : RandomSearch.cpp 
	$(CPP)  RandomSearch.cpp  -o RandomSearch.o

RandomSearchFD.o : RandomSearchFD.cpp 
	$(CPP)  RandomSearchFD.cpp  -o RandomSearchFD.o

BiasedRandomSearch.o : BiasedRandomSearch.cpp 
	$(CPP)  BiasedRandomSearch.cpp  -o BiasedRandomSearch.o

HillClimbing.o : HillClimbing.cpp 
	$(CPP)  HillClimbing.cpp  -o HillClimbing.o

Experiment.o : Experiment.cpp 
	$(CPP)  Experiment.cpp  -o Experiment.o

Configuration.o : Configuration.cpp 
	$(CPP)  Configuration.cpp  -o Configuration.o

HcConfiguration.o : HcConfiguration.cpp 
	$(CPP)  HcConfiguration.cpp  -o HcConfiguration.o

RsConfiguration.o : RsConfiguration.cpp 
	$(CPP)  RsConfiguration.cpp  -o RsConfiguration.o

TabuConfiguration.o : TabuConfiguration.cpp 
	$(CPP)  TabuConfiguration.cpp  -o TabuConfiguration.o

SaConfiguration.o : SaConfiguration.cpp 
	$(CPP)  SaConfiguration.cpp  -o SaConfiguration.o

EsConfiguration.o : EsConfiguration.cpp 
	$(CPP)  EsConfiguration.cpp  -o EsConfiguration.o

EpConfiguration.o : EpConfiguration.cpp 
	$(CPP)  EpConfiguration.cpp  -o EpConfiguration.o

Genome.o : Genome.cpp 
	$(CPP)  Genome.cpp  -o Genome.o

Mutation.o : Mutation.cpp 
	$(CPP)  Mutation.cpp  -o Mutation.o

Population.o : Population.cpp 
	$(CPP)  Population.cpp  -o Population.o

Selection.o : Selection.cpp 
	$(CPP)  Selection.cpp  -o Selection.o

Crossover.o : Crossover.cpp 
	$(CPP)  Crossover.cpp  -o Crossover.o

Random.o : Random.cpp
	$(CPP)  Random.cpp  -o Random.o

Results.o : Results.cpp
	$(CPP)  Results.cpp  -o Results.o

ge.o : ge.cc
	$(CPP)  ge.cc  -o ge.o

ge_gep.o : ge_gep.cc
	$(CPP)  ge_gep.cc  -o ge_gep.o

grammar.o : grammar.cc
	$(CPP)  $(PROBLEM)/grammar.cc  -o grammar.o

grammar_gep.o : grammar_gep.cc
	$(CPP)  $(PROBLEM)/grammar_gep.cc  -o grammar_gep.o

interpreter.o : interpreter.cc
	$(CPP)  $(PROBLEM)/interpreter.cc  -o interpreter.o

interpreter_gep.o : interpreter_gep.cc
	$(CPP)  $(PROBLEM)/interpreter_gep.cc  -o interpreter_gep.o

GEant.o : GEant.cc
	$(CPP)  $(PROBLEM)/GEant.cc  -o GEant.o

GEtrail.o : GEtrail.cc
	$(CPP)  $(PROBLEM)/GEtrail.cc  -o GEtrail.o

converter.o : converter.cpp
	$(CPP)  converter.cpp  -o converter.o

FrequencyDistribution.o : FrequencyDistribution.cpp
	$(CPP)  FrequencyDistribution.cpp  -o FrequencyDistribution.o

FrequencyDistributionElement.o : FrequencyDistributionElement.cpp
	$(CPP)  FrequencyDistributionElement.cpp  -o FrequencyDistributionElement.o

analyser_main.o : analyser_main.cpp 
	$(CPP)  analyser_main.cpp  -o analyser_main.o

Analyser.o : Analyser.cpp 
	$(CPP)  Analyser.cpp  -o Analyser.o

AnalyserConfig.o : AnalyserConfig.cpp 
	$(CPP)  AnalyserConfig.cpp  -o AnalyserConfig.o

generator_main.o : generator_main.cpp 
	$(CPP)  generator_main.cpp  -o generator_main.o

Generator.o : Generator.cpp 
	$(CPP)  Generator.cpp  -o Generator.o

#************************************************************************
#make clean
#************************************************************************
clean:
	rm -f GramaEvolve core *.o
	cp parser/parser.o .
	rm ./grammar.cc 
	rm ./grammar.hpp 
	rm ./interpreter.cc 
	rm ./interpreter.hpp 
	rm ./defines.h 
	$(COMPILER) --version














