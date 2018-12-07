
#ifndef PROJECT_LABELGEN_H
#define PROJECT_LABELGEN_H
#include <string>

using namespace std;

class labelGenerator {
    public:
        labelGenerator();

        labelGenerator(string str, int num);

        string toString();

        string nextLabel();

    private:
        string label = "";
        int number = 0;
};


#endif
