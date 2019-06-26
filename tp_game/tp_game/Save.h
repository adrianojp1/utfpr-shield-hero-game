#pragma once
class Save {
private:
	std::string _storaged_content;
public:
	Save();
	~Save();

	void clear_content();

	void add_content(std::string new_content, int key);
	void rm_content(std::string rm_content, int key);

	std::string get_content(std::string key);

	void recover_content();
	void record_content();
};

