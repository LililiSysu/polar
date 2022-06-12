/*****************************************************************//**
 * \file   main.cpp
 * \brief  sample app of polar class
 * 
 * \author lilili
 * \date   June 2022
 *********************************************************************/

#include<stdio.h>
#include<vector>
#include<random>
#include<ctime>
using namespace std;

#include"polar.h"

void count_running_time(int start_n = 6, int end_n = 10, \
	double _rate = 0.5, int _list_num = 8, int _round = 100);

void test_error_rate(double start_SNR = 1, double end_SNR = 2.5, double SNR_step = 0.25, \
	int n = 10, double rate = 0.5, vector<int> list_num = { 2,4,8,16,32 }, int _round = 20, \
	bool is_CRC16_aided = true);

void test_error_rate2(vector<double> SNR = { 1,1.25,1.5,1.75,2,2.25,2.5 }, \
	int n = 10, double rate = 0.5, vector<int> list_num = { 2,4,8,16,32 }, \
	vector<int> _round = { 0,0,0,0,0,20000,0 }, bool is_CRC16_aided = true);

int main()
{
	//count_running_time();
	test_error_rate2();

	return 0;
}

void count_running_time(int start_n, int end_n, double _rate, int _list_num, int _round) {
	
	printf("\n<--- time consume verse N in one simulation, rate=%f, list_num=%d --->\n", _rate, _list_num);

	printf("N = [ ");
	vector<polar> p;
	for (int i = start_n; i <= end_n; ++i) {
		p.push_back(polar(i));
		p.back().set_rate(_rate);
		p.back().set_SNR(1);				// has no effect to counting running time
		p.back().set_list_num(_list_num);
		//p.back().set_is_CRC16_aided(true);
		if (i != end_n)
			printf("%d, ", 1<<i);
		else
			printf("%d ", 1<<i);
	}
	printf("]\n");

	int plen = p.size();
	clock_t start, end;
	/*
	printf("generate_random_u = [ ");
	for (int j = 0; j < plen; ++j) {
		start = clock();		// starting time
		for (int i = 0; i < _round; ++i) {
			p[j].generate_random_u();
		}
		end = clock();
		if(j!=plen-1)
			printf("%e, ", double(end - start) / CLOCKS_PER_SEC / _round);
		else
			printf("%e ", double(end - start) / CLOCKS_PER_SEC / _round);
	}
	printf("]\n");

	printf("encode = [ ");
	for (int j = 0; j < plen; ++j) {
		start = clock();		// starting time
		for (int i = 0; i < _round; ++i) {
			p[j].encode();
		}
		end = clock();
		if (j != plen - 1)
			printf("%e, ", double(end - start) / CLOCKS_PER_SEC / _round);
		else
			printf("%e ", double(end - start) / CLOCKS_PER_SEC / _round);
	}
	printf("]\n");

	printf("pass_channel = [ ");
	for (int j = 0; j < plen; ++j) {
		start = clock();		// starting time
		for (int i = 0; i < _round; ++i) {
			p[j].pass_channel();
		}
		end = clock();
		if (j != plen - 1)
			printf("%e, ", double(end - start) / CLOCKS_PER_SEC / _round);
		else
			printf("%e ", double(end - start) / CLOCKS_PER_SEC / _round);
	}
	printf("]\n");

	printf("SC_decode = [ ");
	for (int j = 0; j < plen; ++j) {
		start = clock();		// starting time
		for (int i = 0; i < _round; ++i) {
			p[j].SC_decode();
		}
		end = clock();
		if (j != plen - 1)
			printf("%e, ", double(end - start) / CLOCKS_PER_SEC / _round);
		else
			printf("%e ", double(end - start) / CLOCKS_PER_SEC / _round);
	}
	printf("]\n");

	printf("fast_SC_decode = [ ");
	for (int j = 0; j < plen; ++j) {
		start = clock();		// starting time
		for (int i = 0; i < _round; ++i) {
			p[j].fast_SC_decode();
		}
		end = clock();
		if (j != plen - 1)
			printf("%e, ", double(end - start) / CLOCKS_PER_SEC / _round);
		else
			printf("%e ", double(end - start) / CLOCKS_PER_SEC / _round);
	}
	printf("]\n");
	*/

	// just test SCL deocde
	for (int j = 0; j < plen; ++j) {
		p[j].generate_random_u();
		p[j].encode();
		p[j].pass_channel();
	}
	printf("fast_SCL_decode = [ ");
	for (int j = 0; j < plen; ++j) {
		start = clock();		// starting time
		for (int i = 0; i < _round; ++i) {
			p[j].fast_SCL_decode();
		}
		end = clock();
		if (j != plen - 1)
			//printf("%e(%e), ", double(end - start) / CLOCKS_PER_SEC / _round, p[j].get_time_key_routine() / _round);
			printf("%e, ", double(end - start) / CLOCKS_PER_SEC / _round);
		else
			//printf("%e(%e) ", double(end - start) / CLOCKS_PER_SEC / _round, p[j].get_time_key_routine() / _round);
			printf("%e ", double(end - start) / CLOCKS_PER_SEC / _round);
	}
	printf("]\n");
}

void test_error_rate(double start_SNR, double end_SNR, double SNR_step, \
	int n, double rate, vector<int> list_num, int _round, bool is_CRC16_aided){

	polar q(n);
	q.set_rate(rate);
	q.set_is_CRC16_aided(is_CRC16_aided);
	int qlen = 1 + (int)round((end_SNR - start_SNR) / SNR_step);
	vector<double> fast_SC_error_rate;
	vector<vector<double>> fast_SCL_error_rate(list_num.size());
	for (int i = 0; i < qlen; ++i) {
		q.set_SNR(start_SNR + i * SNR_step);
		for (int j = 0; j < _round; ++j) {
			q.generate_random_u();
			q.encode();

			q.modulation();
			q.add_noise();
			//q.pass_channel();

			q.information_bit_count();

			//q.SC_decode();
			//q.SC_error_count();

			q.fast_SC_decode();
			q.fast_SC_error_count();
			
			for (unsigned int k = 0; k < list_num.size(); ++k) {
				q.set_list_num(list_num[k]);

				//q.SCL_decode();
				//q.SCL_error_count();

				q.fast_SCL_decode();
				q.fast_SCL_error_count();
			}/**/
		}
		//printf("SC_error_rate		: %e\n", q.SC_error_rate());

		fast_SC_error_rate.push_back(q.fast_SC_error_rate());
		for (unsigned int k = 0; k < list_num.size(); ++k) {
			q.set_list_num(list_num[k]);
			fast_SCL_error_rate[k].push_back(q.fast_SCL_error_rate());
		}
		q.clear_error_count();
	}

	printf("error rate verse SNR, N=%d, rate=%f\n", (1 << n), rate);

	printf("SNR = [ ");
	for (int i = 0; i < qlen-1; ++i) {
		printf("%f, ", start_SNR + i * SNR_step);
	}
	printf("%f", start_SNR + ((double)qlen - 1) * SNR_step);
	printf(" ]\n");

	printf("fast_SC_error_rate = [ ");
	for (int i = 0; i < qlen - 1; ++i) {
		printf("%e, ", fast_SC_error_rate[i]);
	}
	printf("%e", fast_SC_error_rate[qlen - 1]);
	printf(" ]\n");

	for (unsigned int k = 0; k < list_num.size(); ++k) {
		printf("fast_SCL%d_error_rate = [ ", list_num[k]);
		for (int i = 0; i < qlen - 1; ++i) {
			printf("%e, ", fast_SCL_error_rate[k][i]);
		}
		printf("%e", fast_SCL_error_rate[k][qlen - 1]);
		printf(" ]\n");
	}
	/**/
}

void test_error_rate2(vector<double> SNR, int n, double rate, vector<int> list_num, \
	vector<int> _round, bool is_CRC16_aided){

	polar q(n);
	q.set_rate(rate);
	q.set_is_CRC16_aided(is_CRC16_aided);
	int qlen = SNR.size();
	vector<double> fast_SC_error_rate;
	vector<vector<double>> fast_SCL_error_rate(list_num.size());
	for (int i = 0; i < qlen; ++i) {
		q.set_SNR(SNR[i]);
		if (_round[i] == 0){
			fast_SC_error_rate.push_back(0);
			for (unsigned int k = 0; k < list_num.size(); ++k) {
				q.set_list_num(list_num[k]);
				fast_SCL_error_rate[k].push_back(0);
			}
			q.clear_error_count();
			continue;
		}
		for (int j = 0; j < _round[i]; ++j) {
			q.generate_random_u();
			q.encode();

			q.modulation();
			q.add_noise();
			//q.pass_channel();

			q.information_bit_count();

			//q.SC_decode();
			//q.SC_error_count();

			q.fast_SC_decode();
			q.fast_SC_error_count();

			for (unsigned int k = 0; k < list_num.size(); ++k) {
				q.set_list_num(list_num[k]);

				//q.SCL_decode();
				//q.SCL_error_count();

				q.fast_SCL_decode();
				q.fast_SCL_error_count();
			}/**/
		}
		//printf("SC_error_rate		: %e\n", q.SC_error_rate());

		fast_SC_error_rate.push_back(q.fast_SC_error_rate());
		for (unsigned int k = 0; k < list_num.size(); ++k) {
			q.set_list_num(list_num[k]);
			fast_SCL_error_rate[k].push_back(q.fast_SCL_error_rate());
		}
		q.clear_error_count();
	}

	printf("error rate verse SNR, N=%d, rate=%f\n", (1 << n), rate);

	printf("SNR = [ ");
	for (int i = 0; i < qlen - 1; ++i) {
		printf("%f, ", SNR[i]);
	}
	printf("%f", SNR.back());
	printf(" ]\n");

	printf("fast_SC_error_rate = [ ");
	for (int i = 0; i < qlen - 1; ++i) {
		printf("%e, ", fast_SC_error_rate[i]);
	}
	printf("%e", fast_SC_error_rate[qlen - 1]);
	printf(" ]\n");

	for (unsigned int k = 0; k < list_num.size(); ++k) {
		printf("fast_SCL%d_error_rate = [ ", list_num[k]);
		for (int i = 0; i < qlen - 1; ++i) {
			printf("%e, ", fast_SCL_error_rate[k][i]);
		}
		printf("%e", fast_SCL_error_rate[k][qlen - 1]);
		printf(" ]\n");
	}
	/**/
}
