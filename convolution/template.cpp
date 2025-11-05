// FFT template:

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

// _________________________

using cd = complex<double>
const double PI = acos(-1);

// a is coefficient vector
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();
    if(n == 1) return a;

    vector<cd> a0(n/2), a1(n/2);
    for(int i = 0; i < n / 2; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for(int i = 0; i < n / 2; i++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if(invert)
        {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

// ___________________________________________________

using cd = complex<double>;
const cd PI = acos(-1);

vector<cd> FFT(vector<cd> &a)
{
    int n = a.size();
    if(n == 1) return a;

    cd i(0.0, 1.0);
    cd w = 2 * PI * i / n;
    
    vector<cd> a0, a1;
    for(int i = 0; i < n/2; i++)
    {
        a0.emplace_back(a[2 * i]);
        a1.emplace_back(a[2 * i + 1]);
    }
    vector<cd> y0 = FFT(a0);
    vector<cd> y1 = FFT(a1);
    vector<cd> y(n);
    for(int i = 0; i < n/2; i++)
    {
        y[i] = y0[i] + pow(w, i) * y1[j];
        y[i + n/2] = y0[i] - pow(w, i) * y1[j];
    }
    return y;
}