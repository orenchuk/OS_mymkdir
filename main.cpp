#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int help_text() {
    cout << "\nmymkdir [-h|--help] [-p] <dirname>... \n\
    Create the DIRECTORY(ies), if they do not already exist.\n\
    \n\
    -p, --parents     no error if existing, make parent directories as needed\n" << endl;
    return 0;
}

int parse_args(const int &argc, const char * argv[], vector<string> &args, bool &p) {
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            help_text();
        } else if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--parent")) {
            p = true;
        } else {
            args.push_back(argv[i]);
        }
    }
    
    return 0;
}

int mymkdir(const vector<string> &args, const bool &hasParents) {
    if (hasParents) {
        try {
            for (auto &name : args) {
                boost::filesystem::path path(name);
                boost::filesystem::create_directories(path);
            }
        } catch (const boost::filesystem::filesystem_error &e) {
            cerr << e.what() << endl;
            exit(-1);
        }
        
    } else {
        try {
            for (auto &name: args) {
                boost::filesystem::path path(name);
                if (boost::filesystem::exists(path)) {
                    cerr << "Error: such file already exists." << endl;
                    exit(-1);
                } else {
                    boost::filesystem::create_directory(path);
                }
            }
        } catch (...) {
            cerr << "Error: use -p if it has a parent directory or -h for more info." << endl;
            exit(-1);
        }
        
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    bool parent = false;
    vector<string> args;
    
    parse_args(argc, argv, args, parent);
    mymkdir(args, parent);
    
    return 0;
}
