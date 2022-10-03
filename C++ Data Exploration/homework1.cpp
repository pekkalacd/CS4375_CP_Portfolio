<<<<<<< HEAD
// preprocessing directives
#include <iostream>  // cout, cin, endl
#include <fstream>   // ifstream
#include <string>    // getline
#include <vector>    // vector
#include <array>     // array
#include <algorithm> // sort
#include <math.h>      // sqrt, pow

#define MAX_LEN 1000

// std:: 
using namespace std;

void debug(vector<double> res) {
	cout << "Result " << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << i << " " << res[i] << endl;
	}
}

vector<double> copyVect(vector<double> col) {
	vector<double> cp;
	cp.assign(col.begin(), col.end());
	return cp;
}

// computes the sum of vector elements, returns as double
double sum(vector<double> col) {
	double s=0;
	for (double d : col)
		s += d;
	return s;
} // end of sum

// computes the mean of vector elements, returns as double
double mean(vector<double> col) {
	int N = col.size();
	return sum(col)/N;
} // end of mean

// computes the median of vector elements, returns as double
double median(vector<double> col) {
	vector<double> cp = copyVect(col);
	sort(cp.begin(), cp.end());
	int n=col.size();
	if(n%2==1) {
		return cp.at(n/2);
	}
	double l,r;
	l=cp.at((n/2)-1);
	r=cp.at(n/2);
	return (l+r)/2;
} // end of median

// determines the minimum and maximum values in the input vector, returns as size 2 array of doubles
std::array<double,2> range(vector<double> col) {
	vector<double> cp = copyVect(col);
    sort(cp.begin(), cp.end());
    std::array<double,2> ans;
    ans[0] = (cp.at(0));
    ans[1] = (cp.at(cp.size()-1));
    return ans;
} // end of range

// computes the covariance between two input columns, returns as double
double covariance(vector<double> col1,vector<double> col2) {
	double mean1 = mean(col1);
	double mean2 = mean(col2);
	int N = col1.size();
	vector<double> t(N,0);
	double d1, d2;
	for (int i = 0; i < N; i++) {
		d1 = col1[i] - mean1;
		d2 = col2[i] - mean2;
		t[i] = d1*d2;
	}
	return sum(t) / (N-1);
}

// computes the standard deviation of a given input column, returns as double
double stdev(vector<double> col) {
	double mu = mean(col);
	int N = col.size();
	vector<double> t(N, 0);
	for (int i=0; i<N; i++)
		t[i] = pow(col[i] - mu, 2);
	return sqrt(mean(t));
}

// computes the correlation between two input columns
double correlation(vector<double> col1, vector<double> col2) {
	return covariance(col1,col2)/(stdev(col1)*stdev(col2));
}


void print_stats(vector<double> col, string title) {
	cout << title << endl;
	cout << "sum = " << sum(col) << endl;
	cout << "mean = " << mean(col) << endl;
	cout << "median = " << median(col) << endl;
	cout << "range = ";
	std::array<double,2> res;
	res = range(col);
	cout << "[" << res[0] << "," << res[1] << "]" << endl << endl << endl;
}


int main(int argc, char** argv) {

	ifstream infile;
	string line;
	string rm_in, medv_in;
	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);

	infile.open("Boston.csv");
	ofstream out("test_ex.csv");
	
	// if file fails -> end program
	if(!infile.is_open()) {
		cout << "could not open Boston.csv" << endl;
		return 1;
	}
	
	// otherwise, ifstream is modified
	// first row contains headers ~ set fp to second line 
	getline(infile,line);
	
	
	// read in each column value in csv format & fill vector
	int row=0;
	while(infile.good()) {
		
		getline(infile, rm_in, ',');
		getline(infile, medv_in, '\n');

		out << rm_in << "," << medv_in << "\n";

		rm.at(row) = stod(rm_in);
		medv.at(row) = stod(medv_in);
		
		row++;
	}
	
	// resize vectors to total number of rows
	rm.resize(row);
	medv.resize(row);
	
	// close file to Boston.csv
	infile.close();
	
	// computing sum, mean, median, range for each column
	print_stats(rm,"stats for rm");
	print_stats(medv,"stats for medv");
	
	// computing covariance and correlation for both
	double cov, corr;
	cov = covariance(rm,medv);
	corr = correlation(rm,medv);
	cout << "\ncovariance & correlation for both\n" << endl;
	cout << "covariance = " << cov << endl;
	cout << "correlation = " << corr << endl;


	return 0;
}
=======
// preprocessing directives
#include <iostream>  // cout, cin, endl
#include <fstream>   // ifstream
#include <string>    // getline
#include <vector>    // vector
#include <array>     // array
#include <algorithm> // sort
#include <math.h>      // sqrt, pow

#define MAX_LEN 1000

// std:: 
using namespace std;

void debug(vector<double> res) {
	cout << "Result " << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << i << " " << res[i] << endl;
	}
}

vector<double> copyVect(vector<double> col) {
	vector<double> cp;
	cp.assign(col.begin(), col.end());
	return cp;
}

// computes the sum of vector elements, returns as double
double sum(vector<double> col) {
	double s=0;
	for (double d : col)
		s += d;
	return s;
} // end of sum

// computes the mean of vector elements, returns as double
double mean(vector<double> col) {
	int N = col.size();
	return sum(col)/N;
} // end of mean

// computes the median of vector elements, returns as double
double median(vector<double> col) {
	vector<double> cp = copyVect(col);
	sort(cp.begin(), cp.end());
	int n=col.size();
	if(n%2==1) {
		return cp.at(n/2);
	}
	double l,r;
	l=cp.at((n/2)-1);
	r=cp.at(n/2);
	return (l+r)/2;
} // end of median

// determines the minimum and maximum values in the input vector, returns as size 2 array of doubles
std::array<double,2> range(vector<double> col) {
	vector<double> cp = copyVect(col);
    sort(cp.begin(), cp.end());
    std::array<double,2> ans;
    ans[0] = (cp.at(0));
    ans[1] = (cp.at(cp.size()-1));
    return ans;
} // end of range

// computes the covariance between two input columns, returns as double
double covariance(vector<double> col1,vector<double> col2) {
	double mean1 = mean(col1);
	double mean2 = mean(col2);
	int N = col1.size();
	vector<double> t(N,0);
	double d1, d2;
	for (int i = 0; i < N; i++) {
		d1 = col1[i] - mean1;
		d2 = col2[i] - mean2;
		t[i] = d1*d2;
	}
	return sum(t) / (N-1);
}

// computes the standard deviation of a given input column, returns as double
double stdev(vector<double> col) {
	double mu = mean(col);
	int N = col.size();
	vector<double> t(N, 0);
	for (int i=0; i<N; i++)
		t[i] = pow(col[i] - mu, 2);
	return sqrt(mean(t));
}

// computes the correlation between two input columns
double correlation(vector<double> col1, vector<double> col2) {
	return covariance(col1,col2)/(stdev(col1)*stdev(col2));
}


void print_stats(vector<double> col, string title) {
	cout << title << endl;
	cout << "sum = " << sum(col) << endl;
	cout << "mean = " << mean(col) << endl;
	cout << "median = " << median(col) << endl;
	cout << "range = ";
	std::array<double,2> res;
	res = range(col);
	cout << "[" << res[0] << "," << res[1] << "]" << endl << endl << endl;
}


int main(int argc, char** argv) {

	ifstream infile;
	string line;
	string rm_in, medv_in;
	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);

	infile.open("Boston.csv");
	ofstream out("test_ex.csv");
	
	// if file fails -> end program
	if(!infile.is_open()) {
		cout << "could not open Boston.csv" << endl;
		return 1;
	}
	
	// otherwise, ifstream is modified
	// first row contains headers ~ set fp to second line 
	getline(infile,line);
	
	
	// read in each column value in csv format & fill vector
	int row=0;
	while(infile.good()) {
		
		getline(infile, rm_in, ',');
		getline(infile, medv_in, '\n');

		out << rm_in << "," << medv_in << "\n";

		rm.at(row) = stod(rm_in);
		medv.at(row) = stod(medv_in);
		
		row++;
	}
	
	// resize vectors to total number of rows
	rm.resize(row);
	medv.resize(row);
	
	// close file to Boston.csv
	infile.close();
	
	// computing sum, mean, median, range for each column
	print_stats(rm,"stats for rm");
	print_stats(medv,"stats for medv");
	
	// computing covariance and correlation for both
	double cov, corr;
	cov = covariance(rm,medv);
	corr = correlation(rm,medv);
	cout << "\ncovariance & correlation for both\n" << endl;
	cout << "covariance = " << cov << endl;
	cout << "correlation = " << corr << endl;


	return 0;
}
>>>>>>> 2933f282301f70e6f63b065cd7a27d1423a3eea7
