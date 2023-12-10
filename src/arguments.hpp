#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

class Arguments {
  public:
    int simulationLength;
    int skacelovaGreenLength;
    int purkynovaGreenLength;
    Arguments(int argc, char** argv);
};

#endif
