#include <iostream>
#include <cstdlib>
#include <string>
#include <dlfcn.h>
#include <getopt.h>

#include "primihub-party.h"

// typedef void (*NODEFUNC) (
//               const std::string &node_id, 
// 			  const std::string &config,
//               int port);

static int parse_argument(int argc, char **argv, 
			  uint16_t &port, std::string &config, 
			  std::string &node_id)
{
	static struct option long_options[] = {
		{"port", required_argument, 0, 'p'},
		{"config", required_argument,  0, 'f'},
		{"node_id", required_argument, 0, 'i'},
		{0, 0, 0, 0}
	};
	
	int opt = 0;
	int long_opt = 0;
	int hit = 0;
	while ((opt = getopt_long(argc, argv, "pfi", long_options, &long_opt)) != -1) {
		switch (opt) {
		case 'p':
			port = static_cast<uint16_t>(std::atoi(optarg));
			hit ++;
			break;
		case 'f':
			config = optarg;
			hit ++;
			break;
		case 'i':
			node_id = optarg;
			hit ++;
			break;
		default:
			std::cerr << "Unknown argument " << argv[opt] << std::endl;
			return -1;
		}
	}

	if (hit != 3) {
		std::cerr << "Too many or too few argument." << std::endl;
		return -2;
	}

	return 0;

}

static int run_node(const std::string &node_id, 
		            const std::string &config, 
		            int port) {

	// const char *so_file = "/root/work/primihub/bazel-bin/libnode.so";
	// void *handle = nullptr;
	// char *error = nullptr;
	
	// handle = dlopen(so_file, RTLD_LAZY);
	// if (!handle) {
	// 	std::cerr << "Failed to open file, " 
	// 		  << dlerror() << std::endl;
	// 	return -1;
	// }	

	// dlerror();

	// NODEFUNC func;
	// *(void**) (&func)  = dlsym(handle, "node_main");
	// 
	// if ((error = dlerror()) != NULL) {
	// 	std::cout << "dlsym failed, " << error << std::endl;
	// 	return -2;
	// }

	// func(node_id, config, port);
	// dlclose(handle);

    node_main(node_id, config, port);
	return 0;
}

int main(int argc, char **argv) {
	uint16_t port = 0;
	std::string config;
	std::string node_id;
	int ret = parse_argument(argc, argv, port, config, node_id);
	if (ret) {
		return -1;
	}

	ret = run_node(node_id, config, port);
	if (ret) {
		return -2;
	}	

	return 0;
}
