#include "buffer_manager.hpp"
#include <fstream>
#include <sys/time.h>

BufferManager::BufferManager() {

}

BufferManager::~BufferManager() {

}

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
		if(block_info_[i].file_name == file_name && block_info_[i].file_block_num == file_block_num)
			return block_[i];
	int block_num = GetAnAvailableBufferBlock();
	ReadFileBlock(file_name, file_block_num, block_num);
	return block_[block_num];
}

int BufferManager::GetAnAvailableBufferBlock() {
	int block_num;
	long time = MAX_TIME;
	for(int i = 0; i < block_num_; i++)
		if(block_info_[i].time < time) {
			time = block_info_[i].time;
			block_num = i;
		}
	WriteFileBlock(block_info_[block_num].file_name, block_info_[block_num].file_block_num, block_num);
	return block_num;
}

void BufferManager::ReadFileBlock(std::string file_name, int file_block_num, int block_num) {
	std::ifstream input((file_name).c_str());
	input.seekg(file_block_num * BLOCK_SIZE, input.beg);
	input.read(block_[block_num], BLOCK_SIZE);
	input.close();
	block_info_[block_num].file_name = file_name;
	block_info_[block_num].file_block_num = file_block_num;
    struct timeval time;
    gettimeofday(&time, NULL);
    block_info_[block_num].time = time.tv_sec * 1000000 + time.tv_usec;
	block_info_[block_num].is_modified = 0;
	block_info_[block_num].is_pined = 0;
}

void BufferManager::WriteFileBlock(std::string file_name, int file_block_num, int block_num) {
	std::ofstream output((file_name).c_str(), std::ofstream::in | std::ofstream::out);
	output.seekp(file_block_num * BLOCK_SIZE, output.beg);
	output.write(block_[block_num], BLOCK_SIZE);
	output.close();
}

void BufferManager::DeleteBlock(std::string file_name) {
	for(int i = 0; i < block_num_; i++)
		if(block_info_[i].file_name == file_name)
			block_info_[i].file_name.clear();
}

void BufferManager::Terminate() {
	for(int i = 0; i < block_num_; i++)
		if(!block_info_[i].file_name.empty())
			WriteFileBlock(block_info_[i].file_name, block_info_[i].file_block_num, i);
}
