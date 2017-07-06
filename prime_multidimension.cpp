#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin ("training_set.txt");

float value_of_pos (int dimensions, float* norm, float* input, float d){ //returns a positive or negative number depending on the side of the surface
	float value=0;
	for (int i=0; i<dimensions; i++){
		value += ( *(norm+i) * (*(input+i) ));
	}
	value -= d;
	return value;
}

void set_val(int N, float& a, float& b, float& c){  //feature setting
	a = (N-1) % 6; 
	b = (N+1) % 6;
	c = N % 5;
}

const int dimensions = 3;
const int max_number_per_cluster = 1000000; //guess
int N;
string S;

float p_points [dimensions][max_number_per_cluster];
float np_points [dimensions][max_number_per_cluster];
float p_cluster_center [dimensions];
float np_cluster_center [dimensions];
int p_count, np_count;

int main(){
	
	int no_samples = 1000000;
	
	for (int i=0; i<no_samples; i++){
		
		fin >> N >> S;
		if (S == "p"){
			set_val(N, p_points[0][p_count], p_points[1][p_count], p_points[2][p_count] );
			p_count++;
		}else if (S == "np"){
			set_val(N, np_points[0][np_count], np_points[1][np_count], np_points[2][np_count] );
			np_count++;
		}
	}
	
	// p cluster center calculation
	for (int i=0; i<dimensions; i++){
		for (int j=0; j<p_count; j++){
			p_cluster_center[i] += (float) p_points[i][j];
		}
		p_cluster_center[i] /= (p_count);
	}
	
	//np cluster center calculation
	for (int i=0; i<dimensions; i++){
		for (int j=0; j<np_count; j++){
			np_cluster_center[i] += (float) np_points[i][j];
		}
		np_cluster_center[i] /= (np_count);
	}
	
	
	float norm [dimensions];
	float mid_point[dimensions];
	
	for (int i=0; i<dimensions; i++){
		norm[i] = p_cluster_center[i] - np_cluster_center[i];
		mid_point[i] = (p_cluster_center [i] + np_cluster_center[i]) / 2.0;
	}
	
	//calculation of the constant
	float constant=0;
	for (int i=0; i<dimensions; i++){
		constant += norm[i] * mid_point[i];
	}
	
	
	int number;
	float dim_vals [dimensions];
	while (true){
		cin >> number;
		set_val(number, dim_vals[0], dim_vals[1], dim_vals[2]);         //places to change when new dimensions are added
		float temp = value_of_pos(dimensions, norm, dim_vals, constant);
		if (temp > 0){
			cout << "p" << endl << endl;
		}else{
			cout << "np" << endl << endl;
		}
	}	
	
	//system ("pause");
	return 0;
}
