# template_array
Array manipulation at compile time in C++.

# Usage

```
auto a = GetElem<2, Array<1, 32, 1337>>(); // a == 1337
auto b = Size<Array<1,2,3>>(); // b == 3
Append<4, Array<1,2,3>> c; // c is of type Array<1,2,3,4>
SetElem<1, 5, Array<1,2,3>> d; // d is of type Array<1,5,3>
```
