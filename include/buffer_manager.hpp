#pragma once

#include <string>
#include <fstream>
#include <sys/time.h>

namespace bpt {

const int BLOCK_SIZE = 4096;

namespace bm {

const int DEFAULT_BLOCK_NUM = 2; // at least 2
const long MAX_TIME = 9223372036854775807;

class BufferManager {
	struct BlockInfo {
		std::string file_name;
		int file_block_num;
		long time;
		bool modified;
		bool pined;
	};

	int block_num_;
	char (*block_)[BLOCK_SIZE];
	BlockInfo *block_info_;
	void ReadFileBlock(std::string file_name, int file_block_num, int block_num);
	void WriteFileBlock(std::string file_name, int file_block_num, int block_num);
	int GetAnAvailableBufferBlock();
public:
	void Init();
	void Init(int block_num);
	void Pin(char *block_address);
	void Unpin(char *block_address);
	char *GetFileBlock(std::string file_name, int file_block_num);
	void DeleteBlock(std::string file_name); // maybe useless here
	void Terminate();
};

/********** **********/

void BufferManager::Init() {
	Init(DEFAULT_BLOCK_NUM);
}

void BufferManager::Init(int block_num) {
	block_num_ = block_num;
	block_ = (char (*)[BLOCK_SIZE])new char[block_num_ * BLOCK_SIZE];
	block_info_ = new BlockInfo[block_num_];
	for(int i = 0; i < block_num_; i++)
		block_info_[i].time = 0;
}

char *BufferManager::GetFileBlock(std::string file_name, int file_block_num) {
	for(int i = 0; i < block_num_; i++)
		if(block_info_[i].file_name == file_name && block_info_[i].file_block_num == file_block_num) {
			struct timeval time;
			gettimeofday(&time, NULL);
			block_info_[i].time = time.tv_sec * 1000000 + time.tv_usec;
			return block_[i];
		}
	int block_num = GetAnAvailableBufferBlock();
	ReadFileBlock(file_name, file_block_num, block_num);
	return block_[block_num];
}

void BufferManager::Pin(char *block_address) {
	block_info_[(block_address - (char*)block_) / BLOCK_SIZE].pined = 1;
}

void BufferManager::Unpin(char *block_address) {
	block_info_[(block_address - (char*)block_) / BLOCK_SIZE].pined = 0;
}

int BufferManager::GetAnAvailableBufferBlock() {
	int block_num;
	long time = MAX_TIME;
	for(int i = 0; i < block_num_; i++)
		if(!block_info_[i].pined && block_info_[i].time < time) {
			time = block_info_[i].time;
			block_num = i;
		}
	if(block_info_[block_num].modified)
		WriteFileBlock(block_info_[block_num].file_name, block_info_[block_num].file_block_num, block_num);
	return block_num;
}

void BufferManager::ReadFileBlock(std::string file_name, int file_block_num, int block_num) {
	std::ifstream ifs((file_name).c_str());
	ifs.seekg(file_block_num * BLOCK_SIZE, ifs.beg);
	ifs.read(block_[block_num], BLOCK_SIZE);
	ifs.close();
	block_info_[block_num].file_name = file_name;
	block_info_[block_num].file_block_num = file_block_num;
	struct timeval time;
	gettimeofday(&time, NULL);
	block_info_[block_num].time = time.tv_sec * 1000000 + time.tv_usec;
	block_info_[block_num].modified = 1;
	block_info_[block_num].pined = 0;
}

void BufferManager::WriteFileBlock(std::string file_name, int file_block_num, int block_num) {
	std::ofstream ofs((file_name).c_str(), std::ofstream::in | std::ofstream::out);
	ofs.seekp(file_block_num * BLOCK_SIZE, ofs.beg);
	ofs.write(block_[block_num], BLOCK_SIZE);
	ofs.close();
}

void BufferManager::DeleteBlock(std::string file_name) {
	for(int i = 0; i < block_num_; i++)
		if(block_info_[i].file_name == file_name)
			block_info_[i].file_name.clear();
}

void BufferManager::Terminate() {
	for(int i = 0; i < block_num_; i++)
		if(!block_info_[i].file_name.empty() && block_info_[i].modified)
			WriteFileBlock(block_info_[i].file_name, block_info_[i].file_block_num, i);
}

}
}
