/*
CS 202 Assignment 7

Name: Keith Beauvais, 5005338658, CS 202 Assignment 7
*/
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Sorter
{
private:
	vector<T> *list;
	vector<int> ids;

public:

	Sorter(vector<T> *l,vector<int> i){
		list = l;
		ids = i;
	}
/* sort-  This function sorts the templated vector and the vector of int. 

return value - does not return; void.

*/
	void sort(){
		T temp;
		int tempIds;

		for (int i = 0; i < ids.size()-1; i++)
			for (int j = 0; j < ids.size()-i-1; j++)
				if ((*list)[j] > (*list)[j+1]) {

				 temp = (*list)[j];
				 (*list)[j] = (*list)[j+1];
				 (*list)[j+1] = temp;

				 tempIds = ids[j];
				 ids[j] = ids[j+1];
				 ids[j+1] = tempIds;
				}

	}

	vector<T> * getListVector(){
		return list;
	}

	vector<int>  getIdsVector(){
		return ids;
	}

};
//complete the class implementation
