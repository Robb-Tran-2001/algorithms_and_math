#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

class data
{
	std::vector<uint8_t>* feature_vector;
	uint8_t label;
	int enum_label; //A --> 1, B --> 2

public:
	data() {
		feature_vector = new std::vector<uint8_t> * ();
	};

	~data() {
	};
	void set_feature_vector(std::vector<uint8_t>* vect) {
		feature_vector = vect;
	};

	void append_to_feature_vector(uint8_t val) {
		feature_vector->emplace_back(val);
	};

	void set_label(uint8_t val) {
		label = val;
	};

	void set_enum_label(int val) {
		enum_label = val;
	};

	int get_feature_vector_size() {
		return feature_vector->size();
	};

	uint8_t get_label() {
		return label;
	};

	uint8_t get_enum_label() {
		return enum_label;
	};

	std::vector<uint8_t>* get_feature_vector() {
		return feature_vector;
	};
};

#endif // !__DATA_H
