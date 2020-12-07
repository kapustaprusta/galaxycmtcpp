#include <iostream>

#include "src/walker/dir_walker/dir_walker.h"

int main() {
	walker::Settings seetings;
	seetings.is_recursive_ = true;
	seetings.extensions_ = {".h", ".cpp"};

	walker::DirWalker walker(seetings);
	walker.Walk("/home/vniksihov/src/initial_setup");

    return 0;
}
