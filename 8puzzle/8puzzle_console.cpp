#include<cstring>
#include<iostream>
#include<unistd.h>
using namespace std;
void p(const char *str){
	write(1,str,strlen(str));
	sleep(1);
}
int main()
{
	const char *str ="\n_____________\n";
	p("| 1 | 2 |   |\n| 4 | 5 | 6 |\n| 7 | 8 | 9 |\n"); /*p("can't \n"); p("see \n"); p("me\n");*/

// 	write(1,str,strlen(str));
	//write(1,str,strlen(str));
	//sleep(1);
	//write(1,str,strlen(str));	
	//write(1,"\33[2K\r",5); //erase line and carriage return
	//write(1,"\33[1A",4); // move 1 line up
	//write(1,"\33[2K\r",5); //erase line and carriage return

	//while(i){
	write(1,"\33[2K\r",5); //erase line and carriage return
	write(1,"\33[1A",4); // move 1 line up
	write(1,"\33[2K\r",5); //erase line and carriage return
	//i--;
	//}

	write(1,"\33[2K\r",5); //erase line and carriage return
	write(1,"\33[1A",4); // move 1 line up
	write(1,"\33[2K\r",5); //erase line and carriage return
	
	 write(1,"\33[2K\r",5); //erase line and carriage return
	 write(1,"\33[1A",4); // move 1 line up
	 write(1,"\33[2K\r",5); //erase line and carriage return
	 
	
	p("| 1 | 2 | 6 |\n| 4 | 5 |   |\n| 7 | 8 | 9 |");

	//}
	return 0;
}
