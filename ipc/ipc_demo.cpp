
#include <string>
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/algorithm/string.hpp>

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
	/*
	对于上面的ipc_vector_string类型对象，如何(如果可能)让它以普通的内存管理方式，也就是不再boost::interprocess::managed_shared_memory
	的管理下分配内存，形如:
	ipc_vector_string strs;
	当然，上面这行代码是无法编译的，VC++会提示错误:
	C2512	“boost::interprocess::allocator<ipc_string,boost::interprocess::segment_manager<CharType,MemoryAlgorithm,IndexType>>::allocator”: 没有合适的默认构造函数可用
	那么应该传怎样一个参数呢？
	抑或在第12，15行定义的类型，已经无法像通常的方式(非进程间共享)分配和管理内存？
	*/

	std::string str;
	while (std::getline(std::cin, str))
	{
		boost::trim(str);
		if (str.empty())
		{
			continue;
		}
		else if (str == "q")
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