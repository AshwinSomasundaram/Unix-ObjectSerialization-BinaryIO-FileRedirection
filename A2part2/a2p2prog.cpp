#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class passwd{
public: string username;
	string uid;
	string gid;
	string gecos;
	string uhd;
	string logshell;
};

int main(){
ifstream file;
file.open("passwd.txt");
string line;
int count;
while(getline(file,line)){
count++;
}
file.close();


passwd passwdArray[count];

count=0;

file.open("passwd.txt");

while(getline(file,line)){
passwd obj;
size_t col1 = line.find(':');
obj.username = line.substr(0,col1);
size_t col2 = line.find(':',col1+1);
size_t col3 = line.find(':',col2+1);
obj.uid = line.substr(col2+1,col3-col2-1);
size_t col4 = line.find(':',col3+1);
obj.gid = line.substr(col3+1,col4-col3 -1);
size_t col5 = line.find(':',col4+1);
obj.gecos = line.substr(col4+1,col5-col4-1);
size_t col6 = line.find(':',col5+1);
obj.uhd = line.substr(col5+1,col6-col5-1);
obj.logshell = line.substr(col6+1);
passwdArray[count] = obj;
count++;
}

file.close();
ofstream out;
ofstream binout("a2p2out2.bin", ios::out|ios::binary);
out.open("a2p2out1.txt");
for(int i=0;i<count;i++){
out<<"Record #"<<i<<endl;
out<<"Username: "<<passwdArray[i].username<<endl;
out<<"uid: "<<passwdArray[i].uid<<endl;
out<<"gid:  "<<passwdArray[i].gid<<endl;
out<<"gecos: "<<passwdArray[i].gecos<<endl;
out<<"uhd: "<<passwdArray[i].uhd<<endl;
out<<"logshell: "<<passwdArray[i].logshell<<endl<<endl;
binout.write((char*)&passwdArray[i], sizeof(passwd));
}
out.close();
binout.close();
ifstream binIn("a2p2out2.bin", ios::out|ios::binary);

passwd passwdArray2[count];
for(int i=0;i<count;i++){
binIn.read((char*)&passwdArray2[i],sizeof(passwd));
}
ofstream out1;
out1.open("a2p2task2.txt");
for(int i=0;i<count;i++){
out1<<"Record #"<<i<<endl;
out1<<"Username: "<<passwdArray2[i].username<<endl;
out1<<"uid: "<<passwdArray2[i].uid<<endl;
out1<<"gid:  "<<passwdArray2[i].gid<<endl;
out1<<"gecos: "<<passwdArray2[i].gecos<<endl;
out1<<"uhd: "<<passwdArray2[i].uhd<<endl;
out1<<"logshell: "<<passwdArray2[i].logshell<<endl<<endl;
}
out1.close();
return 0;
}
