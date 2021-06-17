#include <vector>
#include <chrono>
#include "vector.hpp"

using namespace std::chrono;

void test1(){
    std::cout << "Pradedamas TEST1: " << endl;

    std::vector<int> real_vector;
    Vector<int> custom_vector;

    std::cout << "std::vector results: " << endl;

    real_vector.push_back(10);
    real_vector.push_back(20);
    real_vector.push_back(30);
    real_vector.push_back(40);

    cout << "push_back() funkcija: " << real_vector[0] << ", " << real_vector[1] << ", "
    << real_vector[2] << ", " << real_vector[3] << endl;

    cout << "at(2) funkcija: " << real_vector.at(2) << endl;

    cout << "size() funkcija: " << real_vector.size() << endl;

    real_vector.pop_back();
    cout << "pop_back() funkcija (vector size): " << real_vector.size() << endl;

    real_vector.clear();
    cout << "clear() funkcija (vector size): " << real_vector.size() << endl;

    // ----------------------------------------------

    cout << endl << "Custom vector results: " << endl;

    custom_vector.push_back(10);
    custom_vector.push_back(20);
    custom_vector.push_back(30);
    custom_vector.push_back(40);

    cout << "push_back() funkcija: " << custom_vector[0] << ", " << custom_vector[1] << ", "
    << custom_vector[2] << ", " << custom_vector[3] << endl;

    cout << "at(2) funkcija: " << custom_vector.at(2) << endl;

    cout << "size() funkcija: " << custom_vector.size() << endl;

    custom_vector.pop_back();
    cout << "pop_back() funkcija (vector size): " << custom_vector.size() << endl;

    custom_vector.clear();
    cout << "clear() funkcija (vector size): " << custom_vector.size() << endl;
}


void test2(){                   // testing push_back function

    std::vector<int> real_vector;
    Vector<int> custom_vector;

    unsigned int sz[5] = { 10000, 100000, 1000000, 10000000, 100000000 };


    std::cout << "Pradedamas TEST2: " << endl;
    

    for(int i = 0; i < 5; i++){ 
        std::cout << "-----------------------------------------------------" << endl;

        std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        for (int j = 0; j <= sz[i]; j++){
            real_vector.push_back(j);   
        }

        std::cout << "std::vector '" << sz[i] << "' elementu push_back laikas :" << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count() / 1000. << "s." << endl;

        std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        for (int j = 0; j <= sz[i]; j++){
            custom_vector.push_back(j);   
        }
        
        std::cout << "custom vector '" << sz[i] << "' elementu push_back laikas :" << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t2).count() / 1000. << "s." << endl;
    }
}

void test3(){
    std::vector<int> real_vector;
    Vector<int> custom_vector;

    unsigned int sz = 100000000;

    int reallocCount = 0, capacity;
    bool didReallocate = false;

    std::cout << "Pradedamas TEST 3: " << endl;

    for (int i = 0; i < sz; i++) {
        if (real_vector.size() == real_vector.capacity()) {
            reallocCount++; 
            didReallocate = true;
        }
        real_vector.push_back(i);
        if (didReallocate) {
            capacity = real_vector.capacity();
            didReallocate = false;
        }
    }

    std::cout << "Reallocated: " << reallocCount << " times" << endl;
    std::cout << "Reached capacity: " << capacity << endl << endl;

    reallocCount = 0;
    capacity = 0;

    for(int i = 0; i < sz; i++) {
        if (custom_vector.size() == custom_vector.capacity()) {
            reallocCount++; 
            didReallocate = true;
        }
        custom_vector.push_back(i);
        if (didReallocate) {
            capacity = custom_vector.capacity();
            didReallocate = false;
        }
    }

    std::cout << "Reallocated: " << reallocCount << " times" << endl;
    std::cout << "Reached capacity: " << capacity << endl;
}

int main(){

    int a;

    std::cout << "Pasirinkite custom_vector testavimo buda (1/2/3): " << endl
    //---------
    << "TEST 1 (PROGRAMOS FUNKCIJU TESTAVIMAS) " << endl
    << "TEST 2 (PUSH_BACK FUNKCIJOS PALYGINIMAS) " << endl
    << "TEST 3 (ATMINTIES PERSKIRSTYMAS V2.0 UZDUOTYJE) " << endl;
    //---------
    
    cin >> a;
    cout << endl;

    if(a == 1) test1();
    else if(a == 2) test2();
    else if(a == 3) test3();
    else{
        std::cout << "Wrong input. Ending program.";
        return 0;
    }

    std::cout << endl;
    system("pause");
}