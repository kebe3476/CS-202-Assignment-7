/*
CS 202 Assignment 7

Name: Keith Beauvais, 5005338658, CS 202 Assignment 7
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include "date.h"
#include "transaction.h"
#include "sorter.h"
using namespace std;

/* stringConvertInt - This function converts strings into int.

string s - this string is passed in from the parse function.

return value - returns an int from the string when called.

*/
int stringConvertInt(string s){
  stringstream ss;
  int value;

  ss << s;
  ss >> value;

  return value;
}
/* parse - This function parses through the ifstream file and and returns the transaction.

string record - this string is passed in from the parse function.

return value - returns a transaction type.

*/
Transaction parse(string record){

	string strTrans, date, prod, payType, name, city, state, country, strMon, strDay;
	string strYear, strHour, strMin, strPrice;
	int month, day, year, hour, minute, price, trans;


		stringstream s(record);
		getline(s,strTrans,',');  //parsing through line
		trans = stringConvertInt(strTrans);
		getline(s,date,','); //parsing through line

		stringstream s1(date);
		getline(s1,strMon,'/');
		month = stringConvertInt(strMon);
		getline(s1,strDay,'/');
		day = stringConvertInt(strDay);
		getline(s1,strYear,' ');
		year = stringConvertInt(strYear);
		getline(s1,strHour,':');
		hour = stringConvertInt(strHour);
		getline(s1,strMin,':');
		minute = stringConvertInt(strMin);
		Date d(year, month, day, hour, minute);

		getline(s,prod,','); //parsing through line
		getline(s,strPrice,','); //parsing through line
		price = stringConvertInt(strPrice);
		getline(s,payType,','); //parsing through line
		getline(s,name,','); //parsing through line
		getline(s,city,','); //parsing through line
		getline(s,state,','); //parsing through line
		getline(s,country,','); //parsing through line

		Transaction t(trans,d,prod,price,payType,name,city,state,country);

	return t;
}


/*Function to readfile and return vector of Transaction
objects.*/
vector<Transaction> readFile(string filename)
{

	vector<Transaction> transactions;
	string line;

	try
	{
		ifstream myFile(filename);

		if(!myFile)
			throw string(filename);

		int lineCount=0;
		while(getline(myFile,line))
		{
			//Parse the line here ignoring the first line
			if(lineCount>0)
			{
				transactions.push_back(parse(line));
			}
			lineCount++;
		}
	}
	catch(string str)
	{
		cout <<"File "<<str<<" not found"<<endl;
	}

	return transactions;

}


/* findModeTransaction - This function passes in a template vector and a vector of type int and finds the 
most occurances of a product and the date.

vector<T> records - this is an already sorted vector and could be date or price.

vector<int>  ids - this is an already sorted vector of transaction ids of type int. 

return value - returns the mode, type int.

*/
template <class T>
int findModeTransaction(vector<T> records,vector<int>  ids){

	int	count, mode;
	int maxMode = count = 0;

	for(int i = 0; i< records.size(); i++){
		cout<< records[i]<<endl; // prints all the dates and prices. 
	}

	for (int i = 0; i < records.size(); i++){
		if (records[i] == records[i+1]){ // compares the next index to current one
    		count++;
    	}
		else{ // different number 

			if (count > maxMode){
  				maxMode = count;
    			mode = ids[i];
  			}
  		count = 0; // resets the count
  		}
	}
	return mode;
}



int main(int argc,char * argv[])
{

	//Correct file name
	string file="SalesJan2009.csv";

	//vector to hold all the transactions
	vector<Transaction> transactions;


	cout<<"Reading SalesJan2009.csv"<<endl;
	transactions= readFile(file);


	cout <<"File read."<<transactions.size()<<" transactions returned"<<endl;

	//vectors to hold the transaction dates, ids and prices
	vector<Date>* dates=new vector<Date>();
	vector<int> ids;
	vector<int>* prices=new vector<int>();

	//populating the vectors
	for(int i=0;i<transactions.size();i++)
	{
		dates->push_back(transactions[i].getDate());
		ids.push_back(transactions[i].getId());
		prices->push_back(transactions[i].getPrice());

	}

	//creating a sorter object to sort by transaction dates
	Sorter<Date> * sortByDate=new Sorter<Date>(dates,ids);

	sortByDate->sort();

	//find the mode transaction date
	int modeDay=findModeTransaction(*sortByDate->getListVector(),sortByDate->getIdsVector());

	//printing the mode date
	for(int i=0;i<transactions.size();i++)
	{
		if(transactions[i].getId()==modeDay)
		{
			Date d=transactions[i].getDate();
			cout <<"Maximum number of transaction happened on:"<<d.getMonth()<<":"<<d.getDay()<<":"<<d.getYear()<<endl;
			break;
		}
	}

	//creating a sorter object to sort by product price
	Sorter<int> * sortByPrice=new Sorter<int>(prices,ids);

	sortByPrice->sort();

	//find the mode product price
	int modePrice=findModeTransaction(*sortByPrice->getListVector(),sortByPrice->getIdsVector());

	//print the product relating to the mode price
	for(int i=0;i<transactions.size();i++)
	{
		if(transactions[i].getId()==modePrice)
		{
			string product=transactions[i].getProduct();
			cout <<"Maximum transactions happened for:"<<product<<endl;
			break;
		}
	}
	return 0;
}
