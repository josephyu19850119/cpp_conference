#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <map>
#include <iostream>

using namespace boost::interprocess;

typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> ipc_string_mgr;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, ipc_string_mgr> ipc_string;

typedef boost::interprocess::allocator<ipc_string, boost::interprocess::managed_shared_memory::segment_manager> ipc_vector_string_mgr;
typedef boost::interprocess::vector<ipc_string, ipc_vector_string_mgr> ipc_vector_string;

typedef boost::interprocess::allocator<std::pair<const ipc_string, int>, boost::interprocess::managed_shared_memory::segment_manager> ipc_string2int_mgr;
typedef boost::interprocess::map<ipc_string, int, std::less<ipc_string>, ipc_string2int_mgr> ipc_string2int;

typedef boost::interprocess::allocator<std::pair<const ipc_string, ipc_vector_string>, boost::interprocess::managed_shared_memory::segment_manager> ipc_string_2_strings_mgr;
typedef boost::interprocess::map<ipc_string, ipc_vector_string, std::less<ipc_string>, ipc_string_2_strings_mgr> ipc_string_2_strings;

typedef boost::interprocess::allocator<std::pair<const ipc_string, double>, boost::interprocess::managed_shared_memory::segment_manager> ipc_string_2_double_mgr;
typedef boost::interprocess::map<ipc_string, double, std::less<ipc_string>, ipc_string_2_double_mgr> ipc_string_2_double;

template<typename T>
void print_str2strs(T str2strs)
{
	for (const auto& item : *str2strs)
	{
		std::cout << item.first << ": ";
		for (const auto& str : item.second)
		{
			std::cout << str << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;
}

template<typename T>
void print_string_2_double(T string_2_double)
{
	for (const auto& item : *string_2_double)
	{
		std::cout << item.first << ": " << item.second << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;
}

int main()
{
	boost::interprocess::shared_memory_object::remove("Boost");
	boost::interprocess::managed_shared_memory managed_shm{ boost::interprocess::open_or_create, "Boost", 1024 };

	ipc_string_2_strings* str2strs = managed_shm.find_or_construct<ipc_string_2_strings>("str2strs")(managed_shm.get_segment_manager());

	str2strs->find(ipc_string("guys", managed_shm.get_segment_manager()));

	auto inserted = str2strs->insert(std::make_pair(ipc_string("ladies", managed_shm.get_segment_manager()), ipc_vector_string(managed_shm.get_segment_manager())));
	print_str2strs(str2strs);

	(inserted.first)->second.push_back(ipc_string("Lucy Pinder", managed_shm.get_segment_manager()));
	print_str2strs(str2strs);

	(inserted.first)->second.push_back(ipc_string("Kelly Brook", managed_shm.get_segment_manager()));
	print_str2strs(str2strs);

	inserted = str2strs->insert(std::make_pair(ipc_string("girls", managed_shm.get_segment_manager()), ipc_vector_string(managed_shm.get_segment_manager())));
	print_str2strs(str2strs);

	(inserted.first)->second.push_back(ipc_string("Choi Somi", managed_shm.get_segment_manager()));
	print_str2strs(str2strs);

	(inserted.first)->second.push_back(ipc_string("Demi Rose", managed_shm.get_segment_manager()));
	print_str2strs(str2strs);

	inserted = str2strs->insert(std::make_pair(ipc_string("guys", managed_shm.get_segment_manager()), ipc_vector_string(managed_shm.get_segment_manager())));
	print_str2strs(str2strs);


	ipc_string_2_double* str2double = managed_shm.find_or_construct<ipc_string_2_double>("str2double")(managed_shm.get_segment_manager());

	(*str2double)[ipc_string("pi", managed_shm.get_segment_manager())] = 3.14;
	(*str2double)[ipc_string("e", managed_shm.get_segment_manager())] = 2.6;
	(*str2double)[ipc_string("golden", managed_shm.get_segment_manager())] = 0.618;
	return 0;
}