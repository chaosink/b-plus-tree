#ifndef BUFFER_MANAGER_HPP
#define BUFFER_MANAGER_HPP

#include <string>

#define BLOCK_SIZE 61 //4096
#define DEFAULT_BLOCK_NUM 10
#define MAX_TIME 2147483647

struct BlockInfo {
	std::string file_name;
	int file_block_num;
	long time;
	bool is_modified;
	bool is_pined;
};

class BufferManager {
	int block_num_;
	char (*block_)[BLOCK_SIZE];
	BlockInfo *block_info_;
	void ReadFileBlock(std::string file_name, int file_block_num, int block_num);
	void WriteFileBlock(std::string file_name, int file_block_num, int block_num);
	int GetAnAvailableBufferBlock();
public:
	BufferManager();
	~BufferManager();
	void Init();
	void Init(int block_num);
	char *GetFileBlock(std::string file_name, int file_block_num);
	void DeleteBlock(std::string file_name);
	void Terminate();
};

#endif // BUFFER_MANAGER_HPP
