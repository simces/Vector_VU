# Vector
## 1. Vector konteinerio funkcionalumo patikrinimas ##

Funkcionalumo patikrinime, panaudojus 5 vector funkcijas, buvo palygintas customVector is std::vector.

Atlikus testavimą, std::vector ir customVector išvedė vienodus rezultatus, kurie parodo, jog funkcionalumo prasme konteineris customVector veikia taip pat, kaip ir std::vector.

```
std::vector results:
push_back() funkcija: 10, 20, 30, 40
at(2) funkcija: 30
size() funkcija: 4
pop_back() funkcija (vector size): 3
clear() funkcija (vector size): 0

Custom vector results:
push_back() funkcija: 10, 20, 30, 40
at(2) funkcija: 30
size() funkcija: 4
pop_back() funkcija (vector size): 3
clear() funkcija (vector size): 0 
```
### Panaudotos funkcijos ###

#### size() funkcija ####

```cpp
size_type size() const { return avail - data; }
```

#### at() funkcija ####

```cpp
template <class T>
typename Vector<T>::reference Vector<T>::at(size_type i) {
    if (i >= 0 && size() > i)
        return data[i];

    else throw std::out_of_range {"Vector::at"};
}
```



#### push_back() funkcija ####

```cpp
template <class T>
void Vector<T>::push_back(const T& val){
    if(avail == limit)
        growTwice();
    unchecked_append(val);
}
```



#### pop_back() funkcija ####

```cpp
template <class T>
void Vector<T>::pop_back(){
    iterator it = avail;
    alloc.destroy(--it);
    avail--;
}
```



#### clear() funkcija ####

```cpp
template <class T>
void Vector<T>::clear() {
    iterator it = avail;
    while (it != data)
        alloc.destroy(--it);
    avail = data;
}
```

## 2. Efektyvumo/spartos analizė naudojant push_back() funkciją ##

Šiame testavime buvo palyginti std::vector ir customVector laikai, užpildant 10'000, 100'000, 1'000'000, 10'000'000 ir 100'000'000 int elementus, panaudojant push_back() funkciją.

#### Gaunami rezultatai: ####

| Masyvo dydis \ konteinerio tipas | std::vector | Vector klasė |
| :------------------------------- | :---------- | :----------- |
| 10'000                           | 0s          | 0s           |
| 100'000                          | 0.001s      | 0s           |
| 1'000'000                        | 0.003s      | 0.003s       |
| 10'000'000                       | 0.039s      | 0.023s       |
| 100'000'000                      | 0.401s      | 0.247s       |





## 3. Atminties perskirstymų tyrimas ##

Šiame testavime palyginama std::vector ir customVector atminties perskirstymai, užpildant 100'000'000 elementų.
Perskirstymas įvyksta tada, kai yra patenkinama sąlyga: capacity() == size().

```
Reallocated: 28 times
Reached capacity: 134217728

Reallocated: 28 times
Reached capacity: 134217728
```




## 4. Spartos analizė, programos veikimo palyginimas ##

Šioje užduotyje buvo palyginami programos v2.0 veikimo laikai naudojant std::vector ir customVector konteinerius.

| Masyvo dydis \ konteinerio tipas | std::vector | Vector klasė |
| :------------------------------- | :---------- | :----------- |
| 1'000                            | 0.015s      | 0.012s       |
| 10'000                           | 0.128s      | 0.123s       |
| 100'000                          | 1.687s      | 1.612s       |
| 1'000'000                        | 23.987s     | 23.114s      |

