template <class T, size_t n, size_t m> struct mat : public array<arr<T, m>, n> {
  using array<arr<T, m>, n>::array;
  template<class ...Args>
  mat(arr<T,m> a,Args... args):array<arr<T,m>,n>{a,args...}{}
  template<class U>
  mat(const array<arr<U, m>, n>& a){
    for (size_t i=0;i<n;i++)
      (*this)[i]=a[i];
  }
  static mat<T, n, m> unit() {
    mat<T, n, m> a{};
    for (size_t i = 0; i < min(n, m); i++)
      a[i][i] = 1;
    return a;
  }
  static constexpr mat<T, n, m> zero() {
    return mat<T, n, m>{};
  }
};
template <class T, size_t n, size_t m> class tuple_size<mat<T, n, m>> {
public:
  constexpr static size_t value = n;
};

template <class AT = void, class T, class U, size_t n, size_t m,
          class UT = typename conditional<is_same<AT, void>::value,
                                          decltype(declval<T>() * declval<U>()),
                                          AT>::type>
mat<UT, n, m> operator+(const mat<T, n, m> &a, const mat<U, n,m> &b) {
  mat<UT,n,m> x;
  for (size_t i=0;i<n;i++)
    x[i]=a[i]+b[i];
  return x;
}

template <class AT = void, class T, class U, size_t n, size_t m,
          class UT = typename conditional<is_same<AT, void>::value,
                                          decltype(declval<T>() * declval<U>()),
                                          AT>::type>
mat<UT, n, m> operator-(const mat<T, n, m> &a, const mat<U, n,m> &b) {
  mat<UT,n,m> x;
  for (size_t i=0;i<n;i++)
    x[i]=a[i]+b[i];
  return x;
}

template <class T, class U, size_t n, size_t m>
mat<T,n,m>& operator+=(mat<T,n,m>& a,const mat<U,n,m>& b){
  for (size_t i=0;i<n;i++)
    a[i]+=b[i];
  return a;
}

template <class T, class U, size_t n, size_t m>
mat<T,n,m>& operator-=(mat<T,n,m>& a,const mat<U,n,m>& b){
  for (size_t i=0;i<n;i++)
    a[i]+=b[i];
  return a;
}

template <class AT = void, class T, class U, size_t n, size_t m, size_t u,
          class UT = typename conditional<is_same<AT, void>::value,
                                          decltype(declval<T>() * declval<U>()),
                                          AT>::type>
mat<UT, n, u> operator*(const mat<T, n, m> &a, const mat<U, m, u> &b) {
  mat<UT, n, u> x{};
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < u; j++)
      for (size_t k = 0; k < m; k++)
        x[i][j] += a[i][k] * b[k][j];
  return x;
}

template <class AT = void, class T, class U, size_t n, size_t m, size_t u>
mat<T, n, u>& operator*=(mat<T, n, m> &a, const mat<U, m, u> &b) {
  return a = operator*<T>(a, b);
}

template <class T, class U, size_t n, size_t m>
mat<T, n, m>& operator*=(mat<T, n, m> &a, const U &b) {
  for (auto &i:a) i*=b;
  return a;
}

template <class T, class U, size_t n, size_t m>
mat<T, n, m>& operator/=(mat<T, n, m> &a, const U &b) {
  for (auto &i:a) i/=b;
  return a;
}

template <class T, class U, size_t n, size_t m>
mat<T, n, m> operator*(const mat<T, n, m> &a, const U &b) {
  mat<T, n, m> x;
  for (size_t i=0;i<n;i++) x[i]=a[i]*b;
  return x;
}

template <class T, class U, size_t n, size_t m>
mat<T, n, m> operator/(mat<T, n, m> &a, const U &b) {
  mat<T, n, m> x;
  for (size_t i=0;i<n;i++) x[i]=a[i]/b;
  return x;
}

template <
    class AT = void, class T, size_t n, size_t m,
    class UT = typename conditional<is_same<AT, void>::value, T, AT>::type>
pair<int, mat<UT, n, m>> inv(const mat<T, n, m> &_a) {
  mat<UT, n, m> a = _a;
  auto b = mat<UT, n, m>::unit();
  for (int i = 0; i < n - 1; i++) {
    int k = -1;
    for (int j = i; j < n; j++)
      if (a[j][i]) {
        k = j;
        break;
      }
    if (k != -1) {
      swap(a[i], a[k]);
      swap(b[i], b[k]);
      for (int j = i + 1; j < n; j++)
        if (a[k][i]) {
          UT d = a[j][i] / a[k][i];
          a[j] -= a[k] * d;
          b[j] -= b[k] * d;
        }
    }
  }
  int rank = 0;
  for (int i = n - 1; i >= 0; i--) {
    UT aii = a[i][i];
    if (aii) {
      rank++;
      b[i] /= aii;
      a[i] /= aii;
      for (int j = i - 1; j >= 0; j--) {
        UT aji = a[j][i];
        a[j] -= a[i] * aji;
        b[j] -= b[i] * aji;
      }
    }
  }
  return {rank, b};
}

template <
    class AT = void, class T, size_t n, size_t m,
    class UT = typename conditional<is_same<AT, void>::value, T, AT>::type>
UT det(const mat<T, n, m> &_a) {
  mat<UT, n, m> a = _a;
  vector<int> x(n, -1);
  int ans = 0, ii = 0;
  UT D = 1;
  for (int i = 0; i < n; i++) {
    int it = -1;
    for (int j = i; j < n; j++)
      if (a[j][ii]) {
        it = j;
        break;
      }
    if (it == -1)
      continue;
    swap(a[ii], a[it]);
    auto d = a[ii][x[ii] = i];
    a[ii] /= d;
    D *= d;
    for (int j = ii + 1; j < n; j++)
      if (a[j][i]) {
        UT d = a[j][i];
        a[j] -= a[ii] * d;
      }
    ans++;
    ii++;
  }
  return ans != n ? 0 : D;
}