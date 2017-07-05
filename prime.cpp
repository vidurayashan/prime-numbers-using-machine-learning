#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void set_val(int N, int& an, int& bn, int& cn){  //feature setting
	an = (N-1) % 6; 
	bn = (N+1) % 6;
	cn = N % 5;
}

//float distance()

//maximum and minimum of the features selected
int mina, minb, minc;
int maxa = 5;
int maxb = 5;
int maxc = 4;

float fit_parameter(float min_val, float max_val, float a, float b){
	float temp = abs(a-b)/(max_val-min_val);
	return temp*100;
}

ifstream fin ("training_set.txt");
int N;
int a, b, c;

int sad_ar[1000000];
int sad_br[1000000];
int sad_cr[1000000];
int happy_ar[1000000];
int happy_br[1000000];
int happy_cr[1000000];

//int happy[1000];
//int sad[1000];
int k1 = 0;
int k2 = 0;

int main(){

	int no_samples = 1000000;
	string S;
	for (int i = 0; i < no_samples; i++){
		
		fin >> N >> S;
		
		if (i<100) continue; //avoid taking the first 100 numbers 

		set_val(N, a, b, c);
		
		if (S == "np"){
			sad_ar[k1] = a;
			sad_br[k1] = b;
			sad_cr[k1] = c;
			k1++;
		}
		else if (S == "p"){
			happy_ar[k2] = a;
			happy_br[k2] = b;
			happy_cr[k2] = c;
			k2++;
		}
		//cout << a << b << c << endl;
	}
	float ha_avg = 0;
	float hb_avg = 0;
	float hc_avg = 0;
	
	for (int i = 0; i < k2; i++){
		ha_avg += happy_ar[i];
	}
	ha_avg = ha_avg / k2;
	
	for (int i = 0; i < k2; i++){
		hb_avg += happy_br[i];
	}

	hb_avg = hb_avg / k2;
	
	for (int i = 0; i < k2; i++){
		hc_avg += happy_cr[i];
	}
	hc_avg = hc_avg / k2;

	float sa_avg = 0;
	float sb_avg = 0;
	float sc_avg = 0;
	for (int i = 0; i < k1; i++){
		sa_avg += sad_ar[i];
	}
	sa_avg = sa_avg / k1;

	for (int i = 0; i < k1; i++){
		sb_avg += sad_br[i];
	}

	sb_avg = sb_avg / k1;

	for (int i = 0; i < k1; i++){
		sc_avg += sad_cr[i];
	}
	sc_avg = sc_avg / k1;

	cout << "\ncluster center - p    ="<< ha_avg << " " << hb_avg << " " << hc_avg << endl;
	cout << "cluster center - np   =" << sa_avg << " " << sb_avg << " " << sc_avg << endl << endl;
	
	cout << fit_parameter(mina,maxa,ha_avg,sa_avg) << endl;
	cout << fit_parameter(minb,maxb,hb_avg,sb_avg) << endl;
	cout << fit_parameter(minc,maxc,hc_avg,sc_avg) << endl;
	
	//for (int i=0; )

	float X = ha_avg - sa_avg;
	float Y = hb_avg - sb_avg;
	float Z = hc_avg - sc_avg;

	float l = (ha_avg + sa_avg) / 2.0;
	float m = (hb_avg + sb_avg) / 2.0;
	float n = (hc_avg + sc_avg) / 2.0;

	float d = X*l*1.0 + Y*m*1.0 + Z*n*1.0;

	//cout << X << " " << Y << " " << Z << " " << d << endl;

	while (true){
		int VALUE, A_VALUE, B_VALUE, C_VALUE;
		cin >> VALUE;
		set_val(VALUE, A_VALUE, B_VALUE, C_VALUE);
		
		float compa = A_VALUE*X*1.0 + B_VALUE*Y*1.0 + C_VALUE*Z*1.0 - d;

		if (compa > 0 /*&& VALUE % 2 != 0*/){
			cout << "p" << endl << endl;
		}
		else{
			cout << "np" << endl << endl;
		}
	}
	system("pause");
	return 0;

}
