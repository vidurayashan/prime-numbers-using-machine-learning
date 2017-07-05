#include <iostream>
#include <fstream>
using namespace std;

ofstream fout("training_set.txt");

int prime [500000];
int prime_sz = 2;
int final_prime[1000];

int train [1000000];

int main (){
	
	int p=4;
	bool PRIME;
	prime[0] = 2;
	prime[1] = 3;

	for (int p=4; p<1000; p++){
		PRIME = true;
		for (int i=0; i<prime_sz; i++){
			if ( p % prime[i]==0 ){
				PRIME = false;
				break;
			}
		}
		if (PRIME == true){
			prime[prime_sz] = p;
			prime_sz ++;
		}
	}
	
/*	for (int i=0; i<prime_sz; i++){
		cout << prime[i] << " ";
	}*/
	
	for (int i=0; i<prime_sz; i++){
		final_prime[ prime[i] ] = 1;
	}
//	cout << "dsds";
	
	for (p=1000; p<1000000; p++){
		PRIME = true;
		for (int i=0; i<1000; i++){
		//	cout << "dsds";
			if (final_prime[i] == 0) continue;
		//	cout << "aaaaa";
			if (p % i == 0){
				PRIME = false;
				break;
			}
		}
		if (PRIME == true){
			prime[prime_sz] = p;
			prime_sz++;
			//cout << p << endl;
		}
	}
	
	for (int i=0; i<prime_sz; i++){
		train [ prime[i] ] = 1;
	}
	
	for (int i=1; i<1000000; i++){
		string ss = "np";
		if (train[i] == 1) ss = "p";
		
		fout << i << " " << ss << endl;
	}
	
	//system("pause");
	return 0;
	
}
