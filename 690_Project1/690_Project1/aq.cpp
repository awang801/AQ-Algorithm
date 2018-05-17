#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "aq.h"

aq::aq()
{
}

void aq::setTable(std::vector<std::vector<std::string>> vec)
{
	table = vec;
	rows = table.size();
	columns = table[0].size();
}

aq::~aq()
{
	table.clear();
}

void aq::algorithm()
{
	std::ofstream output;
	std::ofstream output2;
	std::vector<int> doneset;
	std::string decisionValue;
	output.open("my-data.with.negation.rul");
	output2.open("my-data.without.negation.rul");
	do
	{
		if(doneset.empty())
		{
			decisionValue = table[1][3];
			//std::cout << decisionValue;
		}
		else
		{
			bool decision;
			for (int i = 1; i < rows; i++)
			{
					decisionValue = table[i][3];
					decision  = true;
					for (int j=0; j < doneset.size(); j++)
					{
						//std::cout << doneset[j] << "\n";
						//std::cout << table[i][3] << "\n";
						if (i == doneset[j])
						{
							decision = false;
						}
					}
					if (decision)
					{
						i = rows;
					}
			}
		}
		//std::cout << "decision value "<< decisionValue << "\n";
		for (int i=1; i<rows; i++)
		{
			//std::cout << table[i][3];
			//std::cout << decisionValue << "\n";
			if (table[i][3].compare(decisionValue) == 0)
			{
				decisionSet.push_back(i);
			}
			else
			{
				notdecisionSet.push_back(i);
			}
		}
		std::vector<std::pair<int,std::string>> GPrime;
		std::vector<std::pair<int,std::string>> GPrimePrev;
		std::vector<std::vector<std::string>> GG;
		std::string G;
		std::vector<int> negatives;
		std::pair <int, std::string> product;
		std::vector <std::pair<int, std::string>> productRule;
		std::vector<int> partialStar;
		std::vector<std::vector<std::pair<int, std::string>>> partialstarRules;
		std::vector<std::vector<std::pair<int, std::string>>> finalRules;
		int sameValue;
		std::pair <int, std::string> linearDrop;
		bool linearDropBool = false;
		std::vector<std::pair<int, std::string>> negated;
		// for (int k=0; k < (columns - 1); k++)
		// {
		// 	if (table[decisionSet[0]][k].compare(table[notdecisionSet[0]][k]))
		// 	{
		// 		product = std::make_pair(k, table[decisionSet[0]][k]);
		// 		productRule = std::make_pair(product, product);
		// 		partialstarRules.push_back(productRule);
		// 		GPrime.push_back(product);
		// 	}
		// }
		// partialStar.push_back(notdecisionSet[0]);
		// std::cout << "PartialStar: " << decisionSet[0] << " | " << partialStar[0];
		// for (int i = 0; i < GPrime.size(); i++)
		// {
		// 		std::cout<< "     " << table[0][std::get<0>(GPrime[i])]<< " not " << std::get<1>(GPrime[i]) << "\n";
		// }
		// GPrime.clear();

		//std::cout << notdecisionSet.size();
		for (int i=0; i<decisionSet.size(); i++)
		{

			for (int j=0; j<notdecisionSet.size(); j++)
			{
				for (int k=0; k < (columns - 1); k++)
				{
					if (table[decisionSet[i]][k].compare(table[notdecisionSet[j]][k]) && GPrime.size()<maxstar)
					{
						product = std::make_pair(k, table[notdecisionSet[j]][k]);
						GPrime.push_back(product);
					}
				}
				partialStar.push_back(notdecisionSet[j]);
				std::cout << "PartialStar: " << decisionSet[i] << " | " << notdecisionSet[j];
				for (int l = 0; l < GPrime.size(); l++)
				{
						std::cout<< "     " << table[0][std::get<0>(GPrime[l])]<< " not " << std::get<1>(GPrime[l]) << "    ";
				}
				std::cout << "\n";
				if(j==0)
				{
					//productRule = std::make_pair(product,product);
					//partialstarRules.push_back(productRule);
					GPrimePrev = GPrime;
				}
				else if (j==1)
				{
					std::cout << "PartialStar: " << decisionSet[i] << " | " << "{";
					for (int o = 0; o <partialStar.size(); o++)
					{
						std::cout << partialStar[o] << " ";
					}
					std::cout << "}" << "    ";
					notdecisionSet[j];
					for(int m = 0; m < GPrime.size(); m++)
					{
						for (int n = 0; n < GPrimePrev.size(); n++)
						{
							productRule.push_back(GPrime[m]);
							productRule.push_back(GPrimePrev[n]);
							partialstarRules.push_back(productRule);
							std::cout << "     "
												<< table[0][std::get<0>(GPrime[m])]
												<< " not " << std::get<1>(GPrime[m])
												<< " and "
												<< table[0][std::get<0>(GPrimePrev[n])]
												<< " not "
												<< std::get<1>(GPrimePrev[n])
												<< "    ";
							productRule.clear();
						}
					}

					for(int p = 0; p < partialstarRules.size(); p++)
					{
						for (int q = 0; q < partialstarRules[0].size() - 1; q++)
						{
							//std::cout << p << q;
							if((!std::get<1>(partialstarRules[p][q]).compare(std::get<1>(partialstarRules[p][q+1]))) && (std::get<0>(partialstarRules[p][q]) == std::get<0>(partialstarRules[p][q+1])))
							{
								//std::cout << std::get<1>(partialstarRules[p][q]);
								linearDropBool = true;
								linearDrop = partialstarRules[p][q];
							}
						}
					}
					
					if (linearDropBool)
					{
						std::cout << "Linearly drop to get : " << table[0][std::get<0>(linearDrop)] << " not " << std::get<1>(linearDrop) << "\n";
						partialstarRules.resize(1);
						std::vector<std::pair<int, std::string>> temp;
						std::vector<std::pair<int, std::string>> &partialobject = partialstarRules[0];
						productRule.push_back(linearDrop);
						temp.push_back(linearDrop);
						//temp.push_back(linearDrop);
						partialobject.swap(temp);
						productRule.clear();
					}
					else
					{
						productRule.push_back(GPrimePrev[0]);
						productRule.push_back(GPrime[0]);

						partialstarRules.resize(1);
						std::vector<std::pair<int, std::string>> temp;
						std::vector<std::pair<int, std::string>> &partialobject = partialstarRules[0];
						//temp.push_back(linearDrop);
						partialobject.swap(productRule);
						productRule.clear();
							//partialstarRules.erase(partialstarRules.begin() + r);
					}
					linearDropBool = false;
					std::cout << "\n";
					GPrimePrev = GPrime;
				}
				else
				{
					std::cout << "PartialStar: " << decisionSet[i] << " | " << "{";
					for (int o = 0; o <partialStar.size(); o++)
					{
						std::cout << partialStar[o] << " ";
					}
					std::cout << "}" << "    ";
					notdecisionSet[j];
					for(int m = 0; m < GPrime.size(); m++)
					{
						for (int n = 0; n < partialstarRules.size(); n++)
						{
							for (int a = 0; a < partialstarRules[n].size(); a++)
							{
							std::cout << "     "
												<< table[0][std::get<0>(GPrime[m])]
												<< " not " << std::get<1>(GPrime[m])
												<< " and "
												<< table[0][std::get<0>(partialstarRules[n][a])]
												<< " not "
												<< std::get<1>(partialstarRules[n][a])
												<< "    ";
							productRule.clear();
							}
						}
					}

					for(int p = 0; p < partialstarRules.size(); p++)
					{
						for (int q = 0; q < partialstarRules[p].size() - 1; q++)
						{
							//std::cout << p << q;
							if((!std::get<1>(partialstarRules[p][q]).compare(std::get<1>(partialstarRules[p][q+1]))) && (std::get<0>(partialstarRules[p][q]) == std::get<0>(partialstarRules[p][q+1])))
							{
								//std::cout << std::get<1>(partialstarRules[p][q]);
								linearDropBool = true;
								linearDrop = partialstarRules[p][q];
							}
						}
					}
					
					if (linearDropBool)
					{
						//
						std::cout << "Linearly drop to get : " << table[0][std::get<0>(linearDrop)] << " not " << std::get<1>(linearDrop) << "\n";
						partialstarRules.resize(1);
						std::vector<std::pair<int, std::string>> temp;
						std::vector<std::pair<int, std::string>> &partialobject = partialstarRules[0];
						productRule.push_back(linearDrop);
						temp.push_back(linearDrop);
						//temp.push_back(linearDrop);
						partialobject.swap(temp);
						productRule.clear();
					}
					else
					{
						productRule.push_back(partialstarRules[0][0]);
						productRule.push_back(GPrime[0]);
						partialstarRules.resize(1);
						std::vector<std::pair<int, std::string>> temp;
						std::vector<std::pair<int, std::string>> &partialobject = partialstarRules[0];

						//temp.push_back(linearDrop);
						partialobject.swap(productRule);
						productRule.clear();

					}
					linearDropBool = false;
					std::cout << "\n";
					GPrimePrev = GPrime;
				}
				GPrime.clear();
			}
			partialStar.clear();
			finalRules.push_back(partialstarRules[0]);
			partialstarRules.resize(1);
		}
		
		std::cout << "\n\n";
		for (int i = 0; i < finalRules.size(); i++)
		{
			for (int j = 0; j < finalRules[i].size(); j++)
			{
				if(j==0)
				{
					std::cout
							<< table[0][std::get<0>(finalRules[i][j])]
							<< " not " << std::get<1>(finalRules[i][j]);
					output 	<< table[0][std::get<0>(finalRules[i][j])]
							<< " not " << std::get<1>(finalRules[i][j]);
				}
				else
				{
					std::cout << " and "
							<< table[0][std::get<0>(finalRules[i][j])]
							<< " not " << std::get<1>(finalRules[i][j]);
					output << " and "
							<< table[0][std::get<0>(finalRules[i][j])]
							<< " not " << std::get<1>(finalRules[i][j]);
				}
			for (int k = 1; k < rows; k++)
			{
				if (negated.empty())
				{
					if (std::get<1>(finalRules[i][j]).compare(table[k][std::get<0>(finalRules[i][j])]))
					{
						product = std::make_pair(std::get<0>(finalRules[i][j]), table[k][std::get<0>(finalRules[i][j])]);
						negated.push_back(product);
					}
				}
				else
				{
					bool pass = true;
					for (int l = 0; l < negated.size(); l++)
					{

						if (!table[k][std::get<0>(finalRules[i][j])].compare(std::get<1>(negated[l])))
						{
							if(!std::get<1>(finalRules[i][j]).compare(table[k][std::get<0>(finalRules[i][j])]))
							{
								pass = false;
							}
						}
					}
					product = std::make_pair(std::get<0>(finalRules[i][j]), table[k][std::get<0>(finalRules[i][j])]);
					negated.push_back(product);
				}

			}
			}
			for (int m = 0; m < negated.size(); m++)
			{
				if(m==0)
				{
					output2 	<< table[0][std::get<0>(negated[m])]
							<< " " << std::get<1>(negated[m]);
				}
				else
				{
					output2 << " and "
							<< table[0][std::get<0>(negated[m])]
							<< " " << std::get<1>(negated[m]);
				}
			}
			std::cout << "   -->   "
					<< table[0][columns - 1]
					<< " "
					<< table[decisionSet[0]][columns - 1]
					<< "\n\n";
			output << "   -->   "
					<< table[0][columns - 1]
					<< " "
					<< table[decisionSet[0]][columns - 1]
					<< "\n\n";
			output2 << "   -->   "
					<< table[0][columns - 1]
					<< " "
					<< table[decisionSet[0]][columns - 1]
					<< "\n\n";
			negated.clear();

		}				  
		for(int i = 0; i <decisionSet.size(); i++)
		{
			doneset.push_back(decisionSet[i]);
		}
		// for(int i =0; i<doneset.size(); i++)
		// {
		// 	std::cout<< "   " << doneset[i];
		// }
		decisionSet.clear();
		notdecisionSet.clear();
	}while(doneset.size() < (rows - 1));
output.close();
output2.close();
}

bool aq::consistent()
{
	bool returnValue = true;
	for(int i = 0; i < rows; i++)
	{
		int same = 0;
		for (int j = 0 ; j < rows; j++)
		{
			for (int k = 0; k < columns - 1; k++)
			{
				if(i == j)
				{
				}
				else
				{
					if (!table[i][k].compare(table[j][k]))
					{
						same ++;
					}
				}
			}
		}
		if (same == rows-1)
		{
			if(!table[i][columns - 1].compare(table[i][columns-1]))
			{
				returnValue = false;
			}
		}
		same = 0;
	}
	return(returnValue);
}
void aq::setMaxStar(int input)
{
	maxstar = input;
}
