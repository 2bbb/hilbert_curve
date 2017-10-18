# hilbert_curve.hpp

calculate Hilbert curve.

## constructor

```cpp
const std::size_t order{8};
bbb::hilbert_curve curve{order};
```

## get n-th point

```cpp
bbb::hilbert_curve::coordinate coord = curve[n];
```

## get index at (x, y)

```cpp
std::size_t index = curve.index_at(x, y);
```

## License

MIT

## Author

- ISHII 2bit
- i[at]2bit.jp
