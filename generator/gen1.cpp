#include <bits/stdc++.h>
using namespace std;
# define int long long

static constexpr int START_YEAR = 2010;
static constexpr int TOTAL_DAYS = 5555;           // number of distinct days to sample from
static constexpr unsigned int DATAROWS = 100000; // no of rows in dataset


static std::mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

inline int rnd_int(int a, int b) {
    return std::uniform_int_distribution<int>(a, b)(rng);
}

inline double rnd_real(double a, double b) {
    return std::uniform_real_distribution<double>(a, b)(rng);
}

// date helpers (day is 0-indexed)
inline int get_year(int day) {
    return START_YEAR + day / 365;
}
inline int get_month(int day) { // 1..12
    int day_of_year = day % 365;
    return day_of_year / 30 + 1;
}
inline int get_day_of_month(int day) { // 1..30
    int day_of_year = day % 365;
    return day_of_year % 30 + 1;
}

// Fast output buffer (1 MiB)
static const size_t OUTBUF_SZ = 1 << 20;
static char outbuf[OUTBUF_SZ];
static size_t outpos = 0;

inline void flush_out() {
    if (outpos) {
        fwrite(outbuf, 1, outpos, stdout);
        outpos = 0;
    }
}
inline void write_char(char c) {
    if (outpos + 1 >= OUTBUF_SZ) flush_out();
    outbuf[outpos++] = c;
}
inline void write_str(const string &s) {
    size_t i = 0, L = s.size();
    while (i < L) {
        size_t can = min(OUTBUF_SZ - outpos, L - i);
        memcpy(outbuf + outpos, s.data() + i, can);
        outpos += can;
        i += can;
        if (outpos == OUTBUF_SZ) flush_out();
    }
}
inline void write_cstr(const char *s) {
    write_str(string(s));
}
template<typename T>
inline void write_int(T v) {
    if (v == 0) {
        write_char('0');
        return;
    }
    if (v < 0) {
        write_char('-');
        v = -v;
    }
    char tmp[32];
    int tp = 0;
    while (v) {
        tmp[tp++] = char('0' + (v % 10));
        v /= 10;
    }
    for (int i = tp - 1; i >= 0; --i) write_char(tmp[i]);
}
inline void write_double_fixed(double x, int prec = 2) {
    // write with fixed precision (simple implementation)
    int whole = (int)floor(x);
    double frac = x - whole;
    write_int(whole);
    write_char('.');
    for (int i = 0; i < prec; ++i) {
        frac *= 10;
        int d = (int)floor(frac) % 10;
        write_char('0' + d);
    }
}

// Crop generator avoiding heavy storage
struct CropRow {
    string crop_name;
    int day;
    int year, month, date;
    int zone;
    int ground_water;    // mm
    int rainfall;        // mm
    int daytemp;         // Kelvin scaled-ish
    int nighttemp;       // Kelvin
    int humidity;        // %
    int irrigation;      // L
    int soilquality;     // 0-100
    string weather;
    int area;            // acres
    int production; // kg
    int production_per_hect; // kg/ha
    int yield_per_acre;  // kg/acre
    int fertilizer;      // kg
    int pesticide;       // kg
    int weedicide;       // kg

    void randomize(const string &crop, int days_total) {
        crop_name = crop;
        day = rnd_int(0, days_total - 1);
        year = get_year(day);
        month = get_month(day);
        date = get_day_of_month(day);

        zone = rnd_int(1, 30);
        ground_water = rnd_int(1, 100);
        rainfall = rnd_int(30, 500);
        daytemp = rnd_int(280, 320);
        nighttemp = rnd_int(260, 310);
        humidity = rnd_int(10, 100);
        irrigation = rnd_int(100, 2000); // L/acre
        soilquality = rnd_int(2, 10);

        static const vector<string> weathers = {
            "sunny","rainy","cloudy","stormy","windy","cold","hot"
        };
        weather = weathers[rnd_int(0, (int)weathers.size()-1)];

        area = rnd_int(1, 50); // ha
        production_per_hect = rnd_int(1, 40); // kg/ha
        // 1 hectare = 2.47105 acres
        yield_per_acre = max(1ll, (int)(production_per_hect / 2.47105 + rnd_int(-5, 5)));
        production = 1LL * area * yield_per_acre; // kg
        fertilizer = rnd_int(0, 4); // kg/ha
        pesticide = rnd_int(0, 1); // kg/ha
        weedicide = rnd_int(0, 1); // kg/ha
    }

    // write CSV row to output buffer
    void write_csv_row() const {
        // zone:
        // fields, crop, day, year,month,date,zone,ground_water,
        // rainfall,daytemp,nighttemp,humidity,irrigation,soilquality,weather,area,
        // production,production_per_hect,yield_per_acre,fertilizer,pesticide,weedicide
        // we are not using fields, it's upto future decisions upon complexity
        write_str(crop_name); write_char(',');
        write_int(day); write_char(',');
        write_int(year); write_char(',');
        write_int(month); write_char(',');
        write_int(date); write_char(',');
        write_int(zone); write_char(',');
        write_int(ground_water); write_char(',');
        write_int(rainfall); write_char(',');
        write_int(daytemp); write_char(',');
        write_int(nighttemp); write_char(',');
        write_int(humidity); write_char(',');
        write_int(irrigation); write_char(',');
        write_int(soilquality); write_char(',');
        write_str(weather); write_char(',');
        write_int(area); write_char(',');
        write_int(production); write_char(',');
        write_int(production_per_hect); write_char(',');
        write_int(yield_per_acre); write_char(',');
        write_int(fertilizer); write_char(',');
        write_int(pesticide); write_char(',');
        write_int(weedicide);
        write_char('\n');
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> crop_names = {
        "Rice","Wheat","Potato","Onion","Tomato","Sugarcane","Bajra","Mango","Banana","Other"
    };

    // printing CSV header
    const string header = "crop,day,year,month,date,zone,ground_water_mm,rainfall_mm,daytemp_K,nighttemp_K,humidity_percent,irrigation_L,soilquality,weather,area_acres,production_kg,production_per_hect_kg,yield_per_acre_kg,fertilizer_kg,pesticide_kg,weedicide_kg\n";
    write_str(header);

    CropRow row;
    for (unsigned int i = 0; i < DATAROWS; ++i) {
        const string &cname = crop_names[rnd_int(0, (int)crop_names.size() - 1)];
        row.randomize(cname, TOTAL_DAYS);
        row.write_csv_row();
	// Flushing periodically brdr..avoids internal memory heap full limit
        if ((i & 0x0FFF) == 0) flush_out(); // flush every ~16384 rows to avoid huge internal buffer waits
    }
    flush_out();
    return 0;
}
