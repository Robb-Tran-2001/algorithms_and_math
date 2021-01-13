#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <fstream>
#include "data.hpp"
#include <string>
#include <map>
#include <unordered_set>

class data_handler
{
	std::vector<data*>* data_array; //all data pre-split
	std::vector<data*>* training_data; 
	std::vector<data*>* test_data; 
	std::vector<data*>* validation_data;

	int num_classes;
	int feature_vector_size;
	std::map<uint8_t, int> class_map;

	const double TRAIN_SET_PERCENT = .75;
	const double TEST_SET_PERCENT = .20;
	const double VALIDATION_PERCENT = .05;

public:
	data_handler() {
		data_array = new std::vector<data*>();
		training_data = new std::vector<data*>();
		test_data = new std::vector<data*>();
		validation_data = new std::vector<data*>();
	};
	~data_handler() {
		delete[] data_array;
		delete[] training_data;
		delete[] test_data;
		delete[] validation_data;
	};

	void read_feature_vector(std::string path) {
		uint32_t header[4]; // Magic | Num images | row size | col size
		unsigned char bytes[4];
		FILE* f = fopen(path.c_str(), "r");
		if (f)
		{
			for (int i = 0; i < 2; i++)
			{
				if (fread(bytes, sizeof(bytes), 1, f)
				{
					header[i] = convert_to_little_endian(bytes);
				}
			}
			printf("Done getting input file header\n");
			int image_size = header[2] * header[3];
			for (int i = 0; i < header[1]; i++)
			{
				data* d = new data();
				uint8_t element[1];
				for (int j = 0; j < image_size; i++) 
				{
					if (fread(element, sizeof(element), 1, f)) {
						d->append_to_feature_vector(element[0]);
					}
					else {
						printf("Error reading from file\n");
						exit(1);
					}
				}
				data_array->emplace_back(d);
			}
			printf("Read and store feature vectors.\n");
		}
		else {
			printf("Couldn't find file\n");
			exit(1);
		}
	};

	void read_feature_labels(std::string path) {
		uint32_t header[2]; // Magic | Num items
		unsigned char bytes[4];
		FILE* f = fopen(path.c_str(), "r");
		if (f)
		{
			for (int i = 0; i < 4; i++)
			{
				if (fread(bytes, sizeof(bytes), 1, f)
				{
					header[i] = convert_to_little_endian(bytes);
				}
			}
			printf("Done getting label file header\n");
			for (int i = 0; i < header[1]; i++)
			{
				uint8_t element[1];
				if (fread(element, sizeof(element), 1, f)) {
					data_array->at(i)->set_label(element[0]);
				}
				else {
					printf("Error reading from file\n");
					exit(1);
				}	
			}
			printf("Read and store labels.\n");
		}
		else {
			printf("Couldn't find file\n");
			exit(1);
		}
	};


	void split_data() {
		std::unordered_set<int> used_indices;
		int train_size = data_array->size() * TRAIN_SET_PERCENT;
		int test_size = data_array->size() * TEST_SET_PERCENT;
		int valid_size = data_array->size() * VALIDATION_PERCENT;

		//training data
		int count = 0;
		while (count < train_size)
		{
			int rand_index = rand() % data_array->size(); //0 to data array size - 1
			if (used_indices.find(rand_index) == used_indices.end())
			{
				training_data->push_back(data_array->at(rand_index));
				used_indices->insert(rand_index);
				++count;
			}
		}

		//test data
		int count = 0;
		while (count < train_size)
		{
			int rand_index = rand() % data_array->size(); //0 to data array size - 1
			if (used_indices.find(rand_index) == used_indices.end())
			{
				test_data->push_back(data_array->at(rand_index));
				used_indices->insert(rand_index);
				++count;
			}
		}

		//validation data
		int count = 0;
		while (count < train_size)
		{
			int rand_index = rand() % data_array->size(); //0 to data array size - 1
			if (used_indices.find(rand_index) == used_indices.end())
			{
				validation_data->push_back(data_array->at(rand_index));
				used_indices->insert(rand_index);
				++count;
			}
		}

		printf("Training data size: %lu\n", training_data->size());
		printf("Test data size: %lu\n", test_data->size());
		printf("Validation data size: %lu\n", validation_data->size());
	};

	void count_classes() {
		int count = 0;
		for (unsigned i = 0; i < data_array->size(); i++) {
			if (class_map.find(data_array->at(i)->get_label()) == class_map.end())
			{
				class_map[data_array->at(i)->get_label()] = count;
				data_array->at(i)->set_enum_label(count++);
			}
		}
		num_classes = count;
		printf("Extracted %d Classes", num_classes);
	};

	uint32_t convert_to_little_endian(const unsigned char* bytes) {
		return static_cast<uint32_t> ((bytes[0] << 24) | (bytes[1] << 16) |
			(bytes[2] << 8) | (bytes[3]));
	};

	std::vector<data*>* get_training_data() {
		return training_data;
	};

	std::vector<data*>* get_test_data() {
		return test_data;
	};

	std::vector<data*>* get_validation_data() {
		return validation_data;
	};
};

#endif // !__DATA_HANDLER_H