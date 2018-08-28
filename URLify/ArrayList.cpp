#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include<stdio.h>
#include<string.h>

using namespace std;

std::string URLify(std::string words,int _size)
{
	std::string url = words;

	int urlSize = words.size();
	char urlC[urlSize +1];
	char temp[urlSize +1];
	url.copy(urlC,urlSize+1);
	urlC[urlSize] = '\0';
	strcpy(temp, urlC);

	int spaceC=0;

	const char space = ' ';
	for(int i= 0; i < urlSize;i++)
	{
		if(temp[i] == space)
		{
			urlSize = urlSize +3;
			//for(i;i<urlSize;i++)
			//{
			urlC[i + spaceC] = '%';
			urlC[i+1 + spaceC]='2';
			urlC[i+2 + spaceC]='0';

			memcpy(&urlC[i+3],&temp[i+1],sizeof(temp));
			spaceC++;

			//}
		}
		//cout << i << "= " << urlC[i] << endl;

	}

	//cout << urlC << endl;
	url = urlC;
	return url;
}

std::string joinWords(std::string words[],int size)
{
	std::string sentance;
	
	for(int i=0;i<size;i++)
		sentance = sentance + words[i] + " ";

	return sentance;
}

int main(int argc, char const *argv[])
{
	/* code */
	std::vector<double> arr;
	arr.push_back(2.88);
	arr.push_back(3.21);
	arr.push_back(1.55);
	std::sort(arr.begin(),arr.end());

	for(auto x : arr)
		std::cout << x << std::endl;

	std::string s[5] = {"hello", "this" ,"is", "string"};
	int length =  sizeof(s)/sizeof(s[0]);

	std::string sentance = joinWords(s,length);
	cout << sentance << endl;

	std::string url = URLify("Mr John Smith",13);

	cout << url << endl;

	return 0;
}