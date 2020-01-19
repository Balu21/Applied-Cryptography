#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<vector>
#include<chrono>
#include<iomanip>
#include<cstring>
#include<bits/stdc++.h>
#include<numeric>
#include <boost/utility/binary.hpp>
#include <bitset>
#include <iomanip>
#include<string>
#include <sstream>      // std::stringstream

using namespace std;
using namespace std::chrono;


string key = "1A2B9E0F";  
map<int,int> keyMap; 
int arr[8];

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

std::string hexStr(unsigned char *data, int len)
{
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

string sortString(string &str) 
{
	//cout<<key<<endl;
	
	for(int i=0; i<8; i++)
	{arr[i] = i;}
	char temp;
	int t;
	for(int i=0;i<str.length();i++)
	{
		for(int j=0;j<i;j++)
		{
			if(str[i] < str[j])
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
		
	}
	/*
	cout<<str<<endl;
  	for(int i=0; i<8; i++)
  	{
  		cout<<arr[i];
  	}
  	cout<<endl;
  	*/
	//sort(str.begin(), str.end()); 
	//return str;
}

 
void setPermutationOrder() 
{              
    // Add the permutation order into map  
    for(int i=0; i < key.length(); i++) 
    { 
        keyMap[key[i]] = i; 
    } 
} 
  
string encryptMessage(string msg)
{
	string temp = msg;
	//int k = 0;
	for(int i=0; i<msg.length()/8; i++)
	{
		for(int j=0; j<8; j++)
		{
			temp[8*i+j] = msg[arr[j]+8*i];
		}
	}
	char hexVal = 'c';
	//cout<<hexVal<<endl;
	hexVal += 0x4;
	//cout<<hexVal<<endl;
	return temp;		
}

string sbox(string msg)
{
	string temp = msg;
	char* t;
	char strue[] = "0123456789abcdef";
	char smap[] = "7b3a150d98fc62e4";
	for(int i = 0; i<msg.length(); i++)
	{
		t = strchr(strue, msg[i]);
		temp[i] = smap[t-strue];
	}
	return temp;
}


void brute(string input, string cipher)
{
	unsigned long int k = 95;
	std::stringstream stream;
	string c1, c2, fin;
	//cout<<"result k = "<<result<<endl;
	cout<<"input = "<<input<<endl;
	
	for(k=0; k< 4000000000; k++)
	{
		if(k%10000000 == 0)
			cout<<"k = "<<k<<endl;
		stream.str("");
		stream << std::hex << setw(8) << setfill('0')<<k;
		std::string result( stream.str() );	
		//cout<<"result = "<<result<<endl;
		sortString(result);
		//cout<<"hello"<<endl;
		c1 = encryptMessage(input);
		//cout<<c1<<endl;
		c2 = encryptMessage(c1);
		//cout<<c2<<endl;
		fin = sbox(c2);
		if(cipher.compare(fin) == 0)
		{
			cout<<"Match found"<<endl;
			cout<<"Key is : "<<result<<endl;
			break;
		}
		//cout<<"iter1 done"<<endl;
	}
		
}


int main()
{
	ifstream input;
	input.open("input.txt", ios::binary);
    //std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
	//cout<<buffer[0]<<endl;	
	
	sortString(key);
	
	
	std::string packet;
	getline(input, packet);
	std::string hex = hexStr((unsigned char*)packet.c_str(), packet.size());
	printf("%s\n", hex.c_str());
	if(hex.length() % 32 != 0)
	{
		int append = 32 - hex.length()%32;
		for(int i=0;i<append;i++)
		{
			hex += '0x0';
		}
	}
	
	cout<<hex<<endl;
	
	string cipher = encryptMessage(hex);
	cout<<cipher<<endl;
	string c2 = encryptMessage(cipher);
	cout<<c2<<endl;
	string fin = sbox(c2);
	cout<<fin<<endl;
	
	auto start = high_resolution_clock::now(); 
	brute(hex.substr(0,8), fin.substr(0,8));
	auto stop = high_resolution_clock::now(); 
	
	auto duration = duration_cast<seconds>(stop - start); 
	
	cout << "Time taken to brute force the key : "<<duration.count() << " seconds"<<endl; 
	/*
	unsigned b = BOOST_BINARY( 10010 );
	char buf[sizeof(b)*8+1];
	printf("hex: %04x, dec: %u, oct: %06o, bin: %16s\n", b, b, b, itoa(b, buf, 2));
	cout << setfill('0') <<
	"hex: " << hex << setw(4) << b << ", " <<
	"dec: " << dec << b << ", " <<
	"oct: " << oct << setw(6) << b << ", " <<
	"bin: " << bitset< 16 >(b) << endl;
	return 0;
	*/
	
	/*
	//cout<<setfill('0')<<hex<<setw(2)<<x<<endl;
	for(int i = 0; i< 1;i++)
	{
		printf("hex = %08x\n",x);
		x++;
	}
	*/
	
	
}

















