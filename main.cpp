#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
#include <fstream>
#include <stdio.h>
#include <map>

#include "driver.h"

#define ll long long

using namespace std;
using namespace sf;


int main(){
    // Main variables
    solaris MAIN;

    while(MAIN.running()){ // main loop
        // Update
        MAIN.update();
        // Render
        MAIN.render();
    }
    cout << "Application Terminated." << endl;
    return 0;
}
