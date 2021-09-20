constexpr auto p1 = point<int>{3, 5};                   // ok, copy-initialization
constexpr auto pr1 = point_r<int>{3, 5};                // ok, copy-initialization
constexpr auto pr1u = point_r<unsigned>{3, 5};                // ok, copy-initialization
constexpr auto prn = point_r<int>{-1, -1};              // ok, copy-initialization
constexpr auto prmax = point_r<unsigned int>{-1u, -1u}; // ok, copy-initialization

point<int> p2 = static_cast<point<int>>(pr1);
point<short> p3 = static_cast<point<short>>(pr1);
point<unsigned> p4 = static_cast<point<unsigned>>(pr1);
point<int> p5 = static_cast<point<int>>(pr1u);
point<unsigned> p6 = static_cast<point<unsigned>>(pr1u);

auto const mus = std::numeric_limits<unsigned short>::max();
auto const mui = std::numeric_limits<unsigned int>::max();
auto const mul = std::numeric_limits<unsigned long>::max();

auto const ms = std::numeric_limits<short>::max();
auto const mi = std::numeric_limits<int>::max();
auto const ml = std::numeric_limits<long>::max();

auto const mf = std::numeric_limits<float>::max();
auto const mld = std::numeric_limits<long double>::max();

point<unsigned short> pusus = static_cast<point<unsigned short>>(point_r<unsigned short>{mus, mus});
point<unsigned int> puius = static_cast<point<unsigned int>>(point_r<unsigned short>{mus, mus});
point<unsigned long> pulus = static_cast<point<unsigned long>>(point_r<unsigned short>{mus, mus});

// point<short> psus = static_cast<point<short>>(point_r<unsigned short>{mus, mus});
point<int> pius = static_cast<point<int>>(point_r<unsigned short>{mus, mus});
point<long> plus = static_cast<point<long>>(point_r<unsigned short>{mus, mus});

point<float> pfus = static_cast<point<float>>(point_r<unsigned short>{mus, mus});
point<long double> pdus = static_cast<point<long double>>(point_r<unsigned short>{mus, mus});
//
// point<unsigned short> pusui = static_cast<point<unsigned short>>(point_r<unsigned int>{mui, mui});
point<unsigned int> puiui = static_cast<point<unsigned int>>(point_r<unsigned int>{mui, mui});
point<unsigned long> pului = static_cast<point<unsigned long>>(point_r<unsigned int>{mui, mui});

// point<short> psui = static_cast<point<short>>(point_r<unsigned int>{mui, mui});
// point<int> piui = static_cast<point<int>>(point_r<unsigned int>{mui, mui});
point<long> plui = static_cast<point<long>>(point_r<unsigned int>{mui, mui});

point<float> pfui = static_cast<point<float>>(point_r<unsigned int>{mui, mui});
point<long double> pdui = static_cast<point<long double>>(point_r<unsigned int>{mui, mui});
//
// point<unsigned short> pusul = static_cast<point<unsigned short>>(point_r<unsigned long>{mul, mul});
// point<unsigned int> puiul = static_cast<point<unsigned int>>(point_r<unsigned long>{mul, mul});
point<unsigned long> pulul = static_cast<point<unsigned long>>(point_r<unsigned long>{mul, mul});

// point<short> psul = static_cast<point<short>>(point_r<unsigned long>{mul, mul});
// point<int> piul = static_cast<point<int>>(point_r<unsigned long>{mul, mul});
// point<long> plul = static_cast<point<long>>(point_r<unsigned long>{mul, mul});

point<float> pful = static_cast<point<float>>(point_r<unsigned long>{mul, mul});
point<long double> pdul = static_cast<point<long double>>(point_r<unsigned long>{mul, mul});
//
point<unsigned short> puss = static_cast<point<unsigned short>>(point_r<short>{ms, ms});
point<unsigned int> puis = static_cast<point<unsigned int>>(point_r<short>{ms, ms});
point<unsigned long> puls = static_cast<point<unsigned long>>(point_r<short>{ms, ms});

point<short> pss = static_cast<point<short>>(point_r<short>{ms, ms});
point<int> pis = static_cast<point<int>>(point_r<short>{ms, ms});
point<long> pls = static_cast<point<long>>(point_r<short>{ms, ms});

point<float> pfs = static_cast<point<float>>(point_r<short>{ms, ms});
point<long double> pds = static_cast<point<long double>>(point_r<short>{ms, ms});
//
// point<unsigned short> pusi = static_cast<point<unsigned short>>(point_r<int>{mi, mi});
point<unsigned int> puii = static_cast<point<unsigned int>>(point_r<int>{mi, mi});
point<unsigned long> puli = static_cast<point<unsigned long>>(point_r<int>{mi, mi});

// point<short> psi = static_cast<point<short>>(point_r<int>{mi, mi});
point<int> pii = static_cast<point<int>>(point_r<int>{mi, mi});
point<long> pli = static_cast<point<long>>(point_r<int>{mi, mi});

point<float> pfi = static_cast<point<float>>(point_r<int>{mi, mi});
point<long double> pdi = static_cast<point<long double>>(point_r<int>{mi, mi});
//
// point<unsigned short> pusl = static_cast<point<unsigned short>>(point_r<long>{ml, ml});
// point<unsigned int> puil = static_cast<point<unsigned int>>(point_r<long>{ml, ml});
point<unsigned long> pull = static_cast<point<unsigned long>>(point_r<long>{ml, ml});

// point<short> psl = static_cast<point<short>>(point_r<long>{ml, ml});
// point<int> pil = static_cast<point<int>>(point_r<long>{ml, ml});
point<long> pll = static_cast<point<long>>(point_r<long>{ml, ml});

point<float> pfl = static_cast<point<float>>(point_r<long>{ml, ml});
point<long double> pdl = static_cast<point<long double>>(point_r<long>{ml, ml});
//
// point<unsigned short> pusf = static_cast<point<unsigned short>>(point_r<float>{mf, mf});
// point<unsigned int> puif = static_cast<point<unsigned int>>(point_r<float>{mf, mf});
// point<unsigned long> pulf = static_cast<point<unsigned long>>(point_r<float>{mf, mf});

// point<short> psf = static_cast<point<short>>(point_r<float>{mf, mf});
// point<int> pif = static_cast<point<int>>(point_r<float>{mf, mf});
// point<long> plf = static_cast<point<long>>(point_r<float>{mf, mf});

point<float> pff = static_cast<point<float>>(point_r<float>{mf, mf});
point<long double> pdf = static_cast<point<long double>>(point_r<float>{mf, mf});
//
// point<unsigned short> pusld = static_cast<point<unsigned short>>(point_r<long double>{mld, mld});
// point<unsigned int> puild = static_cast<point<unsigned int>>(point_r<long double>{mld, mld});
// point<unsigned long> pulld = static_cast<point<unsigned long>>(point_r<long double>{mld, mld});

// point<short> psld = static_cast<point<short>>(point_r<long double>{mld, mld});
// point<int> pild = static_cast<point<int>>(point_r<long double>{mld, mld});
// point<long> plld = static_cast<point<long>>(point_r<long double>{mld, mld});

// point<float> pfld = static_cast<point<float>>(point_r<long double>{mld, mld});
point<long double> pdld = static_cast<point<long double>>(point_r<long double>{mld, mld});
