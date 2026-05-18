#include <vector>
using namespace std;
#include <cassert>
#include "deque.h"
#include "maxScore.h"
#include <iostream>

int main() {
    using algorithm::maxScore;
    //vector vacio y k=0
    assert(maxScore(vector<int>{}, 1) == 0);   
    assert(maxScore(vector<int>{1,2,3}, 0) == 0); 
    // unitarios y tribiales
    assert(maxScore(vector<int>{-100}, 1) == -100);
    assert(maxScore(vector<int>{0}, 1) == 0);
    assert(maxScore(vector<int>{100, -200}, 2) == -100);
    //valores iguales
    assert(maxScore(vector<int>{0,0,0,0,0}, 1) == 0);
    assert(maxScore(vector<int>{-1,-1,-1,-1,-1}, 1) == -5);
    //todo positivo, negativo, mixto
    assert(maxScore(vector<int>{100,200,150,300,250}, 5) == 1000);
    assert(maxScore(vector<int>{-10,-5,-8,-3,-1,-7}, 3) == -20);
    assert(maxScore(vector<int>{100,-50,-30,-20,10}, 2) == 80);
    assert(maxScore(vector<int>{-10,-5,20,15,25}, 2) == 50);
    //valores extremos
    assert(maxScore(vector<int>{10000,10000,10000}, 2) == 30000);
    assert(maxScore(vector<int>{-10000,-5000,-3000}, 2) == -13000);
    assert(maxScore(vector<int>{10000,-5000,8000,-3000,7000}, 2) == 25000);
    assert(maxScore(vector<int>{1,1,1000000,1,1}, 2) == 1000004);
    //valores con patrones
    assert(maxScore(vector<int>{10,-5,10,-5,10}, 2) == 30);
    assert(maxScore(vector<int>{5,1,1,1,5}, 1) == 13);
    assert(maxScore(vector<int>{1,1,100,1,1}, 2) == 104);
    assert(maxScore(vector<int>{100,-100,100,50}, 2) == 250);
    //casos con cero
    assert(maxScore(vector<int>{1,0,2,0,3}, 1) == 6);
    assert(maxScore(vector<int>{0,0,5,0,0,3}, 2) == 8);
    //casos criticos
    assert(maxScore(vector<int>{1,100,-50,50}, 2) == 151);
    assert(maxScore(vector<int>{50,-100,10,10,10,100}, 2) == 180);
    assert(maxScore(vector<int>{5,-10,15,-5,20}, 2) == 40);
    assert(maxScore(vector<int>{1,-5,1,-5,1,-5,100}, 3) == 103);
    //secuencias largas
    {
        vector<int> v(10);
        for (int i = 0; i < 10; ++i) v[i] = i + 1;
        assert(maxScore(v, 1) == 55);
    }

    {
        vector<int> v(15);
        for (int i = 0; i < 15; ++i) v[i] = (i % 2 == 0) ? 10 : -3;
        assert(maxScore(v, 2) == 80);
    }
    //Casos especiales para deque (secuencias)
    assert(maxScore(vector<int>{1,2,3,4,5,6,7,8}, 2) == 36);
    assert(maxScore(vector<int>{10,9,8,7,6,5,4}, 1) == 49);
    assert(maxScore(vector<int>{5,1,10,2,8,3,7}, 2) == 36);
    assert(maxScore(vector<int>{1,1,1,100,1,1,1}, 3) == 106);

    assert(maxScore(vector<int>{100, -200}, 2) == algorithm::maxScoreSlow(vector<int>{100, -200}, 2));

    cout << "No hubo errores en las pruebas" << endl;
    return 0;
}
