#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "aq.h"



int main(int argCount, char** args)
{
	bool consistency = true;
do{
	
  std::ifstream input;
  std::string line;
  std::string userIn;
  
  
    std::cout << "Please provide an input file\n";
	std::cin >> userIn;
    input.open(userIn, std::ifstream::in);
	

  std::getline(input, line);
  std::getline(input, line);
  std::stringstream data(line);
  std::vector<std::vector<std::string>> masterVec;
  std::string current;
  data >> current;
  data >> current;
  int count = 0;
  std::vector<std::string> currentVec;
  while (!data.eof())
  {
    currentVec.push_back(current);
    count ++;
    std::cout << current;
    data >> current;
  }

  masterVec.push_back(currentVec);
  std::getline(input, line);
  currentVec.clear();
  while(!input.eof())
  {
	std::stringstream data2(line);
	while(!data2.eof())
	{
		data2 >> current;
		currentVec.push_back(current);
		std::cout << current;

	}
	masterVec.push_back(currentVec);
	std::getline(input,line);
	currentVec.clear();
	data2.flush();
	std::cout << "\n";
  }
  	aq alg;
	alg.setTable(masterVec);
	if(!alg.consistent())
	{
		std::cout << "Input Data is not consistent! Please input a different set of data\n";
		consistency = false;
	}
	else
	{
		std::cout  << "Please input a MaxStar value\n";
		std::cin >> userIn;
		
		alg.setMaxStar(stoi(userIn));
		alg.algorithm();
	}
input.close();		
}while(!consistency);
return(0);
	

}