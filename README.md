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

