#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
#include <cstdlib>

#ifndef DEBUG
#define DEBUG 0
#endif // DEBUG

using namespace std;

typedef map<char,map<char, int> > char_map;

static bool debug=DEBUG;

void read_file(istream& in,char_map& m);
void print_char_map(ostream& out, char_map& m);
char find_next_char(char_map m, char c, int k);
bool access(char_map m,char i, char j);

int main(int argc,char** argv)
{
	int i=1;
	int n=10;
	string file_name;
	ifstream f;
	char_map m;
	bool file=0,file_is_read=0;
	if(argc>1) {
		file=1;
	}
	if(file) {
		n=static_cast<int>(strtol(argv[i++],nullptr,10));///if we don't get a number with something tacked on the end, we ignore it.
		if(n==0) {
			cerr<<"Please provide a valid number as the first parameter. Treating it a  file instead, and using 10 as the number.";
			i--;
			n=10;
		}
		if(!strcmp(argv[i],"--debug")) {
			debug=1;
			i++;
		}
		while(!file_is_read && i<argc) {
			file_name=argv[i];
			if(file_name!="-") {
				f.open(file_name);
				if(!f.is_open()) {
					cerr<<"Could not open file "<<file_name<<endl;
				} else {
					file_is_read=1;
					read_file(f,m);
				}
			} else {
				file_is_read=1;
				read_file(cin,m);
			}
			i++;
		};
	} else {
		read_file(cin,m);
	}
	if(debug) {
		print_char_map(cerr,m);
	}

	if(m.empty()) {
		cerr<<"No data to crunch!\nPlease give me lunch.\n";
		return 1;
	}

	//time to actually use this usefull data! Crunch me some nmbers!

	srand(static_cast<unsigned int>(time(nullptr))); ///incompatible with c++98, but who cares?

	for(int _=0; _<n; _++) { /// perl ftw!
		char c=0;
		do {
			c=find_next_char(m,c,rand()%1000);/// hopefully big enough, but not too big.
			//if(isprint(c))
			cout<<c;

		} while (c);
		cout<<endl;
	}

	return 0;
}

void read_file(istream& in, char_map& m)
{
	string s;
	unsigned int i;
	while(!in.eof()) {
		getline(in,s); ///if a non-newline seperator option is desired, add it here.
		if(s.length()>1) {
			m[0][s.at(0)]++;
			m[s.at(s.length()-1)][0]++;
			for(i=0; i<s.length()-1; ++i) {
				m[s.at(i)][s.at(i+1)]++;
			}
		}
	}
}

void print_char_map(ostream& out,char_map& m)
{
	char i,j;
	for(i=0; i<CHAR_MAX; i++) {
		if(m.find(i)==m.end()) {
			for(j=0; j<CHAR_MAX; j++) {
				out<<0<<' ';
			}
		} else {
			for(j=0; j<CHAR_MAX; j++) {
				if(m[i].find(j)==m[i].end()) {
					out<<0<<' ';
				} else {
					out<<m[i][j]<<' ';
				}
			}
		}
		out<<endl;
	}
}

bool access(char_map m, char i, char j)
{
	if(debug) {
		cerr<<"access called for i='"<<i<<"', j='"<<j<<"':";
	}
	if(m.find(i)==m.end()) {
		if(debug) {
			cerr<<0<<endl;
		}
		return 0;
	}
	if(m[i].find(j)==m[i].end()) {
		if(debug) {
			cerr<<0<<endl;
		}
		return 0;
	}
	if(debug){
		cerr<<1<<endl;
	}
	return 1;
}

char find_next_char(char_map m, char c, int k)
{
	if(debug) {
		cerr<<"find_next_char called for c='"<<c<<"', k="<<k<<endl;
	}
	char j=0;
	if(m.find(c)==m.end()) {
		if(debug) {
			cerr<<"no such c, returning \\0\n";
		}
		return 0;
	}
	while(k>0) {
		for(j=0; j<CHAR_MAX && k>0; j++) {
			if(access(m,c,j)) {
				k-=m[c][j];
				if(debug) {
					cerr<<k<<endl;
				}
			}
		}
		j--;
	}
	if(debug) {
		cerr<<"find_next_char returned '"<<j<<"'\n";
	}
	return j;
}
