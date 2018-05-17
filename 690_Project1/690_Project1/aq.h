#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>


#ifndef ADD_H
#define ADD_H
class aq
{
	public:
		int rows;
		int columns;
		std::vector<std::vector<std::string>> table;
		aq();
		void setTable(std::vector<std::vector<std::string>>);
		~aq();
		void algorithm();
		void negativeExamples(std::vector<std::pair<int,std::string>> GPrimePrev);
		std::vector<int> decisionSet;
		std::vector<int> notdecisionSet;
		static const std::vector<std::vector<std::pair<int, std::string>>> emptyVec;
		bool consistent();
		int maxstar;
		void setMaxStar(int input);

};


#endif
