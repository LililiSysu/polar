/*****************************************************************//**
 * \file   polar.h
 * \brief  polar coding class is here
 * 
 * \author lilili
 * \date   June 2022
 *********************************************************************/

#pragma once
#include<vector>
using namespace std;

class polar{
	static const unsigned short crc_table[256];

private:
	// private member

	int n;						// number of layer in polar code
	int N;						// number of bit (or channel) in polar code

	vector<int> u;				// the vector of information bit to encode, with size less than 2^n

	vector<int> v;				// the vector of encoding result, with size equals 2^n
	vector<int> v_sys;			// the vector of systematic encoding result, with size equals 2^n

	bool SNR_is_set;			// whether 'SNR' has set
	double SNR;					// Signal Noise Ratio in dB, that is Eb / N0 where Eb = 1, N0 = 2 * sigma^2
	double sigma;				// sigma value of Gaussian noise
	vector<double> received_v;	// 'v' after BPSK modulation in AWGN channel
	vector<int> decoded_u;		// the not freezed value of 'decoded_eu' after sorting by 'sorted_channel_ind'
	
	bool list_num_is_set;		// whether 'list_num' has set
	int list_num;				// number of path for list decoding

	bool rate_is_set;			// whether 'rate' is set
	double rate;				// rate of polar code, that is size of 'u' over 'N'

	int total_bit;				// number of information bit for error rate compute
	int total_SC_error_bit;		// number of error information bit for SC decode
	int total_fast_SC_error_bit;// number of error information bit for fast SC decode
	int total_SCL2_error_bit;	// number of error information bit for SCL deocde with list_num 2
	int total_SCL4_error_bit;	// number of error information bit for SCL deocde with list_num 4
	int total_SCL8_error_bit;	// number of error information bit for SCL deocde with list_num 8
	int total_SCL16_error_bit;	// number of error information bit for SCL deocde with list_num 16
	int total_SCL32_error_bit;	// number of error information bit for SCL deocde with list_num 32
	int total_SCL_error_bit;	// number of error information bit for SCL deocde with list_num not the above
	int total_fast_SCL_error_bit;// number of error information bit for SCL deocde with list_num not the above

	bool is_CRC16_aided;		// whether use CRC16 for polar code
	bool is_SCL_decode_failed;	// whether SCL decode failed
	int SCL_decode_failed_time;	// times of SCL decode failed
	int SCL_decode_failed_bit;	// number of bit cast due to SCL decode failed	
	bool use_adaptive_L;		// whether change L adaptively, see 'adaptive_fast_SCL_decode()'


	// private auxiliary member

	vector<pair<int, double>> sorted_channel_ind_ZWi;	// the vector to hold pair of index of ordered channel and its ZW value
	
	vector<double> LLR;									// the Log Likelilhood Ratio for each channel
	vector<int> active_channel_sum;						// the i^th element is the active channel number between index 0 and i-1
	vector<int> decoded_v_tmp;							// the v decoded from LLR (fast SC decode)
	vector<int> decoded_eu;								// the decoded result of 'received_v'

	vector<pair<int,double>> decoded_list_PM;			// the list of pair list index and decoded Path Metric, activate till size of list_num
	vector<vector<double>> decoded_list_LLR;			// list of decoded LLR, row equals 'list_num' should be configured first
	vector<vector<int>> decoded_list_eu;				// same as 'decoded_eu', but information bit stored in decoded_list_path
	vector<bool> occupied;								// whether the index of list occupied
	vector<bool> is_done;								// another indicator for list occupied

	double time_key_routine;							// time consume for key routine

	// private member function

	/**
	 * .default constructor function
	 *
	 */
	polar();

	/**
	 * .generate the vector to hold pair of index of ordered channel and its ZW value, changing 'sorted_channel_ind_ZWi'
	 *
	 */
	void generate_BEC_ZWi();

	/**
	 * .reverse bit order
	 *
	 * \param a:	number to solve
	 * \return		bit reverse of a
	 */
	int bit_revorder(int a);

	/**
	  * .polar encoding in recursive way, changing 'v'
	  *
	  * \param start_ind:	the start index of vector 'v' being processed in this recursion
	  * \param end_ind:		the end index of vector 'v' being processed in this recursion
	 */
	void encode_recur(int start_ind, int end_ind);

	/**
	  * .polar encoding in recursive way, changing 'v_sys'
	  *
	  * \param start_ind:	the start index of vector 'v_sys' being processed in this recursion
	  * \param end_ind:		the end index of vector 'v_sys' being processed in this recursion
	 */
	void encode_systematic_recur(int start_ind, int end_ind);

	/**
	 * .compute the upper part LLR in the former layer of polar code
	 * 
	 * \param L1:	the first LLR
	 * \param L2:	the second LLR
	 * \return		the result LLR
	 */
	inline double f(double L1, double L2);

	/**
	 * .compute the lower part LLR in the former layer of polar code
	 * 
	 * \param u:	the upper part encoded bit
	 * \param L1:	the upper in this layer LLR
	 * \param L2:	the lower in this layer LLR
	 * \return		the result LLR
	 */
	inline double g(int u, double L1, double L2);

	/**
	 * .get the minimum absolute value of x and y
	 * 
	 * \param x:	the first input value
	 * \param y:	the second input value
	 * \return		result as stated
	 */
	inline double min_abs(double x, double y);

	/**
	 * .a simple two channel polar decode function, input as 'received_v', output as 'decode_u'
	 *
	 */
	void two_channel_decode();

	/**
	 * .print 'decoded_eu', cannot access now because in private member
	 * 
	 */
	void print_decoded_eu();

	/**
	 * .decode polar code recursively, input as 'active_channel_sum', 'LLR', output as 'decoded_eu'
	 * changing 'LLR' and 'decoded_eu'
	 * 
	 * \param LLR_start_ind:	start index of the part of LLR to decode
	 * \param LLR_end_ind:		end index of the part of LLR to decode
	 */
	void SC_decode_recur(int LLR_start_ind, int LLR_end_ind);

	/**
	 * .decode polar code recursively in a fast method, input as 'active_channel_sum', 'LLR', 
	 * output as 'decoded_eu', changing 'LLR' and 'decoded_eu'
	 * 
	 * \param LLR_start_ind:	start index of the part of LLR to decode
	 * \param LLR_end_ind:		end index of the part of LLR to decode
	 */
	void fast_SC_decode_recur(int LLR_start_ind, int LLR_end_ind);

	/**
	 * .polar encoding in recursive way, changing 'decoded_v_tmp'
	 * 
	 * \param start_ind:	the start index of vector 'decoded_v_tmp' being processed in this recursion
	 * \param end_ind:		the end index of vector 'decoded_v_tmp' being processed in this recursion
	 */
	void encode_recur_for_dv(int start_ind, int end_ind);

	/**
	 * .compute the absolute value
	 * 
	 * \param x:	number to solve
	 * \return		absolute value of 'x'
	 */
	inline double abs(double x);

	/**
	 * .list decode polar code recursively, input as 'active_channel_sum', 'decoded_list_LLR',
	 * 'decoded_list_eu', 'decoded_list_PM', output as 'decoded_eu'. not using lazy copy !!
	 *
	 * \param LLR_start_ind:	start index of the part of LLR to decode
	 * \param LLR_end_ind:		end index of the part of LLR to decode
	 */
	void SCL_decode_recur(int LLR_start_ind, int LLR_end_ind);

	/**
	 * .use LLR to store fixed received bit LLR to save copying bit
	 * 
	 */
	void SCL_decode_recur_father();

	/**
	 * .fast list decode polar code recursively, only deal with R0 and REP case
	 *  input as 'active_channel_sum', 'decoded_list_LLR','decoded_list_eu', 
	 * 'decoded_list_PM', output as 'decoded_eu'. not using lazy copy !!
	 * 
	 * \param LLR_start_ind
	 * \param LLR_end_ind
	 */
	void fast_SCL_decode_recur(int LLR_start_ind, int LLR_end_ind);

	/**
	 * .use LLR to store fixed received bit LLR to save copying bit
	 *
	 */
	void fast_SCL_decode_recur_father();

public:
	// public constructor and destructor

	/**
	 * .construct with number of layer in polar code
	 * 
	 * \param _n:	number of layer in polar code, greater than 0
	 */
	polar(int _n);

	/**
	 * .construct with number of layer in polar code and the vector of information bit to encode, with size less than 2^n
	 * 
	 * \param _n:	number of layer in polar code, greater than 0
	 * \param _u:	the vector of information bit to encode, with size less than 2^n
	 */
	polar(int _n, const vector<int>& _u);

	// public member function

	/**
	 * .polar encode function, non-systematically, 'u' as input, changing 'v'
	 *
	 */
	void encode();

	/**
	 * .polar encode function, systematically, 'u' as input, changing 'v_sys'
	 *
	 */
	void encode_systematic();

	/**
	 * .change the vector of information bit to encode, 'v' and 'v_sys' is cleared
	 * 
	 * \param new_u:	the new vector, with size less than 2^n,
	 */
	void set_u(const vector<int>& new_u);

	/**
	 * .print vector 'u'
	 * 
	 */
	void print_u();

	/**
	 * .print vector 'v'
	 *
	 */
	void print_v();

	/**
	 * .print vector 'v_sys'
	 *
	 */
	void print_v_sys();

	/**
	 * .changing 'SNR' and 'sigma'
	 * 
	 * \param _SNR:	the value to set SNR in dB
	 */
	void set_SNR(double _SNR);

	/**
	 * .input as 'v', changing 'received_v' using BPSK modulation, 0 -> 1 and 1 -> -1
	 *
	 */
	void modulation();

	/**
	 * .according to parameter 'sigma' to add Gaussian noise to 'received_v',
	 * should after modulation and set SNR!!
	 *
	 */
	void add_noise();

	/**
	 * .let the polar code pass the channel, input as 'v', output as 'received_v', should set SNR first !!
	 * 
	 */
	void pass_channel();

	/**
	 * .SC decoding of polar code, input as 'received_v', 'sigma' and output as 'decoded_u'
	 * 
	 */
	void SC_decode();

	/**
	 * .print 'decoded_u'
	 * 
	 */
	void print_decoded_u();

	/**
	 * .fast SC decoding of polar code, input as 'received_v', 'sigma' and output as 'decoded_u'
	 * 
	 */
	void fast_SC_decode();

	/**
	 * .set the list number for list decode
	 * 
	 * \param _list_num:	the list number
	 */
	void set_list_num(int _list_num);

	/**
	 * .SC List decoding of polar code, input as 'received_v', 'sigma' and output as 'decoded_u'
	 * 
	 */
	void SCL_decode();

	/**
	 * .set 'rate' for polar code
	 * 
	 * \param _rate:	number to set
	 */
	void set_rate(double _rate);

	/**
	 * .randomly generete 'u' in {0,1}, 'rate' should be set first
	 * 
	 */
	void generate_random_u();

	/**
	 * .count how many bit transmitted, result stored in 'total_bit'
	 * 
	 */
	void information_bit_count();

	/**
	 * .count number of SC decode error bit, result stored in 'total_SC_error_bit'
	 * 
	 */
	void SC_error_count();

	/**
	 * .count number of fast SC decode error bit, result stored in 'total_fast_SC_error_bit'
	 * 
	 */
	void fast_SC_error_count();

	/**
	 * .count number of SCL decode error bit, result stored in 'total_SCL_error_bit'
	 * 
	 */
	void SCL_error_count();

	/**
	 * .
	 * 
	 * \return SC error rate, that is 'total_SC_error_bit' over 'total_bit'
	 */
	double SC_error_rate();

	/**
	 * .
	 * 
	 * \return fast SC error rate, that is 'fast_total_SC_error_bit' over 'total_bit'
	 */
	double fast_SC_error_rate();
	
	/**
	 * .
	 * 
	 * \return SCL error rate, that is 'total_SCL_error_bit' over 'total_bit'
	 */
	double SCL_error_rate();

	/**
	 * .clean error bit count for the next simulation
	 * 
	 */
	void clear_error_count();

	/**
	 * .
	 * 
	 * \param _is_CRC16_aided: true means set list decoding CRC16 aided
	 */
	void set_is_CRC16_aided(bool _is_CRC16_aided);

	/**
	 * .
	 * 
	 * \return crc16 bit for 'u'
	 */
	unsigned short u_crc16();

	/**
	 * .put crc16 at back of 'u'
	 * 
	 */
	void u_append_crc16();

	/**
	 * .remove the last 16 bit for 'u'
	 * 
	 */
	void u_remove_crc16();

	/**
	 * .
	 * 
	 * \return the last 16 bit in 'decoded_u'
	 */
	unsigned short du_get_crc16();

	/**
	 * .remove the last 16 bit for 'decoded_u'
	 * 
	 */
	void du_remove_crc16();

	/**
	 * .
	 * 
	 * \return crc16 value for 'decoded_u'
	 */
	unsigned short du_crc16();

	/**
	 * .append 16 bit at the end of 'decoded_u'
	 * 
	 * \param us: bits to append
	 */
	void du_append_us(unsigned short us);

	/**
	 * .
	 * 
	 * \return whether 'decoded_u' satisfied condition of CRC16
	 */
	bool is_du_satisfied_crc16();

	/**
	 * .
	 * 
	 * \return 'time_key_routine'
	 */
	double get_time_key_routine();

	/**
	 * .fast SC List decoding of polar code, input as 'received_v', 'sigma' and output as 'decoded_u'
	 *
	 */
	void fast_SCL_decode();

	/**
	 * .count number of fast SCL decode error bit, result stored in 'total_fast_SCL_error_bit'
	 *
	 */
	void fast_SCL_error_count();

	/**
	 * .
	 *
	 * \return SCL error rate, that is 'total_fast_SCL_error_bit' over 'total_bit'
	 */
	double fast_SCL_error_rate();

	/**
	 * .adaptively increase parameter L as 1,2,4,8,16,32 until 
	 * decode correction, if not at L 32, let the result be
	 * with minimum path metric
	 * 
	 */
	void adaptive_fast_SCL_decode();
};
