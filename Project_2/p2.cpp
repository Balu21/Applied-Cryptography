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
#include <sstream>
#include <locale>         // std::locale, std::toupper
#include<bits/stdc++.h> 



using namespace std;
using namespace std::chrono;


string ToHex(const string& s, bool upper_case)
{
    ostringstream ret;

    for (string::size_type i = 0; i < s.length(); ++i)
    {
        int z = s[i]&0xff;
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << z;
    }

    return ret.str();
}

//--------------------------Funcitons for XOR of hex strings-----------------------------------

static inline unsigned int value(char c)
{
    if (c >= '0' && c <= '9') { return c - '0';      }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
    return -1;
}

std::string str_xor(std::string const & s1, std::string const & s2)
{
    assert(s1.length() == s2.length());

    static char const alphabet[] = "0123456789ABCDEF";

    std::string result;
    result.reserve(s1.length());

    for (std::size_t i = 0; i != s1.length(); ++i)
    { 
        unsigned int v = value(s1[i]) ^ value(s2[i]);

        assert(v < sizeof alphabet);

        result.push_back(alphabet[v]);
    }

    return result;
}

string brute(string cipher)
{
	unsigned long int k = 95;
	std::stringstream stream;
	stringstream ss2;
	//string c1, c2, fin;
	//cout<<"result k = "<<result<<endl;
	//cout<<"input = "<<input<<endl;
	string res;
	string s1, s2, s3, s4;
	unsigned int x;
	int count = 0;
	string result;
	int n = 0;
	int flag = 0;
	
	vector <string> keys;
	string subcipher;
	
	for(k=389665688; k< 389665689; k++)
	{
		n++;
		count = 0;
		if(k%10000000 == 0)
			cout<<"k = "<<k<<endl;
		stream.str("");
		stream<<std::hex<<setw(8)<<setfill('0')<<k;

		result = stream.str();
		
		//cout<<"cipher length : "<<cipher.length()<<endl;
		//cout<<"result length : "<<result.length()<<endl;
		
		for(int i = 0; i<152; i+=8) {
			//if(i%8==0)
				//cout<<i<<endl;
			subcipher = cipher.substr(i,8);
			res = str_xor(subcipher, result);
		
			s1 = res.substr(0,2);
			s2 = res.substr(2,2);
			s3 = res.substr(4,2);
			s4 = res.substr(6,2);
			
			ss2.str("");
			ss2 << s1;
			x = stoi(ss2.str(), nullptr, 16);
			
			if(x>=32 && x<=126) {
				count++;
			}
			
			else
				continue;
			ss2.str("");
			ss2 << s2;
			x = stoi(ss2.str(), nullptr, 16);
			
			if(x>=32 && x<=126) {
				count++;
			}
			else
				continue;
			ss2.str("");
			ss2 << s3;
			x = stoi(ss2.str(), nullptr, 16);
			//if(n<10)
				//cout<<x<<"\t";
			
			if(x>=32 && x<=126) {
				count++;
			}
			else
				continue;
			ss2.str("");
			ss2 << s4;
			x = stoi(ss2.str(), nullptr, 16);
			//if(n<10)
				//cout<<x<<"\t";
			
			if(x>=32 && x<=126) {
				count++;
			}
			
			if(count == 152)
				flag = 1;
			
			
		}
		cout<<"count = "<<count<<endl;
		if(flag == 1){
			cout<<"The prog is working"<<endl;
			break;		
			
			}
		
	}
	
	return result;
	
	/*
	for(int i=0; i<keys.size(); i++)
		cout<< keys[i] <<endl;
	*/
}


string brute2(string cipher) {
	unsigned long int k = 95;
	std::stringstream stream;
	stringstream ss2;
	//string c1, c2, fin;
	//cout<<"result k = "<<result<<endl;
	//cout<<"input = "<<input<<endl;
	string res;
	string s1, s2, s3, s4;
	unsigned int x;
	int count = 0;
	string result;
	
	for(k=0; k< 4000000000; k++)
	{
		if(k%10000000 == 0)
			cout<<"k = "<<k<<endl;
		stream.str("");
		stream<<std::hex<<setw(8)<<setfill('0')<<k;
		result = stream.str();
		res = str_xor(cipher, result);
		if(res.compare("474E5089")==0)
			break;
	}
	return result;

}


//--------------------MAIN FUNCTION________________________________________________________
int main() {
	streampos size;
	char* memblock;
	locale loc;
	
	ifstream file ("image-encr", ios::in|ios::binary|ios::ate);
	if(file.is_open()) {
		size = file.tellg();
		memblock = new char [size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();
	}
	
	else cout<<"Unable to open file"<<endl;
	
	std::string tohexed = ToHex(std::string(memblock, 160), true);
	
	cout<<"size = "<<size<<endl;
	//cout<<tohexed<<endl;
	stringstream ss;
	
	string thex;
	for(int i=8;i<160;) {
		thex = tohexed.substr(i,8);
	
		
		ss << thex.substr(6,2);
		ss << thex.substr(4,2);
		ss << thex.substr(2,2);
		ss << thex.substr(0,2);
		i+=8;
	}
	
	
	string result(ss.str());
	
	cout<<"result  = "<<result<<endl;
	
	
	
	auto start = high_resolution_clock::now(); 
	string fin = brute(result);
	//brute(result);
	auto stop = high_resolution_clock::now(); 
	
	auto duration = duration_cast<seconds>(stop - start); 
	
	cout<<"key = "<<fin<<endl;
	
	cout << "Time taken to brute force the key : "<<duration.count() << " seconds"<<endl; 
	
	
	/*
	cout<<result<<endl;
	string plainHex = "46445025";
	
	string res = str_xor(plainHex, result);
	cout<<res<<endl;
	
	/*
	string s1 = "50987308";
	string s2 = "3c000000";
	
	string res2 = str_xor(s1, s2);
	cout << res2 <<endl;
	
	
	cout<<res<<endl;
	*/
}

