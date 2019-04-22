
#include <string>
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> ipc_string_mgr;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, ipc_string_mgr> ipc_string;

typedef boost::interprocess::allocator<ipc_string, boost::interprocess::managed_shared_memory::segment_manager> ipc_vector_string_mgr;
typedef boost::interprocess::vector<ipc_string, ipc_vector_string_mgr> ipc_vector_string;

template<typename T>
void print_strs(T strs)
{
	for (const auto& str : *strs)
	{
		std::cout << str << "\t";
	}
	std::cout << std::endl << "---------------------------------------------" << std::endl;
}

int main()
{
	boost::interprocess::managed_shared_memory managed_shm{ boost::interprocess::open_or_create, "ipc_demo", 4096 };
	ipc_vector_string* strs = managed_shm.find_or_construct<ipc_vector_string>("strs")(managed_shm.get_segment_manager());

	std::string str;
	while (std::getline(std::cin, str))
	{
		if (str == "q")
		{
			break;
		}
		else if (str == "Q")
		{
			boost::interprocess::shared_memory_object::remove("ipc_demo");
		}
		else if (str == "p")
		{
			print_strs(strs);
		}
		else if (str == "c")
		{
			strs->clear();
		}
		else
		{
			strs->push_back(ipc_string(str.c_str(), managed_shm.get_segment_manager())); 
		}
	}
	return 0;
}