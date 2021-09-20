template<typename T> // , typename...>
struct ttp {
    T x, y;
    ttp() = default;

    constexpr ttp(T x, T y) noexcept
        : x{x}, y{y}
    { std::cout << "[ttp init ctor][" << +x << "][" << +y << "]\n"; }

    constexpr ttp(ttp const& other) noexcept
        : x{other.x}, y{other.y}
    { std::cout << "[ttp cpy ctor][" << +x << "][" << +y << "]\n"; }

    constexpr ttp(ttp&& other) noexcept
        : x{other.x}, y{other.y}
    { std::cout << "[ttp mov ctor][" << +x << "][" << +y << "]\n"; }

    constexpr auto operator=(ttp const& other) noexcept -> ttp&
        { x = other.x; y = other.y;
    std::cout << "...[ttp cpy asgn][" << +x << "][" << +y << "]\n"; return *this; }

    constexpr auto operator=(ttp&& other) noexcept -> ttp&
        { x = other.x; y = other.y;
    std::cout << "...[ttp mov asgn][" << +x << "][" << +y << "]\n"; return *this; }

    // template<template<typename, typename...> typename TT, typename U, typename... Ts>
    template<typename R, typename U>
    constexpr auto convertt() const noexcept -> R/*(std::is_same_v<C, XT>)*/ // -> TT<U, Ts...>
    { return {static_cast<U>(x), static_cast<U>(y)}; }

    template<template<typename, typename...> typename TT, typename U, typename... Ts, typename R = TT<U, Ts...>>
    constexpr operator TT<U, Ts...>() const noexcept
    // { return {x, y}; }
    { std::cout<< "[udc]\n"; return convertt<R, U>(); } //  {static_cast<U>(x), static_cast<U>(y)}; }
    // { return *this; }

    // note: simply copying everthing instead of dereferencing is probably faster
    // template<typename U>
    // constexpr auto operator+=(ttp<U> const& other)& noexcept -> ttp& {
    //     x += other.x;
    //     y += other.y;
    //     return *this;
    // }

    // template<typename U>
    // constexpr auto operator+=(U unit)& noexcept -> ttp& {
    //     x += unit;
    //     y += unit;
    //     return *this;
    // }

    // constexpr auto operator-() const& noexcept -> ttp
    // { std::cout << "&-ver\n"; return {-x, -y}; }

    // constexpr auto operator-()&& noexcept -> ttp&&;// {
    //     std::cout << "&&-ver\n";
    //     x = -x;
    //     y = -y;
    //     return std::move(*this);
    // }
};

int main() { // static_assert(std::is_same_v<std::common_type_t<short, short>, int>);

static_assert(std::is_same_v<compound_opt_t<int, typet<double, XT>>,
    typet<double>& (&)(typet<double>&, typet<double> const&)>);

static_assert(std::is_same_v<compound_opt_t<typet<long, YT>, float>,
    typet<float, YT>& (&)(typet<float, YT>&, float)>);

static_assert(std::is_same_v<std::common_type_t<typet<int>, typet<double>>, typet<double>>);
static_assert(std::is_same_v<std::common_type_t<typet<double, YT>, typet<int, YT>>, typet<double, YT>>);
static_assert(std::is_same_v<std::common_type_t<typet<int, YT>, double>, typet<double, YT>>);
static_assert(std::is_same_v<std::common_type_t<typet<double, YT>, int>, typet<double, YT>>);

static_assert(std::is_same_v<std::common_type_t<double, typet<int>>, typet<double>>);

// static_assert(std::is_same_v<std::common_type_t<typet<int>, typet<double>>, typet<double>>);

static_assert(std::is_same_v<std::common_type_t<ttp<char>, ttp<int>>, ttp<int>>);
static_assert(std::is_same_v<std::common_type_t<ttp<double>, ttp<int>>, ttp<double>>);
static_assert(std::is_same_v<std::common_type_t<ttp<char>, short>, ttp<int>>);
static_assert(std::is_same_v<std::common_type_t<short, ttp<char>>, ttp<int>>);

typet<char, YT> mytyp{1, 2};
typet<char, XT> mytypx{1, 2};
typet<long, YT> mytyp2 = mytyp; //{mytyp.operator typet<long, YT>()};// = mytyp; //{mytyp};
spet<long long> sp = mytyp;

typet<double> tytest1 = mytypx;
typet<char, YT> tytest2 = static_cast<typet<char, YT>>(mytypx); // {static_cast<typet<char>>(mytyp)}; // {mytyp};
// static_assert(std::is_same_v<decltype(mytyp2), typet<long, YT>>);
//
typet<long long> mytyp3 = static_cast<typet<long, XT>>(mytyp2);
// static_assert(std::is_same_v<decltype(mytyp), typet<char, YT>>);
ttff(mytyp, mytyp);

locc::namy<int> n1;
locc::namy<int> n2;
n1 - n2;
// ttff2(mytyp, (short)3);

// constexpr point<int, internal::interface::conversion::throw_on_out_of_range> ap{31'000, 9};
// constexpr point<int, internal::interface::conversion::throw_on_out_of_range> ap{33'000, 9};
// ap.x += 5'000;
constexpr point<int> ap{7, 9};
Z<int> myz{3, 5};
constexpr point<long> lp(ap);//{static_cast<point<long>>(ap)};
constexpr point<long> lp2(ap.operator point<long>());//{static_cast<point<long>>(ap)};
constexpr point<long> lp3{static_cast<point<long>>(ap)};
// constexpr point<long> lp4 = myz;
// constexpr point<int> lp{myz};
// ttp<int> myttp{7, 8};
// ttp<long> myttp2(myttp);
// ttp<long> myttp3{static_cast<ttp<long>>(myttp)};
// ttp<long> myttp4{myttp.operator ttp<long>()};
// ttp<long> myttp5 = myttp;
// ttp<long> myttp6 = myz;
Z<long> myz2 = ap;

std::cout << "--------------- cpy/mov init\n";
ttp<int> at{3, 5};
std::cout << "--------------- at2 = at\n";
ttp<int> at2 = at;
std::cout << "--------------- at3{at}\n";
ttp<int> at3{at};
std::cout << "--------------- at4(at)\n";
ttp<int> at4(at);
std::cout << "--------------- at5 = {at}\n";
ttp<int> at5 = {at};
std::cout << "--------------- at6 = (at)\n";
ttp<int> at6 = (at);
std::cout << "--------------- at7{{at}}\n";
ttp<int> at7{{at}};

std::cout << "---------------\n";
std::cout << "--------------- atr2 = ttp<int>{}\n";
ttp<int> atr2 = ttp<int>{};
std::cout << "--------------- atr3{ttp<int>{}}\n";
ttp<int> atr3{ttp<int>{}};
std::cout << "--------------- atr4(ttp<int>{})\n";
ttp<int> atr4(ttp<int>{});
std::cout << "--------------- atr5 = {ttp<int>{}}\n";
ttp<int> atr5 = {ttp<int>{}};
std::cout << "--------------- atr6 = (ttp<int>{})\n";
ttp<int> atr6 = (ttp<int>{});
std::cout << "--------------- atr7{{ttp<int>{}}}\n";
ttp<int> atr7{{ttp<int>{}}};

std::cout << "---------------\n";
std::cout << "--------------- atx2 = std::move(at)\n";
ttp<int> atx2 = std::move(at);
std::cout << "--------------- atx3{std::move(at)}\n";
ttp<int> atx3{std::move(at)};
std::cout << "--------------- atx4(std::move(at))\n";
ttp<int> atx4(std::move(at));
std::cout << "--------------- atx5 = {std::move(at)}\n";
ttp<int> atx5 = {std::move(at)};
std::cout << "--------------- atx6 = (std::move(at))\n";
ttp<int> atx6 = (std::move(at));
std::cout << "--------------- atx7{{std::move(at)}}\n";
ttp<int> atx7{{std::move(at)}};

std::cout << "---------------\n";
std::cout << "--------------- cpy/mov assign\n";
ttp<int> au;
std::cout << "--------------- au = at\n";
au = at;
std::cout << "--------------- au = {at}\n";
au = {at};
std::cout << "--------------- au = (at)\n";
au = (at);
std::cout << "--------------- au = {{at}}\n";
au = {{at}};

std::cout << "---------------\n";
ttp<int> aur;
std::cout << "--------------- aur = ttp<int>{}\n";
aur = ttp<int>{};
std::cout << "--------------- aur = {ttp<int>{}}\n";
aur = {ttp<int>{}};
std::cout << "--------------- aur = (ttp<int>{})\n";
aur = (ttp<int>{});
std::cout << "--------------- aur = {{ttp<int>{}}}\n";
aur = {{ttp<int>{}}};

std::cout << "---------------\n";
ttp<int> aux;
std::cout << "--------------- aux = std::move(at)\n";
aux = std::move(at);
std::cout << "--------------- aux = {std::move(at)}\n";
aux = {std::move(at)};
std::cout << "--------------- aux = (std::move(at))\n";
aux = (std::move(at));
std::cout << "--------------- aux = {{std::move(at)}}\n";
aux = {{std::move(at)}};

std::cout << "---------------\n";
ttp<short> aus;
std::cout << "--------------- aus = at\n";
aus = at;
// std::cout << "--------------- aus = {at}\n";
// aus = {at};
std::cout << "--------------- aus = (at)\n";
aus = (at);
// std::cout << "--------------- aus = {{at}}\n";
// aus = {{at}};

std::cout << "---------------\n";
ttp<short> aurs;
std::cout << "--------------- aurs = ttp<int>{}\n";
aurs = ttp<int>{};
// std::cout << "--------------- aurs = {ttp<int>{}}\n";
// aurs = {ttp<int>{}};
std::cout << "--------------- aurs = (ttp<int>{})\n";
aurs = (ttp<int>{});
// std::cout << "--------------- aus = {{ttp<int>{}}}\n";
// aurs = {{ttp<int>{}}};

std::cout << "---------------\n";
ttp<short> auxs;
std::cout << "--------------- auxs = std::move(at)\n";
auxs = std::move(at);
// std::cout << "--------------- auxs = {std::move(at)}\n";
// auxs = {std::move(at)};
std::cout << "--------------- aus = (std::move(at))\n";
auxs = (std::move(at));
// std::cout << "--------------- auxs = {{std::move(at)}}\n";
// auxs = {{std::move(at)}};


std::cout << "---------------\n";
std::cout << "---------------\n";

ttp<char> c{1, 2};
ttp<short> s{3, 4};
ttp<int> i{5, 6};
ttp<long> l{7, 8};

std::cout << "--------------- c + c\n";
// c + c;
[[maybe_unused]]auto tcc{c + c};
static_assert(std::is_same_v<decltype(tcc), ttp<char>>);
std::cout << "--------------- c + s\n";
// c + s;
[[maybe_unused]]auto tcs{c + s};
static_assert(std::is_same_v<decltype(tcs), ttp<int>>);
std::cout << "--------------- s + c\n";
// s + c;
[[maybe_unused]]auto tsc{s + c};
static_assert(std::is_same_v<decltype(tsc), ttp<int>>);
std::cout << "--------------- s + s\n";
// s + s;
[[maybe_unused]]auto tss{s + s};
static_assert(std::is_same_v<decltype(tss), ttp<short>>);
std::cout << "--------------- c + i\n";
// c + i;
[[maybe_unused]]auto tci{c + i};
static_assert(std::is_same_v<decltype(tci), ttp<int>>);
std::cout << "--------------- i + c\n";
// i + c;
[[maybe_unused]]auto tic{i + c};
static_assert(std::is_same_v<decltype(tic), ttp<int>>);
std::cout << "--------------- i + i\n";
// i + i;
[[maybe_unused]]auto tii{i + i};
static_assert(std::is_same_v<decltype(tii), ttp<int>>);
std::cout << "--------------- c + l\n";
// c + l;
[[maybe_unused]]auto tcl{c + l};
static_assert(std::is_same_v<decltype(tcl), ttp<long>>);
std::cout << "--------------- l + c\n";
// l + c;
[[maybe_unused]]auto tlc{l + c};
static_assert(std::is_same_v<decltype(tlc), ttp<long>>);
std::cout << "--------------- i + l\n";
// i + l;
[[maybe_unused]]auto til{i + l};
static_assert(std::is_same_v<decltype(til), ttp<long>>);
std::cout << "--------------- l + i\n";
// l + i;
[[maybe_unused]]auto tli{l + i};
static_assert(std::is_same_v<decltype(tli), ttp<long>>);
std::cout << "--------------- l + l\n";
// l + l;
[[maybe_unused]]auto tll{l + l};
static_assert(std::is_same_v<decltype(tll), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

std::cout << "--------------- c + cr\n";
[[maybe_unused]]auto tccr{c + ttp<char>{}};
static_assert(std::is_same_v<decltype(tccr), ttp<char>>);
std::cout << "--------------- c + sr\n";
[[maybe_unused]]auto tcsr{c + ttp<short>{}};
static_assert(std::is_same_v<decltype(tcsr), ttp<int>>);
std::cout << "--------------- s + cr\n";
[[maybe_unused]]auto tscr{s + ttp<char>{}};
static_assert(std::is_same_v<decltype(tscr), ttp<int>>);
std::cout << "--------------- s + sr\n";
[[maybe_unused]]auto tssr{s + ttp<short>{}};
static_assert(std::is_same_v<decltype(tssr), ttp<short>>);
std::cout << "--------------- c + ir\n";
[[maybe_unused]]auto tcir{c + ttp<int>{}};
static_assert(std::is_same_v<decltype(tcir), ttp<int>>);
std::cout << "--------------- i + cr\n";
[[maybe_unused]]auto ticr{i + ttp<char>{}};
static_assert(std::is_same_v<decltype(ticr), ttp<int>>);
std::cout << "--------------- i + ir\n";
[[maybe_unused]]auto tiir{i + ttp<int>{}};
static_assert(std::is_same_v<decltype(tiir), ttp<int>>);
std::cout << "--------------- c + lr\n";
[[maybe_unused]]auto tclr{c + ttp<long>{}};
static_assert(std::is_same_v<decltype(tclr), ttp<long>>);
std::cout << "--------------- l + cr\n";
[[maybe_unused]]auto tlcr{l + ttp<char>{}};
static_assert(std::is_same_v<decltype(tlcr), ttp<long>>);
std::cout << "--------------- i + lr\n";
[[maybe_unused]]auto tilr{i + ttp<long>{}};
static_assert(std::is_same_v<decltype(tilr), ttp<long>>);
std::cout << "--------------- l + ir\n";
[[maybe_unused]]auto tlir{l + ttp<int>{}};
static_assert(std::is_same_v<decltype(tlir), ttp<long>>);
std::cout << "--------------- l + lr\n";
[[maybe_unused]]auto tllr{l + ttp<long>{}};
static_assert(std::is_same_v<decltype(tllr), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

std::cout << "--------------- cr + c\n";
[[maybe_unused]]auto tcrc{ttp<char>{} + c};
static_assert(std::is_same_v<decltype(tcrc), ttp<char>>);
std::cout << "--------------- sr + c\n";
[[maybe_unused]]auto tsrc{ttp<short>{} + c};
static_assert(std::is_same_v<decltype(tsrc), ttp<int>>);
std::cout << "--------------- cr + s\n";
[[maybe_unused]]auto tcrs{ttp<char>{} + s};
static_assert(std::is_same_v<decltype(tcrs), ttp<int>>);
std::cout << "--------------- sr + s\n";
[[maybe_unused]]auto tsrs{ttp<short>{} + s};
static_assert(std::is_same_v<decltype(tsrs), ttp<short>>);
std::cout << "--------------- ir + c\n";
[[maybe_unused]]auto tirc{ttp<int>{} + c};
static_assert(std::is_same_v<decltype(tirc), ttp<int>>);
std::cout << "--------------- cr + i\n";
[[maybe_unused]]auto tcri{ttp<char>{} + i};
static_assert(std::is_same_v<decltype(tcri), ttp<int>>);
std::cout << "--------------- ir + i\n";
[[maybe_unused]]auto tiri{ttp<int>{} + i};
static_assert(std::is_same_v<decltype(tiri), ttp<int>>);
std::cout << "--------------- lr + c\n";
[[maybe_unused]]auto tlrc{ttp<long>{} + c};
static_assert(std::is_same_v<decltype(tlrc), ttp<long>>);
std::cout << "--------------- cr + l\n";
[[maybe_unused]]auto tcrl{ttp<char>{} + l};
static_assert(std::is_same_v<decltype(tcrl), ttp<long>>);
std::cout << "--------------- lr + i\n";
[[maybe_unused]]auto tlri{ttp<long>{} + i};
static_assert(std::is_same_v<decltype(tlri), ttp<long>>);
std::cout << "--------------- ir + l\n";
[[maybe_unused]]auto tirl{ttp<int>{} + l};
static_assert(std::is_same_v<decltype(tirl), ttp<long>>);
std::cout << "--------------- lr + l\n";
[[maybe_unused]]auto tlrl{ttp<long>{} + l};
static_assert(std::is_same_v<decltype(tlrl), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

std::cout << "--------------- cr + cr\n";
[[maybe_unused]]auto tcrcr{ttp<char>{} + ttp<char>{}};
static_assert(std::is_same_v<decltype(tcrcr), ttp<char>>);
std::cout << "--------------- sr + cr\n";
[[maybe_unused]]auto tsrcr{ttp<short>{} + ttp<char>{}};
static_assert(std::is_same_v<decltype(tsrcr), ttp<int>>);
std::cout << "--------------- cr + sr\n";
[[maybe_unused]]auto tcrsr{ttp<char>{} + ttp<short>{}};
static_assert(std::is_same_v<decltype(tcrsr), ttp<int>>);
std::cout << "--------------- sr + sr\n";
[[maybe_unused]]auto tsrsr{ttp<short>{} + ttp<short>{}};
static_assert(std::is_same_v<decltype(tsrsr), ttp<short>>);
std::cout << "--------------- ir + cr\n";
[[maybe_unused]]auto tircr{ttp<int>{} + ttp<char>{}};
static_assert(std::is_same_v<decltype(tircr), ttp<int>>);
std::cout << "--------------- cr + ir\n";
[[maybe_unused]]auto tcrir{ttp<char>{} + ttp<int>{}};
static_assert(std::is_same_v<decltype(tcrir), ttp<int>>);
std::cout << "--------------- ir + ir\n";
[[maybe_unused]]auto tirir{ttp<int>{} + ttp<int>{}};
static_assert(std::is_same_v<decltype(tirir), ttp<int>>);
std::cout << "--------------- lr + cr\n";
[[maybe_unused]]auto tlrcr{ttp<long>{} + ttp<char>{}};
static_assert(std::is_same_v<decltype(tlrcr), ttp<long>>);
std::cout << "--------------- cr + lr\n";
[[maybe_unused]]auto tcrlr{ttp<char>{} + ttp<long>{}};
static_assert(std::is_same_v<decltype(tcrlr), ttp<long>>);
std::cout << "--------------- lr + ir\n";
[[maybe_unused]]auto tlrir{ttp<long>{} + ttp<int>{}};
static_assert(std::is_same_v<decltype(tlrir), ttp<long>>);
std::cout << "--------------- ir + lr\n";
[[maybe_unused]]auto tirlr{ttp<int>{} + ttp<long>{}};
static_assert(std::is_same_v<decltype(tirlr), ttp<long>>);
std::cout << "--------------- lr + lr\n";
[[maybe_unused]]auto tlrlr{ttp<long>{} + ttp<long>{}};
static_assert(std::is_same_v<decltype(tlrlr), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

// char  + char(3) --> char, val
// short + char(3) --> int,  ref
// int   + char(3) --> int,  val
// long  + char(3) --> long, val

// char  + short(3) --> int,   ref
// short + short(3) --> short, val
// int   + short(3) --> int,   val
// long  + short(3) --> long,  val

// char  + 3 --> int,  ref
// short + 3 --> int,  ref
// int   + 3 --> int,  val
// long  + 3 --> long, val

// char  + 3l --> long, ref
// short + 3l --> long, ref
// int   + 3l --> long, ref
// long  + 3l --> long, val

std::cout << "--------------- c + c3\n";
[[maybe_unused]]auto cc3{c + (char)3};
static_assert(std::is_same_v<decltype(cc3), ttp<char>>);
std::cout << "--------------- s + c3\n";
[[maybe_unused]]auto sc3{s + (char)3};
static_assert(std::is_same_v<decltype(sc3), ttp<int>>);
std::cout << "--------------- i + c3\n";
[[maybe_unused]]auto ic3{i + (char)3};
static_assert(std::is_same_v<decltype(ic3), ttp<int>>);
std::cout << "--------------- l + c3\n";
[[maybe_unused]]auto lc3{l + (char)3};
static_assert(std::is_same_v<decltype(lc3), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- c + s3\n";
[[maybe_unused]]auto cs3{c + (short)3};
static_assert(std::is_same_v<decltype(cs3), ttp<int>>);
std::cout << "--------------- s + s3\n";
[[maybe_unused]]auto ss3{s + (short)3};
static_assert(std::is_same_v<decltype(ss3), ttp<short>>);
std::cout << "--------------- i + s3\n";
[[maybe_unused]]auto is3{i + (short)3};
static_assert(std::is_same_v<decltype(is3), ttp<int>>);
std::cout << "--------------- l + s3\n";
[[maybe_unused]]auto ls3{l + (short)3};
static_assert(std::is_same_v<decltype(ls3), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- c + i3\n";
[[maybe_unused]]auto ci3{c + 3};
static_assert(std::is_same_v<decltype(ci3), ttp<int>>);
std::cout << "--------------- s + i3\n";
[[maybe_unused]]auto si3{s + 3};
static_assert(std::is_same_v<decltype(si3), ttp<int>>);
std::cout << "--------------- i + i3\n";
[[maybe_unused]]auto ii3{i + 3};
static_assert(std::is_same_v<decltype(ii3), ttp<int>>);
std::cout << "--------------- l + i3\n";
[[maybe_unused]]auto li3{l + 3};
static_assert(std::is_same_v<decltype(li3), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- c + l3\n";
[[maybe_unused]]auto cl3{c + 3l};
static_assert(std::is_same_v<decltype(cl3), ttp<long>>);
std::cout << "--------------- s + l3\n";
[[maybe_unused]]auto sl3{s + 3l};
static_assert(std::is_same_v<decltype(sl3), ttp<long>>);
std::cout << "--------------- i + l3\n";
[[maybe_unused]]auto il3{i + 3l};
static_assert(std::is_same_v<decltype(il3), ttp<long>>);
std::cout << "--------------- l + l3\n";
[[maybe_unused]]auto ll3{l + 3l};
static_assert(std::is_same_v<decltype(ll3), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

std::cout << "--------------- cr + c3\n";
[[maybe_unused]]auto crc3{ttp<char>{} + (char)3};
static_assert(std::is_same_v<decltype(crc3), ttp<char>>);
std::cout << "--------------- sr + c3\n";
[[maybe_unused]]auto src3{ttp<short>{} + (char)3};
static_assert(std::is_same_v<decltype(src3), ttp<int>>);
std::cout << "--------------- ir + c3\n";
[[maybe_unused]]auto irc3{ttp<int>{} + (char)3};
static_assert(std::is_same_v<decltype(irc3), ttp<int>>);
std::cout << "--------------- lr + c3\n";
[[maybe_unused]]auto lrc3{ttp<long>{} + (char)3};
static_assert(std::is_same_v<decltype(lrc3), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- cr + s3\n";
[[maybe_unused]]auto crs3{ttp<char>{} + (short)3};
static_assert(std::is_same_v<decltype(crs3), ttp<int>>);
std::cout << "--------------- sr + s3\n";
[[maybe_unused]]auto srs3{ttp<short>{} + (short)3};
static_assert(std::is_same_v<decltype(srs3), ttp<short>>);
std::cout << "--------------- ir + s3\n";
[[maybe_unused]]auto irs3{ttp<int>{} + (short)3};
static_assert(std::is_same_v<decltype(irs3), ttp<int>>);
std::cout << "--------------- lr + s3\n";
[[maybe_unused]]auto lrs3{ttp<long>{} + (short)3};
static_assert(std::is_same_v<decltype(lrs3), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- cr + i3\n";
[[maybe_unused]]auto cri3{ttp<char>{} + 3};
static_assert(std::is_same_v<decltype(cri3), ttp<int>>);
std::cout << "--------------- sr + i3\n";
[[maybe_unused]]auto sri3{ttp<short>{} + 3};
static_assert(std::is_same_v<decltype(sri3), ttp<int>>);
std::cout << "--------------- ir + i3\n";
[[maybe_unused]]auto iri3{ttp<int>{} + 3};
static_assert(std::is_same_v<decltype(iri3), ttp<int>>);
std::cout << "--------------- lr + i3\n";
[[maybe_unused]]auto lri3{ttp<long>{} + 3};
static_assert(std::is_same_v<decltype(lri3), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- cr + l3\n";
[[maybe_unused]]auto crl3{ttp<char>{} + 3l};
static_assert(std::is_same_v<decltype(crl3), ttp<long>>);
std::cout << "--------------- sr + l3\n";
[[maybe_unused]]auto srl3{ttp<short>{} + 3l};
static_assert(std::is_same_v<decltype(srl3), ttp<long>>);
std::cout << "--------------- ir + l3\n";
[[maybe_unused]]auto irl3{ttp<int>{} + 3l};
static_assert(std::is_same_v<decltype(irl3), ttp<long>>);
std::cout << "--------------- lr + l3\n";
[[maybe_unused]]auto lrl3{ttp<long>{} + 3l};
static_assert(std::is_same_v<decltype(lrl3), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

std::cout << "--------------- c3 + c\n";
[[maybe_unused]]auto c3c{(char)3 + c};
static_assert(std::is_same_v<decltype(c3c), ttp<char>>);
std::cout << "--------------- c3 + s\n";
[[maybe_unused]]auto c3s{(char)3 + s};
static_assert(std::is_same_v<decltype(c3s), ttp<int>>);
std::cout << "--------------- c3 + i\n";
[[maybe_unused]]auto c3i{(char)3 + i};
static_assert(std::is_same_v<decltype(c3i), ttp<int>>);
std::cout << "--------------- c3 + l\n";
[[maybe_unused]]auto c3l{(char)3 + l};
static_assert(std::is_same_v<decltype(c3l), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- s3 + c\n";
[[maybe_unused]]auto s3c{(short)3 + c};
static_assert(std::is_same_v<decltype(s3c), ttp<int>>);
std::cout << "--------------- s3 + s\n";
[[maybe_unused]]auto s3s{(short)3 + s};
static_assert(std::is_same_v<decltype(s3s), ttp<short>>);
std::cout << "--------------- s3 + i\n";
[[maybe_unused]]auto s3i{(short)3 + i};
static_assert(std::is_same_v<decltype(s3i), ttp<int>>);
std::cout << "--------------- s3 + l\n";
[[maybe_unused]]auto s3l{(short)3 + l};
static_assert(std::is_same_v<decltype(s3l), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- i3 + c\n";
[[maybe_unused]]auto i3c{3 + c};
static_assert(std::is_same_v<decltype(i3c), ttp<int>>);
std::cout << "--------------- i3 + s\n";
[[maybe_unused]]auto i3s{3 + s};
static_assert(std::is_same_v<decltype(i3s), ttp<int>>);
std::cout << "--------------- i3 + i\n";
[[maybe_unused]]auto i3i{3 + i};
static_assert(std::is_same_v<decltype(i3i), ttp<int>>);
std::cout << "--------------- i3 + l\n";
[[maybe_unused]]auto i3l{3 + l};
static_assert(std::is_same_v<decltype(i3l), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- l3 + c\n";
[[maybe_unused]]auto l3c{3l + c};
static_assert(std::is_same_v<decltype(l3c), ttp<long>>);
std::cout << "--------------- l3 + s\n";
[[maybe_unused]]auto l3s{3l + s};
static_assert(std::is_same_v<decltype(l3s), ttp<long>>);
std::cout << "--------------- l3 + i\n";
[[maybe_unused]]auto l3i{3l + i};
static_assert(std::is_same_v<decltype(l3i), ttp<long>>);
std::cout << "--------------- l3 + l\n";
[[maybe_unused]]auto l3l{3l + l};
static_assert(std::is_same_v<decltype(l3l), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";

std::cout << "--------------- c3 + cr\n";
[[maybe_unused]]auto c3cr{(char)3 + ttp<char>{}};
static_assert(std::is_same_v<decltype(c3cr), ttp<char>>);
std::cout << "--------------- c3 + sr\n";
[[maybe_unused]]auto c3sr{(char)3 + ttp<short>{}};
static_assert(std::is_same_v<decltype(c3sr), ttp<int>>);
std::cout << "--------------- c3 + ir\n";
[[maybe_unused]]auto c3ir{(char)3 + ttp<int>{}};
static_assert(std::is_same_v<decltype(c3ir), ttp<int>>);
std::cout << "--------------- c3 + lr\n";
[[maybe_unused]]auto c3lr{(char)3 + ttp<long>{}};
static_assert(std::is_same_v<decltype(c3lr), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- s3 + cr\n";
[[maybe_unused]]auto s3cr{(short)3 + ttp<char>{}};
static_assert(std::is_same_v<decltype(s3cr), ttp<int>>);
std::cout << "--------------- s3 + sr\n";
[[maybe_unused]]auto s3sr{(short)3 + ttp<short>{}};
static_assert(std::is_same_v<decltype(s3sr), ttp<short>>);
std::cout << "--------------- c3 + ir\n";
[[maybe_unused]]auto s3ir{(short)3 + ttp<int>{}};
static_assert(std::is_same_v<decltype(s3ir), ttp<int>>);
std::cout << "--------------- c3 + lr\n";
[[maybe_unused]]auto s3lr{(short)3 + ttp<long>{}};
static_assert(std::is_same_v<decltype(s3lr), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- i3 + cr\n";
[[maybe_unused]]auto i3cr{3 + ttp<char>{}};
static_assert(std::is_same_v<decltype(i3cr), ttp<int>>);
std::cout << "--------------- i3 + sr\n";
[[maybe_unused]]auto i3sr{3 + ttp<short>{}};
static_assert(std::is_same_v<decltype(i3sr), ttp<int>>);
std::cout << "--------------- i3 + ir\n";
[[maybe_unused]]auto i3ir{3 + ttp<int>{}};
static_assert(std::is_same_v<decltype(i3ir), ttp<int>>);
std::cout << "--------------- i3 + lr\n";
[[maybe_unused]]auto i3lr{3 + ttp<long>{}};
static_assert(std::is_same_v<decltype(i3lr), ttp<long>>);

std::cout << "---------------\n";
std::cout << "--------------- l3 + cr\n";
[[maybe_unused]]auto l3cr{3l + ttp<char>{}};
static_assert(std::is_same_v<decltype(l3cr), ttp<long>>);
std::cout << "--------------- l3 + sr\n";
[[maybe_unused]]auto l3sr{3l + ttp<short>{}};
static_assert(std::is_same_v<decltype(l3sr), ttp<long>>);
std::cout << "--------------- l3 + ir\n";
[[maybe_unused]]auto l3ir{3l + ttp<int>{}};
static_assert(std::is_same_v<decltype(l3ir), ttp<long>>);
std::cout << "--------------- l3 + lr\n";
[[maybe_unused]]auto l3lr{3l + ttp<long>{}};
static_assert(std::is_same_v<decltype(l3lr), ttp<long>>);
std::cout << "--------------- l3 + lr + lr\n";
[[maybe_unused]]auto l3lrlr{3l + ttp<long>{} + ttp<long>{}};
static_assert(std::is_same_v<decltype(l3lrlr), ttp<long>>);
std::cout << "---------------\n";
std::cout << "---------------\n";
// std::cout << "---------------\n";
// [[maybe_unused]]auto cnc{c + (char)3};
// // static_assert(std::is_same_v<decltype(cnc), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto ncc{(char)3 + c};
// // static_assert(std::is_same_v<decltype(ncc), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto cni{c + 3};
// static_assert(std::is_same_v<decltype(cni), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nic{3 + c};
// static_assert(std::is_same_v<decltype(nic), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto cnl{c + 3l};
// static_assert(std::is_same_v<decltype(cnl), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nlc{3l + c};
// static_assert(std::is_same_v<decltype(nlc), ttp<long>>);
// std::cout << "---------------\n";
// std::cout << "---------------\n";

// [[maybe_unused]]auto inc{i + (char)3};
// static_assert(std::is_same_v<decltype(inc), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nci{(char)3 + i};
// static_assert(std::is_same_v<decltype(nci), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto ini{i + 3};
// static_assert(std::is_same_v<decltype(ini), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nii{3 + i};
// static_assert(std::is_same_v<decltype(nii), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto inl{i + 3l};
// static_assert(std::is_same_v<decltype(inl), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nli{3l + i};
// static_assert(std::is_same_v<decltype(nli), ttp<long>>);
// std::cout << "---------------\n";
// std::cout << "---------------\n";

// [[maybe_unused]]auto lnc{l + (char)3};
// static_assert(std::is_same_v<decltype(lnc), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto ncl{(char)3 + l};
// static_assert(std::is_same_v<decltype(ncl), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto lni{l + 3};
// static_assert(std::is_same_v<decltype(lni), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nil{3 + l};
// static_assert(std::is_same_v<decltype(nil), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto lnl{l + 3l};
// static_assert(std::is_same_v<decltype(lnl), ttp<long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nll{3l + l};
// static_assert(std::is_same_v<decltype(nll), ttp<long>>);
// std::cout << "---------------\n";
// std::cout << "---------------\n";

// [[maybe_unused]]auto lnull{l + 3ull};
// static_assert(std::is_same_v<decltype(lnull), ttp<unsigned long long>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto nulll{3ull + l};
// static_assert(std::is_same_v<decltype(nulll), ttp<unsigned long long>>);

std::cout << "--------------- -c\n";
[[maybe_unused]]auto mc{-c};
static_assert(std::is_same_v<decltype(mc), ttp<char>>);
// static_assert(mc.x == -c.x and mc.y == -c.y);
std::cout << "--------------- -s\n";
[[maybe_unused]]auto ms{-s};
static_assert(std::is_same_v<decltype(ms), ttp<short>>);
// static_assert(ms.x == -s.x and ms.y == -s.y);
std::cout << "--------------- -i\n";
[[maybe_unused]]auto mi{-i};
static_assert(std::is_same_v<decltype(mi), ttp<int>>);
// static_assert(mi.x == -i.x and mi.y == -i.y);
std::cout << "--------------- -l\n";
[[maybe_unused]]auto ml{-l};
static_assert(std::is_same_v<decltype(ml), ttp<long>>);
// static_assert(ml.x == -l.x and ml.y == -l.y);

std::cout << "---------------\n";
std::cout << "--------------- -cr\n";
[[maybe_unused]]auto mcr{-ttp<char>{1, 2}};
static_assert(std::is_same_v<decltype(mcr), ttp<char>>);
// static_assert(mcr.x == -1 and mcr.y == -2);
std::cout << "--------------- -sr\n";
[[maybe_unused]]auto msr{-ttp<short>{3, 4}};
static_assert(std::is_same_v<decltype(msr), ttp<short>>);
// static_assert(msr.x == -3 and msr.y == -4);
std::cout << "--------------- -ir\n";
[[maybe_unused]]auto mir{-ttp<int>{5, 6}};
static_assert(std::is_same_v<decltype(mir), ttp<int>>);
// static_assert(mir.x == -5 and mir.y == -6);
std::cout << "--------------- -lr\n";
[[maybe_unused]]auto mlr{-(-(-ttp<long>{7, 8}))};
static_assert(std::is_same_v<decltype(mlr), ttp<long>>);
// static_assert(mlr.x == -7 and mlr.y == -8);

std::cout << "---------------\n";
std::cout << "--------------- +c\n";
[[maybe_unused]]auto pc{+c};
static_assert(std::is_same_v<decltype(pc), ttp<int>>);
// static_assert(pc.x == c.x and pc.y == c.y);
std::cout << "--------------- +s\n";
[[maybe_unused]]auto ps{+s};
static_assert(std::is_same_v<decltype(ps), ttp<int>>);
// static_assert(ps.x == s.x and ps.y == s.y);
std::cout << "--------------- +i\n";
[[maybe_unused]]auto pi{+i};
static_assert(std::is_same_v<decltype(pi), ttp<int>>);
// static_assert(pi.x == i.x and pi.y == i.y);
std::cout << "--------------- +l\n";
[[maybe_unused]]auto pl{+l};
static_assert(std::is_same_v<decltype(pl), ttp<long>>);
// static_assert(pl.x == l.x and pl.y == l.y);

std::cout << "---------------\n";
std::cout << "--------------- +cr\n";
[[maybe_unused]]auto pcr{+ttp<char>{1, 2}};
static_assert(std::is_same_v<decltype(pcr), ttp<int>>);
// static_assert(pcr.x == 1 and pcr.y == 2);
std::cout << "--------------- +sr\n";
[[maybe_unused]]auto psr{+ttp<short>{3, 4}};
static_assert(std::is_same_v<decltype(psr), ttp<int>>);
// static_assert(psr.x == 3 and psr.y == 4);
std::cout << "--------------- +ir\n";
[[maybe_unused]]auto pir{+ttp<int>{5, 6}};
static_assert(std::is_same_v<decltype(pir), ttp<int>>);
// static_assert(pir.x == 5 and pir.y == 6);
std::cout << "--------------- +lr\n";
[[maybe_unused]]auto plr{+(+(+ttp<long>{7, 8}))};
static_assert(std::is_same_v<decltype(plr), ttp<long>>);
// static_assert(plr.x == 7 and plr.y == 8);

std::cout << "--------------- post/pre-fix inc/dec\n";
[[maybe_unused]]auto pid = ttp<int>{3, 3}; 
[[maybe_unused]]auto mid = ttp<int>{5, 5};
[[maybe_unused]]auto rid = ttp<int>{4, 4};
std::cout << "--------------- ++pid\n";
if (++pid != rid) throw std::runtime_error{"++pid != rid"};
std::cout << "--------------- --mid\n";
if (--mid != rid) throw std::runtime_error{"--mid != rid"};
std::cout << "--------------- pid++\n";
if (pid++ != rid) throw std::runtime_error{"pid++ != rid"};
std::cout << "--------------- mid--\n";
if (mid-- != rid) throw std::runtime_error{"mid-- != rid"};
std::cout << "--------------- --pid\n";
if (--pid != rid) throw std::runtime_error{"--pid != rid"};
std::cout << "--------------- ++mid\n";
if (++mid != rid) throw std::runtime_error{"++mid != rid"};

// [[maybe_unused]]auto urc{-ttp<char>{1, 2}};
// static_assert(std::is_same_v<decltype(urc), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto uri{-ttp<int>{1, 2}};
// static_assert(std::is_same_v<decltype(uri), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto url{-ttp<long>{1, 2}};
// static_assert(std::is_same_v<decltype(url), ttp<long>>);
// std::cout << "---------------\n";
// std::cout << "---------------\n";

// [[maybe_unused]]auto ulc{-c};
// static_assert(std::is_same_v<decltype(ulc), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto uli{-i};
// static_assert(std::is_same_v<decltype(uli), ttp<int>>);
// std::cout << "---------------\n";
// [[maybe_unused]]auto ull{-l};
// static_assert(std::is_same_v<decltype(ull), ttp<long>>);
// std::cout << "---------------\n";
// std::cout << "---------------\n";

// ttp<char> ot{2, 3};
// ttp<long> ot2{4, 5};
// ot - ot2;

// mytff(ot, tag<long>{});

// ttp<short> ot2{4, 6};
// ttp<short> ot22{5, 7};
// ttp<short> ot222 = ot2 + ot22;
// ttp<long> lttp{88, 99};
// ttp<int> ittp = myttp + lttp;
// ttp<int> ittp2 = lttp + myttp;

// ttp<char> ot3(ot + ot2);
// ttp<char> ot4 = ot + ot2;
// // int x = 7 * 7;
// ttp<char> nt(3 + ot);
// ttp<char> nt2(ot + (char)3);
// ttp<int> nt3{ot + 3};
// ttp<int> nt5 = myttp + 3l;
// ttp<int> nt4{myttp + 9};

// ttp<char> nt2f((char)3 + ot);
// ttp<int> nt3f{3 + ot};
// ttp<int> nt5f = 3l + myttp;
// ttp<int> nt4f{9 + myttp};

// ttp<long> myttp7{myttp.operator ttp<long>()};
// ttp<long> myttp6{myttp};

// ttp<int> tor{-ttp<int>{77, 88}};
// std::cout << tor.x << tor.y;

}
