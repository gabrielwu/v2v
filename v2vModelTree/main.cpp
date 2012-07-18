
#include <list>
#ifndef TREE_H 
#define TREE_H 
#include "tree.h"
#endif
using namespace std;

int main () {
	
	srand((int)time(0));
	TreeConfig *config = new TreeConfig();
	//TreeTrunkBranch ttb(Point(0,0,0), Point(0,0,10), 2, config);
	//ttb.generateGrowPoints();
	//ttb.displayGrowPoints();
	TreeModel tree(config);
	tree.generate();
	tree.displayConfig();
	tree.displayLeaves();
	tree.displayBranches();

    return 0;
}
